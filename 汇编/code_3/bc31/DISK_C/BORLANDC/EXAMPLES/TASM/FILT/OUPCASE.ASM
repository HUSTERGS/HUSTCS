;    FILENAME: OUPCASE.ASM
;    Copyright (c) 1988,1989 by Borland International, Inc.
;
;    Description: This module implements the routine UpCase.  The
;    routine converts a letter to upper-case.
;    This module uses MASM mode syntax and standard segment directives.
;
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;    TASM command line.
;
;        TASM oupcase

include globals.inc

_TEXT   segment

    UpCase proc

    ;    This function returns the corresponding upper-case letter for
    ;    the lower-case letter passed in al.
    ;
    ;    Input
    ;        al - contains the ASCII value for an lower-case letter
    ;    Output
    ;        al - contains the ASCII value for the corresponding upper-case
    ;             letter            
    ;    Registers modified
    ;         al

; Convert the letter in AL to upper-case.

    cmp     al, 'a'
    jb      upcas1
    cmp     al, 'z'
    ja      upcas1
    sub     al, 'a'-'A'
upcas1:
    ret
    UpCase  endp

_TEXT    ends

end
