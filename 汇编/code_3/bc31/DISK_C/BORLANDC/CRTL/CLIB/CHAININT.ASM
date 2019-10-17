;[]-----------------------------------------------------------------[]
;|      chainint.asm                                                 |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1991, 1992 by Borland International
;       All Rights Reserved.
; 

        INCLUDE rules.asi

; Name          _chain_intr - chain to another interrupt handler
;
; Usage         void _chain_intr (void interrupt (far *target)());
;
; Description   _chain_intr passes control from one interrupt
;               handler to another.  The current register set
;               is NOT passed to the new handler.  Instead,
;               the new handler receives the registers that
;               were stacked (and possibly modified in the stack)
;               by the old handler.  The new handler can simply
;               return, as if it were the original handler.
;               The old handler is not entered again.
;
; Return value  This function does not return.
;
; This function is always called by a C interrupt function, so the
; stack now looks like this (high address at top, low at bottom):
;
;       FLAGS
;       CS
;       IP
;       AX
;       BX
;       CX
;       DX
;       ES
;       DS
;       SI
;       DI
; BP->  BP
;       target (low word)
;       target (high word)
;       return address (low word)
; SP->  return address (high word -- only present in large code models)
;
; To chain to "target" (the new interrupt handler), we poke the target
; address into the stack where AX and BX were saved (after loading
; AX and BX directly from the stack).  Then we pop all registers up
; to where "target" was poked in, and execute a far return.  This
; causes execution to start at "target" with only the CS, IP, and flags
; on the stack, exactly as if an interrupt had just occurred.

                Code_Seg@

PubProc@        _chain_intr, __CDECL__

                pop     ax              ; discard return address
IF LPROG
                pop     ax              ; discard high word of return address
ENDIF
                mov     bx,[bp+14]      ; restore stacked BX
                mov     ax,[bp+16]      ; restore stacked AX
                pop     [bp+14]         ; pop target address into stack
                pop     [bp+16]         ;  in place of stacked AX:BX
                mov     sp,bp           ; point SP at stacked registers
                pop     bp              ; restore all other stacked registers
                pop     di
                pop     si
                pop     ds
                pop     es
                pop     dx
                pop     cx
                cli                     ; disable interrupts
                retf                    ; "return" to target

EndProc@        _chain_intr, __CDECL__

                Code_EndS@
                END
