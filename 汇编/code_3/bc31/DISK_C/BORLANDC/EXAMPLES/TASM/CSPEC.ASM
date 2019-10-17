; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; CSPEC.ASM

; From the Turbo Assembler Users Guide

     .MODEL    SMALL
     .DATA
     EXTRN     C Flag:word
     .CODE
     PUBLIC    C ToggleFlag
ToggleFlag     PROC
     cmp       [Flag],0
     jz        SetFlag
     mov       [Flag],0
     jmp       short EndToggleFlag
SetFlag:
     mov       [Flag],1
EndToggleFlag:
     ret
ToggleFlag     ENDP
     END
