
;    FILENAME: OTABSET.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine TabSet. TabSet 
;    sets a tap stop at a specified column location. 
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM otabset

include globals.inc

_TEXT   segment

    TabSet   proc

    ;    This procedure sets a tab stop. The value passed in bx
    ;    represents the column number in which the tab is to be placed.
    ;    A tab is represented by the number 1 in the tab table.
    ;    Input
    ;        bx - column number
    ;        TabTbl - starting location of the tab table
    ;        TabEnd - ending location of the tab table
    ;    Output
    ;        TabTbl - cleared and set to null
    ;    Registers modified
    ;        none

    push    bx
    lea     bx, [TabTbl + bx]       ;get address
    cmp     bx, TabEnd              ;check if past end
    jae     tabset1
    mov     BYTE PTR [bx], 1        ;set to non-zero
tabset1:
    pop     bx
    ret
    TabSet  endp

_TEXT    ends

end
