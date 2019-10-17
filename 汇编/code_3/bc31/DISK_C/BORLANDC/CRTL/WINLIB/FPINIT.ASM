;[]-----------------------------------------------------------------[]
;|      FPINIT.ASM -- Pre/post code for WIN87EM                      |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1987, 1992 by Borland International
;       All Rights Reserved.
; 

;This module is memory model indepedent

                include RULES.ASI

                extrn __FPMATH:far
                extrn LOADLIBRARY:far
                extrn __fperr:far
                extrn __turboFloat
                extrn __turboCvt
                extrn __FPVector:dword
                extrn __LockWIN87EM:word

                public  FIDRQQ          ; wait, esc
                public  FIARQQ          ; wait, DS:
                public  FICRQQ          ; wait, CS:
                public  FIERQQ          ; wait, ES:
                public  FISRQQ          ; wait, SS:
                public  FIWRQQ          ; nop, wait
                public  FJARQQ          ; Esc nn -> DS:nn
                public  FJCRQQ          ; Esc nn -> CS:nn
                public  FJSRQQ          ; Esc nn -> ES:nn

FIDRQQ          equ     05C32h
FIARQQ          equ     0FE32h
FICRQQ          equ     00E32h
FIERQQ          equ     01632h
FISRQQ          equ     00632h
FIWRQQ          equ     0A23Dh
FJARQQ          equ     04000h
FJCRQQ          equ     0C000h
FJSRQQ          equ     08000h

SIGFPE          equ     8
SIG_DFL         equ     0

                public __windowsFloat
__windowsFloat  equ     0

                public  __cvtfak
__cvtfak        equ     0

_DATA           segment
LibName         db  'WIN87EM', 0
                ends

_TEXT           segment
                assume cs:_TEXT,ds:DGROUP

__exitfp:       mov     bx,2                    ; close WIN87EM
                call    __FPMATH
                ret

__initfp:       cmp     __LockWIN87EM, 0        ; lock WIN87EM by forcing load
                je      NoLock                  ; workaround for DLL unload
                push    ds                      ;   ordering problem in Windows
                lea     ax, LibName
                push    ax
                call    LOADLIBRARY
NoLock:
                mov     word ptr __FPVector,offset __FPMATH
                mov     word ptr __FPVector+2,seg __FPMATH

                xor     bx,bx                   ; init WIN87EM
                call    __FPMATH

                mov     bx, 3                   ; set exception handler
                mov     dx, seg    __fperr
                mov     ax, offset __fperr
                call    __FPMATH
                ret
                ends

_INIT_          segment word public 'INITDATA'
                db      0                       ; near call
                db      1                       ; priority 1
                dw      offset __initfp
                dw      ?
                ends

_EXIT_          segment word public 'EXITDATA'
                db      0                       ; near call
                db      1                       ; priority 1
                dw      offset __exitfp
                dw      ?
                ends

                end
