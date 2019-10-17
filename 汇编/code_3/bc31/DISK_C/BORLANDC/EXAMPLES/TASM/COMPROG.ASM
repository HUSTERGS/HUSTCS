; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; COMPROG.ASM - Template for writing .COM files.

; From the Turbo Assembler Users Guide

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
