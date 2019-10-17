
;   FILENAME: ISKPWHIT.ASM
;
;   Copyright (c) 1988, 1992 by Borland International, Inc.
;
;   DESCRIPTION: This module implements a routine that advances the pointer
;   es:di past any spaces(20h) in a string. This module uses ideal mode syntax.
;
;   ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;   TASM command line.
;
;       TASM /dMDL=memorymodel iskpwhit
;
;   'memorymodel' in the above command line may be replaced by TINY, SMALL,
;   MEDIUM, COMPACT, LARGE or HUGE.
;
;   NOTE: This module requires that the main program declare and initialize
;   the global variable PspAddress.

%tabsize 4

ifndef  MDL
    display "Error: This module requires that you provide a memory model"
    display "       definition on the command line. I.E. /dMDL=SMALL."
    err ; Force a fatal error
else

    ideal                           ; Use TASM's Ideal mode
%   model   MDL                     ; Define the memory model

    include "kbd.inc"

    codeseg

    global  SkipSpaces:proc         ; Declare global proc

    proc    SkipSpaces

    ;   This routine advances es:di past any spaces in the string currently
    ;   being pointed at.
    ;
    ;   Input
    ;       StrAddress - far pointer to string
    ;       cx - maximum number of bytes to search
    ;   Output
    ;       StrAddress - points to next non-space(20h) character in string
    ;       cx - bytes left un-searched
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       al, cx, di, es, Flags

    arg StrAddress:DWORD

        push    bp
        mov     bp, sp
        les     di, [StrAddress]        ; Get the address of the string
        mov     al, SPACE
        cld
        repe    scasb
        dec     di
        mov     [word StrAddress], di
        mov     [word StrAddress + 2], es
                                        ; Adjust pointer and counter because
        inc     cx                      ; scasb goes one too far
        pop     bp
        ret                             ; Leave the pointer on the stack
    endp    SkipSpaces

endif   ; ifndef MDL

end
