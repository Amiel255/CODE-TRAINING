.MODEL SMALL
.STACK 100H

.DATA
    ; Messages to show on the DOS screen (ending with '$' for DOS display)
    MSG1 DB 'STATE 1: North/South GREEN | East/West RED', 13, 10, '$'
    MSG2 DB 'STATE 2: North/South YELLOW | East/West RED', 13, 10, '$'
    MSG3 DB 'STATE 3: North/South RED | East/West GREEN', 13, 10, '$'
    MSG4 DB 'STATE 4: North/South RED | East/West YELLOW', 13, 10, '$'

    ; Hardware bit patterns (sent to Port 4)
    SITUATIONS DW 0000001100001100B
               DW 0000011010011010B
               DW 0000100001100001B
               DW 0000010011010011B
    SITUATIONS_END EQU $

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

START_CYCLE:
    MOV SI, OFFSET SITUATIONS

NEXT_PATTERN:
    ; 1. Send the physical signal to Port 4
    MOV AX, [SI]
    OUT 4, AX          

    ; 2. Check current state pointer and branch
    CMP SI, OFFSET SITUATIONS
    JE SHOW_1
    CMP SI, OFFSET SITUATIONS + 2
    JE SHOW_2
    CMP SI, OFFSET SITUATIONS + 4
    JE SHOW_3
    JMP SHOW_4

SHOW_1: 
    MOV DX, OFFSET MSG1
    JMP PRINT

SHOW_2: 
    MOV DX, OFFSET MSG2
    JMP PRINT

SHOW_3: 
    MOV DX, OFFSET MSG3
    JMP PRINT

SHOW_4: 
    MOV DX, OFFSET MSG4

PRINT:
    MOV AH, 09H         ; DOS string display function
    INT 21H

    ; 3. Run the software delay loop
    CALL DELAY_LOOP

    ; Advance to next pattern
    ADD SI, 2          
    CMP SI, SITUATIONS_END
    JB NEXT_PATTERN

    ; Loop indefinitely
    JMP START_CYCLE

MAIN ENDP


; =========================================================================
; RELIABLE DOSBOX SOFTWARE DELAY SUBROUTINE
; =========================================================================
DELAY_LOOP PROC
    PUSH CX
    PUSH BX

    MOV CX, 00A0H       ; Outer loop counter (Adjust this to change speed)
L1:
    MOV BX, 0FFFFH      ; Inner loop counter
L2:
    DEC BX
    JNZ L2
    LOOP L1

    POP BX
    POP CX
    RET
DELAY_LOOP ENDP

END MAIN
