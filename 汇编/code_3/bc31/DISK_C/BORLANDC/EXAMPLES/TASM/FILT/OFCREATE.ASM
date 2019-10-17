
;    FILENAME: OFCREATE.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine FileCreate. FileCreate
;    creates or truncates a file. The file is opened for writing.
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM ofcreate

include globals.inc

_TEXT   segment

    FileCreate proc

    ;    Input 
    ;        bx - file record offset
    ;        cx - buffer size
    ;        dx - offset of filespec
    ;    Output (of INT 21h, Function 3Ch)
    ;        cf - set if error occurred
    ;        ax - error code
    ;            3 - if path not found
    ;            4 - if no handle available
    ;            5 - if access denied
    ;    Registers modified 
    ;        ax

    mov     WORD PTR [bx], 1  ;set status
    mov     [bx+2], cx        ;save size
    call    FileAlloc         ;allocate buffer
    jc      filcre1           ;jump if error
    mov     ah, 3ch           ;function
    sub     cx, cx            ;file attribute - 00h normal
    int     21h               ;execute
    mov     [bx+8], ax        ;save handle
    jnc     filcre1
    call    FileFree          ;deallocate buffer
    stc
filcre1:
    ret
    FileCreate endp

_TEXT    ends

end
