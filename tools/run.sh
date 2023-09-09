# add cross compiler to path just for this script
export PATH=$PATH:/usr/local/i386elfgcc/bin


# directories used
SRC_DIR="./src"
BOOT_STAGE1_DIR="$SRC_DIR/boot/stage1"
BOOT_STAGE2_DIR="$SRC_DIR/boot/stage2"
KERNEL_DIR="$SRC_DIR/kernel"

BUILD_DIR="./build"
BIN_DIR="$BUILD_DIR/bin"
OBJ_DIR="$BUILD_DIR/obj"
OUTPUT_FILE="$BUILD_DIR/OS.bin"


# format build dir
rm -r $BUILD_DIR/*
mkdir $BIN_DIR
mkdir $OBJ_DIR


# BOOTLOADER STAGE 1
nasm "$BOOT_STAGE1_DIR/boot.asm" -f bin -o "$BIN_DIR/boot.bin"
nasm "$BOOT_STAGE1_DIR/enter_stage2.asm" -f elf -o "$OBJ_DIR/boot_enter_stage2.o"


# BOOTLOADER STAGE 2
for filename in src/boot/stage2/*.c; do
    gcc -ffreestanding -m32 -g -c $filename -o "$OBJ_DIR/boot_$(basename ${filename%.c}).o"
done


# KERNEL
for filename in src/kernel/*.c; do
    gcc -ffreestanding -m32 -g -c $filename -o "$OBJ_DIR/kernel_$(basename ${filename%.c}).o"
done
# c files nested in dirs
for filename in src/kernel/*/*.c; do
    gcc -ffreestanding -m32 -g -c $filename -o "$OBJ_DIR/kernel_$(basename $(dirname $filename))_$(basename ${filename%.c}).o"
done


# link
i386-elf-ld -o "$BIN_DIR/kernel.bin" -Ttext 0x1000 $OBJ_DIR/*.o --oformat binary --ignore-unresolved-symbol _GLOBAL_OFFSET_TABLE_


# pad with zeroes
nasm "$SRC_DIR/zeroes.asm" -f bin -o "$BIN_DIR/zeroes.bin"


# concatenate into a single binary
cat "$BIN_DIR/boot.bin" "$BIN_DIR/kernel.bin" "$BIN_DIR/zeroes.bin"  > "$OUTPUT_FILE"


# run
qemu-system-x86_64 -drive format=raw,file="$OUTPUT_FILE",index=0,if=floppy, -m 128M -serial stdio