
;   FILENAME: ILOCSTRG.ASM
;
;   Copyright (c) 1988, 1992 by Borland International, Inc.
;
;   DESCRIPTION: This module implements a routine that searches the current
;   data segment looking for the nth string. The strings must be in Turbo
;   Pascal format(i.e. must have a preceeding length byte) and must be
;   consecutive.
;
;   ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;   TASM command line.
;
;       TASM /dMDL=memorymodel ilocstrg
;
;   'memorymodel' in the above command line may be replaced by TINY, SMALL,
;   MEDIUM, COMPACT, LARGE or HUGE. If assembling this module to run on
;   a 286/386 machine, turn on the P286 directive in order to take advantage
;   of 286/386 specific instructions. For example:
;
;       TASM /dMDL=memorymodel /jP286 ilocstrg

%tabsize 4

ifndef  MDL
    display "Error: This module requires that you provide a memory model"
    display "       definition on the command line. I.E. /dMDL=SMALL."
    err ; Force a fatal error
else

    ideal               ; Use TASM's Ideal mode
%   model   MDL         ; Define the memory model

    include "imacros.mac"
    include "ibios.mac"
    include "bios.inc"

    codeseg

    global  LocateString:proc       ; Declare public proc

    proc    LocateString

    ;   This procedure determines the offset of the error message referenced
    ;   by the value in AX. It returns a near pointer to the string in di.
    ;
    ;   Input
    ;       al - Message to find
    ;       es:di - Far pointer to location to start search
    ;   Output
    ;       es:di - Far pointer to start of string
    ;   Calling conventions
    ;       NA
    ;   Registers modified
    ;       bl, cl, di, es, Flags

        mov     bl, 1               ; Use bl as a counter of how many strings
                                    ; we've found
        xor     cl, cl              ; Initialize cl

    NextString:
        cmp     bl, al              ; Check if we've found the string we're
        je      Exit                ; looking for. If it is, leave.

        mov     cl, [BYTE es:di]    ; Get length byte of the next string
        inc     cl

        ; Find the end of the string

    NextChar:
        inc     di                  ; Point to the next character
        loop    NextChar

        inc     bl                  ; Increment the string counter
        jmp     NextString          ; Find the next string

    Exit:
        ret
    endp    LocateString

endif   ; ifndef MDL

end
