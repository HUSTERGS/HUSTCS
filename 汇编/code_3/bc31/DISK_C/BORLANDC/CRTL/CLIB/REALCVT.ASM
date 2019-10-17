;[]-----------------------------------------------------------------[]
;|      REALCVT.ASM -- Real number conversion routine                |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

        INCLUDE RULES.ASI
        %MACS

;       Segment and Group declarations

_TEXT   SEGMENT BYTE PUBLIC 'CODE'
_TEXT   ENDS
_CVTSEG SEGMENT WORD PUBLIC 'DATA'
_CVTSEG ENDS

DGROUP  GROUP   _CVTSEG

        ASSUME  CS:_TEXT, DS:DGROUP

;       External References

ExtSym@         _cvtfak, ABS, __CDECL__
extrn           __RealCvtVector:word

_TEXT   SEGMENT

                public __REALCVT
__REALCVT       proc near
IFDEF   __HUGE__
ExtSym@         DGROUP@, WORD, __PASCAL__
                mov     es, cs:DGROUP@@
                jmp     ES:[__RealCvtVector]
ELSE
                jmp     [__RealCvtVector]
ENDIF
                endp
_TEXT   ENDS
        END
