; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; VAREXCH.ASM

; From the Turbo Assembler Users Guide

CODE      SEGMENT
          ASSUME cs:CODE,ds:NOTHING

; Parameters (note that offset are +2 because of push bp)

var1      EQU    DWORD PTR ss:[bp+12]
var2      EQU    DWORD PTR ss:[bp+8]
count     EQU    WORD PTR  ss:[bp+6]


Exchange  PROC FAR
          PUBLIC Exchange
          cld                        ;exchange goes upward
          mov     dx,ds              ;save DS
          push    bp
          mov     bp,sp              ;get stack base
          lds     si,var1            ;get first address
          les     di,var2            ;get second address
          mov     cx,count           ;get number of bytes to move
          shr     cx,1           ;get word count (low bit -> carry)
          jnc     ExchangeWords  ;if no odd byte, enter loop
          mov     al,es:[di]     ;read odd byte from var2
          movsb                  ;move a byte from var1 to var2
          mov     [si-1],al      ;write var2 byte to var1
          jz      Finis          ;done if only 1 byte to exchange
ExchangeWords:
          mov     bx,-2          ;BX is a handy place to keep -2
ExchangeLoop:
          mov     ax,es:[di]         ;read a word from var2
          movsw                      ;do a move from var1 to var2
          mov     [bx][si],ax        ;write var2 word to var1
          loop    ExchangeLoop       ;repeat "count div 2" times
Finis:
          mov     ds,dx              ;get back Turbo's DS
          pop     bp
          ret     10
Exchange  ENDP
CODE      ENDS
          END
