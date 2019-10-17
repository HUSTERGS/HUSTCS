;***************************************************************
;* Show87 - (C) Copyright 1988, 1989 by Borland International  *
;*              Used with permission of author                 *
;***************************************************************
;
 title 'Turbo Assembler SHOW87 Program', '8087 State Display'
 page 65,72
;=============================================================================
;
; This a memory resident program to display the present state of an
; installed 8087 coprocessor.  Once assembled, to execute, type:
;
;   SHOW87 [/R]
;
; If run without any options, the program executes a DOS shell and can be
; removed from memory by typing EXIT at any DOS prompt.  If run with the
; /R option, the progam is made resident and cannot be removed (but uses
; less memory).  Uses about 5600 bytes of memory with /R, over 8000 without.
; Requires CONVERT1.INC, CONVERT2.INC, VIDEO1.INC, and VIDEO2.INC on the
; default drive/path for assembly.
;
; The hot key is ALT-7.  Traps interrupt 16H and uses only BIOS routines for
; display, thus should work on most computers with most software.
;
;
;----------------------------------------------------------------------------
;8 Ins Ptr  XXXXX | Prec      XX | ST(0) +X.XXXXXXXXXXXXXXXXX +XXXXX XXXXXX S
;0 Opr Ptr  XXXXX | Round  XXXXX | ST(1) +X.XXXXXXXXXXXXXXXXX +XXXXX XXXXXX H
;8 Op Code   XXXX | Infin  XXXXX | ST(2) +X.XXXXXXXXXXXXXXXXX +XXXXX XXXXXX O
;7 Control   XXXX |------------- | ST(3) +X.XXXXXXXXXXXXXXXXX +XXXXX XXXXXX W
;| Status    XXXX | Cond    XXXX | ST(4)    =XXXXXXXXXXXXXXXX  =XXXX XXXXXX 8
;S Tag       XXXX | Comp       X | ST(5)    =XXXXXXXXXXXXXXXX  =XXXX XXXXXX 7
;T ---------------| Test       X | ST(6)    =XXXXXXXXXXXXXXXX  =XXXX XXXXXX |
;A Stack Top    X | Exam  XXXXXX | ST(7)    =XXXXXXXXXXXXXXXX  =XXXX XXXXXX X
;T ------------------------------------------------------------------------ X
;E Except PX UX OX ZX DX IX    Intr Mask PX UX OX ZX DX IX    Ints XXXXXXXX X
;----------------------------------------------------------------------------
;
; Compare: > < = ?
; Test: + - 0 ?
; Examine:  +Unorm +NAN -Unorm -NAN +Norm +Infin -Norm -Infin +0 -0
;           +Dnorm -Dnorm Empty
; Precision: 24 53 64 ??
; Rounding:  near Up Down Trunc
; Infinity:  Proj Affin
; Interrupts: Enabled Disabled
;=========================================================================
;
Ver_Hi          equ     1       ;ones version number
Ver_Lo          equ     10      ;tens version number

HotKey          equ     7e00h   ;hot key, Alt-7
StartRow        equ     0       ;screen row offset
StartCol        equ     0       ;screen column offset
Rows            equ     12      ;rows in display
Cols            equ     76      ;columns in display

Atr_Bor         equ     07h     ;border attribute
Atr_Mes         equ     70h     ;edge text attribute
Atr_Lin         equ     07h     ;line attribute
Atr_Tex         equ     07h     ;center text attribute
Atr_Set         equ     07h     ;number and settings attribute

Sig_Bits        equ     57      ;number of significant bits in real
                                ;number display

;================================================
; Main program, execute shell after resetting
; interrupt 16H.
;================================================
;

.model TINY
.code
org 100h

;----------------- Program Entry point --------------------------
Entry:
        jmp Init                ;go to initialization

;--- switch stack and set memory allocation

Start:
        mov     bx, offset Program_Stack        ;new stack top
        mov     sp, bx                          ;switch to stack
        mov     cl, 4
        shr     bx, cl                          ;make paragraph
        inc     bx                              ;account for extra

        test    byte ptr Status, Status1        ;check if resident mode
        jnz     Main1

        mov     ah, 4ah                         ;function
        int     21h                             ;execute

;--- save the interrupt data

Main1:
        push    bx
        push    es
        mov     ax, 3516h                       ;function and interrupt number
        int     21h
        mov     word ptr Original16, bx         ;save offset
        mov     word ptr Original16+2, es       ;save segment
        pop     es
        pop     bx

;--- load the new interrupt

        mov     ax, 2516h                       ;function
        mov     dx, offset Interrupt16          ;entry point offset
        int     21h                             ;execute

        test    byte ptr Status, Status1        ;check if resident mode
        jnz     Main3

