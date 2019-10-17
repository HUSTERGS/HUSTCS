;   FILENAME: IASCIIZS.ASM
;
;   Copyright (c) 1988, 1992 by Borland International, Inc.
;
;   DESCRIPTION: This module implements a routine that displays ASCIIZ
;   style strings. The module uses Ideal mode syntax.
;
;   ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;   TASM command line.
;
;       TASM /m /dMDL=memorymodel iasciizs
;
;   /m in the above command line allows TASM to use extra passes to resolve
;   jumps and other operations to their shortest form and get rid of extra NOPs.
;   'memorymodel' in the above command line may be replaced by TINY, SMALL,
;   MEDIUM, COMPACT, LARGE or HUGE. If assembling this module to run on
;   a 286/386 machine, turn on the P286 directive in order to take advantage
;   of 286/386 specific instructions. For example:
;
;       TASM /m /dMDL=memorymodel /jP286 iasciizs

%tabsize 4

ifndef  MDL
    display "Error: This module requires that you provide a memory model"
    display "       definition on the command line. I.E. /dMDL=SMALL."
    err ; Force a fatal error
else

    ideal                   ; Use TASM's Ideal mode
%   model   MDL             ; Define the memory model

    include "imacros.mac"
    include "dos.inc"
    include "idos.mac"
    include "bios.inc"
    include "ibios.mac"

    dataseg
    global  DisplayPage:byte        ; declare extrn variable

    codeseg

    global  WriteASCIIZString:proc  ; declare public proc

    proc    WriteASCIIZString

    ;   This routine displays a string to the screen by calling the BIOS
    ;   service to display a character in TTY mode. It expects a far pointer
    ;   to the string to be passed on the stack.
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
        les     di, [StrAddress]    ; Get the address of the string
    DisplayChar:                    ; Display the next character
        cmp     [byte es:di], 0     ; Check for the terminating NULL character
        je      Exit
        CharacterOutput <[byte es:di]>
        inc     di                  ; Point to the next character
        jmp     DisplayChar
    Exit:
        pop     bp
        ret     ParamSize           ; Clean up the stack since we're using
                                    ; Pascal calling conventions
    endp    WriteASCIIZString

endif   ; ifndef MDL

end
