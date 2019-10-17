public _fuction3
public _fuction4
public _fuction5
extrn item1 : word
extrn dispdec : near
.386
data segment use16 para public 'DATA'
N EQU 2

        BUF1   DB 'username:$'
        BUF2   DB 'password:$'
        BUF3   DB 'commodity:$'
        BUF4  DB 'discount:$'
        BUF5  DB 'price:$'
        BUF6  DB 'purchase volume:$'
        BUF7  DB 'sales:$'
        BUF8  DB 'recommand degree:$'
        BUF9  DB 'rank:$'
        ranking dw 2*N dup(0)
        match  dw N dup(0)
;GA1 DB 'PEN',7 DUP(0),10
;    DW 35,56,70,25,?
;GA2 DB 'BOOK',6 DUP(0),9
;    DW 12,30,25,5,?
;GAN DB N-3 DUP('Temp-Value',8,15,0,20,0,30,0,2,0,?,?)
;GA_text DB 'BAG',7 DUP(0),9
;        DW 15,30,1100,0,?

;AUTH   db 0
data ends
stack   segment use16 stack
        db 200 dup(0)
stack   ends
code    segment use16 para public 'CODE'
assume cs:code,ds:data,ss:stack


;调试用  
        
        ;call fuction3
        ;call fuction4
        ;call fuction5
        ;mov ah,1
        ;int 21h
        ;mov ah,4CH
        ;int 21H






;计算推荐度
_fuction3 proc
      pusha

      mov ax,data
      mov ds,ax
      
      lea bx,ds : item1
      mov dx,0
      mov cx, N
lopa: push cx
      mov cx,0
      mov ax,[bx+13]
      mov cl,[bx+10]
      mul cx
      mov cx,10
      mov dx,0
          div cx
          mov cx,ax
          mov ax,[bx+11]
          sal ax,7
          mov dx,0
          div cx
          mov cx,ax
          mov ax,[bx+17]
          sal ax,7
          mov dx,0
          div word ptr [bx+15]
          add ax,cx
          mov [bx+19],ax
          add bx,21
          pop cx
          loop lopa
          popa
          ret
_fuction3 endp




;推荐度排名
_fuction4 proc

    pusha

    mov ax,data
    mov ds,ax

    lea bx,ds : item1
    mov cx,N
    mov si,0
    mov di,0
lopb: mov ax,[bx+19]
    mov ranking[si],ax
    mov ranking[si+2],di
    add si,4
    inc di
    add bx,21
    loop lopb 
    lea bx,ds : item1
    mov dx,1
lopd: mov si,0
    mov di,0
    mov cx,N
    sub cx,dx
lopc: mov di,si
    add si,4
    mov ax,ranking[si]
    cmp ax,ranking[di]
    ja swap
continue: loop lopc
    inc dx
    cmp dx,N
    jne lopd
    mov si,0
    mov di,0
    mov ax,1
    mov cx,N 
lope: mov si,ranking[di+2]
    sal si,1
    mov match[si],ax
    add di,4
    inc ax
    loop lope
    popa
    ret

swap: push ax
      mov ax,ranking[di]
      mov ranking[si],ax
      pop ax
      mov ranking[di],ax
      mov ax,ranking[si+2]
      push ax
      mov ax,ranking[di+2]
      mov ranking[si+2],ax
      pop ax
      mov ranking[di+2],ax
      jmp continue

_fuction4 endp



;输出全部商品信息
_fuction5 proc

        pusha

        mov ax,data
        mov ds,ax

        mov cx,N
        mov di,0
        lea bx,ds : item1
cycle1: 
        lea dx,BUF3
        mov ah,9
        int 21H
        mov si,0
cycle2: mov dl,byte ptr [bx+si]
        cmp dl,0
        je skip
        mov ah,2
        int 21H
        inc si
        jmp cycle2
skip:   mov dl,10
        mov ah,2
        int 21H
        mov dl,13
        mov ah,2
        int 21H
        lea dx,BUF4
        mov ah,9
        int 21H
        mov dx,0
        mov dl,byte ptr [bx+10]
        call dispdec
        mov dl,10
        mov ah,2
        int 21H
        mov dl,13
        mov ah,2
        int 21H
        lea dx,BUF5
        mov ah,9
        int 21H
        mov dx, word ptr [bx+11]
        ;mov dh, 0
        call dispdec
        mov dl,10
        mov ah,2
        int 21H
        mov dl,13
        mov ah,2
        int 21H
        lea dx,BUF6
        mov ah,9
        int 21H
        mov dx,word ptr[bx+15]
        call dispdec
        mov dl,10
        mov ah,2
        int 21H
        mov dl,13
        mov ah,2
        int 21H
        lea dx,BUF7
        mov ah,9
        int 21H
        mov dx,word ptr [bx+17]
        call dispdec
        mov dl,10
        mov ah,2
        int 21H
        mov dl,13
        mov ah,2
        int 21H
        lea dx,BUF8
        mov ah,9
        int 21H
        mov dx, word ptr [bx+19]
        call dispdec
        mov dl,10
        mov ah,2
        int 21H
        mov dl,13
        mov ah,2
        int 21H
        lea dx,BUF9
        mov ah,9
        int 21H
        mov dx,match[di]
        call dispdec
        mov dl,10
        mov ah,2
        int 21H
        mov dl,10
        mov ah,2
        int 21H
        mov dl,13
        mov ah,2
        int 21H
        add di,2
        add bx,21
        dec cx
        cmp cx,0
        jne far ptr cycle1
        popa
        ret

_fuction5 endp
  



;显示十进制子程序
;入口参数DX=要显示的数值，出口：无
;dispdec proc
;        ; uses ax bx cx dx
;        pusha
;        mov ax,dx
;        xor dx,dx
;        mov bx,10
;        mov cx,0
;a:
;        cmp ax,10
;        jb ok
;        div bx
;        add dl,30h
;        push dx
;        xor dx,dx
;        inc cx
;        jmp a
;ok:
;        add al,30h
;        push ax
;        inc cx
;b:
;        pop dx
;        mov ah,2
;        int 21h
;        loop b
;        popa
;        ret
;dispdec endp

code ends
    end



