extern fuction3 : near
extern fuction4 : near
extern fuction5 : near
public item1
.386

stack   segment use16 stack
        db 500 dup(0)
stack   ends

data   segment use16 para public 'DATA'
        Bname           db 'GE SONG'
        Bpassword       db 'lulala'
        Sname           db 0aH, 0dH, 'shop', '$'
        N               equ 2

        menu            db 0ah, 0dh, 'Please choose your action', 
                           0ah, 0dh, '1. search',
                           0ah, 0dh, '2. edit',
                           0ah, 0dh, '3. calculate',
                           0ah, 0dh, '4. rank',
                           0ah, 0dh, '5. print all goods',
                           0ah, 0dh, '6. exit',
                           '$'
        
        goodname        db  0ah, 0dh, 'name: ', '$'
        discount        db  0ah, 0dh, 'discount: ', '$'
        price           db  0ah, 0dh, 'price: ', '$'
        quanity         db  0ah, 0dh, 'quanity: ', '$'
        sold_num        db  0ah, 0dh, 'sold_num: ', '$'
        recommend_level db  0ah, 0dh, 'recommend_level: ', '$'

        username_hint   db 0ah, 0dh, 'Please enter your username', '$'
        password_hint   db 0ah, 0dh, 'Please enter your password', '$'
        fail_hint       db 0ah, 0dh, 'Auth fail, wrong username or password', '$'
        success_hint    db 0ah, 0dh, 'Auth success', '$'
        query_hint      db 0ah, 0dh, 'Please enter the item name you want to query', '$'
        in_name         db 80
                        db 0
                        db 80 dup(0)
        in_pwd          db 80
                        db 0
                        db 80 dup(0)
        in_item         db 80
                        db 0
                        db 80 dup(0)
        in_choice       db ?
        edit_buf        db 80
                        db 0
                        db 80 dup(0)

        item1           db 'pen', 7 dup(0), 10
                        dw 35, 56, 70, 25, ?
        item2           db 'book', 6 dup(0), 9
                        dw 12, 30, 25, 5, ?
        ;rest_items      db N-2 dup('Temp-Value',8, 15, 0, 20, 0, 30, 0, 2, 0, ?, ?)
        item_size       dw 21
        auth            dw 0
        input_filter    dw 0

        
data ends

code segment use16 para public 'CODE'
     assume cs:code, ds:data, ss:stack

start:  mov ax, data
        mov ds, ax

login:  ;show the name of my shop
        lea dx, Sname
        mov ah, 9
        int 21h
        call newline
        ; show the hint for users to enter their username
        lea dx, username_hint
        mov ah, 9
        int 21h
        call newline
        
        ; user input username
        lea dx, in_name
        mov ah, 10
        int 21h
        
        mov si, offset in_name
        ; if the input is 'q', then quit
        cmp byte ptr 2[si], 'q'
        je exit


        ; if the input is '\n', then begin query
        cmp byte ptr 2[si], 13
        je cumtomer

        call check_username

        ; show the hint for users to enter their password
        lea dx, password_hint
        mov ah, 9
        int 21h
        call newline

        lea dx, in_pwd
        mov ah, 10
        int 21h

        call check_password
        jmp function3

cumtomer:
    mov auth, 0
    jmp function3

check_username proc 
        ; check the username
        ; the length of the input is stored in cx
        mov cl, in_name + 1
        mov ch, 0
        mov bx, 0
        
        cmp cx, 7
        jne auth_fail

        mov si, offset in_name
        mov di, offset Bname

    loopa:  mov ah, byte ptr 2[bx+si]
            mov al, byte ptr [bx+di]
            cmp ah, al
            jne  auth_fail

            inc bx
            cmp cx, bx
            jne loopa
    ret
check_username endp

check_password proc
        ; check the password
        ; the length of the input is stored in cx
        mov cl, in_pwd + 1
        mov ch, 0
        mov bx, 0
        
        cmp cx, 6
        jne auth_fail

        mov si, offset in_pwd
        mov di, offset Bpassword

    loopb:  mov ah, byte ptr 2[bx+si]
            mov al, byte ptr [bx+di]
            cmp ah, al
            jne  auth_fail

            inc bx
            cmp cx, bx
            jne loopb
    mov auth, 1
    ret
check_password endp  
        
auth_fail:
    mov auth, 0
    lea dx, fail_hint
    mov ah, 9
    int 21h
    call newline
    jmp login


