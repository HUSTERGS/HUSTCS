; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; SOMESTR.ASM

; From the Turbo Assembler Users Guide

DATA      SEGMENT PUBLIC
          EXTRN prefixSeg : WORD  ;gives location of PSP
DATA      ENDS
CODE      SEGMENT PUBLIC
          ASSUME cs:CODE,ds:DATA

EnvString PROC FAR
          PUBLIC  EnvString
          push    bp
          cld                     ;work upward
          mov     es,[prefixSeg]  ;look at PSP
          mov     es,es:[2Ch]     ;ES:DI points at environment
          xor     di,di           ;which is paragraph-aligned
          mov     bp,sp           ;find the parameter address
          lds     si,ss:[bp+6]    ;which is right above the
                                  ; return address
          ASSUME  ds:NOTHING
          lodsb                   ;look at length
          or      al,al           ;is it zero?
          jz      RetNul          ;if so, return
          mov     ah,al           ;otherwise, save in AH
          mov     dx,si           ;DS:DX contains pointer
                                  ; to first parm char
          xor     al,al           ;make a zero
Compare:
          mov     ch,al           ;we want ch=0 for next count, if any
          mov     si,dx           ;get back pointer to string sought
          mov     cl,ah           ;get length
          mov     si,dx           ;get pointer to string sought
          repe    cmpsb           ;compare bytes
          jne     Skip            ;if fails, try next string
          cmp     byte ptr es:[di],'='
                                  ;compare succeeded; is next
                                  ; char '='?
          jne     NoEqual         ;if not, still no match
Found:
          mov     ax,es           ;make DS:SI point to string
                                  ; we found
          mov     ds,ax
          mov     si,di
          inc     si              ;get past the equal (=) sign
          les     bx,ss:[bp+10]   ;get address of function result
          mov     di,bx           ;put it in ES:DI
          inc     di              ;get past the length byte
          mov     cl,255          ;set up a maximum length
CopyLoop:
          lodsb                   ;get a byte
          or      al,al           ;zero test
          jz      Done            ;if zero, we're done
          stosb                   ;put it in the result
          loop    CopyLoop        ;move up to 255 bytes
Done:     not     cl              ;we've been decrementing CL
                                  ; from 255 during save
          mov     es:[bx],cl      ;save the length
          mov     ax,SEG DATA
          mov     ds,ax           ;restore DS
          ASSUME  ds:DATA
          pop     bp
          ret     4
          ASSUME  ds:NOTHING
Skip:
          dec     di              ;check for null from this
                                  ; character on
NoEqual:
          mov     cx,7FFFh        ;search a long way if necessary
          sub     cx,di           ;environment never >32K
          jbe     RetNul          ;if we're past end, leave
          repne   scasb           ;look for the next null
          jcxz    RetNul               ;exit if not found
          cmp     byte ptr es:[di],al  ;second null in a row?
          jne     Compare              ;if not, try again
RetNul:
          les     di,ss:[bp+10]   ;get address of result
          stosb                   ;store a zero there
          mov     ax,SEG DATA
          mov     ds,ax           ;restore DS
          ASSUME  ds:DATA
          pop     bp
          ret     4
EnvString ENDP
CODE      ENDS
          END
