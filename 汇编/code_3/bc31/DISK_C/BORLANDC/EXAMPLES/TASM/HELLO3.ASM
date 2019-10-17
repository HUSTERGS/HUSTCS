; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; HELLOPRN.ASM - Display "Hello World" on the printer

; From the Turbo Assembler Users Guide - Getting started

   DOSSEG
   .MODEL SMALL
   .STACK 100h
   .DATA
HelloMessage DB 'Hello, world',13,10,12
HELLO_MESSAGE_LENGTH EQU $ - HelloMessage
   .CODE
   mov  ax,@data
   mov  ds,ax                        ;set DS to point to the data segment
   mov  ah,40h                       ;DOS write to device function #
   mov  bx,4                         ;printer handle
   mov  cx,HELLO_MESSAGE_LENGTH      ;number of characters to print
   mov  dx,OFFSET HelloMessage       ;string to print
   int  21h                          ;print "Hello, world"
   mov  ah,4ch                       ;DOS terminate program function #
   int  21h                          ;terminate the program
   END
