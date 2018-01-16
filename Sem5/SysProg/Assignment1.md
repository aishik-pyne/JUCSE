# MASM Assignment 1

## Q1: Take a character from the keyboard and print it

Code:
```asm
;ACCEPTS CHARACTYER AND DISPLAYS IT
.MODEL SMALL
.STACK 300H
.DATA
MSG DB "ENTER CHARACTER $"
.CODE
MAIN PROC
MOV AX,@DATA
MOV DS,AX
LEA DX,MSG
MOV AH,09H ;DISPLAY ACCEPT STATEMENT
INT 21H
MOV AH,1H ;ACCEPT
INT 21H
MOV CL, AL
MOV DL,10
MOV AH,02H
INT 21H
MOV DL,13
MOV AH,02H
INT 21H
MOV DL,CL ;DISPLAY
MOV AH,2H
INT 21H
MOV AH,4CHINT 21H
MAIN ENDP
END MAIN
```

Output:
![a1q1][a1q1]

---
## Q2: Convert a letter from upper case to lower case

Code:
```asm
;ACCEPTS CHARACTER AND CHANGES IT'S CASE
.MODEL SMALL
.STACK 300H
.DATA
MSG DB "ENTER CHARACTER $"
.CODE
MAIN PROC
MOV AX,@DATA
MOV DS,AX
LEA DX,MSG
MOV AH,09H ;DISPLAY ACCEPT STATEMENTINT 21H
MOV AH,1H ;ACCEPT
INT 21H
CMP AL,'a'
JL NOT_LOWER
CMP AL,'z'
JG NOT_LOWER
SUB AL,20H
NOT_LOWER:
MOV CL,AL
MOV DL,10
MOV AH,02H
INT 21H
MOV DL,13
MOV AH,02H
INT 21H
MOV DL,CL ;DISPLAY
MOV AH,2H
INT 21H
MOV AH,4CH
INT 21H
MAIN ENDP
END MAIN
```

Output:
![a1q2][a1q2]

---
## Q3: Print all the characters from A-Z

Code:
```asm
;PRINT ALL THE ALPHABETS FROM A TO Z
.MODEL SMALL
.STACK 300H
.DATA
MSG DB "THE CHARACTERS $"
.CODE
MAIN PROC
MOV AX,@DATA
MOV DS,AX
LEA DX,MSG
MOV AH,09H ;DISPLAY ACCEPT STATEMENT
INT 21H
MOV AL,41H ;INITILAISELOOP1:
MOV DL,AL ;DISPLAY
MOV AH,2H
INT 21H
CMP AL,'Z'
JE FINISHED
ADD AL,01H
CMP AL,'Z'
JNE LOOP1
FINISHED:
MOV DL,AL ;DISPLAY
MOV AH,2H
INT 21H
MOV AH,4CH
INT 21H
MAIN ENDP
END MAIN
```

Output:
![a1q3][a1q3]

---
## Q4: Print your name


Code:
```asm
;PRINTS MY NAME
.MODEL SMALL
.STACK 300H
.DATA
MSG DB "AISHIK PYNE$"
.CODE
MAIN PROC
MOV AX,@DATA
MOV DS,AX
LEA DX,MSG
MOV AH,09H
INT 21H
MOV AH,4CH
INT 21HMAIN ENDP
END MAIN
```

Output:
![a1q4][a1q4]

---
## Q5:

