; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; DBLCOLON.ASM - Showing how to use the :: colon directive.

; From the Turbo Assembler Users Guide

VERSION M510
.MODEL SMALL,C
.CODE

A PROC
          NOP
ASINGLE:NOP
ADOUBLE::NOP
          NOP
          RET
A ENDP

B PROC
          NOP
          JMP ASINGLE    ;Will fail now
          JMP ADOUBLE
          RET
B ENDP
  END
