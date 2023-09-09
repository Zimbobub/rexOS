section .text
global _start

_start:
    [bits 32]
    [extern bootloaderStage2]
    call bootloaderStage2
    jmp $