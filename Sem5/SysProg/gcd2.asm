.MODEL SMALL
.STACK 300H
.DATA
no1  dw 0120  
no2  dw 0090  
gcd dw 0h  
.CODE
MAIN PROC
MOV AX,@DATA
MOV DS,AX

  mov      ax,@data          ; initialize DS  
      mov      ds, ax      
      mov      ax, no1           ; get the first number  
      mov      bx, no2           ; get the second number  
again:      cmp      ax, bx     ; check if nos are equal  
          je      endd           ; if equal, save the GCD  
      jb      exchg              ; if no,  
                                 ; is AX                                 ; if yes interchange  
l2:     mov      dx, 0  
      div      bx                ; check if ax is  
                                 ; divisible by bx  
      cmp      dx, 0     ;  
      je      endd  
      mov      ax, dx            ; mov the remainder  
                                 ; as no1 data  
      jmp      again  
exchg :      xchg      ax, bx ;jmp l2  
endd :      mov      gcd, bx  
      mov      ch, 04h           ; Count of digits to be  
                ; displayed  
      mov      cl, 04h           ; Count to roll by 4 bits  
l12:     rol      bx, cl        ; roll bl so that msb  
                ; comes to lsb  
         mov      dl, bl         ; load dl with data  
                ; to be displayed  
         and      dl, 0fH        ; get only lsb  
         cmp      dl, 09         ; check if digit is 0-9  
                ; or letter A-F  
         jbe      l4  
         add      dl, 07         ; if letter add 37H else  
                ; only add 30H  
l4:       add      dl, 30H  
         mov      ah, 02         ; INT 21H  
                ; (Display character)  
         int      21H  
         dec      ch             ; Decrement Count  
         jnz      l12                     
MOV AH,4CH
INT 21H
MAIN ENDP
END MAIN

