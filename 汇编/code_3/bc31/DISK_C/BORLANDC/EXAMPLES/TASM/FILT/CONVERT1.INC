;********************************************************************
;* Show87 - Copyright (c) 1988, 1989 by Borland International, Inc. *
;* CONVERT1.INC - Include module for Show87                         *
;********************************************************************
;
;=============================================================================
; Number Conversion Routines
;
; This is a routine to convert from binary numbers to a strings. All registers
; are preservedexcept those used to return parameters. All parameters are
; passed through registers. It is assumed that DS = ES = CS.

Convert_Digs db '0123456789ABCDEF'

;================================================
; Convert a 32 bit number to a string.
;
; In: DX.AX= number to convert; CX= number base
; (1 to 16); DI= place to put string.
;================================================
Convert_Num proc near
        pushf
        push    ax
        push    bx
        push    cx
        push    dx
        push    di
        push    si
        push    bp

        sub     sp, 4
        mov     bp, sp

        cld
        mov     si, di
        push    si

;--- loop for each digit

        sub     bh, bh
        mov     word ptr [bp], ax               ;save low word
        mov     word ptr [bp+2], dx             ;save high word
        sub     si, si                          ;count digits

Connum1:
        inc     si
        mov     ax, word ptr [bp+2]             ;high word of value
        sub     dx, dx                          ;clear for divide
        div     cx                              ;divide, DX gets remainder
        mov     word ptr [bp+2], ax             ;save quotient (new high word)

        mov     ax, word ptr [bp]               ;low word of value
        div     cx                              ;divide, DX gets remainder
                                                ;  (the digit)
        mov     word ptr [bp], ax               ;save quotient (new low word)

        mov     bl, dl
        mov     al, byte ptr [Convert_Digs+bx]  ;get the digit
        stosb                                   ;store

        cmp     word ptr [bp], 0                ;check if low word zero
        jne     Connum1                         ;jump if not
        cmp     word ptr [bp+2], 0              ;check if high word zero
        jne     Connum1                         ;jump if not

        sub     al, al
        stosb                                   ;store the terminator

;--- reverse digits

        pop     cx                              ;restore start of string
        xchg    cx, si
        shr     cx, 1                           ;number of reverses
        jz      Connum3                         ;jump if none

        xchg    di, si
        sub     si, 2                           ;point to last digit

Connum2 :
        mov     al, byte ptr [di]               ;load front character
        xchg    al, byte ptr [si]               ;swap with end character
        stosb                                   ;store new front character
        dec     si                              ;back up
        loop    Connum2                         ;loop back for each digit

;--- finished

Connum3  :
        add     sp, 4
        pop     bp
        pop     si
        pop     di
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        popf
        ret
 endp           ;Convert_Num
