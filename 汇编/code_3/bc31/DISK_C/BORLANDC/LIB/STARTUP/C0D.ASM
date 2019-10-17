;[]------------------------------------------------------------[]
;|      C0D.ASM -- Start Up Code For Windows DLLs               |
;[]------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1991, 1992 by Borland International
;       All Rights Reserved.
; 

                locals

                __C0__ = 1
include         RULES.ASI

                ASSUME CS:_TEXT, DS:DGROUP

                public  __acrtused              ;satisfy MS for now
__acrtused      equ     0


                extrn LIBMAIN:far       ;the C routine to be called
                extrn LOCALINIT:far     ;Windows heap init routine
                extrn LOCKSEGMENT:far
                extrn UNLOCKSEGMENT:far
                extrn GETWINFLAGS:far
                extrn __WEP:far
                extrn __cexit:DIST
                extrn __setupio:near    ;required!

                public LibEntry         ;Entry point for the DLL
                publicdll WEP

NULL            segment
                db      16 dup (?)
                ends

_CVTSEG         segment
                public __RealCvtVector
__RealCvtVector label word
                ends

_SCNSEG         segment
                public __ScanTodVector
__ScanTodVector label word
                ends

_FPSEG          segment
                public __FPVector
__FPVector      dd      0
                ends

_DATA           segment
                public _errno
_errno          dw      0
                public __protected
__protected     dw      0
                public __8087
__8087          dw      0
                public __StartTime
__StartTime     dd      0
                public __version
__version       label word
                public __osversion
__osversion     label word
                public __osmajor
__osmajor       db      0
                public __osminor
__osminor       db      0
                public __osmode         ;Used for OS/2 protected mode by MS,
__osmode        db      0               ;currently set to 0 under Windows
                public __hInstance
__hInstance     dw      0
                public __WinAllocFlag   ;Used by malloc for additional flags
__WinAllocFlag  dw      0               ;to pass to GlobalAlloc (used in DLLs)
                public __LockWIN87EM    ;Used do lock down WIN87EM to avoid
__LockWIN87EM   dw      1               ;DLL unload ordering problem

_abend          dw      1               ;If LibEntry is called gets set to
                                        ;normal state (0).  If it is 1 then
                                        ;exit routines are not performed
                                        ;Gets set to 1 if DLL is terminated
                                        ;by a call to abort() or _exit().

CopyRight       db      'Borland C++ - Copyright 1991 Borland Intl.',0
                ends

_TEXT           segment

LibEntry        proc far
                mov     __hInstance, di ;save SI and DI
                push    si

                push    di              ;handle of the module instance
                push    ds              ;library data segment
                push    cx              ;heap size
                push    es              ;command line segment
                push    si              ;command line offset

                ;if we have some heap then initialize it
                jcxz    @@Init          ;jump if no heap specified

                ;call the Windows function LocalInit() to set up the heap
                ;LocalInit((LPSTR)start, WORD cbHeap);

                push    ds              ;Heap segment
                xor     ax,ax
                push    ax              ;Heap start offset in segment
                push    cx              ;Heap end offset in segment
                call    LOCALINIT
                xchg    ax,cx
                jcxz    @@JmpExit       ;quit if it failed
                jmp     short @@Init
@@JmpExit:      jmp     @@Exit

@@Init:

IF LDATA EQ false
                mov     ax,-1
                push    ax
                call    LOCKSEGMENT
ENDIF

                ;Clear _BSS, uninitialized data area

                xor     ax, ax
                push    ds
                pop     es
                mov     di,offset DGROUP:BeginBSS
                mov     cx,offset DGROUP:EndBSS
                sub     cx,di
                cld
                rep
                stosb

;Save start time of DLL

                mov     ah, 0
                int     1ah             ; get current BIOS time in ticks
                mov     word ptr __StartTime,dx ; save it for clock() fn
                mov     word ptr __StartTime+2,cx
                or      al,al                   ; was midnight flag set?
                jz      @@NotMidnight
                mov     ax,40h                  ; set BIOS midnight flag
                mov     es,ax                   ;  at 40:70
                mov     bx,70h
                mov     byte ptr es:[bx],1
@@NotMidnight:

;Determine DOS version

                mov     ah, 30h
                int     21h
                mov     __version, ax   ; save minor and major revision

;Determine whether we are in protected mode

                call    GETWINFLAGS
                test    ax,1            ; WF_PMODE = 1
                jz      @@realmode      ; Note:  GETWINFLAGS returns a long,
                                        ; so if WF_PMODE changed it could be
                                        ; in the high word.
                mov     __protected, 8  ; Eight is for convenience.
@@realmode:

;Test for 8087 presence

                test    ax,0400h        ; WF_8087 = 0x0400
                jz      @@no8087
                mov     __8087, 1
@@no8087:

;Call our initialization functions, including C++ static constructors.

                mov     ax,ds
                mov     es,ax
                mov     si,offset DGROUP:InitStart      ;si = start of table
                mov     di,offset DGROUP:InitEnd        ;di = end of table

                mov     __WinAllocFlag, 2000h           ; GMEM_SHARE
                call    Initialize
                mov     __WinAllocFlag, 0
                mov     _abend, 0                       ; Set LibEntry called

                ;invoke the C routine to do any special initialization
@@Main:         call    LIBMAIN         ;invoke the 'C' routine (result in AX)
                mov     di, __hInstance ;restore SI and DI
                pop     si
                ret

@@Exit:         mov ax, 0               ;set return code
                pop si                  ;remove arguments to LIBMAIN
                pop es                  ;  since we didn't call it.
                pop cx
                pop ds
                pop di
                pop si                  ;restore saved SI.  DI is restored
                ret                     ;  by removing arguments to LIBMAIN
                endp

