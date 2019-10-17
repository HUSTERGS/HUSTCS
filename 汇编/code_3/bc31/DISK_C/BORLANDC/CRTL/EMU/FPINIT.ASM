;[]------------------------------------------------------------[]
;|      FPINIT.ASM -- Emulator initialization                   |
;[]------------------------------------------------------------[]

;
;       C/C++ Run Time Library - Version 5.0
; 
;       Copyright (c) 1986, 1992 by Borland International
;       All Rights Reserved.
; 

        NAME    fpInit

; Floating point (FPU) initialization.
; Includes detection of coprocessor, checking for environment override
; (SET 87=N), installation of interrupt vectors, and FINIT.

; This module replaces EMUINIT and 87INIT, both used in TC 2.0.
; It also replaces some code in C0 related to floating point.
; Assemble with /DFP87 for hard 80x87 opcodes.

; Caution: This code is in the _TEXT segment, and assumes that certain
; external routines can be called with NEAR calls.

.286
.287
locals  @@

include equates.asi

ifdef   FP87
_Emu_   equ     0               ; no emulation, '87 required
else
_Emu_   equ     1               ; emulator
endif

include emurules.asi
include emuvars.asi

; Segment and Group declarations

Header@

DSeg@

; Public data
; initialize to -1
; if executed, emu1st will change it to 0, 1, 2, or 3
PubSym@         _8087,  <dw     -1>,    __CDECL__

; External References
ExtSym@         _version, WORD, __CDECL__
ExtSym@         _psp, WORD, __CDECL__
ExtSym@         _protected, BYTE, __CDECL__
ExtSym@         _LDT, WORD, __CDECL__
ExtSym@         _default87, WORD, __CDECL__

DSegEnd@

; External data, possibly not in DGROUP.
ExtSym@         _fpstklen, word, __CDECL__
ExtSym@         _stklen, word, __CDECL__
extrn   __turboCvt : ABS        ; To force the link of REALCVT for printf
extrn   __emu : byte

EmuAssume@      SS

; Public procs.

public  ___fpreset

; External procs.

;extrn  __fperror : far
extrn   __fperror : near
ExtProc@        abort,  __CDECL__       ; called if init fails
;extrn  _abort : near                   ; called if init fails

;-----------------------------------------------------------------------------

FpuPriority     equ     16d
StartupStack    equ     24      ; must be even

; debug symbols
ifdef   DEBUG
public  int2handler
public  int75handler
public  emu1st
public  emuLast
public  init87
;public failure
;public __fpustate
endif

        PAGE
;[]------------------------------------------------------------[]
;|                                                              |
;|      General notes                                           |
;|      =============                                           |
;|                                                              |
;|      Emu086 is  designed to run  in either of  two modes:    |
;|      with   or   without   the   presence   of  the  8087    |
;|      co-processor. The  first action it takes  is to test    |
;|      for the  presence of the co-processor.  Depending on    |
;|      which it  finds, it connects  one of two  modules to    |
;|      the   interrupt   vectors   reserved   for   numeric    |
;|      coprocessor emulation.                                  |
;|                                                              |
;|      E087ENTR.ASM ("Real-87")                                |
;|                                                              |
;|      This module  is to be  used when there  is hardware     |
;|      support.  It  is  much  the  smaller  module.  This     |
;|      module will service 10  interrupt vectors (34h thru     |
;|      3Dh) which are used for floating point invocation by    |
;|      application  programs.  For  the first eight of  the    |
;|      vectors  plus some  functions of  the ninth, Real-87    |
;|      will patch  the calling program with  the equivalent    |
;|      8087  instruction  sequence  and  then  restart  the    |
;|      program to run the  patch. The application will thus    |
;|      be  converted  at  run  time   to  the  use  of  the    |
;|      co-processor.                                           |
;|                                                              |
;|      The non-converted  functions of the  ninth interrupt    |
;|      are transcendental  functions not directly  provided    |
;|      by the 8087. These  functions must be interpreted by    |
;|      a library  provided in Real-87, which  uses the 8087    |
;|      for computations.                                       |
;|                                                              |
;|      The  tenth   interrupt  is  used  for   a  NOP-FWAIT    |
;|      sequence. It is  patched the first time it  is used,    |
;|      like the other direct iNDP instructions.                |
;|                                                              |
;|      The  shortcut  vector  is  used  for instructions or    |
;|      sequences frequently  used by the compiler.  Some of    |
;|      them  are  equivalent  to  '87  instructions,  while    |
;|      others cannot be reduced  to a simple sequence. When    |
;|      the '87  is present the  direct equivalents will  be    |
;|      patched  with  in-line  code,  while  the  composite    |
;|      sequences are excuted in the interrupt routine.         |
;|                                                              |
;|      E086ENTR.ASM ("Virtual-87")                             |
;|                                                              |
;|      The Virtual-87 module is to be used when the 8087 is    |
;|      not  present.  It  supplies  all  code  necessary to    |
;|      emulate the  8087 (excepting some rare  details. See    |
;|      the   description   in   the   general   notes   for    |
;|      e086Entr.asm).  No  patching  occurs  in  this case,    |
;|      except for the tenth  interrupt which can be patched    |
;|      to a No-op sequence.                                    |
;|                                                              |
;[]------------------------------------------------------------[]

        PAGE