;--- initialize the EXEC parameter block and enter shell

        push    es
        push    ds
        mov     Prog_Off, sp                    ;save stack offset
        mov     Prog_Seg, ss                    ;save stack segment

        mov     ax, 4b00h
        mov     bx, offset Parameter_Blk        ;pararmeter block location
        mov     [bx+4], cs                      ;save the present segment
        mov     dx, CmdLoc                      ;program name offset
        mov     ds,cs:[2ch]                     ;             segment
        int     21h

        cli
        mov     sp, cs:Prog_Off                 ;restore stack offset
        mov     ss, cs:Prog_Seg                 ;restore stack segment
        sti
        pop     ds
        pop     es

;--- show exit message

        sub     al, al
        mov     dx, offset Closemes             ;normal termination message
        jnc     Main2
        mov     al, 0ffh
        mov     dx, offset Errormes             ;error message
Main2 :
        mov     ah, 9                           ;function
        int     21h                             ;show message

;--- finished

        push    ax                              ;save return code
        mov     ax, 2516h                       ;function
        lds     dx, Original16                  ;load original interrupt
                                                ;  location
        int     21h                             ;execute
        pop     ax

        mov     ah, 4ch                         ;exit function
        int     21h                             ;execute

;--- resident mode, terminate and stay resident

Main3 :
        mov     ax, 3100h                       ;function and return code
        mov     dx, bx                          ;paragraphs to save
        int     21h                             ;execute

;================================================
; Control recieved through interrupt 16H.

Interrupt16 proc far

;--- check if activation key
        sti                                     ;interrrupts on
        cmp     ah, 0                           ;check if key request
        je      Inter1
        cmp     ah, 1                           ;check if status request
        je      Inter2
        jmp     cs:Original16                   ;non-key request,
                                                ; transfer directly to INT 16

;--- key request, function 0

Inter1:
        pushf                                   ;flags on stack
        call    cs:Original16                   ;get key
        cmp     ax, HotKey                      ;check if activation key
        je      Inter5                          ;jump if so
        iret

;--- key status request

Inter2 :
        pushf                                   ;flags on stack
        call    cs:Original16                   ; get key status
        jz      Inter3                          ;jump if no key
        pushf                                   ;must save return flags
        cmp     ax, HotKey                      ;check if activation key
        je      Inter4                          ;jump if so
        popf                                    ;not key, restore flags
Inter3 :
        ret 2

;=== activation key detected, proceed with display

;--- status only, must toss out key

Inter4 :
        add     sp, 2                           ;throw out flags save
                                                ;  by status
        sub     ah, ah                          ;get key function
        pushf                                   ;flags on stack
        call    cs:Original16                   ;get key
        mov     ah, 1                           ;reset actual function

;--- save stack

Inter5 :
        mov     cs:Stack_Seg, ss                ;segment
        mov     cs:Stack_Off, sp                ;offset

;--- switch to local stack

        cli
        push    cs
        pop     ss                              ;set to local segment
        mov     sp, offset Local_Stack          ;set to offset
        sti

;--- save registers
        pushf
        push    ax
        push    bx
        push    cx
        push    dx
        push    di
        push    si
        push    Bp
        push    ds
        push    es

;--- initialize
        push    cs
        pop     ds                              ;set data segment
        push    cs
        pop     es                              ;set other data segment

        cli
        fnsave  State_Area                      ;save the 8087 state
        fwait                                   ;synchronize
        sti

        cld                                     ;normal direction
        mov     IntFunc, ah                     ;save the function for
                                                ;   termination
        call    Video_Init                      ;initialize display data

        call    Video_Cget                      ;get the cursor location
        mov     CurLoc, dx                      ;save it

;--- save the screen area
        mov     dh, StartRow                    ;first row
        mov     di, offset Save_Area            ;screen save area

Inter6 :
        mov     dl, StartCol                    ;first column

Inter7 :
        call    Video_Cset                      ;move cursor

        mov     ah, 8                           ;function
        mov     bh, Video_Page                  ;get the page
        push    di
        int     10h                             ;execute, get character
        pop     di
        stosw                                   ;store ah and al
        inc     dl                              ;next column

        cmp     dl, StartCol+Cols               ;check if past end
        jb      Inter7                          ;loop back if not
        inc     dh                              ;next row

        cmp     dh, StartRow+Rows               ;check if past end
        jb      Inter6                          ;loop back if not

;--- show main display

        mov     bl, Atr_Set                     ;attribute
        mov     cx, StartRow*256+StartCol       ;upper left corner
        mov     dx, ((StartRow+Rows-1)*256)+StartCol+Cols-1
                                                ;lower right corner
        call    Video_Cpag                      ;clear screen area
        mov     si, offset Display1             ;main display string
        call    Video_Wstr                      ;write to screen

;--- show stats

        call    Display_State                   ;show state

