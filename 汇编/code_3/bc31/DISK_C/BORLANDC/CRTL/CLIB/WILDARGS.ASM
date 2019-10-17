;[]-----------------------------------------------------------------[]
;|      WILDARGS.ASM -- Hook For Wildcard Command Line Parsing       |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 


        INCLUDE RULES.ASI

_DATA           segment word public 'DATA'
PubSym@         _argc,          <dw     0>,             __CDECL__
dPtrPub@        _argv,          0,                      __CDECL__
                ends

_TEXT           segment byte public 'CODE'

extrn           __wildargv

;This is the symbol which pulls in _wildargv (or _setargv)
                public __setargv__
__setargv__     equ    0

_INIT_          SEGMENT WORD PUBLIC 'INITDATA'
                db      0                       ;near call
                db      1                       ;priority 1
                dw      offset __wildargv
                dw      ?
_INIT_          ENDS

                ends
                end
