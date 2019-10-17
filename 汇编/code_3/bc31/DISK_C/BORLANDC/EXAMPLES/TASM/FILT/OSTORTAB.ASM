
;    FILENAME: OSTORTAB.ASM
;    Copyright (c) 1988, 1989 by Borland International, Inc.
;
;    Description: This module implements the routine StoreTab. StoreTab
;    stores a tab character if there are any spaces to compress.
;    This module uses MASM mode syntax and standard segment directives. 
; 
;    ASSEMBLY INSTRUCTIONS: To assemble this module use the following 
;    TASM command line. 
; 
;        TASM ostortab

include globals.inc

_TEXT   segment

    StoreTab proc

    ;    Input 
    ;       SpcCnt - flag to determine if there are any spaces to compress 
    ;       TAB - tab character defined to be ASCII 09 
    ;       cx - the current byte count 
    ;       TabOff - offset into the tab table 
    ;    Output 
    ;       TabOff - is decremented 
    ;       SpcCnt - is set to zero 
    ;    Registers modified 
    ;       cx

    cmp     SpcCnt, 0       ;check if any spaces to compress
    je      stotab1         ;jump if not
    push    ax
    mov     al, TAB         ;load tab
    stosb                   ;store
    inc     cx              ;increment byte count
    dec     TabOff          ;adjust column
    mov     SpcCnt, 0       ;reset space count
    pop     ax
stotab1:
    ret

    StoreTab endp

_TEXT    ends

end