;[]------------------------------------------------------------[]
;|                                                              |
;|      FIXUP constants for FPU                                 |
;|                                                              |
;|      If none of the F??RQQ publics are used, then no         |
;|      floating point code will be linked.                     |
;|                                                              |
;[]------------------------------------------------------------[]

emInt           equ     34h     ; allocated to 8087 by Microsoft Corp.
shortcutInt     equ     3Eh     ; used by Borland for shortcuts
fpuInt          equ     02h     ; FPU interrupt number (normally = NMI)

        public  FIDRQQ          ; wait, esc
        public  FIARQQ          ; wait, DS:
        public  FICRQQ          ; wait, CS:
        public  FIERQQ          ; wait, ES:
        public  FISRQQ          ; wait, SS:
        public  FIWRQQ          ; nop, wait
        public  FJARQQ          ; Esc nn -> DS:nn
        public  FJCRQQ          ; Esc nn -> CS:nn
        public  FJSRQQ          ; Esc nn -> ES:nn


; Use full emulator if _Emu_ is true.

if      _Emu_

FIDRQQ  equ     05C32h
FIARQQ  equ     0FE32h
FICRQQ  equ     00E32h
FIERQQ  equ     01632h
FISRQQ  equ     00632h
FIWRQQ  equ     0A23Dh
FJARQQ  equ     04000h
FJCRQQ  equ     0C000h
FJSRQQ  equ     08000h

else

FIDRQQ  equ     00000h
FIARQQ  equ     00000h
FICRQQ  equ     00000h
FIERQQ  equ     00000h
FISRQQ  equ     00000h
FIWRQQ  equ     00000h
FJARQQ  equ     00000h
FJCRQQ  equ     00000h
FJSRQQ  equ     00000h

endif

        PAGE
;[]------------------------------------------------------------[]
;|                                                              |
;|      Emulator entry points                                   |
;|                                                              |
;[]------------------------------------------------------------[]

if      _Emu_
; This is the segment containing the full emulation code.
EmuSeg@
EXTRN   e086_Entry      : FAR
EXTRN   e086_Shortcut   : FAR
EmuSegEnd@
endif

; This is the segment containing the code to work with the 8087 chip.
E87Seg@
EXTRN   e087_Entry      : FAR
EXTRN   e087_Shortcut   : FAR
EXTRN   e087_Trap       : FAR
E87SegEnd@

        PAGE

CSeg@

        PAGE
;[]------------------------------------------------------------[]
;|                                                              |
;|      emu1st -- Emulator installation routine                 |
;|                                                              |
;|      This  function  is  called  by  RTLstart  before any    |
;|      numeric work  begins. It needs  to save the  initial    |
;|      interrupt vectors  before it can install  itself.       |
;|                                                              |
;|      It will sense whether an iNDP87 co-processor exists,    |
;|      only if the _8087 variable is set to -1, which means    |
;|      that no "87" environment  variable has been defined.    |
;|      In that case it will choose which of the two numeric    |
;|      support modules is to be kept. The interrupt vectors    |
;|      34..3D  are  claimed  for  iNDP  software  interrupt    |
;|      support.                                                |
;|                                                              |
;|      An  additional  interrupt,  3Eh,  is  used  for  the    |
;|      Shortcut entries.                                       |
;|                                                              |
;|      The __fpreset function installs the interrupt vectors   |
;|      and  re-initializes the  emulator. This  function is    |
;|      called by the _fpreset() function of the RTL.           |
;|                                                              |
;[]------------------------------------------------------------[]

