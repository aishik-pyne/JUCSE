# MASM Assignment 2

## Q1: Bubble Sort

Code:
```asm
;SHOWN TO SIR
.MODEL SMALL
.STACK 300H
.DATA
 msg1 DB 10,13,'Enter the limit::$'
  msg2 DB 10,13,'Enter the numbers::$'
  msg3 DB 10,13,'The numbers in ascending order is::$'
  space DB ' $'
 newline DB 10,13,'$'
 count db ?
 tab1 db 20 dup(0)
 .CODE
 printstring MACRO msg
 PUSH AX
 PUSH DX
 MOV AH,09H
 MOV DX,OFFSET msg
  INT 21H
 POP DX
 POP AX
 ENDM
MAIN PROC
MOV AX,@DATA
MOV DS,AX

printstring msg1
  CALL readnumtoAX
  MOV count,AL
  MOV CL,count
  MOV CH,00
  MOV BX,1
  printstring msg2
rdnxt:
  printstring newline
  CALL readnumtoAX
  MOV tab1[BX],AL
  INC BX
  LOOP rdnxt
  MOV CL,count
  MOV CH,00
  CMP CX,1
  JE DONE

nextpass:
	CALL printArray
	MOV DL,00
	MOV BX,01
nextj:
	MOV AL,tab1[BX]
	MOV AH,tab1[BX + 1]
	CMP AL,AH
	JLE skip
	MOV tab1[BX],AH
	MOV tab1[BX + 1],AL
	MOV DL,1
skip:
	INC BX
	CMP BX,CX
	JL nextj
	DEC CX
	jz done
	CMP DL,01H
	JE nextpass
done:
	MOV CL,count
	MOV CH,00
	MOV BX,01
	printstring msg3
prnnxt:
  MOV AX,00
  MOV AL,tab1[BX]
  CALL displayAX
  printstring space
  INC BX
  LOOP prnnxt
  MOV AH,4CH
  MOV AL,00H
  INT 21H
  main endp

;CODE TO ACCEPT NUMBER
readnumtoAX PROC NEAR
  PUSH BX
  PUSH CX
  MOV CX,10
  MOV BX,00
bac:
  MOV AH,01H
  INT 21H
  CMP AL,'0'
  JB skip1
  CMP AL,'9'
  JA skip1
  SUB AL,'0'
  PUSH AX
  MOV AX,BX
  MUL CX;SHIFT
  MOV BX,AX
  POP AX
  MOV AH,00
  ADD BX,AX
  JMP bac
skip1:
  MOV AX,BX
  POP CX
  POP BX
  RET
 readnumtoAX ENDP


displayAX PROC NEAR
  PUSH DX
  PUSH CX
  PUSH BX
  PUSH AX
  MOV CX,0
  MOV BX,10
 back1:
  MOV DX,0
  DIV BX
  PUSH DX
  INC CX
  OR AX,AX
  JNZ back1	;TILL AX IS 0
back2:
  POP DX
  ADD DL,30H
  MOV AH,02H
  INT 21H
  LOOP back2
  POP AX
  POP BX
  POP CX
  POP DX
  RET
displayAX ENDP

printArray PROC NEAR
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	MOV CL,count
	MOV CH,00H
	MOV BX,01H
LABEL1:
	MOV AX,00
	MOV AL,tab1[BX]
	CALL displayAX
	printstring space
	INC BX
	LOOP LABEL1
	printstring newline
	POP DX
	POP CX
	POP BX
	POP AX
	RET
printArray ENDP

END MAIN


```


---
## Q2: Selection Sort

