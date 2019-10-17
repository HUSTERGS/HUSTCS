
;    FILENAME: OSETOPTN.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements these routines.
;    SetOpt1 sets input buffer size.
;    SetOpt2 sets output buffer size.
;    SetOpt3 sets the byte to end lines.
;    SetOpt4 clears all tab stops.
;    SetOpt5 sets a tab stop.
;    SetOpt6 truncates lines to a specified length.
;    SetOpt7 sets the left margin.
;    SetOpt8 deletes the left margin.
;    SetOpt9 displays a help message.
; 
;    ASSEMBLY INSTRUCTIONS:  To assemble this module use the following  
;    TASM command line.     
;  
;        TASM osetoptn

include globals.inc

_TEXT   segment

    SetOpt1 proc

    ;    Input 
    ;        none
    ;    Output
    ;        input buffer size set
    ;    Registers modified
    ;        none

    call    CmdNum         ;get size
    mov     InpBlk+2, cx   ;save
    ret
    SetOpt1 endp

    SetOpt2 proc

    ;    Input 
    ;        none
    ;    Output
    ;        output buffer size set
    ;    Registers modified
    ;        none

    call    CmdNum          ;get size
    mov     OutBlk+2, cx    ;save
    ret
    SetOpt2 endp

    SetOpt3 proc

    ;    Input 
    ;        none
    ;    Output
    ;        input buffer size set
    ;    Registers modified
    ;        none

    call    CmdNum          ;get byte
    mov     EOL, cl         ;save
    ret
    SetOpt3 endp

    SetOpt4 proc

    ;    Input 
    ;        none
    ;    Output
    ;        all tab stops cleared
    ;    Registers modified
    ;        none

    call    TabClear       ;clear all stops
    ret
    SetOpt4 endp

    SetOpt5 proc

    ;    Input 
    ;        none
    ;    Output
    ;        tab stop set
    ;    Registers modified
    ;        none

    call    CmdNum          ;get location
    push    bx
    mov     bx, cx
    dec     bx              ;start numbering at 0
    call    TabSet          ;set tab stop
    pop     bx
    ret
    SetOpt5 endp

    SetOpt6 proc

    ;    Input 
    ;        none
    ;    Output
    ;        lines truncated to specified length
    ;    Registers modified
    ;        none

    call    CmdNum          ;get length
    mov     Trunc, cx       ;save
    ret
    SetOpt6 endp

    SetOpt7 proc

    ;    Input 
    ;        none
    ;    Output
    ;        left margin set
    ;    Registers modified
    ;        none

    call    CmdNum          ;get size
    mov     LeftMar, cx     ;save
    ret
    SetOpt7 endp

    SetOpt8 proc

    ;    Input 
    ;        none
    ;    Output
    ;        left margin deleted
    ;    Registers modified
    ;        none

    call    CmdNum          ;get bytes to delete
    mov     LeftDel, cx     ;save
    ret
    SetOpt8 endp

    SetOpt9 proc

    ;    Input 
    ;        none
    ;    Output
    ;        left margin deleted
    ;    Registers modified
    ;        none

    mov     ah, 9           ;display function
    lea     dx, Help        ;load help location
    int     21h             ;execute
    mov     ax, 4c03h       ;exit function and error code
    int     21h             ;execute
    SetOpt9 endp

_TEXT    ends

end
