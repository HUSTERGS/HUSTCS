; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; COUNT.ASM
; Small model C-callable assembler function to count the number of
; lines and characters in a zero-terminated string.
;
; Function prototype:
;       extern unsigned int LineCount(char * near StringToCount,
;              unsigned int near * CharacterCountPtr);
; Input:
;       char near * StringToCount: pointer to the string on which a
;       line count is to be performed
;
;       unsigned int near * CharacterCountPtr: pointer to the
;                int variable in which the character count is to be stored
;

; From the Turbo Assembler User's Guide - Interfacing Turbo Assembler
;                                          with Borland C++

NEWLINE  EQU     0ah                ;the linefeed character is C's
                                    ; newline character
         DOSSEG
         .MODEL  SMALL
         .CODE
         PUBLIC  _LineCount
_LineCount       PROC
         push    bp 
         mov     bp,sp
         push    si                 ;preserve calling program's register
                                    ; variable, if any
         mov     si,[bp+4]          ;point SI to the string
         sub     cx,cx              ;set character count to 0
         mov     dx,cx              ;set line count to 0 
LineCountLoop:
         lodsb                      ;get the next character
         and     al,al              ;is it null, to end the string?
         jz      EndLineCount       ;yes, we're done
         inc     cx                 ;no, count another character
         cmp     al,NEWLINE         ;is it a newline?
         jnz     LineCountLoop      ;no, check the next character
         inc     dx                 ;yes, count another line
         jmp     LineCountLoop
EndLineCount:
         inc     dx                 ;count the line that ends with the
                                    ; null character
         mov     bx,[bp+6]          ;point to the location at which to
                                    ; return the character count
         mov     [bx],cx            ;set the character count variable
         mov     ax,dx              ;return line count as function value
         pop     si                 ;restore calling program's register
                                    ; variable, if any
         pop     bp
         ret
_LineCount       ENDP
         END
