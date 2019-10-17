page 75,132
%Title "Display routines"
;Copyright (c) 1991 By Borland International, Inc.

ifndef MDL
    display "Error: This module requires that you provide a memory model"
    display "    definition on the command line. I.E. /dMDL=SMALL."

MDL equ <SMALL>
endif

.model MDL,pascal
.code


include display.inc

page
;****************************************************************
; Screen Utilities

; Show value in DL as a hex digit
showhexdigit proc near
         add  dl,'0'
         cmp  dl,'9'
         jbe  showhexdigit_showit
         add  dl,'A'-'0'-10   ; Convert to A,B,C,D,E,F
showhexdigit_showit:
         mov  ah,DOSPRINTCHAR
         int  DOSINT
         ret
showhexdigit endp


; Show value in BH as a hexidecimal byte
ShowHexByte proc
         mov  dl,bh
         shr  dl,1
         shr  dl,1
         shr  dl,1
         shr  dl,1
         call showhexdigit
         mov  dl,bh
         and  dl,0fh
         call showhexdigit
         ret
ShowHexByte endp



; Show value in AX as a hexadecimal word
ShowHexWord proc
         mov  bx,ax
         call ShowHexByte
         mov  bh,bl
         call ShowHexByte
         ret
ShowHexWord endp



Show_Bracket proc
         mov  ah,DOSPRINTCHAR
         mov  dl,'['
         int  DOSINT
         ret
Show_Bracket endp



Show_Endbracket proc
         mov  ah,DOSPRINTCHAR
         mov  dl,']'
         int  DOSINT
         ret
Show_Endbracket endp



CRLF     proc
         mov  ah,DOSPRINTCHAR
         mov  dl,CR
         int  DOSINT
         mov  dl,LF
         int  DOSINT
         ret
CRLF     endp

end


