;[]-----------------------------------------------------------------[]
;|      WRITEU.ASM -- User entry point for write()                   |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1991, 1992 by Borland International
;       All Rights Reserved.
; 

        include rules.asi

;       Segments Definitions

Header@

Code_seg@

;----------------------------------------------------------------------
; Declare internal library function __write.

ifdef   __PAS__

ExtProc@ __WRITE, __PASCAL__             ; PASCAL-callable library
__write@ equ     __WRITE

else
ExtProc@ __write, __CDECL__              ; Normal C library
endif

;----------------------------------------------------------------------
; Define user entry point write, which merely jumps to __write.

ifdef   _BUILDRTLDLL                    ; DLL library

Proc@   write, __CDECL__
        publicdll _write

elseifdef       __PAS__                 ; PASCAL-callable library

PubProc@ WRITE, __PASCAL__
write@   equ     WRITE

else                                    ; Normal C library
PubProc@ write, __CDECL__
endif

        jmp     __write@                ; jump to internal function

EndProc@ write

Code_EndS@

        end
