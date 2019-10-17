;[]-----------------------------------------------------------------[]
;|      READU.ASM -- User entry point for read()                     |
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
; Declare internal library function __read.

ifdef   __PAS__

ExtProc@ __READ, __PASCAL__             ; PASCAL-callable library
__read@ equ     __READ

else
ExtProc@ __read, __CDECL__              ; Normal C library
endif

;----------------------------------------------------------------------
; Define user entry point read, which merely jumps to __read.

ifdef   _BUILDRTLDLL                    ; DLL library

Proc@   read, __CDECL__
        publicdll _read

elseifdef       __PAS__                 ; PASCAL-callable library

PubProc@ READ, __PASCAL__
read@   equ     READ

else                                    ; Normal C library
PubProc@ read, __CDECL__
endif

        jmp     __read@                 ; jump to internal function

EndProc@ read

Code_EndS@

        end
