
;   FILENAME: IWRITEPS.ASM
;
;   Copyright (c) 1988, 1992 by Borland International, Inc.
;
;   DESCRIPTION: This module implements a routine that displays Turbo Pascal
;   style strings. The module uses Ideal mode syntax.
;
;   ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;   TASM command line.
;
;       TASM /dMDL=memorymodel iwriteps
;
;   'memorymodel' in the above command line may be replaced by TINY, SMALL,
;   MEDIUM, COMPACT, LARGE or HUGE. If assembling this module to run on
;   a 286/386 machine, turn on the P286 directive in order to take advantage of
;   286/386 specific instructions. For example:
;
;       TASM /dMDL=memorymodel /jP286 iwriteps
;
;   NOTE: This module requires that main program define the identifier
;   DisplayPage and initialize it.

%tabsize 4

ifndef  MDL
    display "Error: This module requires that you provide a memory model"
    display "       definition on the command line. I.E. /dMDL=SMALL."
    err ; Force a fatal error
else

    ideal                       ; Use TASM's Ideal mode
%   model   MDL             ; Define the memory model

    include "imacros.mac"
    include "dos.inc"
    include "idos.mac"      ; Include DOS interface macros
    include "ibios.mac"
    include "bios.inc"

    dataseg
    global  DisplayPage:byte        ; declare extrn variable

    codeseg

    global  WritePascalString:proc  ; declare public proc

    proc    WritePascalString

    ;   This routine displays a string to the screen by calling the BIOS
    ;   service to display a character in TTY mode. It expects a far pointer
    ;   to the string to be passed on the stack. Note that the length of the
    ;   string is limited to 255 bytes.
    ;
    ;   Input
    ;       StrAddress - Far pointer to string to display
    ;   Output
    ;       none
    ;   Calling convention
    ;       Pascal
    ;   Registers modified
    ;       di, es, Flags

    ARG StrAddress:dword=ParamSize  ; Define parameters passed on the stack

        push    bp
        mov     bp, sp
        xor     cx, cx
        les     di, [StrAddress]    ; Get the address of the string
        mov     cl, [byte es:di]    ; Get the length of the string
        inc     di                  ; Point to the first character to display
        jcxz    Exit
    DisplayChar:                    ; Display the next character
        CharacterOutput <[byte es:di]>
        inc     di                  ; Point to the next character
        loop    DisplayChar
    Exit:
        pop     bp
        ret     ParamSize           ; Clean up the stack since we're using
                                    ; Pascal calling conventions
    endp    WritePascalString

endif   ; ifndef MDL

end