Code:
```asm
MODEL SMALL
.STACK 64
.DATA
VAL1 DB 01H
VAL2 DB 01H
LP DB 00H
V1 DB 00H
V2 DB 00H
NL DB 0DH,0AH,'$'.CODE
MAIN PROC
MOV AX,@DATA
MOV DS,AX
MOV AH,01H
INT 21H
MOV CL,AL
MOV DL,10
MOV AH,02H
INT 21H
MOV DL,13
MOV AH,02H
INT 21H
SUB CL,30H
SUB CL,2
MOV AH,02H
MOV DL,VAL1
ADD DL,30H
INT 21H
MOV AH,09H
LEA DX,NL
INT 21H
MOV AH,02H
MOV DL,VAL2ADD DL,30H
INT 21H
MOV AH,09H
LEA DX,NL
INT 21H
DISP:
MOV BL,VAL1
ADD BL,VAL2
MOV AH,00H
MOV AL,BL
MOV LP,CL
MOV CL,10
DIV CL
MOV CL,LP
MOV V1,AL
MOV V2,AH
MOV DL,V1
ADD DL,30H
MOV AH,02H
INT 21H
MOV DL,V2
ADD DL,30H
MOV AH,02H
INT 21HMOV DL,VAL2
MOV VAL1,DL
MOV VAL2,BL
MOV AH,09H
LEA DX,NL
INT 21H
LOOP DISP
MOV AH,4CH
INT 21H
MAIN ENDP
END MAIN
```

Output:
![a1q5][a1q5]

---
## Q6:

Code:
```asm
.MODEL SMALL
.STACK 300H
.DATA
VAl1 DB ?
NL1 DB 0AH,0DH,'Enter the number :','$'
NL2 DB 0AH,0DH,'Not a prime number','$'
NL3 DB 0AH,0DH,'A prime number','$'
.CODE
MAIN PROC
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
DIV CLcmp al,01
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
MAIN ENDP
END
MAIN
```

Output:
![a1q6][a1q6]

---
## Q7:

