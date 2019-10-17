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

;       External References

;ExtSym@        _cvtfak, ABS, __CDECL__
extrn           __RealCvtVector:word

_TEXT   SEGMENT

                public __REALCVT
__REALCVT       proc near
                jmp     [__RealCvtVector]
                endp
_TEXT   ENDS
        END
