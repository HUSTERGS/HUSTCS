
;    FILENAME: OPRCBYTE.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine ProcByte. ProcByte
;    processes a byte.
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM oprcbyte

include globals.inc

_TEXT   segment

    ProcByte proc

    ;    This procedure processes an ASCII character. 
    ;    ProcByte performs the following tasks
    ;       reads the byte
    ;       determines the type of character
    ;       and checks whether or not an error has occurred
    ;
    ;    Input 
    ;       al - an ASCII character
    ;       di - the buffer location
    ;       InpBlk - input control block
    ;       InpBuf - input buffer
    ;       cx - bytes in the buffer
    ;       Options - the options being used
    ;       STR_BIT - constant set to strip high bits
    ;       INP_EOF - designates the end of the input file
    ;       InpSta - input status
    ;       INP_ERR - constant set to designate an input error
    ;       INP_EOL - constant set to designate an end-of-line condition
    ;    Output 
    ;       di - the buffer is updated
    ;       cx - updated
    ;       ax - byte processed
    ;    Registers modified 
    ;       ax

    ;--- read byte

    push    cx
    push    di
    lea     bx, InpBlk      ;input control block
    mov     cx, 1           ;bytes to read
    lea     di, InpBuf      ;input buffer
    call    FileRead        ;read byte
    pop     di
    pop     cx
    jc      probyt5         ;jump if error or EOF

    ;--- check type of character

    mov     al, InpBuf      ;load byte
probyt1:
    cmp     al, 32
    jb      probyt2
    cmp     al, 127
    ja      probyt3

    ;--- normal byte, 31 < AL < 128

    call    ByteNorm
    ret

    ;--- low byte, AL < 32

probyt2:
    call    ByteLow
    ret

    ;--- high byte, AL > 127

probyt3:
    test    Options, STR_BIT ;check if strip high bit
    jnz     probyt4
    call    ByteHigh
    ret

probyt4:
    and     al, 7fh         ;clear bit
    jmp     probyt1         ;loop back

    ;--- error reading

probyt5:
    cmp     ax, 0           ;check if EOF
    jne     probyt7
    or      InpSta, INP_EOF ;set end of file flag
    or      cx, cx          ;check if any bytes remaining
    jz      probyt6
    or      InpSta, INP_EOL ;set end of line also
probyt6:
    ret
    ret

probyt7:
    or      InpSta, INP_ERR ;set error flag
    ret

    ProcByte endp

_TEXT    ends

end