; vectors 34h .. 3Eh, and 75h, and 2
originalVectors dd      12 DUP (?)
FPEpriorVector  dd      ?               ; interrupt handler for NMI

plus_inf        dd      7F800000R       ; + infinity

; borrowed from T. Pascal, DOS 3.1 BIOS
; avoid DOS 3.2 stack swap
int75handler    proc    far
        push    ax
        xor     al, al                  ; Clear BUSY latch
        out     0F0h, al
        mov     al, 20H                 ; End-of-interrupt
        out     0A0h, al
        out     20h, al
        pop     ax
        int     2
        iret
int75handler    endp


; Floating point exceptions on  PC-compatible machines are routed
;       to the NMI  vector. This vector must be  captured but the
;       previous contents need to  be remembered. The priorVector
;       is  used if NMI occurs  but the coprocessor did not cause
;       it, and also the priorVector  must be restored at the end
;       of the program.

OpJmpf          equ     0EAh            ; opcode for far jump

int2handler     proc    far
        push    ax
        mov     ax, seg __emu
        call    e087_Trap       ; preserves all but ax, flags
ret_trap:
; returns only if error could not be handled
        jc      @@err
        pop     ax
;       jmp     FPEpriorVector
        db      OpJmpf
nmi     dw      2 dup (?)

@@err:
; trap record in ss:ax
;       mov     bx, ax
        xchg    bx, ax
; Set DS := DGROUP
        mov     ax, seg _8087@
        mov     DS, ax
        call    __fperror
        pop     ax
        iret
int2handler     endp

ifdef   VarStack

abortMSG        db      "Insufficient FPU or CPU stack.", 13, 10
lgth_abortMSG   equ     $ - abortMSG

failure proc    near
        mov     ah, 040h
        mov     bx, 2
        mov     cx, lgth_abortMSG
        mov     dx, offset abortMSG
        push    CS
        pop     DS
        MSDOS@                  ; write message at DS:DX
        call    abort@
; never returns
failure endp

endif

emu1st  proc    near            ; called only by startup code
        push    DS
        push    si
        push    di

ifdef   VarStack

; Make some space on the stack.

        mov     ax, seg _fpstklen@
        mov     ES, ax
        mov     ax, ES:_fpstklen@
        and     al, 0FEh                ; round to even
        mov     dx, seg _stklen@
        mov     ES, dx
        cmp     ax, ES:_stklen@
        jae     failure
        cmp     ax, MinFpStack
        jb      failure

        mov     cx, StartupStack
        mov     si, sp
        add     ax, cx
        sub     sp, ax
        mov     di, sp

; set start of FPU stack
; leave a spare to trap emulated underflows
        lea     ax, [si-size_emu_temp]
        mov     SS:__emu.ws_initSP, ax

; move the stack down
        mov     dx, SS
        mov     DS, dx
        mov     ES, dx
        cld
        shr     cx, 1
        rep     movsw

; set end of FPU stack
        mov     SS:__emu.ws_lastSP, di

else

; set end of FPU stack
        lea     ax, __emu + (size fpu)
        mov     SS:__emu.ws_lastSP, ax

; set start of FPU stack
; leave a spare to trap emulated underflows
        add     ax, MinFpStack - size_emu_temp
        mov     SS:__emu.ws_initSP, ax

endif

; Save prior vectors in the code segment.
; If in protected mode, make the segment writeable.
; Save _protected in SS where FPU can find it.

        mov     ax, _LDT@
        mov     SS:__emu.ws_LDT, ax
        mov     al, _protected@
        mov     SS:__emu.ws_protected, al
        mov     cx, CS
        xor     cl, al                  ; al = 0 or 8
        mov     DS, cx

        ASSUME  DS:_TEXT

        mov     ax, 3500h + emInt
        mov     cx, 11          ; there are 10 emulation vectors
        mov     di, offset originalVectors
