
;    FILENAME: OTABRSET.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine TabReset. TabReset 
;    sets tap stops every eight columns. 
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM otabrset

include globals.inc

_TEXT   segment

    TabReset proc

    ;    This procedure sets tab stops every 8 columns.   A tab is
    ;    represented by the number 1 in the tab table.
    ;    Input
    ;        TabTbl - starting location of the tab table
    ;        TabEnd - ending location of the tab table
    ;    Output
    ;        TabTbl - cleared and set to null
    ;    Registers modified
    ;        none

    call    TabClear        ;clear all tab stops first

    push    cx
    push    di
    sub     cx, cx          ;initial column count
    lea     di, TabTbl      ;table location

tabres1:
    cmp     di, TabEnd      ;check if at end
    je      tabres3
    cmp     cx, 8           ;check if at tab stop
    je      tabres2
    inc     cx
    inc     di
    jmp    tabres1

tabres2:
    mov     BYTE PTR [di], 1
    sub     cx, cx
    jmp    tabres1

tabres3:
    pop     di
    pop     cx
    ret
    TabReset  endp

_TEXT    ends

end