;--- wait for key

        mov     dx, ((StartRow+Rows-1)*256)+StartCol+Cols-1
                                                ;lower right corner
        call    Video_Cset                      ;move cursor there

        sub     ah, ah                          ;function number
        pushf
        call    dword ptr Original16            ;get a key

;--- restore the screen area

        mov     dh, StartRow                    ;first row
        mov     si, offset Save_Area            ;screen save area

Inter8  :
        mov     dl, StartCol                    ;first column

Inter9  :
        call    Video_Cset                      ;move cursor

        lodsw                                   ;load character
                                                ;   and attribute
        mov     bl, ah                          ;attribute
        mov     ah, 9                           ;function
        mov     bh, Video_Page                  ;get the page
        mov     cx, 1                           ;count
        push    si
        int     10h                             ;execute, get character
        pop     si

        inc     dl
        cmp     dl, StartCol+Cols               ;check if past end
        jb      Inter9                          ;loop back if not
        inc     dh                              ;next row

        cmp     dh, StartRow+Rows               ;check if past end
        jb      Inter8                          ;loop back if not

;--- finished

        mov     dx, CurLoc                      ;get cursor location
        call    Video_Cset                      ;set it

        frstor  State_Area                      ;restore state

        pop     es
        pop     ds
        pop     bp
        pop     si
        pop     di
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        popf

;--- restore original stack

        cli
        mov     ss, cs:Stack_Seg                ;segment
        mov     sp, cs:Stack_Off                ;offset
        sti

;--- transfer to interrupt 16H as if nothing had happened

        mov     ah, cs:IntFunc                  ;save the function
                                                ;  for termination
        jmp     cs:Original16                   ;transfer to INT 16
        endp                                    ;Interrupt16

;======================================================
; Display the 8087 state.
;=======================================================
Display_State proc near

;--- instruction pointer

        mov     ax, State_Area+6   ;instruction pointer, lower 16 bits
        mov     bx, State_Area+8   ;                     upper 4 bits
        mov     cl, 12
        shr     bx, cl                          ;put the bits in the bottom
        mov     cx, 5*256+16                    ;display width and base
        mov     dx, 1*256+11                    ;display location offset
        call    Display_Number                  ;display

;--- operand pointer

        mov     ax, State_Area+10   ;operand pointer, lower 16 bits
        mov     bx, State_Area+12   ;                 upper 4 bits
        push    cx
        mov     cl, 12
        shr     bx, cl                          ;put the bits in the bottom
        pop     cx
        inc     dh                              ;next row
        call    Display_Number                  ;display

;--- op code

        mov     ax, State_Area+8                ;get the op code
        and     ax, 0000011111111111b           ;mask out bits
        or      ax, 1101100000000000b           ;set implicit bits
        sub     bx, bx                          ;clear high word
        mov     ch, 4                           ;new display width
        inc     dh                              ;next row
        inc     dl                              ;next column
        call    Display_Number                  ;display

;--- control word

        mov     ax, State_Area                  ;control word
        inc     dh                              ;next row
        call    Display_Number                  ;display

;--- status word

        mov     ax, State_Area+2                ;status word
        inc     dh                              ;next row
        call    Display_Number                  ;display

;--- tag word

        mov     ax, State_Area+4                ;tag word
        inc     dh                              ;next row
        call    Display_Number                  ;display

;--- stack top

        call    Get_Stack                       ;get the stack top
        sub     ah, ah
        add     dx, 0203h                       ;add two to the rows and add
                                                ;   three to the columns
        mov     cx, 1*256+10                    ;display width and base
        call    Display_Number                  ;display

;--- precision

        mov     bl, State_Area+1                ;high word of control
        and     bl, 11b                         ;mask bits
        sub     bh, bh
        mov     cl, 2                           ;width
        mov     dx, 1*256+29                    ;display location offset
        mov     di, offset Dissta3b             ;table
        call    Display_Istr                    ;display string

;--- rounding

        mov     bl, byte ptr State_Area+1       ;high word of control
        and     bl, 1100b                       ;mask bits
        sub     bh, bh
        shr     bx, 1
        shr     bx, 1
        mov     cl, 5                           ;width
        inc     dh
        sub     dl, 3                           ;display location offset
        mov     di, offset Dissta4b             ;table
        call    Display_Istr                    ;display string

;--- infinity

        mov     bl, byte ptr State_Area+1       ;high word of control
        and     bl, 10000b                      ;mask bit
        sub     bh, bh
        mov     cl, 4
        shr     bx, cl
        mov     cl, 5                           ;width
        inc     dh                              ;next row
        mov     di, offset Dissta5b             ;table
        call    Display_Istr                    ;display string

;--- condition codes

        mov     al, byte ptr State_Area+3       ;high byte of status
        call    Adjst_Codes                     ;adjust the condition codes
        sub     bx, bx                          ;clear high word
        mov     cx, 4*256+2                     ;display width and base
        add     dx, 0201h                       ;new location
        call    Display_Number                  ;display

