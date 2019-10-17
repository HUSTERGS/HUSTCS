extern fuction3 : near
extern fuction4 : near
extern fuction5 : near
public item1
.386

print MACRO string
    push dx
    push ax
    lea dx, string
    mov ah, 9
    int 21h
    pop ax
    pop dx
ENDM
scanf MACRO destination
    push dx
    push ax
    lea dx, destination
    mov ah, 10
    int 21h
    pop ax
    pop dx
ENDM
print_symbol MACRO symbol
    push dx
    push ax
    mov     dl, ' '
    mov     ah, 02h
    int     21h

    mov     dl, symbol
    mov     ah, 02h
    int     21h

    mov     dl, ' '
    mov     ah, 02h
    int     21h
    pop ax
    pop dx
ENDM

stack   segment use16 stack
        db 500 dup(0)
stack   ends

data   segment use16 para public 'DATA'
        ;Bname           db 'GESONG'
        Bname           db  6 xor 'N',
                           'G' xor 'l', 
                           'E' xor 'u', 
                           'S' xor 'l', 
                           'O' xor 'a', 
                           'N' xor 'l', 
                           'G' xor 'a'
        Bpassword       db 6 xor 'P',
                           ('l' - 29h) * 3,
                           ('u' - 29h) * 3,
                           ('l' - 29h) * 3,
                           ('a' - 29h) * 3,
                           ('l' - 29h) * 3,
                           ('a' - 29h) * 3
        Sname           db 0aH, 0dH, 'shop', '$'
        N               equ 2

        boss_menu       db 0ah, 0dh, 'Please choose your action', 
                           0ah, 0dh, '1. search',
                           0ah, 0dh, '2. edit',
                           0ah, 0dh, '3. calculate',
                           0ah, 0dh, '4. rank',
                           0ah, 0dh, '5. print all goods',
                           0ah, 0dh, '6. exit',
                           0ah, 0dh,
                           '$'

        customer_menu   db 0ah, 0dh, 'Please choose your action', 
                           0ah, 0dh, '1. search',
                           0ah, 0dh, '6. exit',
                           0ah, 0dh,
                           '$'

        goodname        db  0ah, 0dh, 'name: ', '$'
        discount        db  0ah, 0dh, 'discount: ', '$'
        price           db  0ah, 0dh, 'price: ', '$'
        quanity         db  0ah, 0dh, 'quanity: ', '$'
        sold_num        db  0ah, 0dh, 'sold_num: ', '$'
        recommend_level db  0ah, 0dh, 'recommend_level: ', '$'

        username_hint   db 0ah, 0dh, 'Please enter your username', '$'
        password_hint   db 0ah, 0dh, 'Please enter your password', '$'
        fail_hint       db 0ah, 0dh, 'Auth fail, wrong username or password. Total fail time: ', '$'
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
                        dw 35 xor 'G', 56, 70, 25, ?
        item2           db 'book', 6 dup(0), 9
                        dw 12 xor 'G', 30, 25, 5, ?
        ;rest_items      db N-2 dup('Temp-Value',8, 15, 0, 20, 0, 30, 0, 2, 0, ?, ?)
        item_size       dw 21
        auth            dw 0
        input_filter    dw 0
        item_found      dw 0
        fail_time       db '0'

        OLDINT1 DW 0,0  ;1 号中断的原中断矢量(用于中断矢量表反跟踪)
        OLDINT3 DW 0,0  ;3 号中断的原中断矢量
data ends

code segment use16 para public 'CODE'
     assume cs:code, ds:data, ss:stack

start:  mov ax, data
        mov ds, ax
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        ;xor  ax,ax                  ;接管调试用中断，中断矢量表反跟踪
        ;mov  es,ax
        ;mov  ax,es:[1*4]            ;保存原1号和3号中断矢量
        ;mov  OLDINT1,ax
        ;mov  ax,es:[1*4+2]
        ;mov  OLDINT1+2,ax
        ;mov  ax,es:[3*4]
        ;mov  OLDINT3,ax
        ;mov  ax,es:[3*4+2]
        ;mov  OLDINT3+2,ax
        ;cli                           ;设置新的中断矢量
        ;mov  ax,OFFSET NEWINT
        ;mov  es:[1*4],ax
        ;mov  es:[1*4+2],cs
        ;mov  es:[3*4],ax
        ;mov  es:[3*4+2],cs
        ;sti
        ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;




        call login

        ;mov bx,es:[1*4]
        ;cmp bx, offset NEWINT
        ;jne exit


        call function3

login proc  ;show the name of my shop
    pusha
    mov fail_time, '0'
