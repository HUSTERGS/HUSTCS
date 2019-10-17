; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; HELLO2.ASM - Editted version of HELLO.ASM.
;              Display greeting after accepting input.

; From the Turbo Assembler Users Guide - Getting started

   DOSSEG
   .MODEL  SMALL
   .STACK  100h
   .DATA
TimePrompt DB 'Is it after 12 noon (Y/N)?$'
GoodMorningMessage  LABEL  BYTE
   DB  13,10,'Good morning, world!',13,10,'$'
GoodAfternoonMessage  LABEL  BYTE
   DB  13,10,'Good afternoon, world!',13,10,'$'
   .CODE
   mov  ax,@data
   mov  ds,ax                                ;set DS to point to the data segment
   mov  dx,OFFSET TimePrompt                 ;point to the time prompt
   mov  ah,9                                 ;DOS print string function #
   int  21h                                  ;display the time prompt
   mov  ah,1                                 ;DOS get character function #
   int  21h                                  ;get a single-character response
   cmp  al,'y'                               ;typed lowercase y for after noon?
   jz   IsAfternoon                          ;yes, it's after noon
   cmp  al,'Y'                               ;typed uppercase Y for after noon?
   jnz  IsMorning                            ;no, it's before noon
IsAfternoon:
   mov  dx,OFFSET GoodAfternoonMessage       ;point to the afternoon greeting
   jmp  DisplayGreeting
IsMorning:
   mov  dx,OFFSET GoodMorningMessage         ;point to the before noon greeting
DisplayGreeting:
   mov  ah,9                                 ;DOS print string function #
   int  21h                                  ;display the appropriate greeting
   mov  ah,4ch                               ;DOS terminate program function #
   int  21h                                  ;terminate the program
   END