query:
    lea dx, query_hint
    mov ah, 9
    int 21h
    call newline
    ; user enter item name
    lea dx, in_item
    mov ah, 10
    int 21h

    mov si, offset in_item
    ; if the input is \n return to login func
    cmp byte ptr 2[si], 13
    je function3
    
    mov bx, offset item1
    mov cx, 1
    jmp compare_item

next_item:
    ; the cx = N, then it means didn't find, back to query func
    cmp cx, N
    je  query

    inc cx
    mov bx, di
    add bx, item_size
    jmp compare_item
    

compare_item:
    mov di, bx
    mov si, offset in_item
    mov bl, in_item + 1
    mov bh, 0
    mov byte ptr in_item + 2[bx], '$'
    mov bx, 0
    loopc:  
        mov ah, byte ptr [di+bx]
        mov al, byte ptr 2[si+bx]
        cmp ah, 0
        je check_item_length
        cmp bx, 10
        je find_item
        inc bx
        cmp ah, al
        je loopc
    jmp next_item
; check the length of the input
check_item_length:
    mov cl, in_item + 1
    mov ch, 0
    cmp bx, cx
    je find_item
    jmp next_item

find_item:
    mov bx, di
    cmp auth, 1
    je  show_item_name

    cmp in_choice, '1'
    je calculate
    
    cmp in_choice, '2'
    je edit


show_item_name:
    call newline
    lea dx, in_item+2
    mov ah, 9
    int 21h
    jmp login

calculate:
    add bx, 10
    mov ax, 3[bx]
    mov dl, byte ptr [bx]
    mov dh, 0
    ; 销售价*折扣
    mul dx
    mov cx, 10
    ; 除以 10
    div cx
    ; 结果放在 cx
    mov cx, ax
    mov ax, 1[bx]
    mov dx, 128
    mul dx
    mov dx, 0
    div cx

    mov cx, ax
    mov ax, word ptr 7[bx]
    mov dx, 128
    mul dx
    mov dx, 0
    div word ptr 5[bx]
    add ax, cx

    mov word ptr 9[bx], ax
    jmp print_basic_info
    ;cmp ax, 100
    ;jg print_A
    ;cmp ax, 50
    ;jg print_B
    ;cmp ax, 10
    ;jg print_C
    ;jmp print_F


function3:
    call print_menu
    mov ah, 1
    int 21h

    mov in_choice, al

    ; 查询商品信息
    cmp al, '1'
    je query
    ; 修改商品信息
    cmp al, '2'
    je query

    ; 计算推荐度
    cmp al, '3'
    je fuc3
    cmp al, '4'
    je fuc4
    cmp al, '5'
    je fuc5
    cmp al, '6'
    je exit
    jmp fuction3
fuc3:
    call fuction3
    jmp function3
fuc4:
    call fuction4
    jmp function3
fuc5:
    call newline
    call fuction5
    jmp function3




print_basic_info:
    ; 商品名字
    lea dx, goodname
    mov ah, 9
    int 21h

    lea dx, in_item+2
    mov ah, 9
    int 21h

    mov si, bx
    ;折扣
    lea dx, discount
    mov ah, 9
    int 21h

    mov dl, byte ptr 0[si]
    mov dh, 0
    call dispdec
    ;销售价
    lea dx, price
    mov ah, 9
    int 21h

    mov dx, 1[si]
    call dispdec

    
    ;进货总数
    lea dx, quanity
    mov ah, 9
    int 21h

    mov dx, 5[si]
    call dispdec
    ;以售数量
    lea dx, sold_num
    mov ah, 9
    int 21h

    mov dx, 7[si]
    call dispdec
    
    ;推荐度
    lea dx, recommend_level
    mov ah, 9
    int 21h

    cmp word ptr 9[si], 100
    jg print_A
    cmp word ptr 9[si], 50
    jg print_B
    cmp word ptr 9[si], 10
    jg print_C
    jmp print_F
    




;显示十进制子程序
dispdec proc uses ax bx cx dx
    mov ax,dx
    xor dx,dx
    mov bx,10
    mov cx,0
a:
    cmp ax,10
    jb ok
    div bx
    add dl,30h
    push dx
    xor dx,dx
    inc cx
    jmp a
ok:
    add al,30h
    push ax
    inc cx
