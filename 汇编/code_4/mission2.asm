.386
data segment use16 
data ends

stack segment use16 stack
    db 200 dup(0)
stack ends

code segment use16
assume cs:code, ds:data, ss:stack

OLD_INT dw ?,?

NEW_16H:
    cmp ah, 00h
    je judge
    cmp ah, 10H
    je judge
    jmp dword ptr OLD_INT
judge:
    pushf
    call dword ptr OLD_INT
    cmp al, 'A'
    jl exit
    cmp al, 'Z'
    jg exit
    jmp next
next:
    add al, 20h
    jmp exit
exit:
    iret
start:
    xor ax, ax
    mov ds, ax
    mov ax, ds:[16H * 4]
    mov OLD_INT, ax
    mov ax, ds:[16H * 4 + 2]
    mov OLD_INT+2, ax

    CLI

    mov word ptr DS:[16H * 4], offset NEW_16H

    mov ds:[16H * 4 + 2], cs
    STI

    mov dx, offset start + 15

    shr dx, 4
    add dx, 10H

    mov al, 0
    mov ah, 31h

    int 21h

recover proc
    pusha
    xor ax, ax
    mov ds, ax
    CLI

    mov dx, word ptr OLD_INT
    mov word ptr ds:[16H * 4], dx

    mov dx, word ptr OLD_INT + 2
    mov ds:[16H * 4 + 2], dx

    STI
    popa
    ret
recover endp


code ends

end start