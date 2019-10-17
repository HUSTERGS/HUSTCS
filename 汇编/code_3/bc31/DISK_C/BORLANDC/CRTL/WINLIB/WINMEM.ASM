;[]-----------------------------------------------------------------[]
;|      WINMEM.ASM -- Windows memory suballocator helper functions   |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1991, 1992 by Borland International
;       All Rights Reserved.
; 

        INCLUDE RULES.ASI

        locals

        public __RLS_TEMP_BLOCK
        public __GET_TEMP_BLOCK
        public __SIZ_TEMP_BLOCK

        extrn   GLOBALALLOC:far
        extrn   GLOBALFREE:far

        extrn   GLOBALLOCK:far
        extrn   GLOBALUNLOCK:far

        extrn   GLOBALHANDLE:far
        extrn   GLOBALSIZE:far

        extrn   __WinAllocFlag:word

        GMEM_MOVEABLE       equ 2


Code_Seg@

__GET_TEMP_BLOCK  proc    far

;
; Function __GET_TEMP_BLOCK: allocate a memory block
;
; Inputs:
;       DX:AX   =       size of block to allocate
; Outputs:
;       DX:AX   =       address of block

        local   Temp:word=STACKFRAMESIZE

        push    bp
        mov     bp, sp
        sub     sp, STACKFRAMESIZE

        mov     [Temp], ax

        mov     ax, __WinAllocFlag
        or      ax, GMEM_MOVEABLE
        push    ax              ;GLOBALALLOC flags

        mov     ax, [Temp]      ;lower 16-bits of size
        push    dx              ;push 32-bit size
        push    ax

        call    GLOBALALLOC     ;allocate block.  ax = handle
        or      ax, ax          ;error allocating?
        jz      @@Error
        push    ax
        call    GLOBALLOCK      ;dx:ax is pointer to block
        ;; check our assumption that offsets are always zero
        or      ax, ax          ;zero offset
        jnz     @@Error         ; nope, return NULL

@@Exit:
        mov     sp, bp
        pop     bp
        ret

@@Error:
        xor     dx, dx
        jmp     @@Exit

__GET_TEMP_BLOCK  endp

__RLS_TEMP_BLOCK  proc    far

;
; Function __RLS_TEMP_BLOCK: free a memory block
;
; Inputs:
;       ES:DI   =       block address
; Outputs:
;       none
; Assumptions:
;       DI = 0

        push    es              ;selector of block
        call    GLOBALHANDLE    ;ax = handle of block
        or      ax, ax          ;no such block?
        jz      @@Error         ; yes

        push    ax              ;push handle for GLOBALFREE
        push    ax              ;push handle for GLOBALUNLOCK
        call    GLOBALUNLOCK    ;unlock block
        call    GLOBALFREE      ;free block
@@Error:
        ;; No block was found with the given address.  Just return.
        ret

__RLS_TEMP_BLOCK  endp

__SIZ_TEMP_BLOCK  proc    far

;
; Function __SIZ_TEMP_BLOCK: Return the size of an allocated block.
;
; Inputs:
;       ES:DI   =       block address
; Outputs:
;       DX:AX   =       block size
; Assumptions:
;       DI = 0

        push    es              ;selector of block
        call    GLOBALHANDLE    ;ax = handle of block
        or      ax, ax          ;no such block?
        jz      @@Error         ; yes
        push    ax              ;handle of block
        call    GLOBALSIZE      ;dx:ax is size of block
        ret

@@Error:
        ;; Not much to do besides return 0.
        xor     dx, dx
        ;; ax already zero
        ret

__SIZ_TEMP_BLOCK  endp

Code_EndS@
        end
