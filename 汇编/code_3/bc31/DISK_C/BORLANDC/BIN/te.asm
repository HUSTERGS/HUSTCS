public _lulala
public _temp

.386


stack   segment use16 stack
        db 500 dup(0)
stack   ends

data   segment use16 para public 'DATA'
    _temp db 1
data ends

code segment use16 para public 'CODE'
     assume cs:code, ds:data, ss:stack

_lulala proc near 
    pusha
    mov ax, data
    mov ds, ax
    mov _temp, 0
    popa
    ret
_lulala endp
code ends

end 