b:
    pop dx
    mov ah,2
    int 21h
    loop b
    ret
dispdec endp


; func: from @String to @num
; entry: edit_buf
; output: dx
transform proc
    xor ch, ch
    mov cl, edit_buf[1]
    xor dx, dx 
    mov si, 0
lop:
    push cx
    mov  ax, dx 
    mov  cl, 3
    shl  dx, cl 
    shl  ax, 1
    add  dx, ax 
    xor  ah, ah 
    mov  al, edit_buf[2+si]
    inc  si 
    sub  al, '0'
    add  dx, ax  ;dx=dx*10+ax 
    pop  cx 
    loop lop 
    ;mov  num, dx 
    ret
transform endp


print_A:
    
    mov     dl, 'A'
    mov     ah, 02h
    int     21h
    jmp     login

print_B:
    
    mov     dl, 'B'
    mov     ah, 02h
    int     21h
    jmp     login

print_C:
    
    mov     dl, 'C'
    mov     ah, 02h
    int     21h
    jmp     login

print_F:
    mov     dl, 'F'
    mov     ah, 02h
    int     21h
    jmp     login

; func: print a newline
; entry: none
; output: none
newline proc
    mov     dl, 13
    mov     ah, 02h
    int     21h

    mov     dl, 10
    mov     ah, 02h
    int     21h
    ret
newline endp


; func: print menu
; entry: menu
; output: none
print_menu proc 
    lea dx, menu    
    mov ah, 9
    int 21h
    call newline
    ret
print_menu endp

; func: test where the input is legal num
; entry: edit_buf
; output: input_filter
filter proc 
    mov bl, edit_buf[1]
    mov bh, 0
loopf:
    cmp edit_buf[bx+1], '0'
    jl fail_seg
    cmp edit_buf[bx+1], '9'
    jg fail_seg
    cmp bx, 1
    je success_seg
    dec bx
    loop loopf
fail_seg:
    mov input_filter, 0
    ret
success_seg:
    mov input_filter, 1
    ret
filter endp


edit:
    add bx, 10
    ; 商品名字
    lea dx, goodname
    mov ah, 9
    int 21h

    lea dx, in_item+2
    mov ah, 9
    int 21h

    mov di, bx
    ;折扣
dis_seg:    
    lea dx, discount
    mov ah, 9
    int 21h

    mov dl, byte ptr 0[di]
    mov dh, 0
    call dispdec

    call print_sign
    ; 用户输入新的值
    lea dx, edit_buf
    mov ah, 10
    int 21h

    call filter
    cmp input_filter, 0
    je dis_seg
    ; 将输入转化为数字
    call transform
    mov byte ptr 0[di], dl
    ;销售价
price_seg:
    lea dx, price
    mov ah, 9
    int 21h

    mov dx, 1[di]
    call dispdec

    call print_sign
    ; 用户输入新的值
    lea dx, edit_buf
    mov ah, 10
    int 21h

    call filter
    cmp input_filter, 0
    je price_seg

    ; 将输入转化为数字
    call transform
    mov word ptr 1[di], dx
    ;进货总数
quanity_seg:
    lea dx, quanity
    mov ah, 9
    int 21h

    mov dx, 5[di]
    call dispdec

    call print_sign
    ; 用户输入新的值
    lea dx, edit_buf
    mov ah, 10
    int 21h

    call filter
    cmp input_filter, 0
    je quanity_seg

    ; 将输入转化为数字
    call transform
    mov word ptr 5[di], dx
    ;以售数量
sold_num_seg:
    lea dx, sold_num
    mov ah, 9
    int 21h

    mov dx, 7[di]
    call dispdec
    
    call print_sign
    ; 用户输入新的值
    lea dx, edit_buf
    mov ah, 10
    int 21h

    call filter
    cmp input_filter, 0
    je sold_num_seg

    ; 将输入转化为数字
    call transform
    mov word ptr 7[di], dx
    ;推荐度
    lea dx, recommend_level
    mov ah, 9
    int 21h

    jmp function3


; func: print '>' symbol
; entry: none
; output: none
print_sign proc 
    mov     dl, ' '
    mov     ah, 02h
    int     21h

    mov     dl, '>'
    mov     ah, 02h
    int     21h

    mov     dl, ' '
    mov     ah, 02h
    int     21h
    ret
print_sign endp
exit:
    mov ah, 4ch
    int 21h

code ends

end start
          