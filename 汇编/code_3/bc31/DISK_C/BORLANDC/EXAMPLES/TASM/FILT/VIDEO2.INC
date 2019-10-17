;***************************************************************
;* Show87 - (C) Copyright 1988, 1989 by Borland International  *
;* VIDEO2.INC - Include module for Show87                      *
;***************************************************************
;
;=============================================================================
; High Level Video Routines
;
; These are routines to display formatted text strings.  All registers are
; preserved except those used to return parameters.  All parameters are passed
; through the registers.  VIDEO1.INC must be included in the source code.
; VIDEO_INIT must be called before any of these routines. It is assumed that
; DS = ES = CS.
;
;===========================================================================
; Global data.

;--- display attributes

Video_Norm      db      07h             ;normal
Video_Emph      db      02h             ;emphasized (underline)
Video_High      db      70h             ;highlight (reverse video)
Video_Bold      db      0fh             ;bold (intense)

;--- attribute stack

Video_AtrM      equ     10              ;maximum stack entries (n > 0)
Video_AtrN      dw      0               ;present stack number
Video_AtrS      db      07h             ;start of stack
  DD            Video_AtrM, ?           ;rest of stack

;--- string formatting controls

FrmEnd          equ     0               ;end of string
FrmCtl          equ     1               ;control character mask
FrmNorm         equ     2               ;switch to normal attribute
FrmEmph         equ     3               ;switch to emphasized
FrmHigh         equ     4               ;switch to highlight
FrmBold         equ     5               ;switch to bold
FrmAtr          equ     6               ;user defined attribute
FrmPush         equ     7               ;push the present attribute
FrmPop          equ     8               ;pop an attribute
FrmHor          equ     9               ;horizontally repeated character
                                        ;  (left to right)
FrmVer          equ     10              ;vertically repeated character
                                        ;   (up to down)
FrmStr          equ     11              ;nested string
FrmLoc          equ     12              ;locate cursor

Video_StrM      equ     10              ;maximum nested strings

;================================================
; Write a formatted string. Note: uses (32 =
; Video_AtrM * 2 + 14) stack bytes.
;
; In: si= string location.
;=================================================
;
Video_Wstr proc near
        pushf
        push    ax
        push    bx
        push    cx
        push    dx
        push    di
        push    si
        push    bp
        sub     sp, Video_AtrM * 2 + 2          ;room for local data
        mov     bp, sp

        cld
        mov     word ptr [bp], 0                ;clear nested string stack
        mov     di, Video_AtrN                  ;get the present stack number
        mov     bl, [Video_AtrS + di]           ;get attribute

;--- loop for each byte in the string

Vidwst1 :
        lodsb                                   ;get the next byte
        cmp     al, FrmEnd                      ;check if end of string
        je      Vidwst5
        cmp     al, 32                          ;check if control character
        jb      Vidwst2
        call    Video_Wchr                      ;write character
        jmp     Vidwst1

;--- control character

Vidwst2 :
        mov     di, offset Video_Ftab           ;location of table

Vidwst3 :
        cmp     byte ptr [di], -1               ;check if end of table
        je      Vidwst1                         ;jump if so, ignore this
                                                ;  character
        cmp     al, [di]                        ;check if match command
        je      Vidwst4                         ;jump if so, call command
                                                ;  routine
        add     di, 3                           ;next location
        jmp     Vidwst3                         ;loop back until end of table
                                                ;   or match

Vidwst4 :
        call    word ptr [di + 1]               ;call the routine
        jmp     Vidwst1

;--- check if within nested string

Vidwst5  :
        mov     ax, [bp]                        ;get the number
        or      ax, ax                          ;check if any entries
        jz      Vidwst6

        dec     ax                              ;reduce count
        mov     [bp], ax                        ;save it
        mov     di, ax
        shl     di, 1                           ;times two
        mov     si, [bp + 2 + di]               ;get the saved offset
        jmp     Vidwst1                         ;continue

;--- finished, save the attribute in the attribute stack

Vidwst6   :
        mov     di, Video_AtrN                  ;get the present stack number
        mov     [Video_AtrS + di], bl           ;save attribute

        add     sp, Video_AtrM * 2 + 2          ;fix stack
        pop     bp
        pop     si
        pop     di
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        popf
        ret
 endp           ;Video_Wfstr

