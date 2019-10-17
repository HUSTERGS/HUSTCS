
;    FILENAME: OBYTEHI.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine ByteHigh. ByteHigh
;    processes the current high byte value in al.
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM obytehi

include globals.inc

_TEXT   segment

    ByteHigh proc

    ;    This procedure processes a high byte character 
    ;    (ASCII value > 127) in al.
    ;
    ;    Input 
    ;       al - high byte character
    ;       EOL -  defined to be the end of line character
    ;       InpSta - input status
    ;       INP_EOL - designates an end-of-line condition
    ;       Options - the options being used
    ;       STR_HIB - designates high byte to be stripped
    ;    Output 
    ;       al - high byte processed
    ;       cx - byte count incremented
    ;    Registers modified 
    ;       ax, cx

    ; Process high byte

    ;--- end of line

    cmp      al, EOL         ;check if end of line
    jne      bythi1
    or       InpSta, INP_EOL
    ret

    ;--- remove high bytes

bythi1:
    test     Options, STR_HIB ;test if remove high bytes
    jz       bythi2
    ret

    ;--- write byte

bythi2:
    stosb
    inc      cx
    ret
    ByteHigh endp

_TEXT    ends

end
