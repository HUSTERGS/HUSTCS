
;    FILENAME: OFOPENR.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine FileOpenR. FileOpenR
;    opens a file for reading.
;
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM ofopenr

include globals.inc

_TEXT   segment

    FileOpenR proc

    ;    Input 
    ;        bx - file record offset
    ;        cx - buffer size
    ;        dx - offset of filespec
    ;    Output (of INT 21h, Function 3Dh)
    ;        cf - set if error occurred
    ;        ax - error code
    ;            1 - if function number invalid (file-sharing must be loaded)
    ;            2 - if file not found
    ;            3 - if path not found of file doesn't exist
    ;            4 - if no handle available
    ;            5 - if access denied
    ;          0Ch - if file access code invalid
    ;    Registers modified
    ;        ax

    mov     WORD PTR [bx+0], 0  ;set status
    mov     [bx+2], cx          ;save size
    call    FileAlloc           ;allocate buffer
    jc      filopn1             ;jump if error
    mov     ax, 3d00h           ;function and access
    int     21h                 ;execute
    mov     [bx+8], ax          ;save handle
    jnc     filopn1
    call    FileFree            ;deallocate
    stc
filopn1:
    ret
    FileOpenR endp

_TEXT    ends

end