Code:
```asm
MODEL SMALL
.STACK 300H
.DATA
PROMPT_1 DB 'Enter the value of A = $'
PROMPT_2 DB 0DH,0AH,'Enter the value of B = $'
PROMPT_3 DB 0DH,0AH,'The GCD of A and B is = $'
.CODE
MAIN PROC
MOV AX,@DATA
MOV DS,AX
START:
LEA DX, PROMPT_1
MOV AH, 9
INT 21H
; load and display the string PROMPT_1CALL INDEC
; call the procedure INDEC
PUSH AX
; push AX onto the STACK
LEA DX, PROMPT_2
; load and display the string PROMPT_2
MOV AH, 9
INT 21H
CALL INDEC ; call the procedure INDEC
MOV BX, AX ; set BX=AX
POP AX
; pop a value from STACK into AX
@REPEAT:
; jump label
XOR DX, DX
DIV BX
CMP DX, 0
JE @END_LOOP
; clear DX
; set AX=DX:AX\BX , AX=DX:AX%BX
; compare DX with 0
; jump to label @END_LOOP if CX=0
MOV AX, BX ; set AX=BX
MOV BX, DX ; set BX=DX
JMP @REPEAT ; jump to label @REPEAT
@END_LOOP: ; jump label
LEA DX, PROMPT_3
MOV AH, 9
INT 21H
; load and display the string PROMPT_3MOV AX, BX
; set AX=BX
CALL OUTDEC ; call the procedure OUTDEC
MOV AH, 4CH ; return control to DOS
INT 21H
MAIN ENDP
INDEC PROC
; this procedure will read a number in decimal form
; input : none
; output : store binary number in AX
; uses : MAIN
PUSH BX ; push BX onto the STACK
PUSH CX ; push CX onto the STACK
PUSH DX ; push DX onto the STACK
JMP @READ
@SKIP_BACKSPACE:
MOV AH, 2
MOV DL, 20H
INT 21H
; jump to label @READ
; jump label
; set output function
; set DL=' '
; print a character
@READ: ; jump label
XOR BX, BX ; clear BX
XOR CX, CX ; clear CXXOR DX, DX ; clear DX
MOV AH, 1 ; set input function
INT 21H
CMP AL, "-"
JE @MINUS
; read a character
; compare AL with "-"
; jump to label @MINUS if AL="-"
CMP AL, "+" ; compare AL with "+"
JE @PLUS ; jump to label @PLUS if AL="+"
JMP @SKIP_INPUT
; jump to label @SKIP_INPUT
@MINUS: ; jump label
MOV CH, 1 ; set CH=1
INC CL
JMP @INPUT
@PLUS:
MOV CH, 2
INC CL
; set CL=CL+1
; jump to label @INPUT
; jump label
; set CH=2
; set CL=CL+1
@INPUT: ; jump label
MOV AH, 1 ; set input function
INT 21H
@SKIP_INPUT:
CMP AL, 0DH
JE @END_INPUT
; read a character
; jump label
; compare AL with CR
; jump to label @END_INPUTCMP AL, 8H
; compare AL with 8H
JNE @NOT_BACKSPACE
CMP CH, 0
; jump to label @NOT_BACKSPACE if AL!=8
; compare CH with 0
JNE @CHECK_REMOVE_MINUS
CMP CL, 0
; jump to label @CHECK_REMOVE_MINUS if CH!=0
; compare CL with 0
JE @SKIP_BACKSPACE ; jump to label @SKIP_BACKSPACE if CL=0
JMP @MOVE_BACK ; jump to label @MOVE_BACK
@CHECK_REMOVE_MINUS:
CMP CH, 1
; jump label
; compare CH with 1
JNE @CHECK_REMOVE_PLUS
CMP CL, 1
; jump to label @CHECK_REMOVE_PLUS if CH!=1
; compare CL with 1
JE @REMOVE_PLUS_MINUS
@CHECK_REMOVE_PLUS:
CMP CL, 1
; jump to label @REMOVE_PLUS_MINUS if CL=1
; jump label
; compare CL with 1
JE @REMOVE_PLUS_MINUS
JMP @MOVE_BACK
; jump to label @MOVE_BACK
@REMOVE_PLUS_MINUS:
MOV AH, 2
MOV DL, 20H
INT 21H
MOV DL, 8H
INT 21H
; jump to label @REMOVE_PLUS_MINUS if CL=1
; jump label
; set output function
; set DL=' '
; print a character
; set DL=8H
; print a characterJMP @READ
; jump to label @READ
@MOVE_BACK:
; jump label
MOV AX, BX ; set AX=BX
MOV BX, 10 ; set BX=10
DIV BX
; set AX=AX/BX
MOV BX, AX ; set BX=AX
MOV AH, 2 ; set output function
MOV DL, 20H
; set DL=' '
INT 21H
; print a character
MOV DL, 8H
; set DL=8H
INT 21H
; print a character
XOR DX, DX
DEC CL
; clear DX
; set CL=CL-1
JMP @INPUT
; jump to label @INPUT
@NOT_BACKSPACE:
INC CL
; jump label
; set CL=CL+1
CMP AL, 30H ; compare AL with 0
JL @ERROR ; jump to label @ERROR if AL<0
CMP AL, 39H ; compare AL with 9JG @ERROR
AND AX, 000FH
PUSH AX
MOV AX, 10
MUL BX
MOV BX, AX
POP AX
; jump to label @ERROR if AL>9
; convert ascii to decimal code
; push AX onto the STACK
; set AX=10
; set AX=AX*BX
; set BX=AX
; pop a value from STACK into AX
ADD BX, AX ; set BX=AX+BX
JS @ERROR ; jump to label @ERROR if SF=1
JMP @INPUT
; jump to label @INPUT
@ERROR: ; jump label
MOV AH, 2 ; set output function
MOV DL, 7H ; set DL=7H
INT 21H
XOR CH, CH
; print a character
; clear CH
@CLEAR: ; jump label
MOV DL, 8H ; set DL=8H
INT 21H
MOV DL, 20H
INT 21H
; print a character
; set DL=' '
; print a characterMOV DL, 8H
INT 21H
LOOP @CLEAR
JMP @READ
@END_INPUT:
; set DL=8H
; print a character
; jump to label @CLEAR if CX!=0
; jump to label @READ
; jump label
CMP CH, 1 ; compare CH with 1
JNE @EXIT ; jump to label @EXIT if CH!=1
NEG BX ; negate BX
@EXIT: ; jump label
MOV AX, BX
; set AX=BX
POP DX ; pop a value from STACK into DX
POP CX ; pop a value from STACK into CX
POP BX ; pop a value from STACK into BX
RET
; return control to the calling procedure
INDEC ENDP
OUTDEC PROC
; this procedure will display a decimal number
; input : AX
; output : none
; uses : MAIN
PUSH BX ; push BX onto the STACK
PUSH CX ; push CX onto the STACKPUSH DX ; push DX onto the STACK
CMP AX, 0 ; compare AX with 0
JGE @START
PUSH AX
; jump to label @START if AX>=0
; push AX onto the STACK
MOV AH, 2 ; set output function
MOV DL, "-" ; set DL='-'
INT 21H ; print the character
POP AX ; pop a value from STACK into AX
NEG AX ; take 2's complement of AX
@START: ; jump label
XOR CX, CX ; clear CX
MOV BX, 10 ; set BX=10
@OUTPUT: ; loop label
XOR DX, DX
DIV BX
PUSH DX
INC CX
OR AX, AX
JNE @OUTPUT
; clear DX
; divide AX by BX
; push DX onto the STACK
; increment CX
; take OR of Ax with AX
; jump to label @OUTPUT if ZF=0
MOV AH, 2 ; set output function
@DISPLAY: ; loop labelPOP DX
OR DL, 30H
INT 21H
LOOP @DISPLAY
; pop a value from STACK to DX
; convert decimal to ascii code
; print a character
; jump to label @DISPLAY if CX!=0
POP DX ; pop a value from STACK into DX
POP CX ; pop a value from STACK into CX
POP BX ; pop a value from STACK into BX
RET
; return control to the calling procedure
OUTDEC ENDP
END MAIN
END MAIN
```

