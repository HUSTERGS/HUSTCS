
;    FILENAME: OFILALOC.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine FileAlloc. FileAlloc
;    allocates a read/write buffer.
;
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM ofilaloc

include globals.inc

_TEXT   segment

    FileAlloc proc

    ;    Input 
    ;        bx - file record offset
    ;        [bx+2] - buffer size
    ;    Output (of INT 21h, Function 48h)
    ;        cf - set if error occurred
    ;        ax - error code
    ;            7 - if memory control blocks destroyed
    ;            8 - if insufficient memory
    ;    Registers modified 
    ;        ax

    push     cx
    push     dx
    push     bx
    mov      bx, [bx+2]          ;size in bytes
    mov      cl, 4               ;paragraph shift
    shr      bx, cl              ;get size in paragraphs
    inc      bx                  ;round up
    mov      dx, bx
    shl      dx, cl              ;shift back to byte form
    mov      ah, 48h             ;function
    int      21h                 ;execute
    pop      bx
    jc       filall1
    mov      [bx+2], dx          ;save size
    mov      WORD PTR [bx+4], 0  ;clear data pointer
    mov      [bx+6], ax          ;save segment
    mov      WORD PTR [bx+10], 0 ;clear bytes in buffer
filall1:
    pop      dx
    pop      cx
    ret
    FileAlloc endp

_TEXT    ends

end
