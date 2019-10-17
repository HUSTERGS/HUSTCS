;    FILENAME: OLOCASE.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine LoCase.  The
;    routine converts a letter to lower case.
;    This module uses MASM mode syntax and standard segment directives.
;
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;    TASM command line.
;
;        TASM olocase

include globals.inc

_TEXT   segment

    LoCase proc

    ;    This function returns the corresponding lowercase letter for
    ;    the uppercase letter passed in al.
    ;
    ;    Input
    ;        al - contains the ASCII value for an upppercase letter
    ;    Output
    ;        al - contains the ASCII value for the corresponding lowercase
    ;             letter            
    ;    Registers modified
    ;         al

; Convert the letter in AL to lower case.

    cmp     al, 'A'
    jb      locas1
    cmp     al, 'Z'
    ja      locas1
    add     al, 'a'-'A'
locas1:
    ret
    LoCase  endp

_TEXT    ends

end
