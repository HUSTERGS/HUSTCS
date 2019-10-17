; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; COUNTADD.ASM  - Example of getting around name mangling

; From the Turbo Assembler Users Guide

     .MODEL small   ; Select small model (near code and data)
     .CODE
     PUBLIC _count_add_increment
_count_add_increment  PROC
     ARG count_offset:word      ; Address of the member variable
     push bp                    ; Preserve caller's stack frame
     mov  bp,sp                 ; Set our own stack frame
     mov  bx,[count_offset]     ; Load pointer
     inc  word ptr [bx]         ; Increment member variable
     pop  bp                    ; Restore callers stack frame
     ret
_count_add_increment  ENDP

     PUBLIC _count_add_add
_count_add_add  PROC
     ARG count_offset:word,what_to_add:word
     push bp
     mov  bp,sp
     mov  bx,[count_offset]     ; Load pointer
     mov  ax,[what_to_add]
     add  [bx],ax
     pop  bp
     ret
_count_add_add  ENDP

     end
