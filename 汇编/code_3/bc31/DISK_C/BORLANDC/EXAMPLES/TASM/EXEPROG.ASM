; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; EXEPROG.ASM - Template for writing .EXE files.

; From the Turbo Assembler Users Guide

P8086         ;select the processor
DOSSEG        ;indicate DOS segment conventions
MODEL SMALL   ;select the model - can be any model
DOSHEAP = 0   ;specify whether DOS heap is to be used, or
              ; internal heap; 1 indicates DOS heap; 0 internal
STACK 200h    ;reserve stack space as needed for application

DATASEG
   ;<<Any initialized data is defined here>>

UDATASEG
   ;<<Any uninitialized data is defined here>>

CODESEG
   ;This marks the start of executable code
   STARTUPCODE
   ;EXE program has all available memory allocated to it

IF DOSHEAP
   ;Release all memory except the amount currently being used
   ;End of stack is end of non-heap portion of program
   MOV BX,SP
   ADD BX,15    ;convert SP into paragraphs
   SHR BX,4
   MOV AX,SS    ;calculate size of program using ES PSP address
   ADD BX,AX
   MOV AX,ES
   SUB BX,AX
   MOV AH,4AH   ;resize memory block with PSP
   INT 21H      ;address in ES
ENDIF

;Now execute user code.
;The code can be placed here, but it looks better to call it;
;DoIt returns an exit value in AL, which corresponds to ERRORLEVEL in
;.BAT files.
CALL DoIt

   ;Exit to DOS when complete
   MOV AH,4CH
   INT 21H
   RET

;Arguments to this procedure:
;ES=PSP address (for command-line arguments)
;Must return an exit value in AL
DoIt PROC NEAR
   ;<<Your code goes here>>
   RET
DoIt ENDP
END