;------------------------------------------------
; This is the table to access the formatting
; routines below. The table consists of a format
; command byte followed by the 16 bit address of
; the routine to handle the command.  The table
; is terminated with a -1 (FFH).
;-------------------------------------------------
Video_Ftab label Byte
 db FrmCtl
 dw offset Vidwstr1
 db FrmNorm
 dw offset Vidwstr2
 db FrmEmph
 dw offset Vidwstr3
 db FrmHigh
 dw offset Vidwstr4
 db FrmBold
 dw offset Vidwstr5
 db FrmAtr
 dw offset Vidwstr6
 db FrmPush
 dw offset Vidwstr7
 db FrmPop
 dw offset Vidwstr8
 db FrmHor
 dw offset Vidwstr9
 db FrmStr
 dw offset Vidwstr10
 db FrmLoc
 dw offset Vidwstr11
 db FrmVer
 dw offset Vidwstr12
 db -1

;------------------------------------------------
; These are the individual routines to handle
; the special formatting commands.

;--- control character mask

Vidwstr1 proc near
        lodsb                                   ;get the character
        call    Video_Wchr                      ;display
        ret
 endp

;--- normal attribute

Vidwstr2 proc near
        mov     bl, Video_Norm                  ;set to normal attribute
        ret
 endp

;--- emphasized attribute

Vidwstr3 proc near
        mov     bl, Video_Emph                  ;set to normal attribute
        ret
 endp

;--- highlighted attribute

Vidwstr4 proc near
        mov     bl, Video_High                  ;set to normal attribute
        ret
 endp

;--- bold attribute

Vidwstr5 proc near
        mov     bl, Video_Bold                  ;set to normal attribute
        ret
 endp

;--- user defined attribute

Vidwstr6 proc near
        lodsb                                   ;get the attribute
        mov     bl, al                          ;set attribute
        ret
 endp

;--- push the present attribute

Vidwstr7 proc near
        mov     ax, Video_AtrN                  ;get the present stack number
        cmp     ax, Video_AtrM - 1              ;check if stack full
        jae     Vidwstr71

        mov     di, ax                          ;load index
        mov     [Video_AtrS + di], bl           ;save the present attribute

        inc     ax                              ;increment stack
        mov     Video_AtrN, ax                  ;save it

Vidwstr71 :
        ret
 endp

;--- pop an attribute

Vidwstr8 proc near
        mov     ax, Video_AtrN                  ;get the present stack number
        or      ax, ax                          ;check if at bottom
        jz      Vidwstr81

        dec     ax                              ;reduce stack number
        mov     di, ax                          ;load index
        mov     bl, [Video_AtrS + di]           ;set the present attribute

        mov     Video_AtrN, ax                  ;save stack number
Vidwstr81 :
        ret
 endp

;--- repeat display a character

Vidwstr9 proc near
        lodsb                                   ;get the character
        push    ax
        lodsb                                   ;load the count
        mov     cl, al
        sub     ch, ch                          ;count in cx
        pop     ax
        call    Video_Wchrs                     ;display characters
        ret
 endp

;--- nested string

Vidwstr10 proc near
        lodsw                                   ;get the offset
        cmp     word ptr [bp], Video_StrM       ;check if stack full
        je      Vidwstr101

        mov     di, [bp]                        ;stack entries
        shl     di, 1                           ;times two
        mov     [bp + 2 + di], si               ;save present location
        inc     word ptr [bp]                   ;increment entries
        mov     si, ax                          ;new string location
Vidwstr101 :
        ret
 endp

;--- cursor move

Vidwstr11 proc near
        lodsw                                   ;load location
        xchg    ah, al                          ;get row and column in right
                                                ;  register halves
        mov     dx, ax
        call    Video_Cset                      ;set cursor location
        ret
 endp

;--- vertically repeated character

Vidwstr12 proc near
        lodsb                                   ;get the character
        push    ax
        lodsb                                   ;load the count
        mov     cl, al
        sub     ch, ch                          ;count in cx
        pop     ax
        call    Video_Cget                      ;get the cursor location

Vidwstr121 :
        push    dx
        call    Video_Wchr                      ;display character
        pop     dx
        inc     dh                              ;next row
        call    Video_Cset                      ;set the cursor location
        loop    Vidwstr121
        ret
 endp

;================================================
; Calculate the horizontal length of the text in
; a formatted string. Note: uses (32 =
; Video_AtrM * 2 + 10) stack bytes.  Used for
; justifying strings.
;
; In: si= string location.
;
; Out: bx= length.
;==================================================
;
Video_Scnt proc near
        push    ax
        push    di
        push    si
        push    bp
        sub     sp, Video_AtrM * 2 + 2          ;room for local data
        mov     bp, sp

        sub     bx, bx                          ;clear the count
        mov     word ptr [bp], 0                ;clear nested string stack

;--- loop for each byte in the string

Vidscn1     :
        lodsb                                   ;get the next byte
        cmp     al, FrmEnd                      ;check if end of string
        je      Vidscn8
        cmp     al, 32                          ;check if control character
        jb      Vidscn2
        inc     bx                              ;increment count
        jmp     Vidscn1

