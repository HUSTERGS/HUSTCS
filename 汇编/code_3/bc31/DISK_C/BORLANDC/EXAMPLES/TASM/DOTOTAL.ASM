; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; DOTOTAL.ASM - Example for interfacing C++ and Turbo Assembler

; From the Turbo Assembler User's Guide - Interfacing Turbo Assembler
;                                          with Borland C++

       DOSSEG                       ;select Intel-convention
                                    ;segment ordering
       .MODEL  SMALL                ;select small model 
                                    ;(nearcode and data)
       .DATA                        ;TC-compatible initialized
                                    ;data segment
       EXTRN   _Repetitions:WORD    ;externally defined
       PUBLIC  _StartingValue       ;available to other modules
_StartingValue  DW  0
       .DATA?                       ;TC-compatible uninitialized
                                    ;data segment
RunningTotal    DW  ?
       .CODE                        ;TC-compatible code segment
       PUBLIC  _DoTotal
_DoTotal        PROC                ;function (near-callable in
                                    ;small model)
       mov     cx,[_Repetitions]    ;# of counts to do
       mov     ax,[_StartingValue]
       mov     [RunningTotal],ax    ;set initial value
TotalLoop:
       inc     [RunningTotal]       ;RunningTotal++
       loop    TotalLoop
       mov     ax,[RunningTotal]    ;return final total
       ret
_DoTotal        ENDP
       END