Code:
```asm
.MODEL SMALL
.STACK 300H
.DATA
	PROMPT_1  DB  'The array before sorting : $'
    PROMPT_2  DB  0DH,0AH,'The array after sorting by selection sort: $'
    ARRAY   DB  5,3,9,0,2,6,1,7,8,4
.CODE
MAIN PROC
MOV AX,@DATA
MOV DS,AX

MOV BX, 10                   ; set BX=10

     LEA DX, PROMPT_1             ; load and display the string PROMPT_1
     MOV AH, 9
     INT 21H

     LEA SI, ARRAY                ; set SI=offset address of ARRAY

     CALL PRINT_ARRAY             ; call the procedure PRINT_ARRAY

     LEA SI, ARRAY                ; set SI=offset address of the ARRAY

     CALL SELECT_SORT             ; call the procedure SELECT_SORT

     LEA DX, PROMPT_2             ; load and display the string PROMPT_2
     MOV AH, 9
     INT 21H

     LEA SI, ARRAY                ; set SI=offset address of ARRAY

     CALL PRINT_ARRAY             ; call the procedure PRINT_ARRAY

     MOV AH, 4CH                  ; return control to DOS
     INT 21H
MAIN ENDP

PRINT_ARRAY PROC
   ; this procedure will print the elements of a given array
   ; input : SI=offset address of the array
   ;       : BX=size of the array
   ; output : none

   PUSH AX                        ; push AX onto the STACK
   PUSH CX                        ; push CX onto the STACK
   PUSH DX                        ; push DX onto the STACK

   MOV CX, BX                     ; set CX=BX

   @PRINT_ARRAY:                  ; loop label
     XOR AH, AH                   ; clear AH
     MOV AL, [SI]                 ; set AL=[SI]

     CALL OUTDEC                  ; call the procedure OUTDEC

     MOV AH, 2                    ; set output function
     MOV DL, 20H                  ; set DL=20H
     INT 21H                      ; print a character

     INC SI                       ; set SI=SI+1
   LOOP @PRINT_ARRAY              ; jump to label @PRINT_ARRAY while CX!=0

   POP DX                         ; pop a value from STACK into DX
   POP CX                         ; pop a value from STACK into CX
   POP AX                         ; pop a value from STACK into AX

   RET                            ; return control to the calling procedure
 PRINT_ARRAY ENDP

 ;**************************************************************************;
 ;----------------------------  SELECT_SORT  -------------------------------;
 ;**************************************************************************;

 SELECT_SORT PROC
   ; this procedure will sort the array in ascending order
   ; input : SI=offset address of the array
   ;       : BX=array size
   ; output :none

   PUSH AX                        ; push AX onto the STACK
   PUSH BX                        ; push BX onto the STACK
   PUSH CX                        ; push CX onto the STACK
   PUSH DX                        ; push DX onto the STACK
   PUSH DI                        ; push DI onto the STACK

   CMP BX, 1                      ; compare BX with 1
   JLE @SKIP_SORTING              ; jump to label @SKIP_SORTING if BX<=1

   DEC BX                         ; set BX=BX-1
   MOV CX, BX                     ; set CX=BX
   MOV AX, SI                     ; set AX=SI

   @OUTER_LOOP:                   ; loop label
     MOV BX, CX                   ; set BX=CX
     MOV SI, AX                   ; set SI=AX
     MOV DI, AX                   ; set DI=AX
     MOV DL, [DI]                 ; set DL=[DI]

     @INNER_LOOP:                 ; loop label
       INC SI                     ; set SI=SI+1

       CMP [SI], DL               ; compare [SI] with DL
       JNG @SKIP                  ; jump to label @SKIP if [SI]<=DL

       MOV DI, SI                 ; set DI=SI
       MOV DL, [DI]               ; set DL=[DI]

       @SKIP:                     ; jump label

       DEC BX                     ; set BX=BX-1
     JNZ @INNER_LOOP              ; jump to label @INNER_LOOP if BX!=0

     MOV DL, [SI]                 ; set DL=[SI]
     XCHG DL, [DI]                ; set DL=[DI] , [DI]=DL
     MOV [SI], DL                 ; set [SI]=DL

   LOOP @OUTER_LOOP               ; jump to label @OUTER_LOOP while CX!=0

   @SKIP_SORTING:                 ; jump label

   POP DI                         ; pop a value from STACK into DI
   POP DX                         ; pop a value from STACK into DX
   POP CX                         ; pop a value from STACK into CX
   POP BX                         ; pop a value from STACK into BX
   POP AX                         ; pop a value from STACK into AX

   RET                            ; return control to the calling procedure
 SELECT_SORT ENDP

 ;**************************************************************************;
 ;--------------------------------  OUTDEC  --------------------------------;
 ;**************************************************************************;

 OUTDEC PROC
   ; this procedure will display a decimal number
   ; input : AX
   ; output : none

   PUSH BX                        ; push BX onto the STACK
   PUSH CX                        ; push CX onto the STACK
   PUSH DX                        ; push DX onto the STACK

   XOR CX, CX                     ; clear CX
   MOV BX, 10                     ; set BX=10

   @OUTPUT:                       ; loop label
     XOR DX, DX                   ; clear DX
     DIV BX                       ; divide AX by BX
     PUSH DX                      ; push DX onto the STACK
     INC CX                       ; increment CX
     OR AX, AX                    ; take OR of Ax with AX
   JNE @OUTPUT                    ; jump to label @OUTPUT if ZF=0

   MOV AH, 2                      ; set output function

   @DISPLAY:                      ; loop label
     POP DX                       ; pop a value from STACK to DX
     OR DL, 30H                   ; convert decimal to ascii code
     INT 21H                      ; print a character
   LOOP @DISPLAY                  ; jump to label @DISPLAY if CX!=0

   POP DX                         ; pop a value from STACK into DX
   POP CX                         ; pop a value from STACK into CX
   POP BX                         ; pop a value from STACK into BX

   RET                            ; return control to the calling procedure
 OUTDEC ENDP


END MAIN

```


---
## Q3: Insertion Sort