Output:
![a1q7][a1q7]

---
## Q8: Hex to decimal conversion

Code:
```asm
DATA segmentnum dw 12h
MSG db "The decimal number - $"
res db 10 dup('$')
DATA ends
code segment
assume ds:DATA,cs:code
START:
MOV ax,DATA
MOV ds,ax
LEA dx,MSG
MOV ah,09h
INT 21h
MOV ax,num
LEA si,res
call hex2dec
LEA dx,res
;display the string of numbers from hex
MOV ah,9
INT 21h
MOV ah,4ch
INT 21h
hex2dec proc near ;conversion
MOV cx,0
MOV bx,10
LOOP1:
MOV dx,0 div bx
ADD dl,30h
PUSH dx
INC cx
CMP ax,9
JG LOOP1
ADD al,30h
MOV [si],al
LOOP2: pop ax
INC si
MOV [si],al
LOOP LOOP2
RET
hex2dec endp
CODE ends
END START
```

Output:
![a1q8][a1q8]

---
## Q9: Factorial of an input number

Code:
```asm
.MODEL SMALL
.STACK 300H
.DATA
.CODE
MAIN PROC
MOV AX,@DATA
MOV DS,AX
MOV AX,0001H
MOV CX,0006H ;DATA WHOSE FACTORIAL WE FIND
MOV DX,0000H
L1:
MUL CX
LOOP L1MOV CX,00
L2:
MOV DX,0000H
MOV BX,0AH
DIV BX
PUSH DX
INC CX
CMP AX,0000H
JE L3
JMP L2
L3:POP DX
MOV AH,02H
ADD DX,0030H
INT 21H
LOOP L3
MOV AX,4C00H
INT 21H
MAIN ENDP
END MAIN
```

Output:
![a1q9][a1q9]

---


[a1q1]: images/a1q1.jpg
[a1q2]: images/a1q2.jpg
[a1q3]: images/a1q3.jpg
[a1q4]: images/a1q4.jpg
[a1q5]: images/a1q5.jpg
[a1q6]: images/a1q6.jpg
[a1q7]: images/a1q7.jpg
[a1q8]: images/a1q8.jpg
[a1q9]: images/a1q9.jpg
