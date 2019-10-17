;[]-----------------------------------------------------------------[]
;|      PROFC.ASM -- Windows profiling API                           |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1992 by Borland International
;       All Rights Reserved.
; 

        include rules.asi

PROFINT macro   funcno
        mov     ax,4500h+funcno
        int     2fh
        endm

Code_Seg@

PubProc@ PROFINSCHK, __PASCAL__
        PROFINT 0
        xor     ah,ah
        ret
EndProc@ PROFINSCHK, __PASCAL__

PubProc@ PROFSETUP, __PASCAL__
        push    bp
        mov     bp,sp
        mov     bx,8H[bp]
        mov     cx,6H[bp]
        PROFINT 1
        pop     bp
        ret     4
EndProc@ PROFSETUP

PubProc@ PROFSAMPRATE, __PASCAL__
        push    bp
        mov     bp,sp
        mov     bx,8H[bp]
        mov     cx,6H[bp]
        PROFINT 2
        pop     bp
        ret     4
EndProc@ PROFSAMPRATE, __PASCAL__

PubProc@ PROFSTART, __PASCAL__
        PROFINT 3
        ret
EndProc@ PROFSTART, __PASCAL__

PubProc@ PROFSTOP, __PASCAL__
        PROFINT 4
        ret
EndProc@ PROFSTOP, __PASCAL__

PubProc@ PROFCLEAR, __PASCAL__
        PROFINT 5
        ret
EndProc@ PROFCLEAR, __PASCAL__

PubProc@ PROFFLUSH, __PASCAL__
        PROFINT 6
        ret
EndProc@ PROFFLUSH, __PASCAL__

PubProc@ PROFFINISH, __PASCAL__
        PROFINT 7
        ret
EndProc@ PROFFINISH, __PASCAL__

Code_EndS@

        end