Code:
```asm
.MODEL SMALL
.STACK 256H

DAT SEGMENT
INP DB 'Enter Array: $'
ARRAY DW 100 DUP(30H)
;ARRAY DW 000CH, 000EH, 000DH, 000FH, 0010H, 000AH
DAT ends

COD segment
assume cs:COD, DS:DAT
MAIN PROC
	MOV AX, DAT
	MOV DS, AX
	LEA SI, ARRAY
	CALL INPUTARRAY
	MOV CX, SI
	LEA SI, ARRAY
	SUB CX, SI
	CALL INSSORT
	CALL NLINE
	CALL PRINTA
	CALL ENDPROG
MAIN ENDP

CHECKN PROC
	PUSH AX
	PUSH DX
	MOV AX, CX
	CALL PRINTINT
	CALL NLINE
	POP DX
	POP AX
	RET
CHECKN ENDP

PRINTA PROC
	PUSH AX
	PUSH BX
	PUSH DX
	MOV BX, 0
	SUB CX, 2
	LOOPP:
		MOV AX, ARRAY[BX]
		CALL PRINTINT
		MOV AH, 2
		MOV DL, 20H
		INT 21H
		INC BX
		INC BX
		CMP BX, CX
	JL LOOPP
	ADD CX, 2
	POP DX
	POP BX
	POP AX
	RET
PRINTA ENDP

INSSORT PROC
	MOV AX, 2
LOOP1:
		CMP AX, CX
		JGE SKIP1
		MOV DI, AX
		PUSH CX
		LOOP2:
			XOR DI, 0
			JZ SKIP2
			MOV DX, ARRAY[DI-2]
			CMP DX, ARRAY[DI]
			JNG SKIP2
			MOV CX, ARRAY[DI]
			MOV ARRAY[DI], DX
			MOV ARRAY[DI-2], CX
			SUB DI, 2
			CMP DI, DX
		JMP LOOP2
	SKIP2:
		ADD AX, 2
		POP CX
	JMP LOOP1
SKIP1:
	ADD CX, 2
	RET
INSSORT ENDP

NLINE PROC
	MOV dl, 10
	MOV ah, 02h
	INT 21h
	MOV dl, 13
	MOV ah, 02h
	INT 21h
	RET
NLINE ENDP

ENDPROG PROC
	MOV AH, 4ch
	INT 21H
ENDPROG ENDP

GETNUM PROC
	PUSH CX
	MOV BX, 0
	MOV AL,30H
	LoopGetNum:
		SUB AL, 30H
		MOV CH,AL
		MOV AX,BX
		MOV CL, 0AH
		MUL CL
		MOV CL,CH
		MOV CH, 0
		ADD AX,CX
		MOV BX,AX
		MOV AH, 1
		INT 21H
		CMP AL, 0DH ;ENTER key pressed, exit
		JE Outside
		CMP AL, 20H
		JE Outside
		JMP LoopGetNum
	Outside:
	POP CX
	RET
GETNUM ENDP

INPUTARRAY PROC
	MOV AH, 09H
	LEA DX, INP
	INT 21H
	MOV CX, 100
	Loopinp:
		CALL GETNUM
		MOV [SI], BX
		INC SI
		INC SI
		CMP AL, 0DH
		JE HereArray
	LOOP Loopinp
	HereArray:
	RET
INPUTARRAY ENDP
NUM2STRPRINT PROC
  MOV  BX, 10
  MOV  CX, 0
CYCLE1:
  MOV  DX, 0
  DIV  BX
  PUSH DX
  INC  CX
  CMP  AX, 0
  JNE  CYCLE1
;NOW RETRIEVE PUSHED DIGITS.
CYCLE2:
  POP  DX
  ADD  DL, 48 ;CONVERT DIGIT TO CHARACTER.
  MOV AH, 2
  INT 21H
  LOOP CYCLE2
  RET
NUM2STRPRINT ENDP

PRINTINT PROC
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX
	CALL NUM2STRPRINT
	POP DX
	POP CX
	POP BX
	POP AX
	RET
PRINTINT ENDP

END MAIN
```


---

---
## Q4: Binary Search

Code:
```asm
.MODEL SMALL
.STACK 300H
.DATA
ARR DW 0000H,1111H,2222H,3333H,4444H,5555H,6666H,7777H,8888H,9999H
     LEN DW ($-ARR)/2
     KEY EQU 8888H
     MSG1 DB "KEY IS FOUND AT "
     RES DB " th POSITION",13,10," $"
     MSG2 DB 'KEY NOT FOUND!!!.$'

.CODE
MAIN PROC
MOV AX,@DATA
MOV DS,AX

MOV BX,00
      MOV DX,LEN
      MOV CX,KEY
AGAIN: CMP BX,DX
       JA FAIL
       MOV AX,BX
       ADD AX,DX
       SHR AX,1
       MOV SI,AX
       ADD SI,SI
       CMP CX,ARR[SI]
       JAE BIG
       DEC AX
       MOV DX,AX
       JMP AGAIN
BIG:   JE SUCCESS
       INC AX
       MOV BX,AX
       JMP AGAIN
SUCCESS: ADD AL,01
         ADD AL,'0'
         MOV RES,AL
         LEA DX,MSG1
         JMP DISP
FAIL: LEA DX,MSG2
DISP: MOV AH,09H
      INT 21H

      MOV AH,4CH
      INT 21H
MAIN ENDP
END MAIN
```