;--- comparison and test

        call    Get_Comp                        ;get the index
        mov     cl, 1                           ;width
        add     dx, 0103h                       ;location
        mov     di, offset Dissta1b             ;table
        call    Display_Istr                    ;display string

        inc     dh
        mov     di, offset Dissta2b             ;table
        call    Display_Istr                    ;display string

;--- examine

        mov     al, byte ptr State_Area+3       ;high byte of status
        inc     dh
        sub     dl, 5                           ;location
        call    Display_Exam                    ;display

;--- exception bit settings

        mov     al, byte ptr State_Area+2       ;get the bits
        mov     dx, 10*256+10                   ;display offset
        call    Display_Bits                    ;display

;--- mask bit settings

        mov     al, byte ptr State_Area         ;get the bits
        mov     dx, 10*256+41                   ;display offset
        call    Display_Bits                    ;display

;--- interrupts

        mov     ax, word ptr State_Area         ;control word
        shl     ax,1                            ;shift bit to high byte
        and     ah, 1b                          ;mask
        mov     bl, ah
        sub     bh, bh
        mov     cl, -8                          ;width
        mov     dx, 10*256+66                   ;display offset
        mov     di, offset Dissta6b             ;table
        call    Display_Istr                    ;display string

;--- show stack data

        call    Display_Stack                   ;show stack values
        ret

;--- data

Dissta1a db '>',0, '<',0, '=',0, '?',0
Dissta1b dw offset Dissta1a
         dw offset Dissta1a+2
         dw offset Dissta1a+4
         dw offset Dissta1a+6

Dissta2a db '+',0, '-',0, '0',0, '?',0
Dissta2b dw offset Dissta2a
         dw offset Dissta2a+2
         dw offset Dissta2a+4
         dw offset Dissta2a+6

Dissta3a db '24',0, '??',0, '53',0, '64',0
Dissta3b dw offset Dissta3a
         dw offset Dissta3a+3
         dw offset Dissta3a+6
         dw offset Dissta3a+9

Dissta4a db 'Near',0, 'Up',0, 'Down',0, 'Trunc',0
Dissta4b dw offset Dissta4a
         dw offset Dissta4a+5
         dw offset Dissta4a+8
         dw offset Dissta4a+13

Dissta5a db 'Proj',0, 'Affin',0
Dissta5b dw offset Dissta5a
         dw offset Dissta5a+5

Dissta6a db 'Enabled',0, 'Disabled',0
Dissta6b dw offset Dissta6a
         dw offset Dissta6a+8
 endp   ;Display_State

;================================================
; Display of the settings of six consecutive
; bits.
;
; In: al= bit pattern; dx= row and column display
; offset.
;==================================================
;
Display_Bits proc near
        mov     ah, al
        mov     bh, 20h                         ;first bit to check
        mov     cx, 6                           ;bits to check
        add     dx, StartRow*256+StartCol       ;real screen location

;--- loop for each bit

Disbit1 :
        mov     al, '-'                         ;not set sign
        test    ah, bh                          ;check if set
        jz      Disbit2
        mov     al, '+'                         ;set sign

Disbit2  :
        call    Display_Char                     ;display character
        shr     bh,1                             ;shift bit to test
        add     dl, 2                            ;next location
        loop    Disbit1

        ret
 endp           ;Display_Bits

;================================================
; Display the stack values.
;================================================
Display_Stack proc near
        std
        mov     bx, offset State_Area           ;save area
        add     bx, 14                          ;skip to numbers
        mov     cx, 8                           ;8087 stack entries
        mov     dh, StartRow+1                  ;first display row

;=== display a number

Disstk1 :
        push    bx
        push    cx

        fld     TBYTE PTR [bx]                  ;load number

;--- get number type or set to empty

        push    cx                              ;save stack number
        call    Get_Stack                       ;get the stack top
        mov     cl, al
        mov     ax, word ptr State_Area+4       ;get the tag word
        shl     cl,1                            ;two bits for each tag
        ror     ax, cl                          ;adjust so first tag is
                                                ;  in low bits
        pop     cx
        mov     ch, 8
        sub     ch, cl
        shl     ch, 1                           ;bits to shift to put set
                                                ;  tag low
        mov     cl, ch
        shr     ax, cl                          ;tag bits to lower bit
                                                ;  locations 0 and 1
        and     ax, 11b                         ;mask bits

;--- check type

        cmp     ax, 11b                         ;check if empty
        je      Disstk2

        fxam                                    ;check number type
        fstsw   Status87                        ;store status

        cmp     ax, 10b                         ;check if special
        je      Disstk3                         ;jump if so

;--- normal value

        call    Display_Float                   ;display decimal number
        jmp     short Disstk4

;--- empty

Disstk2  :
        mov     Status87, 0ffffh                ;set all bits

;--- special number