login_start:
    cmp fail_time, '3'
    je login_return
    mov auth, 0
    call newline
    print Sname
    ; show the hint for users to enter their username
    print username_hint
    call newline
    
    ; user input username
    scanf in_name
    

    mov si, offset in_name
    ; if the input is 'q', then quit
    cmp byte ptr 2[si], 'q'
    je exit
    ; if the input is '\n', then begin query
    cmp byte ptr 2[si], 13
    je login_return
    call check_username_and_pwd
    cmp auth, 1
    je login_return
    jmp login_start
login_return:
    popa
    ret
login endp


check_username_and_pwd proc
    ; check the username
    ; the length of the input is stored in cx

    ;;;;;;;;;;;;;;;;;;;;;;;;
    ;cli
    ;;计时反跟踪开始
    ;mov ah,2ch
    ;int 21h
    ;push dx
    ;保存获取的秒和百分秒
    ;;;;;;;;;;;;;;;;;;;;;;;;


    movzx cx, in_name + 1
    movzx bx, Bname
    xor bx, 'N'
    cmp cx, bx
    jne auth_fail

    ;;;;;;;;;;;;;;;;;
    ;mov ah, 2ch
    ;int 21h
    ;sti
    ;cmp dx, [esp]
    ;pop dx
    ;jnz exit
    ;;;;;;;;;;;;;;;;;

    ;mov si, offset in_name
    ;mov di, offset Bname
    ;inc di
    
    xor in_name + 2, 'l'
    xor in_name + 3, 'u'
    xor in_name + 4, 'l'
    xor in_name + 5, 'a'
    xor in_name + 6, 'l'
    xor in_name + 7, 'a'
    
    movzx cx, in_name + 1
    mov bx, 0
    loopa:  movzx ax, in_name + 2[bx]
            cmp al, Bname + 1[bx]
            jne  auth_fail
            inc bx
            cmp cx, bx
            jne loopa
    

    ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    print password_hint
    call newline

    scanf in_pwd
    ; check the password
    ; the length of the input is stored in cx


    ;;;;;;;;;;;;;;;;;;;;;;;;
    ;cli
    ;;计时反跟踪开始
    ;mov ah,2ch
    ;int 21h
    ;push dx
    ;;保存获取的秒和百分秒
    ;;;;;;;;;;;;;;;;;;;;;;;;;

    mov cl, in_pwd + 1
    mov ch, 0
    movzx bx, Bpassword
    xor bx, 'P'
    cmp cx, bx
    jne auth_fail

    ;;;;;;;;;;;;;;;;;
    ;mov ah, 2ch
    ;int 21h
    ;sti
    ;cmp dx, [esp]
    ;pop dx
    ;jnz exit
    ;;;;;;;;;;;;;;;;;

    inc di
    mov bx, 0
    mov dl, 3
    movzx cx, in_pwd + 1
    loopb:  movzx ax, in_pwd + 2[bx]
            sub ax, 29h
            mul dl
            cmp al, Bpassword + 1[bx]
            jne  auth_fail

            inc bx
            cmp cx, bx
            jne loopb
    mov auth, 1
    ret
auth_fail:
    mov auth, 0
    inc fail_time
    print fail_hint
    print_symbol fail_time
    ret
check_username_and_pwd endp


        


; bx 存放查找到的商品的首地址
query proc
query_start:
    mov item_found, 0
    print query_hint
    call newline
    scanf in_item
    mov si, offset in_item
    ; if the input is \n return to login func
    cmp byte ptr 2[si], 13
    je query_return
    
    mov bx, offset item1
    mov cx, 0
query_loop:
    call compare_item
    cmp item_found, 1
    je query_return
    call next_item
    cmp cx, N
    jne query_loop
    jmp query_start
query_return:
    ret
query endp


next_item proc
    ; the cx = N, then it means didn't find, back to query func
    inc cx
    mov bx, di
    add bx, item_size
    ret
next_item endp

compare_item proc 
    push cx
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
    jmp compare_item_return
check_item_length:
    mov cl, in_item + 1
    mov ch, 0
    cmp bx, cx
    je find_item
    jmp compare_item_return
find_item:
    mov item_found, 1
    mov bx, di
compare_item_return:
    pop cx
    ret
compare_item endp
; check the length of the input


fuction1 proc
    pusha
    call query
    cmp item_found, 1
    je fuction1_item_found
    popa
    ret
fuction1_item_found:
    call calculate
    call print_basic_info
    popa
    ret
fuction1 endp

fuction2 proc
    pusha
    call query
    cmp item_found, 1
    je fuction2_item_found
    popa
    ret
fuction2_item_found:
    call edit
    popa
    ret
