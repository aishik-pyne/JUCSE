data segment
        num dw 12h
	msg db "The decimal number - $"
        res db 10 dup('$')
        data ends
        code segment
        assume ds:data,cs:code
start:
        mov ax,data
        mov ds,ax
	
	lea dx,msg
	mov ah,09h
	int 21h

        mov ax,num

        lea si,res
        call hex2dec

        lea dx,res	;display the string of numbers from hex
        mov ah,9
        int 21h

        mov ah,4ch
        int 21h

hex2dec proc near	;conversion
        mov cx,0
        mov bx,10

loop1: mov dx,0
        div bx
        add dl,30h	;for character
        push dx
        inc cx
        cmp ax,9
        jg loop1

        add al,30h
        mov [si],al

loop2: pop ax
        inc si
        mov [si],al
        loop loop2
        ret
hex2dec endp

code ends
end start