Disstk3   :
        call    Display_Hex                     ;display hexadecimal bit
                                                ;  pattern

;--- finished with a single stack number

Disstk4    :
        mov     al, byte ptr Status87+1         ;high byte of status
        call    Display_Exam                    ;display
        pop     cx
        pop     bx

        add     bx, 10                          ;next stack entry
        inc     dh                              ;next row
        loop    Disstk1                         ;loop for each entry

        cld
        ret
 endp           ;Display_Stack

;================================================
; Display a decimal floating point number.
;
; In: ST(0)= number; dh= row.
;
; Out: dx= row and column one space after number.
;==================================================
;
Display_Float proc near

;--- convert number and store

        mov     ax, Sig_Bits                    ;number of significant bits
        call    Flt2dec                         ;convert to decimal
        mov     si, offset Number_Store         ;storage for number
        fbstp   Tbyte Ptr [si]                  ;save number string

;--- display the mantissa sign

        push    ax                              ;save the exponent
        mov     dl, StartCol+40                 ;column

        add     si, 9                           ;goto last byte
        fwait                                   ;let fbstp finish
        lodsb                                   ;get the sign byte
        mov     ah, '+'
        test    al, 80h                         ;check if negative
        jz      Disflt1
        mov     ah, '-'
Disflt1 :
        mov     al, ah                          ;sign
        call    Display_Char                    ;display character

;--- first two digits and decimal point

        lodsb
        call    Display_Bhi                     ;high digit
        push    ax
        mov     al, '.'                         ;decimal point
        call    Display_Char                    ;write point
        pop     ax
        call    Display_Blo                     ;low digit

;--- remaining mantissa digits

        mov     cx, 8                           ;remaining number of
                                                ;  packed bytes

Disflt2 :
        lodsb
        call    Display_Bhi                     ;high digit
        call    Display_Blo                     ;low digit
        loop    Disflt2

;--- exponent sign

        pop     ax
        inc     dl                              ;skip to exponent location

        mov     cl, '+'                         ;plus
        add     ax, 17                          ;adjust for decimal point
        jns     Disflt3                         ;jump if not minus
        mov     cl, '-'                         ;minus
        neg     ax
Disflt3 :
        push    ax
        mov     al, cl
        call    Display_Char                    ;display
        pop     ax

         ;--- exponent

        sub     bx, bx                          ;clear high word
        mov     cx, 5*256+10                    ;load width and base
        call    Display_Number                  ;display
        add     dl, 6                           ;position cursor at end
        ret

;=================================================
; Display a high packed BCD digit.
;
; In: al= packed BCD digits; bl= attribute.
;==================================================
Display_Bhi proc near
        push    ax
        shr     al, 1
        shr     al, 1
        shr     al, 1
        shr     al, 1                           ;shift the high bits
        add     al, '0'                         ;convert to decimal digit
        call    Display_Char                    ;write point
        pop     ax
        ret
 endp           ;Display_Bhi

;=================================================
; Display a low packed BCD digit.
;
; In: al= packed BCD digits; bl= attribute.
;==================================================
;
Display_Blo proc near
        push    ax
        and     al, 0fh                         ;mask relevant bits
        add     al, '0'                         ;convert to decimal digit
        call    Display_Char                    ;write point
        pop     ax
        ret
 endp                   ;Display_Blo

 endp                   ;Display_Float

;================================================
; Display the bit pattern of a floating point
; number.
;
; In: ST(0)= number; dh= row.
;
; Out: dx= row and column one space after number.
;==================================================
;
Display_Hex proc near
        fstp    Dishex1                         ;store number
        fwait                                   ;wait just in case

        mov     al, '='                         ;starting character
        mov     dl, byte ptr StartCol+43        ;column
        call    Display_Char                    ;display

        mov     cx, 8                           ;bytes
        lea     si, Dishex1+7                   ;last byte of mantissa
        call    Display_Byts                    ;display

        mov     al, '='                         ;starting character
        add     dl, 2                           ;column
        call    Display_Char                    ;display

        mov     cx, 2                           ;bytes
        lea     si, Dishex1+9                   ;last byte of exponent
        call    Display_Byts                    ;display

        inc     dl                              ;next column
        ret

;--- storage for the tempory real number

Dishex1 label Tbyte
        dt ?        ;

;================================================
; Display backwards bytes.
;
; In: si= starting location; cx= bytes.
;=================================================
;
Display_Byts proc near
        pushf
        std
        sub     ah, ah                          ;clear high byte
        sub     bx, bx                          ;clear high word

Disbys1  :
        lodsb                                   ;load byte
        push    cx
        push    si
        mov     cx, 2*256+16                    ;format
        call    Display_Number                  ;display
        add     dl, 2                           ;next location
        pop     si
        pop     cx
        loop    Disbys1                         ;loop for each byte
        popf
        ret
 endp                   ;Display_Byts

 endp                   ;Display_Hex

