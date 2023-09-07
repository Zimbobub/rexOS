# add cross compiler to path just for this script
export PATH=$PATH:/usr/local/i386elfgcc/bin

# format build dir
rm -r ./build/*
mkdir ./build/objects

# compile asm
nasm "src/boot/boot.asm" -f bin -o "build/objects/boot.bin"
nasm "src/boot/kernel_entry.asm" -f elf -o "build/objects/kernel_entry.o"
nasm "src/zeroes.asm" -f bin -o "build/objects/zeroes.bin"

# compile kernel
for filename in src/kernel/*.c; do
    gcc -ffreestanding -m32 -g -c $filename -o "build/objects/$(basename ${filename%.c}).o"
done
# c files nested in dirs
for filename in src/kernel/*/*.c; do
    gcc -ffreestanding -m32 -g -c $filename -o "build/objects/$(basename $(dirname $filename))_$(basename ${filename%.c}).o"
done


# link
i386-elf-ld -o "build/objects/full_kernel.bin" -Ttext 0x1000 build/objects/*.o --oformat binary --ignore-unresolved-symbol _GLOBAL_OFFSET_TABLE_

# concatenate into a single binary
cat "build/objects/boot.bin" "build/objects/full_kernel.bin" "build/objects/zeroes.bin"  > "build/OS.bin"

# run
qemu-system-x86_64 -drive format=raw,file="build/OS.bin",index=0,if=floppy, -m 128M