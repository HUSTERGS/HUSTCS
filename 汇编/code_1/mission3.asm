.386
stack   segment stack
        db 200 dup(0)
stack   ends
data    segment
        buf1 db 0,1,2,3,4,5,6,7,8,9
        buf2 db 10 dup(0)
        buf3 db 10 dup(0)
        buf4 db 10 dup(0)
data    ends
code    segment
        assume cs:code, ds:data, ss:stack
start:  mov ax, data
        mov ds, ax

        mov esi,0
        mov ecx,10

lopa:   add al, buf1[esi]
        mov buf2[esi], al
        inc al
        mov buf3[esi], al
        add al, 3
        mov buf4[esi], al
        inc esi
        dec ecx
        jnz lopa
        
        mov ah, 4ch
        int 21h
code    ends
        end start
