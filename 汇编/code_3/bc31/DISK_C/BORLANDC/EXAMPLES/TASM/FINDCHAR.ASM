; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; FINDCHAR.ASM  - Searching for the last character of a null terminated string

; From the Turbo Assembler Users Guide

        .MODEL  small
        .CODE
        PUBLIC _FindLastChar
_FindLastChar   PROC
        ARG     StringToScan:WORD
        push    bp
        mov     bp,sp
        cld             ;we need string instructions to count up
        mov     ax,ds
        mov     es,ax   ;set ES to point to the near data segment
        mov     di, [StringToScan]   ;point ES:DI to start of 
                                     ;passed string
        mov     al,0    ;search for the null that ends the string
        mov     cx,0ffffh  ;search up to 64K-1 bytes
        repnz   scasb      ;look for the null
        dec     di         ;point back to the null
        dec     di         ;point back to the last character
        mov     ax,di      ;return the near pointer in AX
        pop     bp
        ret
_FindLastChar   ENDP
        END
