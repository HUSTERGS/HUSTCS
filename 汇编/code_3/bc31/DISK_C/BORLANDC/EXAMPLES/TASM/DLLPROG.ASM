; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; DLLPROG.ASM - Template for writing .DLL files.

; From the Turbo Assembler Users Guide

P286               ;286 processor; the minimum if we're writing
                   ; for protected mode
WARN PRO           ;enable protected mode warning
MODEL SMALL        ;this example is SMALL model; others are possible
INCLUDELIB SDLLCEW ;standard library for SMALL model DLL's
                   ; must match model

;Include libraries
INCLUDELIB LIBW          ;Windows library
EXTRN C _ACRTUSED:ABS    ;Force library to be included in link

;Include files
INCLUDE WINDOWS.INC      ;WINDOWS.INC contains assembly language
                         ; definitions for Windows data types, etc.

DATASEG
   ;<<Initialized data goes here>>

UDATASEG
   ;<<Uninitialized data goes here>>

CODESEG
;----------------------------------------------------------------------
;Dynamic link library initialization procedure.
;LibMain is called to initialize the DLL library routines in module.
;This routine should return a 1 in AX if the library is
;successfully initialized, 0 otherwise.
;----------------------------------------------------------------------
LibMain PROC PASCAL FAR
PUBLIC  PASCAL LibMain
ARG     @@hInstance:WORD,   \Descriptor for instance of application
   @@wDataSeg:WORD,         \Library's data segment
   @@wHeapSize:WORD,        \Heap size
   @@lpszCmdLine:DWORD      ;pointer to command line
USES ES,SI,DI
   ;<<User code that initializes library goes here>>
   MOV AX,1                 ;signals successful initialization
   RET
LibMain ENDP

;----------------------------------------------------------------------
;Dynamic link library de-initialization procedure.
;This routine is optional.
;The example here does nothing; it is included as a guide.
;Returns AX=1 if deinitialization was successful
;----------------------------------------------------------------------
WEP PROC  WINDOWS PASCAL FAR
PUBLICDLL PASCAL WEP
ARG       @@nParameter      ;parameter; specifies situation in which
                            ; WEP is called
USES ES,SI,DI
   ;<<De-initialization code goes here>>
   MOV AX,1                 ;signals successful de-initialization
   RET
WEP ENDP

;----------------------------------------------------------------------
;Dynamic Link Library Routines.
;All user-defined library routines must be declared as PASCAL FAR
;procedures, and must be published using the PUBLICDLL directive.
;The arguments passed to and returned from DLL procedures are
;determined entirely by the programmer.
;----------------------------------------------------------------------
;[SetHello]
;Copy string 'Hello, Windows!' into a buffer.
;Pass address of buffer.
;Return length of string in AX.
SetHello  PROC WINDOWS PASCAL FAR
PUBLICDLL PASCAL SetHello
ARG       @@lpszParam:DWORD         ;storage for string
USES ES,SI,DI
   ;<<User code goes here - here's an example:>>

DATASEG
@@Hello   DB 'Hello, Windows!',0
@@HSize = $-@@Hello
   CODESEG
   MOV SI,OFFSET @@Hello
   LES DI,@@lpszParam
   MOV CX,@@Hsize
   CLD
   REP MOVSB
   MOV AX,@@Hsize-1
   RET
SetHello ENDP
END
P8086          ;select the processor
MODEL TINY     ;always must be TINY model

DATASEG
   ;<<Any initialized data is defined here>>

UDATASEG
   ;<<Any uninitialized data is defined here>>

   ;<<Set up room for user stack, if default stack is not desired>>
   DW 100H DUP (?)
MyStack  LABEL WORD

CODESEG        ;this marks the start of executable code
   STARTUPCODE
   ;COM has all available memory allocated to it

   ;Stack is already set up to top of 64K segment
   ;We can move it if we want using the following instruction:
   MOV SP,OFFSET MyStack

   ;Now execute user code
   ;The code can be placed here, but it looks better to call it.
   ;DoIt returns the exit code in AL.
   CALL DoIt

   ;Exit to DOS when complete
   MOV AH,4CH
   INT 21H
   RET

DoIt PROC NEAR
   ;<<Your code goes here>>
   MOV AL,1
   RET
DoIt ENDP
END
