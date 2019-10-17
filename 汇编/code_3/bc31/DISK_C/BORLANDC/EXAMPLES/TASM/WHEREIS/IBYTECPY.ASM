
;   FILENAME: IBYTECPY.ASM
;
;   Copyright (c) 1988, 1992 by Borland International, Inc.
;
;   DESCRIPTION: This module implements the routine ByteCopy. The routine
;   copys an array of byte values from one location in memory to another.
;   Note that the routine checks which direction it should do the copy in,
;   thus avoiding overwriting any data during the copy. This module uses
;   ideal mode syntax and simplified segment directives.
;
;   ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;   TASM command line.
;
;       TASM /dMDL=memorymodel ibytecpy
;
;   'memorymodel' in the above command line may be replaced by TINY, SMALL,
;   MEDIUM, COMPACT, LARGE or HUGE. If assembling this module to run on
;   a 286/386 machine, turn on the P286 directive in order to take advantage of
;   286/386 specific instructions. For example:
;
;       TASM /dMDL=memorymodel /jP286 ibytecpy

%tabsize 4

ifndef  MDL
    display "Error: This module requires that you provide a memory model"
    display "       definition on the command line. I.E. /dMDL=SMALL."
    err ; Force a fatal error
else

    ideal                               ; Use TASM's Ideal mode
%   model   MDL                         ; Define the memory model

    include "ibios.mac"
    include "imacros.mac"
    include "bios.inc"

    codeseg

    global  ByteCopy:proc               ; Define public proc

    proc    ByteCopy

    ;
    ;   This function copies an array of bytes from one location in memory
    ;   to another. Before doing the copy the routine compares the absolute
    ;   addresses of the two memory locations and sets the direction flag
    ;   appropriately to avoid destroying any data. Note that this routine
    ;   assumes that the pointers passed to it are normalized if the arrays
    ;   being copied are longer than 0FFF0h bytes. I.E. Offset+ax is
    ;   <= 0FFFFh.
    ;
    ;   Input
    ;       SourcePtr - far pointer to source array
    ;       DestPtr   - far pointer to destination array
    ;       ax - number of bytes to copy
    ;   Output
    ;       es:di - points to 1 position past last destination byte
    ;       ds:si - points to 1 position past last source byte
    ;   Calling convention
    ;       Pascal
    ;   Registers modified
    ;       bx, cx, dx, di, si, es, Flags
    ;

    ; Define parameters passed on stack

    arg DestPtr:dword, SourcePtr:dword=ParmSize

        push    bp              ; Set up the stack to access parameters
        mov     bp, sp
        push    ds
        lds     si, [SourcePtr] ; Get the pointers off the stack
        les     di, [DestPtr]

        ; Compare absolute addresses of pointers

        push    ax
        CompareFarPointers  ds, si, es, di
        pop     ax
        jl      HighToLow      ; Move from high address to low address
        cld     ; Move from low address to high address
        jmp     DoMove

    HighToLow:
        std
        add     si, ax          ; Adjust offsets so they can be decremented
        dec     si
        add     di, ax          ; instead of incremented.
        dec     di

    DoMove:
        mov     cx, ax          ; Copy # of bytes to move into cx
        jcxz    DontDoMove
        rep     movsb           ; Copy the bytes
    DontDoMove:
        pop     ds              ; restore ds if necessary
        pop     bp              ; Restore the stack pointer
        ret     ParmSize        ; Clean up stack since we're using Pascal
                                ; calling conventions.
    endp    ByteCopy

endif   ; ifndef MDL

end
