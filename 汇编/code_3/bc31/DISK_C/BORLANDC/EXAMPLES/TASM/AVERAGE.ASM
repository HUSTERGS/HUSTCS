; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; AVERAGE.ASM
;
; Borland C++-callable small-model function that returns the average
; of a set of integer values. Calls the Borland C++ function
; IntDivide() to perform the final division.
;
; Function prototype:
;     extern float Average(int far * ValuePtr, int NumberOfValues);
;
; Input:
;     int far * ValuePtr:          ;the array of values to average
;     int NumberOfValues:          ;the number of values to average

; From the Turbo Assembler User's Guide - Interfacing Turbo Assembler
;                                          with Borland C++

        DOSSEG
        .MODEL  SMALL
        EXTRN   _IntDivide:PROC
        .CODE
        PUBLIC  _Average
_Average        PROC
        push    bp
        mov     bp,sp
        les     bx,[bp+4]          ;point ES:BX to array of values
        mov     cx,[bp+8]          ;# of values to average
        mov     ax,0               ;clear the running total
AverageLoop:
        add     ax,es:[bx]         ;add the current value
        add     bx,2               ;point to the next value
        loop    AverageLoop
        push    WORD PTR [bp+8]    ;get back the number of values passed to
                                   ; IntDivide as the rightmost	parameter
        push    ax                 ;pass the total as the leftmost parameter
        call    _IntDivide         ;calculate the floating-point average
        add     sp,4               ;discard the parameters
        pop     bp
        ret                        ;the average is in the 8087's TOS register
_Average        ENDP
        END
