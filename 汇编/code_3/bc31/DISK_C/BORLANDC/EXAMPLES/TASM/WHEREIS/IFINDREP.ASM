
;   FILENAME: IFINDREP.ASM
;
;   Copyright (c) 1988, 1992 by Borland International, Inc.
;
;   DESCRIPTION: This module implements the routine FindAndReplace. The
;   routine will search through an array of bytes replacing all instances
;   of a particular value with an alternative value. This module uses
;   ideal mode syntax.
;
;   ASSEMBLY INSTRUCTIONS: To assemble this module use the following TASM
;   command line:
;
;       TASM /dMDL=memorymodel Ifindrep
;
;   'memorymodel' in the above command line may be replaced by TINY, SMALL,
;   MEDIUM, COMPACT, LARGE or HUGE.

%tabsize 4

ifndef  MDL
    display "Error: This module requires that you provide a memory model"
    display "       definition on the command line. I.E. /dMDL=SMALL."
    err ; Force a fatal error
else

    ideal           ; Use TASM's Ideal mode
%   model   MDL     ; Define the memory model

    codeseg

    global  FindAndReplace:proc ; Declare public proc

    proc    FindAndReplace

    ;   This routine searches through an array of byte values looking for
    ;   the value indicated in al. Whenever it finds a match it replaces the
    ;   byte with the value stored in ah. Note that this routine assumes that
    ;   the pointer passed to it is normalized if the array being searched
    ;   is longer than 0FFF0h bytes.
    ;
    ;   Input
    ;       ArrayPtr - far pointer to array
    ;       al - unsigned byte value to search for
    ;       ah - unsigned byte value to replace with
    ;       cx - maximum number of bytes to search.
    ;   Output
    ;       none
    ;   Calling convention
    ;       Pascal
    ;   Registers modified
    ;       cx, di, es, Flags

    arg ArrayPtr:dword=PARM_SIZE    ; Define parameter passed on stack

        push    bp                  ; Set up the stack to access parameters
        mov     bp, sp
        les     di, [ArrayPtr]      ; Get the address of the array
        cld                         ; Search from low address to high address
    ReplaceLoop:
        repne   scasb               ; Find a matching byte
        jcxz    Exit                ; At end of array
        mov     [byte es:di], ah    ; Replace byte
        jmp     ReplaceLoop         ; Replace next byte
    Exit:
        pop     bp                  ; Restore stack pointer
        ret     PARM_SIZE           ; Clean up stack since we're using Pascal
                                    ; calling conventions
    endp    FindAndReplace

endif   ; ifndef MDL

end
