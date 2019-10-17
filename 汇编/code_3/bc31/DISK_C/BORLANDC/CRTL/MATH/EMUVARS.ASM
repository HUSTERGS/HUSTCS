;[]------------------------------------------------------------[]
;|      EMUVARS.ASM -- Emulator initialization                  |
;[]------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1990, 1992 by Borland International
;       All Rights Reserved.
; 

        NAME    EmuVars

;[]------------------------------------------------------------[]
;|                                                              |
;|      Emulator variables in the stack segment                 |
;|                                                              |
;[]------------------------------------------------------------[]

; define the FPU variables
; in large model, put them at SS:0
; in small model, this is impossible because the stack is in the DGROUP

include equates.asi
include emuvars.asi

public  __emu

if      LDATA

;_STACK SEGMENT COMMON STACK 'STACK'
_STACK  SEGMENT COMMON 'STACK'
        org     0
__emu   fpu     <>
        db      MinFpStack      DUP (?)
_STACK  ENDS

else

_DATA   SEGMENT PARA PUBLIC 'DATA'
__emu   fpu     <>
        db      MinFpStack      DUP (?)
_DATA   ENDS

endif

end
