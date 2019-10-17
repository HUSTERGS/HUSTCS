;[]-----------------------------------------------------------------[]
;|      DDVT.ASM -- DDVT dispatcher                                  |
;[]-----------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1991, 1992 by Borland International
;       All Rights Reserved.
; 

;memory model aliases, for the convenience of building the library

IFDEF           __s__
__SMALL__       equ     1
ENDIF

IFDEF           __c__
__COMPACT__     equ     1
ENDIF

IFDEF           __m__
__MEDIUM__      equ     1
ENDIF

IFDEF           __l__
__LARGE__       equ     1
ENDIF

IFDEF           __h__
__HUGE__        equ     1
ENDIF

IFNDEF __TINY__
    IFNDEF __SMALL__
        IFNDEF __MEDIUM__
            IFNDEF __COMPACT__
                IFNDEF __LARGE__
                    IFNDEF __HUGE__
                        %OUT  You must supply a model symbol.
                        .ERR
                    ENDIF
                ENDIF
            ENDIF
        ENDIF
    ENDIF
ENDIF

                extrn   _abort:far

ifdef   __SMALL__
                .model  small
LDATA           equ     0
endif

ifdef   __MEDIUM__
                .model  medium
LDATA           equ     0
endif

ifdef   __COMPACT__
                .model  compact
LDATA           equ     1
endif

ifdef   __LARGE__
                .model  large
LDATA           equ     1
endif

ifdef   __HUGE__
                .model  large
LDATA           equ     1
endif

ifdef   FARVTBL
ptrSize         equ     4
else
ptrSize         equ     2
endif

if      LDATA
LES_            equ     <les>
ES_             equ     <es:>
else
LES_            equ     <mov>
ES_             equ     <   >
endif

                .code

FAIL_addr_NULL  dd      0               ; NULL 'fail' value
FAIL_addr_abort dd      _abort          ; RTL  'fail' value

;==============================================================================
;
; NULL dispatcher entry points:
;

ifdef     FARVTBL

entryname       equ     <@_DDVTdispatchNULL$qnvi>
                public  entryname
entryname:      mov     ax, offset FAIL_addr_NULL
                jmp     SHORT start_dispatch

else

entryname       equ     <@_DDVTdispatchNULL$qpvi>
                public  entryname
entryname:      mov     ax, offset FAIL_addr_NULL
                jmp     SHORT start_dispatch

endif

;
; Compiler 'virtual DDVT call' entry points:
;

ifdef   FARVTBL

procname        equ     <@_DDVTdispatch$qnvi>
                public  procname
procname        proc    vptr:DWORD,id:WORD

else

procname        equ     <@_DDVTdispatch$qpvi>
                public  procname
procname        proc    vptr: WORD,id:WORD

endif
                mov     ax, offset FAIL_addr_abort

start_dispatch:

                push    bp
                mov     bp, sp

                push    si
                push    di

                push    ax                      ; save 'fail' address

ifdef   FARVTBL
                les     bx, vptr
else
                mov     bx, vptr
                push    ds
                pop     es
endif

                std

;
; This is the loop that searches for a matching ID.
;
search_loop:    mov     cx, ES_[bx-ptrSize-2]   ; get # of entries
                jcxz    search_next
;
; The table is below the # of entries, 6 bytes per entry; count is in CX.
;
                mov     dx, cx                  ; save the count
;
; Search this table for a matching ID.
;
                mov     ax, id
                lea     di, [bx-ptrSize-4]      ; point at first ID
                repne   scasw
                je      search_match
;
; No luck with this class; see if it has a base class.
;
search_next:

ifdef   FARVTBL
                les     bx, es:[bx-4]           ; get base class link
                mov     ax, es
                or      ax, bx
else
                mov     bx, [bx-2]              ; get base class link
                or      bx, bx
endif
                jnz     search_loop             ; continue if non-zero
;
; No match; return address of the 'fail' function pointer.
;
                pop     ax                      ; pop 'fail' address
                mov     dx, cs

                jmp     SHORT done
;
; Here if we have a match; ES:[DI] points just below the matching ID.
;
search_match:   shl     dx, 1                   ; DX = 2 * count
                sub     bx, dx
                shl     cx, 1                   ; CX = 2 * count remaining
                sub     dx, cx
                shl     dx, 1                   ; DX = 4 * index of match
                add     dx, 2 + ptrSize
                sub     bx, dx

                pop     ax                      ; throw away 'fail' addr

                mov     ax, bx                  ; return the fn address
                mov     dx, es

done:           cld
                pop     di
                pop     si

                pop     bp
                ret

procname        endp

;==============================================================================
                end
