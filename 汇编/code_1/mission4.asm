.386

stack   segment use16 stack
        db 200 dup(0)
stack   ends

data    segment use16
        xuehao db 3 dup(0)
data    ends

code    segment use16
        assume  cs:code, ds:data, ss:stack
start:  mov ax, data
        mov ds, ax

        ;寄存器间接寻址
        mov bx, offset xuehao
        mov ax, '6'
        mov [bx], ax
        inc bx
        mov ax, '6'
        mov [bx], ax
        inc bx
        mov ax, '8'
        mov [bx], ax

        ;变址寻址
        mov bx, offset xuehao
        mov ax, '6'
        mov 0[bx], ax
        mov ax, '6'
        mov 1[bx], ax
        mov ax, '8'
        mov 2[bx], ax

        ;基址加变址寻址
        mov bx, offset xuehao
        mov si, 0
        mov ax, '6'
        mov [bx][si], ax
        inc si
        mov ax, '6'
        mov [bx][si], ax
        inc si
        mov ax,'8'
        mov [bx][si], ax

        ;直接寻址
        mov ah, '6'
        mov xuehao, ah
        mov ah, '6'
        mov xuehao + 1, ah
        mov ah, '8'
        mov xuehao + 2, ah

        ;退出
        mov ah, 4ch
        int 21h
code    ends
        end start
