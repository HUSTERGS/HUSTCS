
;    FILENAME: OTABNEXT.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine TabNext. TabNext 
;    returns the number of spaces to the next tab stop. 
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM otabnext

include globals.inc

_TEXT   segment

    TabNext  proc

    ;    This function returns the number of spaces to the next tab stop.
    ;    The value passed in cx represents the present column number.
    ;    A tab is represented by the number 1 in the tab table.
    ;    Input
    ;        cx - the present column number
    ;        TabTbl - starting location of the tab table
    ;        TabEnd - ending location of the tab table
    ;    Output
    ;        dx - number of spaces to the next tab stop
    ;        cf - set if initially started at a tab stop
    ;    Registers modified
    ;        dx

    push    bx
    push    si
    mov     bx, cx                  ;tab column
    add     bx, TabOff              ;add special offset
    lea     bx, [TabTbl + bx]       ;get starting address
    sub     dx, dx
    cmp     bx, TabEnd              ;check if at or past end
    jae     tabnex4                 ;jump if so

    mov     si, bx                  ;save starting location
    inc     bx                      ;start at next column
    inc     dx                      ;set count

;--- loop until tab stop is found or end of table

tabnex1: 
    cmp     bx, TabEnd              ;check if end
    jae     tabnex2
    cmp     BYTE PTR [bx], 0        ;check if tab
    jne     tabnex2
    inc     bx                      ;next column
    inc     dx                      ;increment count
    jmp     tabnex1                 ;loop back

;--- found tab stop

tabnex2:
    cmp     BYTE PTR [si], 0        ;check if started at tab stop
    jne     tabnex3
    pop     si
    pop     bx
    clc
    ret

;--- initial tab stop

tabnex3:
    stc
tabnex4:
    pop     si
    pop     bx
    ret
    TabNext endp

_TEXT    ends

end
