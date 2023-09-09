section .text
global _start

_start:
    [bits 32]
    [extern kernelMain]
    call kernelMain
    jmp $