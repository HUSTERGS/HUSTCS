;[]-----------------------------------------------------------------[]
;|      SCANTOD.ASM -- Ascii to double conversion                    |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

        INCLUDE RULES.ASI

;       Segment and Group declarations

_TEXT   SEGMENT BYTE PUBLIC 'CODE'
_TEXT   ENDS
_SCNSEG SEGMENT WORD PUBLIC 'DATA'
_SCNSEG ENDS

IFNDEF  __TINY__
DGROUP  GROUP   _SCNSEG
ELSE
DGROUP  GROUP   _TEXT, _EMUSEG
ENDIF
        ASSUME  CS:_TEXT, DS:DGROUP

;       External References

extrn           __cvtfak:word
extrn           __ScanTodVector:word

_TEXT   SEGMENT

                public __scantod
__scantod       proc near
IFDEF   __HUGE__
ExtSym@         DGROUP@, WORD, __PASCAL__
                mov     es, cs:DGROUP@@
                jmp     ES:[__ScanTodVector]
ELSE
                jmp     [__ScanTodVector]
ENDIF
                endp


                public __scanrslt
__scanrslt      proc near
IFDEF   __HUGE__
ExtSym@         DGROUP@, WORD, __PASCAL__
                mov     es, cs:DGROUP@@
                jmp     ES:[__ScanTodVector + 2]
ELSE
                jmp     [__ScanTodVector + 2]
ENDIF
                endp

                public __scanpop
__scanpop       proc near
IFDEF   __HUGE__
ExtSym@         DGROUP@, WORD, __PASCAL__
                mov     es, cs:DGROUP@@
                jmp     ES:[__ScanTodVector + 4]
ELSE
                jmp     [__ScanTodVector + 4]
ENDIF
                endp

_TEXT   ENDS
        END