fuction2 endp


calculate proc
    pusha

    add bx, 10
    mov ax, 3[bx]
    xor ax, 'G'
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

    popa
    ret
calculate endp

function3 proc
    pusha
function3_start:
    cmp auth, 0
    je customer
    jmp boss
customer:
    print customer_menu
    mov ah, 1
    int 21h
    mov in_choice, al
    ; 查询商品信息
    cmp al, '1'
    je fuc1
    cmp al, '6'
    je exit
    jmp function3_start
boss:
    print boss_menu
    mov ah, 1
    int 21h
    mov in_choice, al
    
    ; 查询商品信息
    cmp al, '1'
    je fuc1
    ; 修改商品信息
    cmp al, '2'
    je fuc2
    ; 计算推荐度
    cmp al, '3'
    je fuc3
    cmp al, '4'
    je fuc4
    cmp al, '5'
    je fuc5
    cmp al, '6'
    je exit
    jmp function3_start
fuc1:
    call fuction1
    jmp function3_start
fuc2:
    call fuction2
    jmp function3_start
fuc3:
    call fuction3
    jmp function3_start
fuc4:
    call fuction4
    jmp function3_start
fuc5:
    call newline
    call fuction5
    jmp function3_start

    popa
    ret
function3 endp


print_basic_info proc
    pusha
    ; 商品名字
    add bx, 10
    print goodname
    print in_item+2
    mov si, bx
    ;折扣
    print discount
    mov dl, byte ptr 0[si]
    mov dh, 0
    call dispdec
    ;销售价
    print price
    mov dx, 3[si]
    call dispdec

    ;进货总数
    print quanity
    mov dx, 5[si]
    call dispdec
    ;以售数量
    print sold_num
    mov dx, 7[si]
    call dispdec
    
    ;推荐度
    print recommend_level
    cmp word ptr 9[si], 100
    jg print_A
    cmp word ptr 9[si], 50
    jg print_B
    cmp word ptr 9[si], 10
    jg print_C
    jmp print_F
print_A:
    print_symbol 'A'
    jmp print_basic_info_return
print_B:
    print_symbol 'B'
    jmp print_basic_info_return
print_C:
    print_symbol 'C'
    jmp print_basic_info_return
print_F:
    print_symbol 'F'
print_basic_info_return:
    popa
    ret
print_basic_info endp




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
    jmp loopf
fail_seg:
    mov input_filter, 0
    ret
success_seg:
    mov input_filter, 1
    ret
filter endp


edit proc
    add bx, 10
    ; 商品名字
    print goodname
    print in_item+2
    mov di, bx
    ;折扣
dis_seg:    
    print discount

    mov dl, byte ptr 0[di]
    mov dh, 0
    call dispdec

    print_symbol '>'
    ; 用户输入新的值
    scanf edit_buf

    call filter
    cmp input_filter, 0
    je dis_seg
    ; 将输入转化为数字
    call transform
    mov byte ptr 0[di], dl
    ;销售价
price_seg:
    print price

    mov dx, 1[di]
    call dispdec

    print_symbol '>'
    ; 用户输入新的值
    scanf edit_buf

    call filter
    cmp input_filter, 0
    je price_seg

    ; 将输入转化为数字
    call transform
    mov word ptr 1[di], dx
    ;进货总数
quanity_seg:
    print quanity

    mov dx, 5[di]
    call dispdec

    print_symbol '>'
    ; 用户输入新的值
    scanf edit_buf

    call filter
    cmp input_filter, 0
    je quanity_seg

    ; 将输入转化为数字
    call transform
    mov word ptr 5[di], dx
    ;以售数量
sold_num_seg:
    print sold_num

    mov dx, 7[di]
    call dispdec
    
    print_symbol '>'
    ; 用户输入新的值
    scanf edit_buf

    call filter
    cmp input_filter, 0
    je sold_num_seg

    ; 将输入转化为数字
    call transform
    mov word ptr 7[di], dx
    ;推荐度
    ret

edit endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
NEWINT: iret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


exit:
    ;;;;;;;;;;;;;;;;;;;;;;;;;;
    ;cli                           ;还原中断矢量
    ;mov  ax,OLDINT1
    ;mov  es:[1*4],ax
    ;mov  ax,OLDINT1+2
    ;mov  es:[1*4+2],ax
    ;mov  ax,OLDINT3
    ;mov  es:[3*4],ax
    ;mov  ax,OLDINT3+2
    ;mov  es:[3*4+2],ax 
    ;sti
    ;;;;;;;;;;;;;;;;;;;;;;;;;;
    mov ah, 4ch
    int 21h

code ends

end start
          