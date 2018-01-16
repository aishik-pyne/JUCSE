section .data                           ;Data segment
   userMsg db 'Please enter a char: ' ;Ask the user to enter a number
   lenUserMsg equ $-userMsg             ;The length of the message

section .bss           ;Uninitialized data
   c resb 1

section .text          ;Code Segment
   global _start

_start:                ;User prompt
    mov eax, 4
    mov ebx, 1
    mov ecx, userMsg
    mov edx, lenUserMsg
    int 80h

    ;Read and store the user input
    mov eax, 3
    mov ebx, 2
    mov ecx, c
    mov edx, 1          ;5 bytes (numeric, 1 for sign) of that information
    int 80h

    ;Convert case
    mov eax, 32
    sub [c], eax
    ;Output the result
    mov eax, 4
    mov ebx, 1
    mov ecx, c
    mov edx, 1
    int 80h

   ; Exit code
    mov eax, 1
    mov ebx, 0
    int 80h
