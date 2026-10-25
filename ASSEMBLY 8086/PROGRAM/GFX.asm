
.model small
.stack 100h

.code
main proc
    mov ax, 0013h
    int 10h

    mov ax, 0A000h
    mov es, ax
    cld

    mov bx, 60

draw_row:
    mov ax, bx
    mov dx, 320
    mul dx

    add ax, 90
    mov di, ax

    mov cx, 140
    mov al, 12
    rep stosb

    inc bx
    cmp bx, 130
    jb draw_row

    mov ah, 00h
    int 16h

    mov ax, 0003h
    int 10h

    mov ax, 4C00h
    int 21h
main endp

end main