rememberLoop:
        MSDOS@                  ; ES:BX = read interrupt vector
        mov     DS:[di].W0, bx
        mov     DS:[di].W1, ES
        add     di, 4
        inc     ax
        loop    rememberLoop

; grab INT 75h
        mov     ax,3500h + 75h
        MSDOS@                  ; ES:BX = read interrupt vector
        mov     DS:[di].W0, bx
        mov     DS:[di].W1, ES
        add     di, 4

; grab INT 2
        mov     ax,3500h + fpuInt
        MSDOS@                  ; ES:BX = read interrupt vector
        mov     DS:[di].W0, bx
        mov     DS:[di].W1, ES
        mov     DS:nmi[0], bx
        mov     DS:nmi[2], ES

; Set DS := DGROUP
        mov     ax, seg _8087@
        mov     DS, ax

        ASSUME  CS:_TEXT, DS:seg _8087@

; Do we need to test 80?87 presence ?

        mov     bx, -1
if      _Emu_
        mov     ES, _psp@

; Look for a "87" environment variable.
; Each variable is ended by a 0 and a zero-length variable stops
; the environment. The environment can NOT be greater than 32k.

        mov     ES, ES: word ptr [2Ch]  ; environment segment
        sub     di, di                  ; ES:[di] points to environ
        mov     cx, 07FFFh              ; Environment cannot be > 32 Kbytes
        mov     al, 0
        cld
env87next:
        repne   scasb           ; direction flag is clear
        jcxz    env87done       ; count exhausted imply end
        cmp     al, ES:[di]     ; double zero bytes imply end
        je      env87done
        cmp     word ptr ES:[di], 3738h         ; low = '8', hi = '7'
        jne     env87next
        mov     dx, ES:[di+2]
        cmp     dl, '='
        jne     env87next
        inc     bx
        and     dh, not ('y' - 'Y')
        cmp     dh, 'Y'
        jne     env87done
        inc     bx
env87done:
endif
        pop     di
        pop     si

;[]------------------------------------------------------------[]
;|                                                              |
;|      Co-processor autosense routine                          |
;|                                                              |
;|      Note:   The code used to test the presence of a         |
;|              numeric coprocessor is similar to that          |
;|              recommended by IBM.                             |
;|                                                              |
;[]------------------------------------------------------------[]

; If  CPU is  an 80286,  the FNINIT  instruction can  generate an
;       interrupt  if  the  NDP?87  is  not  present.  On IBM, an
;       interrupt handler is provided by  the BIOS but it may NOT
;       on clones. So won't test if there is or not an NDP?87, we
;       will just trust the BIOS equipment flag.

; IBM uses these ports to reset the coprocessor.
; Some clone have the ports wired incorrectly, in which case it may
; be necessary to delete the OUT instructions.

; Check whether 87=N
        or      bx, bx
        jz      @@set_flag

;       xor     ax, ax
;       out     0F0h, al        ; Clear the busy latch (INT REQ)
;       out     0F1h, al        ; Reset chip in real mode

; Distinguish between 8088/8086 and 80286/80386.
        push    sp
        pop     cx
        cmp     cx, sp
        jne     TestPresence

; Possibly override BIOS test.
        or      bx, bx
        jg      @@test_inf

; The CPU is an 80286 or 80386, so trust the BIOS equipment flag.
        int     11h
        and     al, 2
        jz      @@test_done             ; jump with al = 0

; Distinguish between a 80287 and 80387 using the infinity control.
; 8087 and 80287 support both infinity modes, defaults to projective
; 80387 supports affine infinity only

@@test_inf:
;       xor     ax, ax
;       out     0F0h, al        ; Clear the busy latch (INT REQ)
;       out     0F1h, al        ; Reset chip in real mode

        fninit
ifdef   Intel_Test
        fld1
        fldz
        fdiv                    ; generate infinity
        fld     st              ; duplicate TOS
        fchs                    ; form -INF
        fcompp                  ; compare +INF to -INF
else
        fld     plus_inf
        fchs
        fcomp   plus_inf        ; compare +INF to -INF
endif
        fstsw   ax              ; we have a 287 or better
        sahf

        mov     al, 2
        je      @@test_done     ; equal on 80287 only
        inc     al
        jmp     short @@test_done

