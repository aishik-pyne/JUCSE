.MODEL  SMALL
.STACK 300H
    .DATA
           VAl1     DB      ?
           NL1      DB      0AH,0DH,'Enter the number :','$'
           NL2      DB      0AH,0DH,'Not a prime number','$'
           NL3      DB      0AH,0DH,'A prime number','$'

           .CODE
    MAIN    PROC

            MOV AX,@DATA
            MOV DS,AX

            LEA DX,NL1
            MOV AH,09H
            INT 21H
    
            MOV AH,01H
            INT 21H
            SUB AL,30H
	    cmp al,01H
	    jz LBL2
	    
            MOV VAL1,AL
            
            MOV AH,00

            MOV CL,2
            DIV CL
	    cmp al,01
	    jz LBL3
            MOV CL,AL

    LBL1:
            MOV AH,00
            MOV AL,VAL1
            DIV CL
            CMP AH,00
            JZ LBL2
            DEC CL
            CMP CL,1
            JNE LBL1
            JMP LBL3
    
    LBL2:
    
            MOV AH,09H
            LEA DX,NL2
            INT 21H
            JMP EXIT    
    
    LBL3:
            MOV AH,09H
            LEA DX,NL3
            INT 21H
    
    EXIT:
            MOV AH,4CH
            INT 21H
    
    MAIN    ENDP
            END     MAIN