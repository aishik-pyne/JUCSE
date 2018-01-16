%include "asm_io.inc"
segment .data
prompt1 db    "Enter a number: ", 0       
prompt2 db    "Enter another number: ", 0

segment .bss
input1  resd 1
input2  resd 1

segment .text
    global  asm_main
asm_main:
    enter   0,0               ; setup routine
    pusha

    mov     eax, prompt1      
    call    print_string
    call    read_int   
    push eax       

    mov     eax, prompt2       
    call    print_string
    call    read_int    
    push eax      


    call euclid

    call print_int



    popa
    mov     eax, 0            ; return back to C
    leave                     
    ret


    ; Function euclid

    euclid:
         push ebp
         mov ebp, esp

         mov ebx, [ebp+8]
         mov ecx, [ebp+12]



         _while: 
            div ecx,ebx
            mov ebx,ecx
            mov ecx,edx
            cmp ecx,0
            jz _end
            jmp _while
         _end: 
            mov eax,ebx

        pop ebp
        ret