; First check to see if a real 8087 is available. That allows
;       us to select which version of NDP support is to remain
;       resident.

TestPresence:
;       xor     ax, ax
;       out     0F0h, al        ; Clear the busy latch (INT REQ)
        FNINIT
        mov     _8087@, 0
        FNSTCW  _8087@          ; Store the control word

        mov     cx, 20
        loop    this near               ; Delay awhile
        mov     cx, _8087@              ; Get NPX control word
        and     cx, 0F3Fh               ; Mask off undefined bits
        cmp     cx, 033Fh               ; Do we have a math coprocessor
        jne     @@test_done             ; No ...

        mov     _8087@, -1
        FNSTSW  _8087@                  ; Store the status word
        mov     cx, 20
        loop    this near               ; Delay awhile
        test    _8087@, 0B8BFh          ; All bits off that should be?
        jnz     @@test_done
        inc     al

@@test_done:
        cbw
        xchg    ax, bx

@@set_flag:
        mov     _8087@, bx
        mov     SS:__emu.ws_8087, bl
        pop     DS
; fall thru to reset everything
emu1st  ENDP

temp1   equ     [bp-8]
temp2   equ     [bp-4]

___fpreset      proc    near
        push    DS
        push    bp
        mov     bp, sp
        sub     sp, 8

        mov     bx, seg _8087@
        mov     DS, bx                  ; save DGROUP for later

        ASSUME  CS:_TEXT, DS:seg _8087@

        cmp     _8087@, 0
        mov     temp1.W0, offset e087_Entry
        mov     temp1.W1, seg e087_Entry
        mov     temp2.W0, offset e087_Shortcut
        mov     temp2.W1, seg e087_Shortcut

if      _Emu_
        jne     doCapture
        mov     temp1.W0, offset e086_Entry
        mov     temp1.W1, seg e086_Entry
        mov     temp2.W0, offset e086_Shortcut
        mov     temp2.W1, seg e086_Shortcut
endif

; Now take over the vectors.

doCapture:
        mov     ax, 2500h + emInt
        mov     cx, 10          ; there are 10 emulation vectors
        lds     dx, temp1.DD0
captureLoop:
        MSDOS@                  ; Set interrupt vector with DS:DX
        inc     ax
        loop    captureLoop
; The Shortcut vector must be captured too.

        mov     ax, 2500h + shortcutInt
        lds     dx, temp2.DD0
        MSDOS@                  ; Set interrupt vector with DS:DX

; install INT 2 handler
        mov     ax, 2500h + fpuInt
        push    CS
        pop     DS
        mov     dx, offset int2handler
        MSDOS@                  ; Set interrupt vector with DS:DX

; No need for the INT 75 hack if
;       the 8087 is being emulated, or
;       the version of DOS different from 3.20
        mov     DS, bx                  ; set DS = DGROUP
        cmp     _8087@, 0
        je      init87
        mov     ax, _version@
        xchg    ah, al
        cmp     ax, 20 * 100h + 3       ; ok if version != 3.20
        jne     init87

; install INT 75 handler
        mov     ax, 2500h + 75h
        push    CS
        pop     DS
        mov     dx, offset int75handler
        MSDOS@                  ; Set interrupt vector with DS:DX

; Now emulation is installed. Ensure it is initialized.
; We must use an emulated FINIT in all cases.
init87:
        Int     emInt + 3
        db      0E3h            ; (Wait, FINIT) equivalent
        mov     SS:__emu.ecount1, 0
        mov     SS:__emu.ecount2, 0

; FINIT will disable all exception interrupts.  We want some enabled.
        mov     DS, bx                  ; set DS = DGROUP
;       mov     temp1.W0, CW_DEFAULT
        mov     ax, _default87@
        mov     temp1.W0, ax

; 80387 is fully IEEE, need not trap denormal exception
        cmp     _8087@, 3
        jl      @@control
        or      temp1.W0, EM_DENORMAL
@@control:
        emul
        FLDCW   temp1.W0
; set shadow control
        mov     ax, temp1.W0
        and     SS:__emu.ws_control, ax

; dual mode startup requires AX=DX=0
        xor     ax, ax
        cwd

        mov     sp, bp
        pop     bp
        pop     DS
        ret
