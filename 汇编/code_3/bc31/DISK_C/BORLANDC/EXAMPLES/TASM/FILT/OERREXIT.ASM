
;    FILENAME: OERREXIT.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine ErrorExit. ErrorExit
;    handles the printing of error messages.
; 
;    ASSEMBLY INSTRUCTIONS:  To assemble this module use the following  
;    TASM command line.     
;  
;        TASM oerrexit

include globals.inc

_TEXT   segment

    ErrorExit proc

    ;    Input 
    ;        al - error number
    ;        ErrTbl - starting location of the error table
    ;        si - address of start of command line
    ;        OptTab - Option Table
    ;        Options - designates user set options
    ;    Output
    ;        command line processed
    ;    Registers modified
    ;        none



    ;    get error table entry

    sub     ah, ah
    mov     bx, ax
    shl     ax, 1
    add     bx, ax                  ;error number times three
    lea     si, [ErrTbl + bx]       ;get location of error data

    lodsb                           ;load return code
    push    ax

    ;    write message

    lodsw                           ;load offset of message
    mov     si, ax
    lodsb                           ;load length of message
    sub     ah, ah
    mov     cx, ax                  ;length in CX
    mov     bx, 2                   ;error device
    mov     dx, si                  ;offset in DX
    mov     ah, 40h                 ;function
    int     21h                     ;execute

    ;    exit

    pop     ax                      ;restore error code
    mov     ah, 4ch                 ;exit function
    int     21h                     ;execute

    ErrorExit endp
_TEXT    ends

end