;================================================
; Display an FXAM result.
;
; In: al= high byte of 8087 status; dx= row and
; column location.
;=================================================
;
Display_Exam proc near
        call    Adjst_Codes                     ;adjust the condition codes
        mov     bx, ax
        mov     cl, 6                           ;width
        mov     di, offset Disexm1b             ;table
        call    Display_Istr                    ;display string
        ret

;--- data

Disexm1a db '+Unorm',0, '+NAN',0, '-Unorm',0, '-NAN',0
         db '+Norm',0, '+Infin',0, '-Norm',0, '-Infin',0
         db '+0',0, '-0',0, '+Dnorm',0, '-Dnorm',0, 'Empty',0
Disexm1b dw offset Disexm1a
         dw offset Disexm1a+7
         dw offset Disexm1a+12
         dw offset Disexm1a+19
         dw offset Disexm1a+24
         dw offset Disexm1a+30
         dw offset Disexm1a+37
         dw offset Disexm1a+43
         dw offset Disexm1a+50
         dw offset Disexm1a+70
         dw offset Disexm1a+53
         dw offset Disexm1a+70
         dw offset Disexm1a+56
         dw offset Disexm1a+70
         dw offset Disexm1a+63
         dw offset Disexm1a+70

 endp           ;Display_Exam

;================================================
; Get the stack top number.
;
; Out: al= stack number.
;=================================================
;
Get_Stack proc near
        mov     al, byte ptr State_Area+3       ;get the high byte
                                                ;  of the status word
        and     al, 00111000b                   ;mask out stack
        shr     al, 1
        shr     al, 1
        shr     al, 1                           ;adjust
        ret
 endp            ;Get_Stack

;================================================
; Adjust the condition codes to consecutive bits.
;
; In: al= high byte of status.
; Out: ax= condition codes in consecutive, least
; significant bit locations.
;=================================================
;
Adjst_Codes proc near
        mov     ah, al
        and     al, 00000111b                   ;mask C2 to C0 bits
        and     ah, 01000000b                   ;mask C3 bit
        shr     ah , 1
        shr     ah , 1
        shr     ah , 1                          ;shift bit over
        or      al, ah                          ;combine
        sub     ah, ah
        ret
 endp           ;Adjst_Codes

;================================================
; Get an index for the comparison and test
; instructions. Based on the condition codes.
;
; Out: bx= index.
;==================================================
;
Get_Comp proc near
        sub     bx, bx
        mov     al, State_Area+3                ;high byte of state
        and     al, 01000101b                   ;mask C3 C2 and C0
        cmp     al, 00000000b                   ;check if 0 0 0
        je      Getcom1
        inc     bx
        cmp     al, 00000001b                   ;check if 0 0 1
        je      Getcom1
        inc     bx
        cmp     al, 01000000b                   ;check if 1 0 0
        je      Getcom1
        inc     bx

Getcom1:
        ret
 endp           ;Get_Comp

;================================================
; Display a single character.
;
; In: al= character; dx= location.
;=================================================
;
Display_Char proc near
        mov     bl, Atr_Set                     ;attribute
        call    Video_Cset                      ;set cursor location
        call    Video_Wchr                      ;write character
        inc     dl                              ;next column
        ret
 endp                   ;Display_Char

;================================================
; Display a zero padded number to a location.
;
; In: bx:ax= number; cl= number base; ch= the
; display width; dx= location.
;=================================================
;
Display_Number proc near
        push    ax
        push    cx
        push    dx
        add     dx, StartRow*256+StartCol       ;real screen location
        call    Video_Cset                      ;move cursor

        push    cx
        sub     ch, ch
        mov     dx, bx                          ;high word
        mov     di, offset Number_Store         ;place to store
        call    Convert_Num                     ;convert to string
        pop     cx

        mov     al, '0'                         ;pad character
        mov     cl, ch
        sub     ch, ch
        mov     si, di
        call    Video_Wstrr                     ;display number
        pop     dx
        pop     cx
        pop     ax
        ret
 endp           ;Display_Number

;================================================
; Given an index and a table, displays a space
; padded string to a location.
;
; In: bx= index; di= table offset; cl= width, if
; negative, the string is right justified instead
; of left; dx= location.
;=================================================
;
Display_Istr proc near
        push    ax
        push    bx
        push    cx
        push    dx
        push    si

;--- locate cursor

        add     dx, StartRow*256+StartCol       ;real screen location
        call    Video_Cset                      ;move cursor

;--- display string

        mov     al, ' '                         ;pad with spaces
        shl     bx, 1 ;                         ;two bytes for offset
        sub     ch, ch
        mov     si, [di+bx]                     ;get the string location

        cmp     cl, 0
        jg      Disist1

        neg     cl                              ;absolute value
        call    Video_Wstrl                     ;display, left justified
        jmp     short Disist2

        Disist1:
        call    Video_Wstrr                     ;display, right justified

        Disist2:
        pop     si
        pop     dx
        pop     cx
        pop     bx
        pop     ax
        ret
 endp           ;Display_Istr

