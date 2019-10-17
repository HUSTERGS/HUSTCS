
;    FILENAME: OSPACES.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine Spaces.  Spaces 
;    stores a specified number of spaces at particular location. 
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
;
;        TASM ospaces

include globals.inc

_TEXT   segment

    Spaces proc

    ;    This function inserts the number of spaces (20h) specified in the
    ;    dx register at the value of the location in di and returns the 
    ;    padded result in di.
    ;
    ;    Input
    ;        dx - number of spaces to insert
    ;        di - memory location to insert spaces
    ;    Output
    ;        di - memory location padded with the specified number of
    ;             spaces
    ;    Registers modified
    ;        dx, di

    push    ax
    push    cx
    mov     cx, dx          ;load count
    mov     al, ' '         ;space
    rep
    stosb                   ;store bytes
    pop     cx
    pop     ax
    ret
    Spaces  endp
_TEXT    ends

end
