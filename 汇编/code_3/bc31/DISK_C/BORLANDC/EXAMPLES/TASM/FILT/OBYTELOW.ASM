
;    FILENAME: OBYTELOW.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine ByteLow. ByteLow
;    processes the current low byte value in al.
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM obytelow

include globals.inc

_TEXT   segment

    ByteLow proc

    ;    This procedure processes a low byte character (ASCII value < 32) 
    ;    in al.  
    ;
    ;    Input 
    ;       al - low byte character
    ;       cx - byte count
    ;       dx - number of spaces to insert
    ;       EOL -  defined to be the end of line character
    ;       InpSta - input status
    ;       INP_EOL - designates an end-of-line condition
    ;       Options - the options being used
    ;       REP_TAB - replace tabs without spaces
    ;       TAB - tab character defined to be ASCII 09
    ;       Sav_CR -  denotes CR are to be saved
    ;       CR - ASCII 13
    ;       SKP_EOF - skip input eof
    ;       EOF - ASCII 26
    ;       INP_EOF - designates the end of the input file
    ;       STR_LOB - strip low (control) bytes
    ;
    ;    Output 
    ;       al - low byte processed
    ;       cx - byte count incremented
    ;    Registers modified 
    ;       ax, cx

    ; Process low byte.

    ;--- end of line

    cmp     al, EOL         ;check if end of line
    jne     bytlo1
    or      InpSta, INP_EOL
    ret

    ;--- replace tabs with spaces

bytlo1:
    test    Options, REP_TAB ;test if replace tabs
    jz      bytlo3
    cmp     al, TAB  ;check if tab
    jne     bytlo3
    call    TabNext         ;get spaces needed
    call    Spaces          ;store spaces
    add     cx, dx          ;byte count
    ret

    ;--- carriage return

bytlo3:
    test    Options, SAV_CR  ;check if saving CR's
    jnz     bytlo4
    cmp     al, CR    ;check if carriage return
    jne     bytlo4
    ret

    ;--- end of file

bytlo4:
    test    Options, SKP_EOF ;check if ignore EOF
    jnz     bytlo6
    cmp     al, EOF   ;check if end of page
    jne     bytlo6
    or      InpSta, INP_EOF ;set flag
    or      cx, cx          ;check if any bytes
    jz      bytlo5
    or      InpSta, INP_EOL ;set end of line also
bytlo5:
    ret

    ;--- remove low bytes

bytlo6:
    test    Options, STR_LOB ;test if remove low bytes
    jz      bytlo7
    ret

    ;--- write byte

bytlo7:
    stosb
    inc     cx
    ret

    ByteLow endp

_TEXT    ends

end
