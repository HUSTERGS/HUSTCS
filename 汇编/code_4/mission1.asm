.386
data    segment  use16
data ends

stack   segment  use16 stack
    db  200 dup(0)
stack   ends

code    segment  use16
assume cs:code,ds:data,ss:stack

start:  mov ax,data
        mov ds,ax
        mov ah, 35h
        mov al, 13h
        int 21h
        mov dx, word ptr fs:[13h * 4 + 2]
        mov si, word ptr fs:[13h * 4]
code    ends
end start