;--- control character

Vidscn2 :
        cmp     al, FrmCtl
        jne     Vidscn3
        inc     si                              ;skip character
        inc     bx                              ;add to total
        jmp     Vidscn1

;--- user attribute

Vidscn3 :
        cmp     al, FrmAtr
        jne     Vidscn4
        inc     si                              ;skip attribute byte
        jmp     Vidscn1

;--- horizontal repeated byte

Vidscn4 :
        cmp     al, FrmHor
        jne     Vidscn5
        inc     si                              ;skip character
        lodsb                                   ;load length
        sub     ah, ah
        add     bx, ax                          ;add to total
        jmp     Vidscn1

;--- nested string

Vidscn5 :
        cmp     al, FrmStr
        jne     Vidscn6
        call    Vidwstr10                       ;start nested string
        jmp     Vidscn1

;--- cursor move

Vidscn6 :
        cmp     al, FrmLoc
        jne     Vidscn7
        inc     si
        inc     si                              ;skip location
        jmp     Vidscn1

;--- vertical repeated byte

Vidscn7 :
        cmp     al, FrmVer
        jne     Vidscn1
        inc     si
        inc     si                              ;skip byte and count
        inc     bx                              ;add one for the first byte
        jmp     Vidscn1

;--- check if within nested string

Vidscn8 :
        mov     ax, [bp]                        ;get the number
        or      ax, ax                          ;check if any entries
        jz      Vidscn9

        dec     ax                              ;reduce count
        mov     [bp], ax                        ;save it
        mov     di, ax
        shl     di, 1                           ;times two
        mov     si, [bp + 2 + di]               ;get the saved offset
        jmp     Vidscn1                         ;continue

;--- finished

Vidscn9 :
        add     sp, Video_AtrM * 2 + 2          ;fix stack
        pop     bp
        pop     si
        pop     di
        pop     ax
        ret
 endp           ;Video_Scnt

;================================================
; Write a string padded with some character on
; both sides.
;
; In: si= string location; al= pad character;
; bx= left side pad number; cx= right side pad
; number.
;==================================================
;
Video_Wstrp proc near
        push    bx
        push    cx
        push    di
        mov     di, Video_AtrN                  ;get the present stack number
        push    cx
        mov     cx, bx
        mov     bl, [Video_AtrS + di]           ;get attribute
        call    Video_Wchrs                     ;write preceding spaces
        call    Video_Wstr                      ;write string
        pop     cx
        mov     bl, [Video_AtrS + di]           ;get attribute
        call    Video_Wchrs                     ;write following spaces
        pop     di
        pop     cx
        pop     bx
        ret
 endp           ;Video_Wstrp

;================================================
; Write a left justified string.
;
; In: si= string location; al= pad character;
; cx= total column width.
;===============================================
;
Video_Wstrl proc near
        pushf
        cld
        push    bx
        push    cx
        call    Video_Scnt                      ;get string width
        cmp     bx, cx                          ;check if too big
        jbe     Vidwsl1
        mov     bx, cx                          ;set to maximum length
Vidwsl1 :
        sub     cx, bx                          ;get difference
        sub     bx, bx                          ;no padding in front
        call    Video_Wstrp                     ;print with padding
        pop     cx
        pop     bx
        popf
        ret
 endp           ;Video_Wstrl

;================================================
; Write a right justified string.
;
; In: si= string location; al= pad character;
; cx= total column width.
;==================================================
;
Video_Wstrr proc near
        pushf
        cld
        push    bx
        push    cx
        call    Video_Scnt                      ;get string width
        cmp     bx, cx                          ;check if too big
        jbe     Vidwsr1
        mov     bx, cx                          ;set to maximum length
Vidwsr1  :
        sub     cx, bx                          ;get difference
        mov     bx, cx                          ;padding is before
        sub     cx, cx                          ;no padding after
        call    Video_Wstrp                     ;print with padding
        pop     cx
        pop     bx
        popf
        ret
 endp           ;Video_Wstrr

;================================================
; Write a center justified string.
;
; In: si= string location; al= pad character;
; cx= total column width.
;=================================================
;
Video_Wstrc proc near
        pushf
        cld
        push    bx
        push    cx
        call    Video_Scnt                      ;get string width
        cmp     bx, cx                          ;check if too big
        jbe     Vidwsc1
        mov     bx, cx                          ;set to maximum length
Vidwsc1   :
        sub     cx, bx                          ;get difference
        mov     bx, cx
        shr     bx, 1                           ;divide by two, preceding pad
        sub     cx, bx                          ;difference is end pad
        call    Video_Wstrp                     ;print with padding
        pop     cx
        pop     bx
        popf
        ret
 endp           ;Video_Wstrc
