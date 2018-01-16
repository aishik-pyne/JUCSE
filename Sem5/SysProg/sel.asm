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