___fpreset      endp

        PAGE
;[]------------------------------------------------------------[]
;|                                                              |
;|      emuLast -- Emulator termination routine                 |
;|                                                              |
;|      emuLast  is called  by RTLstart  after the  "main"      |
;|      routine returns or the program exits. Its purpose is    |
;|      to  restore the  original contents  of the interrupt    |
;|      vectors 34h..3Dh, plus the Shortcut vector.             |
;|                                                              |
;[]------------------------------------------------------------[]

emuLast proc    near    ; called only by startup code
        push    DS

; Set DS := DGROUP
        mov     ax, seg _8087@
        mov     DS, ax

        ASSUME  CS:_TEXT, DS:seg _8087@

; Did we ever get initialized?
        cmp     _8087@, 0
        jl      @@done

; leave the chip in a clean state
        emul
        finit

        mov     ax, 2500h + emInt
        mov     bx, offset originalVectors
        mov     cx, 11          ; there are 10 emulation vectors
restoreLoop:
        lds     dx, CS:[bx]
        MSDOS@                  ; Set interrupt vector with DS:DX
        add     bx, 4
        inc     ax
        loop    restoreLoop

; restore INT 75h
        mov     ax, 2500h + 75h
        lds     dx, CS:[bx]
        MSDOS@                  ; Set interrupt vector with DS:DX

; restore INT 2
        mov     ax, 2500h + fpuInt
        lds     dx, CS:[bx+4]
        MSDOS@                  ; Set interrupt vector with DS:DX

@@done:
        pop     DS
        ret
emuLast endp

ifdef   VarStack

; clean off all '87 registers, put chip in a predictable state
; preserves all but bx, cx, flags
; no segment assumptions other than SS
; leave current FPU stack pointer in a word at SS:bx
; void far cdecl fpustate(void);

public  __fpustate

__fpustate      proc    far
        cmp     SS:__emu.ws_8087, 0
        je      @@ret
        noemul
; fill the '87
        mov     cx, 8
@@1:    fldz
        loop    @@1
        fcom    st(7)
; empty the '87
        mov     cl, 8
@@2:    fstp    st(0)
        loop    @@2
; put the '87 in a predictable state
        mov     cx, SS:__emu.ws_adjust
        and     cx, 111b
        jz      @@4
@@3:    fincstp
        loop    @@3
@@4:
        mov     SS:__emu.ws_adjust, cx          ; cx = 0
@@ret:
        lea     bx, SS:__emu.ws_TOS
        ret
__fpustate      endp

endif

;[]------------------------------------------------------------[]
;|                                                              |
;|      __fpuint - return FPU interrupt number                  |
;|                                                              |
;|      This function returns the FPU exception number in AX.   |
;|      Used by emudecod.asm.                                   |
;|                                                              |
;[]------------------------------------------------------------[]

        public  __fpuint

__fpuint        proc    far
        mov     ax, fpuInt
        ret
__fpuint        endp

CSegEnd@

ifdef   VarStack

_EMUSEG SEGMENT PARA COMMON 'DATA'
        dw      __fpustate
_EMUSEG ENDS

endif

        PAGE
;[]------------------------------------------------------------[]
;|                                                              |
;|      FPU automatic initialization logic                      |
;|                                                              |
;[]------------------------------------------------------------[]

PNEAR           EQU     0
PFAR            EQU     1
NOTUSED         EQU     0ffh

SE              STRUC
calltype        db      ?                       ; 0=near,1=far,ff=not used
priority        db      ?                       ; 0=highest,ff=lowest
addrlow         dw      ?
IFNDEF  __TINY__
addrhigh        dw      ?
ENDIF
SE              ENDS

_INIT_          SEGMENT WORD PUBLIC 'INITDATA'
;SE     < PFAR, FpuPriority, offset emu1st, seg emu1st >
SE      < PNEAR, FpuPriority, offset emu1st, 0 >
_INIT_          ENDS

_EXIT_          SEGMENT WORD PUBLIC 'EXITDATA'
;SE     < PFAR, FpuPriority, offset emuLast, seg emuLast >
SE      < PNEAR, FpuPriority, offset emuLast, 0 >
_EXIT_          ENDS

END