;================================================
; External files.

 include Video1.inc
 include Video2.inc
 include Convert1.inc
 include Convert2.inc

;================================================
; Data.

;--- program status

Status1 equ 01h                                 ;execute in memory
                                                ;  resident mode

Status db 0

;--- original interrupt 16H

Original16 label Dword
 dw ?                   ;offset
 dw ?                   ;segment

;--- shell parameter block

Parameter_Blk label Word
 dw 0                                           ;use default environment
 dw offset CmdTail                              ;command tail
 dw ?                                           ;present segment
 dw -1                                          ;
 dw -1                                          ;
 dw -1                                          ;-- no FCB'S
 dw -1                                          ;

CmdTail db 0, 13

;--- saved stack addresses

Prog_Off dw ?           ;-- save area through EXEC function
Prog_Seg dw ?           ;

Stack_Off dw ?          ;-- save area for alternate int 16
Stack_Seg dw ?          ;

;--- other data

CmdLoc dw ?             ;offset of command processor in environment
IntFunc db ?            ;int 16 request
CurLoc dw ?             ;saved cursor location

;--- main display string

Display1 label Byte
 db FrmAtr, Atr_Bor, FrmLoc, StartRow, StartCol, 219
 db FrmHor, 223, Cols-2, 219, FrmLoc, StartRow+1, StartCol
 db FrmVer, 219, Rows-2, FrmLoc, StartRow+1, StartCol+Cols-1
 db FrmVer, 219, Rows-2, FrmLoc, StartRow+Rows-1
 db StartCol, 219, FrmHor, 220, Cols-2, 219

 db FrmAtr, Atr_Lin, FrmLoc, StartRow+9, StartCol+2
 db FrmHor, 196, 72, FrmLoc, StartRow+1, StartCol+32
 db FrmVer, 179, 8, 193

 db FrmAtr
 db Atr_Mes
 db FrmLoc, StartRow+1, StartCol, '8'
 db FrmLoc, StartRow+2, StartCol, '0'
 db FrmLoc, StartRow+3, StartCol, '8'
 db FrmLoc, StartRow+4, StartCol, '7'
 db FrmLoc, StartRow+6, StartCol, 'S'
 db FrmLoc, StartRow+7, StartCol, 'T'
 db FrmLoc, StartRow+8, StartCol, 'A'
 db FrmLoc, StartRow+9, StartCol, 'T'
 db FrmLoc, StartRow+10, StartCol, 'E'

 db FrmLoc, StartRow+1, StartCol+Cols-1, 'S'
 db FrmLoc, StartRow+2, StartCol+Cols-1, 'H'
 db FrmLoc, StartRow+3, StartCol+Cols-1, 'O'
 db FrmLoc, StartRow+4, StartCol+Cols-1, 'W'
 db FrmLoc, StartRow+5, StartCol+Cols-1, '8'
 db FrmLoc, StartRow+6, StartCol+Cols-1, '7'
 db FrmLoc, StartRow+8, StartCol+Cols-1, Ver_Hi MOD 10+'0'  ;
 db FrmLoc, StartRow+9, StartCol+Cols-1, Ver_Lo/10+'0'
 db FrmLoc, StartRow+10, StartCol+Cols-1, Ver_Lo MOD 10+'0' ;

 db FrmAtr, Atr_Tex
 db FrmLoc, StartRow+1, StartCol+2, 'Ins Ptr'
 db FrmLoc, StartRow+2, StartCol+2, 'Opr Ptr'
 db FrmLoc, StartRow+3, StartCol+2, 'Op Code'
 db FrmLoc, StartRow+4, StartCol+2, 'Control'
 db FrmLoc, StartRow+5, StartCol+2, 'Status'
 db FrmLoc, StartRow+6, StartCol+2, 'Tag'

 db FrmLoc, StartRow+8, StartCol+2, 'Stack Top'

 db FrmLoc, StartRow+1, StartCol+19, 'Prec'
 db FrmLoc, StartRow+2, StartCol+19, 'Round'
 db FrmLoc, StartRow+3, StartCol+19, 'Infin'

 db FrmLoc, StartRow+5, StartCol+19, 'Cond'
 db FrmLoc, StartRow+6, StartCol+19, 'Comp'
 db FrmLoc, StartRow+7, StartCol+19, 'Test'
 db FrmLoc, StartRow+8, StartCol+19, 'Exam'

 db FrmLoc, StartRow+1, StartCol+34, 'ST(0)'
 db FrmLoc, StartRow+2, StartCol+34, 'ST(1)'
 db FrmLoc, StartRow+3, StartCol+34, 'ST(2)'
 db FrmLoc, StartRow+4, StartCol+34, 'ST(3)'
 db FrmLoc, StartRow+5, StartCol+34, 'ST(4)'
 db FrmLoc, StartRow+6, StartCol+34, 'ST(5)'
 db FrmLoc, StartRow+7, StartCol+34, 'ST(6)'
 db FrmLoc, StartRow+8, StartCol+34, 'ST(7)'

 db FrmLoc, StartRow+10, StartCol+2, 'Except'
 db FrmLoc, StartRow+10, StartCol+9, FrmStr
 dw offset Display2
 db FrmLoc, StartRow+10, StartCol+30, 'Intr Mask'
 db FrmLoc, StartRow+10, StartCol+40, FrmStr
 dw offset Display2
 db FrmLoc, StartRow+10, StartCol+61, 'Ints'


 db FrmAtr, Atr_Set
 db 0

