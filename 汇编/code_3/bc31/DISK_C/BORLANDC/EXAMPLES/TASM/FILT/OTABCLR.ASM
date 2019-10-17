
;    FILENAME: OTABCLR.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine TabClear. TabClear 
;    clears all tab stops. 
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM otabclr

include globals.inc

_TEXT   segment

    TabClear proc

    ;    This procedure clears all tab stops contained in the input file.
    ;
    ;    Input
    ;        TabTbl - starting location of the TAB table
    ;        MAXLIN - maximum line length
    ;    Output
    ;        TabTbl - cleared and set to null
    ;    Registers modified
    ;        none

    push      ax
    push      cx
    push      di
    sub       al, al          ;zero
                              ;number of entries
    mov       cx, MAXLIN      
    lea       di, TabTbl      ;table location
    rep       stosb           ;fill table
    pop       di
    pop       cx
    pop       ax
    ret
    TabClear  endp
_TEXT    ends

end
