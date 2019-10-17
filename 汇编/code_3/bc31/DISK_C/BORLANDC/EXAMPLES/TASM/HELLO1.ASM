; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; HELLO.ASM - Display the message "Hello World"

; From the Turbo Assembler Users Guide - Getting started

   .MODEL small
   .STACK 100h
   .DATA
HelloMessage DB 'Hello, world',13,10,'$'
   .CODE
   mov  ax,@data
   mov  ds,ax                  ;set DS to point to the data segment
   mov  ah,9                   ;DOS print string function
   mov  dx,OFFSET HelloMessage ;point to "Hello, world"
   int  21h                    ;display "Hello, world"
   mov  ah,4ch                 ;DOS terminate program function
   int  21h                    ;terminate the program
   END
