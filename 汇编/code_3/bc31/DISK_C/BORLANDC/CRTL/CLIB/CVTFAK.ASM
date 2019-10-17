;[]-----------------------------------------------------------------[]
;|      CVTFAK.ASM -- abort when float isn't present                 |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

        INCLUDE RULES.ASI

;       Segment and Group declarations

Header@

;       External references

extrn           _abort:near

;       Public references

                public  __cvtfak
__cvtfak        equ     0

_TEXT           segment
;-------------------------------------------------------------------------
;               Get printf() specific part of message
;-------------------------------------------------------------------------
_FakRealCvt     proc near
                mov     dx, offset DGROUP: RealMSG      ; Message address
                jmp     short DisplayMessage            ; Display the message
                endp

;-------------------------------------------------------------------------
;               Get scanf() specific part of message
;-------------------------------------------------------------------------
_FakScanTod     proc near
                mov     dx, offset DGROUP: ScanMSG      ; Message address
;
; By letting the _FakScanTod PROC to 'fall into' the 'DisplayMessage' routine
; we save the cost of a JMP instruction.  This is a somewhat cheap trick but
; the purpose is quite clear here.

DisplayMessage  LABEL   NEAR

;-------------------------------------------------------------------------
;               Display FLOAT not linked message
;-------------------------------------------------------------------------
IFDEF   __HUGE__
ExtSym@ DGROUP@, WORD, __PASCAL__
                mov     ds, cs:DGROUP@@                 ; Get DS if we're huge
ENDIF

                mov     cx, lgth_UNIQ                   ; Message length
                mov     ah, 040H                        ; Write
                mov     bx, 2                           ;   to
                int     021h                            ;      'stdout'

                mov     cx, lgth_Common                 ; Common msg length
                mov     dx, offset DGROUP: CommonMSG    ; Common msg address
                mov     ah, 040H                        ; Write to
                int     021h                            ;      'stdout'
                jmp     _abort                          ; abort();

                endp
                ends

DSeg@
;-------------------------------------------------------------------------
;               Message texts for 'float not linked' messages
;
; Note : by putting an 'extra' blank in the scanf unique message part we
; save some code space by having a common message length.
;-------------------------------------------------------------------------
;
; Message part unique to the printf() message.
;
RealMSG         db      'print'         ; Unique part of 'printf' message
lgth_UNIQ       equ     $ - RealMSG     ; Length of unique msg parts
;
; Message part unique to the scanf() message(this MUST be same len as print).
;
ScanMSG         db      ' scan'         ; Unique part of 'scanf' message
;
; Message part common to the 'printf and 'scanf' messages.
; NOTE : the 'f' in printf and scanf is common too!.
;
CommonMSG       db      'f : floating point formats not linked', 13, 10
lgth_Common     equ     $ - CommonMSG
DSegEnd@

_CVTSEG SEGMENT WORD PUBLIC 'DATA'
_realcvt        dw      offset _FakRealCvt
_CVTSEG ENDS

_SCNSEG SEGMENT WORD PUBLIC 'DATA'
__scantod       dw      offset _FakScanTod
__scanrslt      dw      offset _FakScanTod
__scanpop       dw      offset _FakScanTod
_SCNSEG ENDS
        END
