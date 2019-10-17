;[]-----------------------------------------------------------------[]
;|      STKAVAIL.ASM -- calculate free stack space                   |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1991, 1992 by Borland International
;       All Rights Reserved.
; 

        INCLUDE RULES.ASI

;       Segments Definitions

Header@

;----------------------------------------------------------------------
; In large data models, the stack is in its own segment.  The stack
; starts at SS:__stklen and grows down to SS:0.
;
; In small data models, the stack is in the DGROUP, and grows down
; to meet the heap.  The end of the heap is marked by ___brklvl.
;----------------------------------------------------------------------

ifdef _WINDOWS
pStackTop equ   0Ah             ; SS:[0A] contains addr of top of stack
else
  if LDATA eq false
ExtSym@         __brklvl, WORD, __CDECL__
  endif
endif

; REGSTACK contains the number of bytes taken up in the stack
; by registers saved in the normal function prologue.  This includes
; space for SI and DI, plus DS in huge model.

ifdef __HUGE__
REGSTACK   equ     6
else
REGSTACK   equ     4
endif

;-----------------------------------------------------------------------
;
;Name           stackavail - get available stack size
;
;Usage          #include <malloc.h>
;               size_t stackavail(void);
;
;Prototype in   malloc.h
;
;Description    This function returns the approximate number of bytes
;               available in the stack for allocation by alloca().
;
;Return value   The number of available stack bytes.
;
;------------------------------------------------------------------------

Code_seg@

PubProc@ stackavail, __CDECL__

        mov     ax,sp           ; get current stack pointer
ifdef _WINDOWS
        mov     cx,pStackTop    ; get base of stack
        add     cx,REGSTACK     ; leave space for pushing registers
else
    if LDATA eq false
        mov     cx,__brklvl@    ; get base of stack
        add     cx,REGSTACK     ; leave space for pushing registers
    else
        mov     cx,REGSTACK     ; leave space for pushing registers
    endif
endif
        sub     ax,cx           ; AX = (current SP) - (stack base)
        jb      noroom          ; if current SP is below stack base, no room
        ret
noroom:
        xor     ax,ax           ; return zero
        ret

EndProc@ stackavail, __CDECL__

Code_EndS@

        end
