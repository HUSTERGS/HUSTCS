.model small
.386
.data
mystring db 'this is just my try', 0ah, 0dh, '$', 0

.code 
public _printstring
_printstring proc near
    pusha
    lea dx, mystring
    mov ah, 9
    int 21h
    popa
    ret
_printstring endp
end