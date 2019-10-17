
;    FILENAME: OPROCLIN.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine ProcLine. ProcLine
;    processes a line.
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM oproclin

include globals.inc

_TEXT   segment

    ProcLine proc

    ;    This procedure processes a normal byte character 
    ;    (31 < ASCII value < 128) in al.
    ;
    ;    Input 
    ;       cx - number of bytes in buffer
    ;       LinBuf - starting location of the line buffer
    ;       SpcCnt - space count (for compressing spaces)
    ;       TabOff - tab offset (decrements the tab column number)
    ;       LAS_LET - designates the last character was a letter
    ;       INP_EOL - designates an end-of-line condition
    ;       INP_EOF - designates an end-of-file condition
    ;       INP_ERR - designates an input error condition
    ;       Options - the options being used
    ;       MAK_CAP - designates character is to be capitalized
    ;       LeftMar - left margin
    ;       LeftDel - left characters to delete
    ;       Trunc - truncate line length (truncate if non-zero)
    ;       REM_SPC - delete trailing spaces
    ;       REP_SPC - replace spaces with tabs
    ;       TAB - ASCII 09
    ;       CR - ASCII 13
    ;       LF - ASCII 10
    ;       OutBlk - output control block
    ;       OUT_ERR - output error
    ;    Output 
    ;       InpSta - input status updated
    ;       di - line buffer location updated
    ;       cx - byte count updated
    ;       si - start of line data
    ;    Registers modified 
    ;       ax, cx, di, si

    ; Process a line.

    sub     cx, cx                  ;clear bytes in buffer
    lea     di, LinBuf              ;buffer location
    mov     SpcCnt, 0               ;initial space count
    mov     TabOff, 0               ;column offset

    push    ax
    or      ax, LAS_LET
    or      ax, INP_EOL
    not     ax
    and     InpSta, ax
    pop     ax

    ;--- loop for each byte in line

prolin1:
    call    ProcByte                       ;process byte

    push    ax
    sub     ax, ax
    or      ax, INP_EOL
    or      ax, INP_EOF
    or      ax, INP_ERR
    test    InpSta, ax
    pop     ax

    jnz     prolin2

    test    Options, MAK_CAP                ;test if capitalize
    jz      prolin1
    or      cx, cx                          ;check if any input
    jz      prolin1

    push    ax
    sub     ax, ax
    mov     ax, LAS_LET
    not     ax
    and     InpSta, ax                      ;clear letter bit
    pop     ax

    mov     al, [di-1]                      ;get last character
    call    LoCase                          ;make lower case
    cmp     al, 'a'                         ;check if below a
    jb      prolin1
    cmp     al, 'z'                         ;check if above z
    ja      prolin1
    or      InpSta, LAS_LET                 ;set letter bit
    jmp     prolin1

    ;--- end of line

prolin2:
    test    InpSta, INP_EOL ;check if any line returned
    jnz     prolin3
    ret

    ;--- extra trailing spaces

prolin3:
    lea     si, LinBuf      ;start of line data

    call    TabNext         ;get next tab stop
    jnc     prolin4         ;jump if not at stop
    call    StoreTab        ;store a tab
    jmp     SHORT prolin5

prolin4:
    call    StoreSpc       ;store any spaces

    ;--- left margin

prolin5:
    mov     ax, LeftMar     ;get left margin
    add     cx, ax          ;add to byte count
    sub     si, ax          ;add margin

    ;--- delete left margin characters

    mov     ax, LeftDel     ;margin remove
    add     si, ax          ;skip beginning characters
    sub     cx, ax          ;reduce count
    jnc     prolin6         ;jump if okay (CX >= AX)
    sub     cx, cx          ;set cx to zero

    ;--- truncate line

prolin6:
    mov     ax, Trunc       ;truncate length
    or      ax, ax          ;check if set
    jz      prolin7
    cmp     cx, ax
    jbe     prolin7
    mov     di, si          ;start of buffer
    add     di, ax          ;line length
    mov     cx, ax          ;byte count

    ;--- remove trailing spaces

prolin7:
    test    Options, REM_SPC        ;check if remove
    jz      prolin10

prolin8:
    or      cx, cx                  ;see if no bytes left
    jz      prolin10
    cmp     BYTE PTR [di-1], ' '    ;check if space
    je      prolin9
    test    Options, REP_SPC        ;check if also delete tabs
    jz      prolin10
    cmp     BYTE PTR [di-1], TAB    ;check if tab
    jne     prolin10

prolin9:
    dec     di                      ;reduce pointer
    dec     cx                      ;reduce count
    jmp     prolin8

    ;--- append CR+LF

prolin10:
    mov     al, CR
    stosb                   ;store CR
    inc     cx
    mov     al, LF
    stosb                   ;store LF
    inc     cx              ;increment

    ;--- write line

    lea     bx, OutBlk      ;output control block
    call    FileWrite       ;write to file
    jnc     prolin11
    or      InpSta, OUT_ERR ;set error flag

prolin11:
    ret
    ProcLine endp

_TEXT    ends

end
