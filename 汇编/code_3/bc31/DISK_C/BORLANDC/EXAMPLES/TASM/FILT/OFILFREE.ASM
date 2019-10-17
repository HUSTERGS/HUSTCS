
;    FILENAME: OFILFREE.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine FileFree. FileFree
;    deallocates a read/write buffer.
;
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM ofilfree

include globals.inc

_TEXT   segment

    FileFree proc

    ;    Input 
    ;        bx - file record offset
    ;        [bx+2] - buffer size
    ;    Output (of INT 21h, Function 49h)
    ;        cf - set if error occurred
    ;        ax - error code
    ;            7 - if memory control blocks destroyed
    ;            9 - if incorrect segment in ES
    ;    Registers modified 
    ;        ax

    push    ax
    push    es
    mov     es, [bx+6]      ;segment
    mov     ah, 49h         ;function
    int     21h             ;execute
    pop     es
    pop     ax
    ret
    FileFree endp

_TEXT    ends

end
