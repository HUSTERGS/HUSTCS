
;    FILENAME: OFILEFIL.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine FileFill. FileFill
;    fills a read buffer. 
;
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM ofilefil

include globals.inc


_TEXT   segment

    FileFill proc

    ;    Input 
    ;        bx - file record offset
    ;        cx - buffer size
    ;        dx - offset of filespec
    ;    Output (of INT 21h, Function 3Fh)
    ;        cf - set if error occurred
    ;        ax - error code
    ;            0 - if EOF and 0 bytes are read
    ;            5 - if access denied
    ;            6 - if handle invalid or not open
    ;    Registers modified
    ;        ax

    push    cx
    push    dx
    push    bx
    push    ds
    mov     ax, [bx+8]      ;file handle
    mov     cx, [bx+2]      ;buffer size
    sub     dx, dx          ;start of segment
    mov     [bx+4], dx      ;set data offset
    mov     ds, [bx+6]      ;buffer segment
    mov     bx, ax
    mov     ah, 3fh         ;function
    int     21h             ;execute
    pop     ds
    pop     bx
    mov     [bx+10], ax     ;save bytes read
    jc      filfil1
    or      ax, ax          ;check if no bytes
    jnz     filfil1
    stc
filfil1:
    pop     dx
    pop     cx
    ret
    FileFill endp

_TEXT    ends

end
