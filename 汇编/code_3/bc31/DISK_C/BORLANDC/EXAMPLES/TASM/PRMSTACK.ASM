; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; PRMSTACK.ASM  - Shows how to access stack parameters with BP offsets.

; From the Turbo Assembler Users Guide

       .MODEL  small
       .CODE
       PUBLIC  _Test
_Test  PROC
       push    bp
       mov     bp,sp
       mov     ax,[bp+4]          ;get parameter 1
       add     ax,[bp+6]          ;add parameter 2 to parameter 1
       sub     ax,[bp+8]          ;subtract parameter 3 from sum
       pop     bp
       ret
_Test  ENDP
       END
