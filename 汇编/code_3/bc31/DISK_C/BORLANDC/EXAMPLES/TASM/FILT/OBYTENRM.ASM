
;    FILENAME: OBYTENRM.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine ByteNorm. ByteNorm
;    processes the current normal byte value in al.
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM obytenrm

include globals.inc

_TEXT   segment

    ByteNorm proc

    ;    This procedure processes a normal byte character 
    ;    (31 < ASCII value < 128) in al.
    ;
    ;    Input 
    ;       al - normal byte character
    ;       EOL -  defined to be the end of line character
    ;       InpSta - input status
    ;       INP_EOL - designates an end-of-line condition
    ;       Options - the options being used
    ;       REP_SPC - replace spaces with tabs
    ;       SpcCnt - space count (for compressing spaces)
    ;       TabOff - tab offset (decrements the tab column number)
    ;       MAK_LWR - designates character is to be shifted to lower-case
    ;       MAK_UPR - designates character is to be shifted to upper-case
    ;       MAK_CAP - designates character is to be capitalized
    ;       LAS_LET - designates the last character was a letter
    ;
    ;    Output 
    ;       al - normal byte processed
    ;       cx - byte count incremented
    ;    Registers modified 
    ;       ax, cx


    ; Process normal byte.

    ;--- end of line

    cmp      al, EOL         ;check if end of line
    jne      bytnor1
    or       InpSta, INP_EOL
    ret

    ;--- replace spaces with tabs

bytnor1:
    test     Options, REP_SPC ;test if replace spaces
    jz       bytnor4

    ;------ write tab stop

    call     TabNext        ;get next tab stop
    jnc      bytnor2        ;jump if not at stop
    call     StoreTab       ;store a tab

    ;------ space

bytnor2:
    cmp      al, ' '         ;check if really space
    jne      bytnor3         ;jump if not
    inc      SpcCnt          ;increment space count
    inc      TabOff          ;increment column
    ret

    ;------ non-space

bytnor3:
    call     StoreSpc        ;store any spaces

    ;--- convert to lower case

bytnor4:
    test     Options, MAK_LWR ;test if make lower-case
    jz       bytnor5
    call     LoCase
    stosb
    inc      cx
    ret

    ;--- convert to upper case

bytnor5:
    test     Options, MAK_UPR ;test if make upper-case
    jz       bytnor6
    call     UpCase
    stosb
    inc      cx
    ret

    ;--- capitalize

bytnor6:
    test     Options, MAK_CAP ;test if capitalize
    jz       bytnor8
    test     InpSta, LAS_LET ;check if last character was letter
    jz       bytnor7
    call     LoCase
    stosb
    inc      cx
    ret

bytnor7:
    call     UpCase
    stosb
    inc      cx
    ret

    ;--- write byte

bytnor8:
    stosb
    inc      cx
    ret
    ByteNorm endp

_TEXT    ends

end
