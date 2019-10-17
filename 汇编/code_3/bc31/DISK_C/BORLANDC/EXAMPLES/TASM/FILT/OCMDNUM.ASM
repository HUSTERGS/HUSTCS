
;    FILENAME: OCMDNUM.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine CmdNum. CmdNum
;    parses the command line. 
;  
;    ASSEMBLY INSTRUCTIONS:  To assemble this module use the following   
;    TASM command line.      
;   
;        TASM ocmdnum

include globals.inc

_TEXT   segment

    CmdNum proc

    ;    This function reads in a command line number.
    ;    The command line number is returned in cx
    ;    Input 
    ;        si - address of start of command line
    ;    Output
    ;        command processed
    ;        cx - command line number
    ;    Registers modified
    ;        ax, bx, cx

    sub     cx, cx

cmdnum1:
    cmp     bx, si              ;check if done
    je      cmdnum2
    cmp     BYTE PTR [si], '0'  ;check if below zero
    jb      cmdnum2
    cmp     BYTE PTR [si], '9'  ;check if above nine
    ja      cmdnum2

    mov     ax, 10              ;base ten
    mul     cx                  ;multiply
    jc      cmdnum3             ;jump if overflow
    mov     cx, ax              ;back into total
    lodsb                       ;load number
    sub     al, '0'             ;convert to binary
    sub     ah, ah
    add     cx, ax              ;add to total
    jmp     cmdnum1

    ;--- finished

cmdnum2:
    ret

    ;--- overflow

cmdnum3:
    mov     al, 0               ;error number
    call    ErrorExit           ;call error routine
    CmdNum endp

_TEXT    ends

end
