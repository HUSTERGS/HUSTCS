
;   FILENAME: IFINDBYT.ASM
;
;   Copyright (c) 1988, 1992 by Borland International, Inc.
;
;   DESCRIPTION: This module implements two routines. The first,
;   GetASCIIZStrLen is simply an alternate entry point into the main routine
;   FindBytePos. FindBytePos determines the position of an unsigned byte value
;   in an array of bytes. This module uses IDEAL mode syntax.
;
;   ASSEMBLY INSTRUCTIONS: To assemble this module use the following
;   TASM command line.
;
;       TASM /dMDL=memorymodel ifindbyt
;
;   'memorymodel' in the above command line may be replaced by TINY, SMALL,
;   MEDIUM, COMPACT, LARGE or HUGE.
;

%tabsize 4

ifndef  MDL
    display "Error: This module requires that you provide a memory model"
    display "       definition on the command line. I.E. /dMDL=SMALL."
    err ; Force a fatal error
else

    ideal                           ; Use TASM's Ideal mode
%   model   MDL             ; Define the memory model

    codeseg

    global  FindBytePos:proc        ; Define public proc's
    global  GetASCIIZStrLen:proc


    label GetASCIIZStrLen proc

    ;   This label is used as an alternate entry point into the
    ;   routine FindBytePos. By initializing ax and cx appropriately we
    ;   take advantage of the code in FindBytePos and gain another sub-routine.
    ;
    ;   The routine returns the length of an ASCIIZ string including the
    ;   termintating length byte.
    ;
    ;   Input
    ;       ArrayPtr - far pointer to byte array
    ;   Output
    ;       cx <> 0
    ;           cx - Number of bytes left to search in array
    ;           es:di - Segment:Offset+1  of the byte value searched for
    ;       cx = 0 - Byte value couldn't be found.
    ;       ax - Number of bytes searched
    ;       es:di - points to one byte past the last byte checked
    ;   Calling convention
    ;       Pascal
    ;   Registers modified
    ;       ax, bx, cx, di, es, Flags

        mov     al, 0           ; Look for the termianting null character
        mov     cx, 0FFFFh      ; Search a max 64K characters

    proc    FindBytePos

    ;   This function returns the position+1 in the indicated array of the
    ;   byte value in al. Note that this routine assumes that the pointer
    ;   passed to it is normalized if the array being searched is longer
    ;   than 0FFF0h bytes.
    ;
    ;   Input
    ;       ArrayPtr - far pointer to byte array
    ;       al - unsigned byte value to search for
    ;       cx - maximum number of bytes to search.
    ;   Output
    ;       cx <> 0
    ;           cx - Number of bytes left to search in array
    ;           es:di - Segment:Offset+1  of the byte value searched for
    ;       cx = 0 - Byte value couldn't be found.
    ;       ax - Number of bytes searched
    ;       es:di - points to one byte past the last byte checked
    ;   Calling convention
    ;       Pascal
    ;   Registers modified
    ;       ax, bx, cx, di, es, Flags

    arg ArrayPtr:dword=ParmSize    ; Define parameter passed on stack

        push    bp                  ; Set up the stack to access parameters
        mov     bp, sp
        les     di, [ArrayPtr]      ; Get the address of the array to search
        cld                         ; Search from low address to high address
        mov     bx, di              ; Store the address of the beginning of the
                                    ; array
        repne   scasb               ; Find the byte if it exists
        mov     ax, di              ; Move the position pointer into ax
        sub     ax, bx              ; Calculate the number of bytes searched
        pop     bp                  ; Restore the stack pointer
        ret     ParmSize            ; Clean up stack since we're using Pascal
                                    ; calling conventions.
    endp    FindBytePos

endif   ; ifndef MDL

end
