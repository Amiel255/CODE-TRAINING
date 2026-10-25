
.model small
.stack 100h

.data
    msg db '8086 GRAPHICS TEST$'
    mouseMsg db 'Mouse detected!$'
    noMouse db 'Mouse not detected$'

.code
main proc
    mov ax, @data
    mov ds, ax

    mov ax, 0013h
    int 10h

    mov ax, 0A000h
    mov es, ax
    cld

    mov bx, 50

draw_row:
    mov ax, bx
    mov cx, 320
    mul cx

    add ax, 80
    mov di, ax

    mov cx, 160
    mov al, 9
    rep stosb

    inc bx
    cmp bx, 120
    jb draw_row

    mov ah, 02h
    mov bh, 0
    mov dh, 2
    mov dl, 9
    int 10h

    mov ah, 09h
    lea dx, msg
    int 21h

    xor ax, ax
    int 33h

    cmp ax, 0
    je mouse_missing

    mov ax, 1
    int 33h

    mov ah, 02h
    mov bh, 0
    mov dh, 18
    mov dl, 8
    int 10h

    mov ah, 09h
    lea dx, mouseMsg
    int 21h
    jmp wait_key

mouse_missing:
    mov ah, 02h
    mov bh, 0
    mov dh, 18
    mov dl, 8
    int 10h

    mov ah, 09h
    lea dx, noMouse
    int 21h

wait_key:
    mov ah, 00h
    int 16h

    mov ax, 0003h
    int 10h

    mov ax, 4C00h
    int 21h
main endp

end main
