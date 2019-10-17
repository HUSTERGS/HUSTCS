; Turbo Assembler    Copyright (c) 1988, 1991 By Borland International, Inc.

; HEX.ASM

; From the Turbo Assembler Users Guide

CODE      SEGMENT
          ASSUME cs:CODE,ds:NOTHING

; Parameters (+2 because of push bp)

byteCount EQU BYTE PTR  ss:[bp+6]
num       EQU DWORD PTR ss:[bp+8]

; Function result address (+2 because of push bp)

resultPtr EQU DWORD PTR ss:[bp+12]


HexStr    PROC FAR
          PUBLIC HexStr

          push bp
          mov bp,sp          ;get pointer into stack
          les di,resultPtr   ;get address of function result
          mov dx,ds          ;save Turbo's DS in DX
          lds si,num         ;get number address
          mov al,byteCount   ;how many bytes?
          xor ah,ah          ;make a word
          mov cx,ax          ;keep track of bytes in CX
          add si,ax          ;start from MS byte of number
          dec si
          shl ax,1           ;how many digits? (2/byte)
          cld                ;store # digits (going forward)
          stosb              ;in destination string's length byte
HexLoop:
          std                ;scan number from MSB to LSB
          lodsb              ;get next byte
          mov ah,al          ;save it
          shr al,1           ;extract high nibble
          shr al,1
          shr al,1
          shr al,1
          add al,90h         ;special hex conversion sequence
          daa                ;using ADDs and DAA's
          adc al,40h
          daa                ;nibble now converted to ASCII
          cld                ;store ASCII going up
          stosb
          mov al,ah          ;repeat conversion for low nibble
          and al,0Fh
          add al,90h
          daa
          adc al,40h
          daa
          stosb
          loop HexLoop       ;keep going until done
          mov ds,dx          ;restore Turbo's DS
          pop bp
          ret 6              ;parameters take 6 bytes
HexStr    ENDP
CODE      ENDS
          END
