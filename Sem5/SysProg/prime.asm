section .data
msg:   db   'Enter an integer: ', 0
chr:   db   '%d', 0
ispmsg:   db   10, 'The integer %d is prime!', 10, 0
nopmsg:   db   10, 'The integer %d is not prime.', 10, 0

section .text
   global main
   extern printf, scanf

main:

push ebp
   mov ebp, esp
   sub esp, $0c

mov dword [ebp-8], 1
   push msg
   call printf
   add esp, 4

lea eax, [ebp-4]
   push eax
   push chr
   call scanf
   add esp, 8

cmp dword [ebp-4], 2
   jge next
   mov dword [ebp-8], 0
   jmp continue

next:
   jne nextt
   jmp continue

nextt:
   mov eax, [ebp-4]
   cdq
   mov ebx, 2
   idiv ebx
   cmp edx, 0
   je nexttt

finit
   fild dword [ebp-4]
   fsqrt
   fistp dword [ebp-$0c]

mov ecx, 3
   jmp ccheck
floop:
   mov eax, [ebp-4]
   cdq
   idiv ecx
   cmp edx, 0
   jne check
   mov dword [ebp-8], 0
   jmp continue
check:
   add ecx, 2
ccheck:
   cmp ecx, [ebp-$0c]
   jle floop
   jmp continue

nexttt:
   mov dword [ebp-8], 0

continue:
   xor eax, eax
   cmp eax, [ebp-8]
   jne isprime
   mov eax, [ebp-4]
   push eax
   push nopmsg
   call printf
   add esp, 8
   jmp endit

isprime:
   mov eax, [ebp-4]
   push eax
   push ispmsg
   call printf
   add esp, 8

endit:
   add esp, $0c
   pop ebp
   xor eax, eax
   ret