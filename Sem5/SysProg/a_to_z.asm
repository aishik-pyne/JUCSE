SYS_EXIT  equ 1
SYS_READ  equ 3
SYS_WRITE equ 4
STDIN     equ 0
STDOUT    equ 1

section .data                           ;Data segment
   c db 'a'
   count db 26

section .text          ;Code Segment
   global _start

_start:                ;User prompt

_loop:

    mov eax, SYS_WRITE
    mov ebx, STDOUT
    mov ecx, c
    mov edx, 1
    int 80h
    mov edx, 1
    inc byte [c]
    dec byte [count]
    jnz _loop



    ; Exit codes
    mov eax, SYS_EXIT
    mov ebx, 0
    int 80h
