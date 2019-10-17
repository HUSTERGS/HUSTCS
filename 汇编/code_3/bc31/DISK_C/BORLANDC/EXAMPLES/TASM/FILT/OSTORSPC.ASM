
;    FILENAME: OSTORSPC.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine StoreSpc. StoreSpc
;    stores any currently stored spaces.
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM ostorspc

include globals.inc

_TEXT   segment

    StoreSpc proc

    ;    Input 
    ;       SpcCnt - flag to determine if there are any spaces to store 
    ;       cx - the current byte count 
    ;       TabOff - offset into the tab table 
    ;    Output 
    ;       TabOff - the column offset is decremented by 1
    ;       SpcCnt - is set to zero 
    ;    Registers modified 
    ;       cx

    push     dx
    mov      dx, SpcCnt      ;get number of stored spaces
    or       dx, dx          ;check if any
    jz       stospc1
    call     Spaces          ;store spaces
    add      cx, dx          ;byte count
    sub      TabOff, dx      ;adjust column offset
    mov      SpcCnt, 0       ;reset space count
stospc1:
    pop      dx
    ret

    StoreSpc endp

_TEXT    ends

end
