.MODEL SMALL
.STACK 100h

.DATA
    prompt    DB 'Enter your text: $'
    reply     DB 13, 10, 'Capitalized text: $'
    
    ; --- The Buffer Structure ---
    maxLen    DB 50         ; Max allowed length
    actLen    DB ?          ; DOS will store actual length here
    charInput DB 50 DUP(?)  ; Storage array for the text

.CODE
main PROC
    ; Initialize Data Segment
    MOV AX, @DATA
    MOV DS, AX

    ; 1. Prompt user for input
    LEA DX, prompt
    MOV AH, 09h
    INT 21h

    ; 2. Read string using Function 0Ah
    LEA DX, maxLen        
    MOV AH, 0Ah           
    INT 21h               

    ; 3. Prepare for capitalization loop
    MOV CL, actLen        ; Load actual string length into loop counter (CL)
    MOV CH, 0             ; Clear CH so CX holds the full count
    JCXZ PrintResult      ; If string is empty, skip the loop entirely

    LEA SI, charInput     ; Point SI to the start of the actual characters

CapitalizeLoop:
    MOV AL, [SI]          ; Load current character into AL
    
    ; Check if character is less than 'a' (97)
    CMP AL, 'a'           
    JB NextChar           ; If below 'a', it's not lowercase. Skip!

    ; Check if character is greater than 'z' (122)
    CMP AL, 'z'           
    JA NextChar           ; If above 'z', it's not lowercase. Skip!

    ; --- Convert to Uppercase ---
    SUB AL, 32            ; Subtract 32 to convert to uppercase
    MOV [SI], AL          ; Save the capitalized letter back into memory

NextChar:
    INC SI                ; Move to the next character in memory
    LOOP CapitalizeLoop   ; Decrement CX and loop if CX != 0

PrintResult:
    ; 4. Terminate the string with '$' for DOS printing
    MOV BL, actLen        
    MOV BH, 0             
    MOV charInput[BX], '$'; Place '$' at the end of the text

    ; 5. Print reply message
    LEA DX, reply
    MOV AH, 09h
    INT 21h

    ; 6. Print the capitalized string
    LEA DX, charInput     
    MOV AH, 09h           
    INT 21h

    ; 7. Exit to DOS
    MOV AX, 4C00h
    INT 21h
main ENDP
END main
