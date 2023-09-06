# add cross compiler to path just for this script
export PATH=$PATH:/usr/local/i386elfgcc/bin

# compile
nasm "src/bootloader/boot.asm" -f bin -o "build/fragments/boot.bin"
nasm "src/kernel/init.asm" -f elf -o "build/fragments/kernel_entry.o"
gcc -ffreestanding -m32 -g -c "src/kernel/kernel.c" -o "build/fragments/kernel.o"
nasm "src/zeroes.asm" -f bin -o "build/fragments/zeroes.bin"

# link
i386-elf-ld -o "build/fragments/full_kernel.bin" -Ttext 0x1000 "build/fragments/kernel_entry.o" "build/fragments/kernel.o" --oformat binary

# concatenate into a single binary
cat "build/fragments/boot.bin" "build/fragments/full_kernel.bin" "build/fragments/zeroes.bin"  > "build/OS.bin"

# run
qemu-system-x86_64 -drive format=raw,file="build/OS.bin",index=0,if=floppy, -m 128M