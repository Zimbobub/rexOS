[bits 16]
[org 0x7c00]
STAGE2_LOCATION equ 0x1000

; lets us know weve made it to the bootloader
mov ah, 0x0
mov al, 0x3
int 0x10                ; text mode (clears screen)


read_stage2:
    mov [BOOT_DISK], dl


    xor ax, ax
    mov es, ax
    mov ds, ax
    mov bp, 0x8000
    mov sp, bp

    mov bx, STAGE2_LOCATION
    mov dh, 2

    mov ah, 0x02
    mov al, dh
    mov ch, 0x00    
    mov dh, 0x00
    mov cl, 0x02
    mov dl, [BOOT_DISK]
    int 0x13                ; no error management yet


; enter protected mode
%include "src/boot/stage1/enter_protected.asm"


[bits 32]
start_protected_mode:
    ; just set all segments to be the same
    mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov ebp, 0x90000		; 32 bit stack base pointer
	mov esp, ebp

    jmp STAGE2_LOCATION

                                     
; sanity check bytes (will appear as "ww")
dw 0x7777
; fill rest of bootsector in and add signature
times 510-($-$$) db 0              
dw 0xaa55