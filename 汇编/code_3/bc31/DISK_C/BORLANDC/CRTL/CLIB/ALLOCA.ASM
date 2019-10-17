;[]-----------------------------------------------------------------[]
;|      ALLOCA.ASM -- Allocate temporary stack space                 |
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

;----------------------------------------------------------------------
; Name          alloca - allocate temporary stack memory
;
; Usage         void *alloca(size_t size);
;
; Prototype in  malloc.h
;
; Description   Alloca allocates size bytes on the stack; the allocated
;               space is automatically freed up when the calling function
;               exits.
;
;               Because alloca modifies the stack pointer, do not place calls
;               to alloca in an expression that is an argument to a function.
;
;               If the calling function does not contain any references
;               to local variables in the stack, the stack will not
;               be restored correctly when the function exits, resulting
;               in a program crash.  To ensure that the stack is restored
;               correctly, use the following code in the calling function:
;
;                       char *p;
;                       char dummy[1];
;
;                       dummy[0] = 0;
;                       ...
;                       p = alloca(nbytes);
;
; Return value  Returns a pointer to the allocated stack area on success.
;               If the stack cannot be extended, a NULL pointer is returned.
;               The returned pointer should never be passed to free().
;
; Note          Compatible with Microsoft C and UNIX.  Not recommended.
;               Use malloc() instead.
;----------------------------------------------------------------------

Code_seg@

PubProc@ alloca, __CDECL__

        pop     bx              ; pop return address (offset)
if LPROG
        pop     es              ; pop return address (segment)
endif
        pop     ax              ; pop size parameter
        add     ax,1            ; round size up to even number of bytes
        and     ax,not 1
        neg     ax              ; negate size
        add     ax,sp           ; add current stack pointer

; Put into cx the value sp would attain after adding the space
; for pushing the return address and size parameter, and copies
; of the register variables saved in the caller's stack.  Compare
; this value with the stack base to guard against stack overflow.

        mov     cx,ax           ; add some extra to ensure there's room for
        sub     cx,REGSTACK+cPtrSize+2   ; ret address, size, and regs
        cmp     cx,sp           ; would new SP wrap around?
        ja      bad
ifdef _WINDOWS
        cmp     ss:pStackTop,cx ; would new SP go below top of stack?
        ja      bad
else
    if LDATA eq false
        cmp     __brklvl@,cx    ; would new SP fall in the near heap?
        ja      bad
    endif
endif
        mov     cx,bp           ; save BP in CX
        mov     bp,sp           ; get a copy of SP into BP for later use

; The current stack looks like this, from high to low address:
;       SI saved by caller (assumed to be present)
;       DI saved by caller (assumed to be present)
; BP -> DS saved by caller (present only in huge model)
;       ... empty space ...
; AX -> new stack area
;
; Before we can return, we need to push on the new stack area the registers
; saved by caller in the old stack area.  We need to copy at least 2 stack words
; (for SI and DI), plus one more in huge model (DS).  We can't tell if SI
; and DI were really saved, so we assume that they were and allocate extra
; space for them.

        mov     sp,ax           ; set up new SP
ifdef __HUGE__
        push    [bp+4]
endif
        push    [bp+2]
        push    [bp+0]
if LDATA
        mov     dx,ss           ; return high word of stack address in DX
endif
        mov     bp,cx           ; restore caller's BP
return:
        sub     sp,2            ; caller will add 2 to SP after we return
if LPROG
        push    es              ; can't "jmp es:bx", so push es:bx,
        push    bx              ;  then do a far return
        retf
else
        jmp     bx              ; return
endif

; Come here if there isn't enough stack space.  Return a null pointer.

bad:
        xor     ax,ax           ; return NULL pointer
if LDATA
        mov     dx,ax
endif
        jmp     return

EndProc@ alloca, __CDECL__

Code_EndS@

        end
