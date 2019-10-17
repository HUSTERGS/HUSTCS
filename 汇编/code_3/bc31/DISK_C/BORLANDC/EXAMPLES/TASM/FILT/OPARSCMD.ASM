
;    FILENAME: OPARSCMD.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine ParseCmd. ParseCmd 
;    parses the command line.
; 
;    ASSEMBLY INSTRUCTIONS:  To assemble this module use the following  
;    TASM command line.     
;  
;        TASM oparscmd

include globals.inc

_TEXT   segment

    ParseCmd proc

    ;    Input 
    ;        si - address of start of command line
    ;        OptTab - Option Table
    ;        Options - designates user set options
    ;    Output
    ;        command line processed
    ;    Registers modified
    ;        si, bx, ax, di

    push    ds              ;save current value of ds
    push    ds              ;set es to point to current
    pop     es              ;data segment

    mov     ax, PSP         ;set ds to point to the PSP
    mov     ds, ax

    mov     si, 80h         ;command tail

    lea     di, CMDBUF      ;get the address of the local buffer
    mov     cx, BUFLEN      ;get the size of the local buffer
    rep     movsb           ;get a copy of the command-line arguments
    pop     ds              ;reset ds to the data segment

    lea     si, CMDBUF      ;load si with the address of CMDBUF for the
                            ;lodsb instruction
    lodsb                   ;get number of bytes
    cmp     al, 0           ;see if command tail exists
    jnz     hastail
    mov     al, '?'         ;force help screen
    jmp     SHORT   parcmd1a

hastail:

    mov     bx, si
    sub     ah, ah
    add     bx, ax          ;BX points to end

parcmd1:
    cmp     bx, si          ;check if done
    je      parcmd5
    lodsb                   ;get character


parcmd1a:

    mov     mess1+16, al    ;put in message in case of error
    lea     di, OptTab      ;start of table

parcmd2:
    cmp     BYTE PTR [di], 0    ;check if end of table
    je      parcmd6
    cmp     al, [di]        ;check if option matches
    je      parcmd3
    add     di, 5           ;skip to next entry
    jmp     parcmd2

    ;--- found matching option

parcmd3:
    mov     ax, [di+1]      ;load command word
    or      ax, ax          ;check if branch location
    jnz     parcmd4
    mov     ax, [di+3]      ;load option flag
    xor     Options, ax     ;flip bits
    jmp     parcmd1

parcmd4:
    call    ax              ;branch to special routine
    jmp     parcmd1

    ;--- finished

parcmd5:
    ret

    ;--- bad option

parcmd6:
    mov     al, 0           ;error number
    call    ErrorExit       ;call error routine
    ParseCmd endp

_TEXT    ends

end
