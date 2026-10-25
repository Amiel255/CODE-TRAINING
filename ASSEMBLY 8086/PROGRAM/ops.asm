
.model small
.stack 100h

.data
    x dw 8
    y dw 5

    msgX db 'x = $'
    msgY db 13, 10, 'y = $'

    msg1 db 13, 10, 13, 10, 'Sum of x and y is: $'
    msg2 db 13, 10, 'Difference of x and y is: $'
    msg3 db 13, 10, 'Product of x and y is: $'
    msg4 db 13, 10, 'Quotient of x and y is: $'

    newline db 13, 10, '$'

.code
main proc
    mov ax, @data
    mov ds, ax

    lea dx, msgX
    mov ah, 09h
    int 21h

    mov ax, x
    call print_number

    lea dx, msgY
    mov ah, 09h
    int 21h

    mov ax, y
    call print_number

    lea dx, msg1
    mov ah, 09h
    int 21h

    mov ax, x
    add ax, y
    call print_number

    lea dx, msg2
    mov ah, 09h
    int 21h

    mov ax, x
    sub ax, y
    call print_number

    lea dx, msg3
    mov ah, 09h
    int 21h

    mov ax, x
    mov bx, y
    mul bx
    call print_number

    lea dx, msg4
    mov ah, 09h
    int 21h

    mov ax, x
    xor dx, dx
    div y

    push dx
    call print_number

    mov dl, '.'
    mov ah, 02h
    int 21h

    pop ax
    mov bx, 100
    mul bx
    div y

    mov bx, ax
    cmp bx, 10
    jae decimal_result

    mov dl, '0'
    mov ah, 02h
    int 21h

decimal_result:
    mov ax, bx
    call print_number

    lea dx, newline
    mov ah, 09h
    int 21h

    mov ax, 4C00h
    int 21h
main endp

print_number proc
    push ax
    push bx
    push cx
    push dx

    mov bx, 10
    xor cx, cx

convert:
    xor dx, dx
    div bx
    push dx
    inc cx

    cmp ax, 0
    jne convert

display:
    pop dx
    add dl, '0'
    mov ah, 02h
    int 21h
    loop display

    pop dx
    pop cx
    pop bx
    pop ax
    ret
print_number endp

end main