;---------------------------------------------------------------------------
;       _cleanup()      call all #pragma exit cleanup routines.
;       _checknull()    check for null pointer zapping copyright message
;       _terminate(exitcode, quick)     exit program with error code
;       _restorezero()  restore interrupt vectors
;
;       These functions are called by exit(), _exit(), _cexit(),
;       and _c_exit().
;---------------------------------------------------------------------------

;       Call cleanup routines

__cleanup       PROC    DIST
                PUBLIC  __cleanup

                mov     ax,ds
                mov     es,ax
                push    si
                push    di
                mov     si,offset DGROUP:ExitStart
                mov     di,offset DGROUP:ExitEnd
                call    Cleanup
                pop     di
                pop     si
                ret
__cleanup       ENDP

;       Check for null pointers before exit.  NO-OP on Windows.

__checknull     PROC    DIST
                PUBLIC  __checknull
                ret
__checknull     ENDP

;       Restore grabbed interrupt vectors.  NO-OP on Windows.

__restorezero     PROC    DIST
                PUBLIC  __restorezero
                ret
__restorezero     ENDP

;       Exit to DOS
;
; Usage:        void _terminate(int exitcode, int quick);

__terminate     PROC    DIST
                PUBLIC  __terminate

                mov     bp,sp
                mov     al,[bp+cPtrSize]        ; get exitcode
                mov     ah,4ch
                int     21h
                ret
                endp

WEP             proc    windows pascal far nParam:WORD
                push    si
                push    di

                cmp     _abend, 0
                jne     @@error
                push    nParam
                call    __WEP
                push    ax
                call    __cexit         ; perform cleanup without exiting

@@unlock:

IF LDATA EQ false
                mov     ax,-1
                push    ax
                call    UNLOCKSEGMENT
ENDIF

                pop     ax
                pop     di
                pop     si
                ret

@@error:
                push    1
                jmp     @@unlock

                endp

;       Return default data segment in AX

__GetDGROUP     PROC    FAR
                PUBLIC  __GetDGROUP
                mov     ax, DGROUP
                ret
                endp

;------------------------------------------------------------------
;  Loop through a startup/exit (SE) table,
;  calling functions in order of priority.
;  ES:SI is assumed to point to the beginning of the SE table
;  ES:DI is assumed to point to the end of the SE table
;  First 64 priorities are reserved by Borland
;------------------------------------------------------------------
PNEAR           EQU     0
PFAR            EQU     1
NOTUSED         EQU     0ffh

SE              STRUC
calltype        db      ?                       ; 0=near,1=far,ff=not used
priority        db      ?                       ; 0=highest,ff=lowest
addrlow         dw      ?
addrhigh        dw      ?
SE              ENDS

Initialize      proc near
@@Start:        mov     ax,100h                 ;start with lowest priority
                mov     dx,di                   ;set sentinel to end of table
                mov     bx,si                   ;bx = start of table

@@TopOfTable:   cmp     bx,di                   ;and the end of the table?
                je      @@EndOfTable            ;yes, exit the loop
                cmp     es:[bx.calltype],NOTUSED;check the call type
                je      @@Next
                mov     cl, es:[bx.priority]    ;move priority to CX
                xor     ch, ch
                cmp     cx,ax                   ;check the priority
                jae     @@Next                  ;too high?  skip
                mov     ax,cx                   ;keep priority
                mov     dx,bx                   ;keep index in dx
@@Next:         add     bx,SIZE SE              ;bx = next item in table
                jmp     @@TopOfTable

@@EndOfTable:   cmp     dx,di                   ;did we exhaust the table?
                je      @@Done                  ;yes, quit
                mov     bx,dx                   ;bx = highest priority item
                cmp     es:[bx.calltype],PNEAR  ;is it near or far?
                mov     es:[bx.calltype],NOTUSED;wipe the call type
                push    es                      ;save es
                je      @@NearCall

@@FarCall:      call    DWORD PTR es:[bx.addrlow]
                pop     es                      ;restore es
                jmp     short @@Start

@@NearCall:     call    WORD PTR es:[bx.addrlow]
                pop     es                      ;restore es
                jmp     short @@Start

@@Done:         ret
                endp

Cleanup         proc near
@@Start:        mov     ah,0                    ;start with highest priority
                mov     dx,di                   ;set sentinel to end of table
                mov     bx,si                   ;bx = start of table

@@TopOfTable:   cmp     bx,di                   ;and the end of the table?
                je      @@EndOfTable            ;yes, exit the loop
                cmp     es:[bx.calltype],NOTUSED;check the call type
                je      @@Next
                cmp     es:[bx.priority],ah     ;check the priority
                jb      @@Next                  ;too low?  skip
                mov     ah,es:[bx.priority]     ;keep priority
                mov     dx,bx                   ;keep index in dx
@@Next:         add     bx,SIZE SE              ;bx = next item in table
                jmp     @@TopOfTable

@@EndOfTable:   cmp     dx,di                   ;did we exhaust the table?
                je      @@Done                  ;yes, quit
                mov     bx,dx                   ;bx = highest priority item
                cmp     es:[bx.calltype],PNEAR  ;is it near or far?
                mov     es:[bx.calltype],NOTUSED;wipe the call type
                push    es                      ;save es
                je      @@NearCall

@@FarCall:      call    DWORD PTR es:[bx.addrlow]
                pop     es                      ;restore es
                jmp     short @@Start

@@NearCall:     call    WORD PTR es:[bx.addrlow]
                pop     es                      ;restore es
                jmp     short @@Start

@@Done:         ret
                endp

                ends
                end LibEntry