Display2 db 'P  U  O  Z  D  I', 0

;--- exit message

Closemes db 13,10,'SHOW87 is removed from memory.',13,10,'$'
Errormes db 13,10,'Error: Could not install SHOW87', 13,10,'$'

;================================================
; Uninitialized data.

Save_Area label Byte                            ;screen data
        org $+(Rows * Cols * 2)
State_Area label UNKNOWN                        ;area to save the 8087 state
        org $+94
Status87 label Word                             ;8087 status storage for
                                                ;  checking numbers
        org $+2
Number_Store label Byte                         ;storage for decimal
                                                ;  number strings
        org $+11
        org $+100h
Local_Stack label Byte                          ;local stack for state display
        org $+100h
Program_Stack label Byte                        ;main program stack

        org offset Save_Area                    ;fix location

;================================================
; Transient code.  Exists in unitialized data
; area, must be executed before the data area is
; used.

;--- display opening message

Init :
        mov     dx, offset Openmes              ;message
        mov     ah, 9                           ;function
        int     21h                             ;display

;--- check for 80x87 installed
        call    Installed8087                   ;check for 80x87
        cmp     ax, 1                           ;ax=1 if 80x87 installed
        je      Init0                           ; else 80x87 is NOT installed
        mov     dx, offset No8087mes
        mov     ah, 9                           ;display message indicating
        int     21h                             ;that no 80x87 is installed
        jmp     short Init8

;--- find command processor
Init0 :
        push    es
        mov     cx, 8                           ;string length
        sub     di, di                          ;starting offset of environment
        mov     es, cs:[2ch]                    ;environment segment

;--- loop for each string in the environment

Init1 :
        cmp     byte ptr es:[di], 0             ;check if end of environment
        je      Init8

        mov     cx, 8                           ;string length
        mov     si, offset Comspec              ;string location

        repe
        cmpsb                                   ;compare bytes
        je      Init3                           ;jump if found

Init2 :
        cmp     byte ptr es:[di-1], 0           ;see if stopped on end
                                                ;  of string
        je      Init1
        inc     di                              ;next byte
        jmp     Init2

Init3  :
        mov     CmdLoc, di                      ;save location
        pop     es

;--- set resident flag

        mov     si, 80h                         ;command tail
        lodsb                                   ;get the length
        or      al, al                          ;check if none
        jz      Init6
        mov     cl, al
        sub     ch, ch                          ;put count in cx

;--- loop through characters in command tail

Init4 :
        lodsb                                   ;load next byte
        cmp     al, '/'                         ;check if switch
        je      Init7                           ;jump if so
Init5 :
        loop    Init4                           ;otherwise loop back

Init6:
        jmp     Start

;--- found slash

Init7:
        dec     cx                              ;reduce count
        jz      Init6                           ;jump if no more bytes

        lodsb                                   ;load command character
        sub     al, 'a'-'A'                     ;convert to upper-case
        cmp     al, 'R'                         ;check if R
        jne     Init5                           ;if not, go back to loop
        xor     Status, Status1                 ;set (or clear) flag
        jmp     Start

;--- could not find COMSPEC=

Init8:
        mov     dx, offset Errormes             ;error message
        mov     ah, 9                           ;function
        int     21h                             ;show message

        mov     ax, 4cffh                       ;exit function
        int     21h                             ;execute

;=========================================================
;returns true if an 8087 or 80x87 coprocessor is installed
;=========================================================
Installed8087   proc near
	int	11h				;get BIOS equipment flags
	and	ax, 2			;bit is ON if 80x87 is present
	shr	ax, 1
	ret
Installed8087   endp

;--- transient data

Openmes db 13,10
        db 'SHOW87, Version '
        db Ver_Hi MOD 10+'0', '.', Ver_Lo/10+'0', Ver_Lo MOD 10+'0','$'
No8087mes db 13,10
          db 'No numeric processor detected',13,10,'$'

;--- command environment string

Comspec db 'COMSPEC='

END Entry
