
Title 'FILT.ASM', 'Text Filter'

;   Text FILTer
;   Version 1.0
;   Copyright (c) 1988, 1989 by Borland International, Inc.
;   Used by permission of the author.
;
;   This program performs various text filter functions.
;
;   Usage:
;
;       FILT [options] < in_file > out_file
;
;   Options:
;
;       x  = expand tabs to spaces           e  = erase all tab stops
;       c  = compress spaces to tabs         t# = set tab stop
;
;       S  = strip high bits                 m  = left margin
;       C  = strip control chars             d  = delete left margin
;       H  = strip high (>127) bytes         l# = truncate long lines
;       U  = all letters to upper-case       r  = remove trailing spaces
;       L  = all letters to lower-case       b# = byte to end input lines
;       A  = capitalize words                s  = save carriage returns
;
;       Z  = write ^Z to output              i# = input buffer size (20000)
;       z  = ignore ^Z in input              o# = output buffer size (20000)

include globals.inc

_STACK  segment
    DW  500h dup (?)
    EndStack    LABEL  BYTE
_STACK  ends
_DATA   segment

PSP    DW      ?

BUFLEN =       130
CMDBUF DB      130 dup (?)

;   line definition
LeftMar DW      0       ;left margin
LeftDel DW      0       ;left characters to delete
Trunc   DW      0       ;truncate line length (truncate if non-zero)

;   input control block

InpBlk  LABEL   WORD
        DW      0       ;status
        DW      20000   ;buffer size
        DW      ?
        DW      ?
        DW      0       ;standard input device
        DW      ?

;   output control block

OutBlk  LABEL   WORD
        DW      1       ;status
        DW      20000   ;buffer size
        DW      ?
        DW      ?
        DW      1       ;standard output device
        DW      ?

;   special characters

FF      EQU     12      ;form feed
EOF     EQU     26      ;carriage return
EOL     DB      LF      ;end of line character

;   character options

STR_LOB EQU     0001h   ;strip low (control) bytes
STR_HIB EQU     0002h   ;strip high bytes
STR_BIT EQU     0004h   ;strip high bits
MAK_UPR EQU     0008h   ;make upper-case
MAK_LWR EQU     0010h   ;make lower-case
MAK_CAP EQU     0020h   ;capitalize
REP_TAB EQU     0040h   ;replace tabs with spaces
REP_SPC EQU     0080h   ;replace spaces with tabs
SAV_CR  EQU     0100h   ;save CR's
REM_SPC EQU     0200h   ;delete trailing spaces
SKP_EOF EQU     0400h   ;skip input EOF
SUP_EOF EQU     0800h   ;suppress output EOF

Options DW      0

InpSta  DW      0

;   help message

Help    LABEL   BYTE
  DB  13,10
  DB  'Text Filter, Version 1.0',13,10
  DB  13,10
  DB  'Usage: FILT [options] < input_file > output_file',13,10
  DB  13,10
  DB  'Tab Replacement:                 Tab Assignment:',13,10
  DB  '  x  = expand tabs to spaces       e  = erase all tab stops',13,10
  DB  '  c  = compress spaces to tabs     t# = set tab stop',13,10
  DB  'Character Replacement:           Line Format:',13,10
  DB  '  S  = strip high bits             m  = add left margin',13,10
  DB  '  C  = strip control chars         d  = delete left margin',13,10
  DB  '  H  = strip high (>127) bytes     l# = truncate long lines',13,10
  DB  '  U  = all letters to upper-case   r  = remove trailing spaces',13,10
  DB  '  L  = all letters to lower-case   b# = byte to end input lines',13,10
  DB  '  A  = capitalize words            s  = save carriage returns',13,10
  DB  'End of File:                     I/O Buffer:',13,10
  DB  '  z  = ignore ^Z in input          i# = input buffer size (20000)',13,10
  DB  '  Z  = suppress ^Z in output       o# = output buffer size (20000)',13,10
  DB  '$'

;   Messages and return codes.

;   messages

mess1    DB      37, 'Option error: "?", enter ? for help',13,10
mess2    DB      21, 'Insufficient memory',13,10
mess3    DB      12, 'Read error',13,10
mess4    DB      13, 'Write error',13,10

;   error table

ErrTbl  LABEL   BYTE
        DB      3
	DW      OFFSET mess1         ;option error           (0)
        DB      4
	DW      OFFSET mess2         ;insufficient memory    (1)
        DB      2
	DW      OFFSET mess3         ;input error            (2)
        DB      1
	DW      OFFSET mess4         ;output error           (3)

;   Uninitialized data.

InpBuf  DB      ?               ;input read location

Margin  DB      MAXLIN dup (?)  ;margin

LinBuf  DB      MAXLIN+2 dup (?) ;line buffer

TabTbl  DB      MAXLIN dup (?)  ;tab table
TabEndx LABEL   BYTE
TabEnd  EQU     OFFSET TabEndx  ;end of tab table

SpcCnt  DW       ?              ;space count (for compressing spaces)

TabOff  LABEL   WORD            ;tab offset (decrements tab column number)
        DW       502 dup (?)

;     Option table.

OptTab  LABEL   BYTE
        DB      ' '
	DW       0, 0                 ;option delimiter

        DB      ','
	DW       0, 0                 ;option delimiter

        DB      '-'
	DW       0, 0                 ;option delimiter

        DB      '/'
	DW       0, 0                 ;option delimiter

        DB      'x' 
        DW       0, REP_TAB           ;expand tabs

        DB      'c'
	DW       0, REP_SPC           ;compress spaces with tabs

        DB      'e'
	DW       OFFSET SetOpt4, 0    ;erase all tab stops

        DB      't'
	DW       OFFSET SetOpt5, 0    ;set tab stop

        DB      'S'
	DW       0, STR_BIT           ;strip high bits

        DB      'C'
	DW       0, STR_LOB           ;strip control (<32) chars

        DB      'H'
	DW       0, STR_HIB           ;strip high (>127) bytes

        DB      'U'
	DW       0, MAK_UPR           ;all letters to upper-case

        DB      'L'
	DW       0, MAK_LWR           ;all letters to lower-case

        DB      'A'
	DW       0, MAK_CAP           ;capitalize words

        DB      'm'
	DW       OFFSET SetOpt7, 0    ;left margin

        DB      'd'
	DW       OFFSET SetOpt8, 0    ;delete left margin

        DB      'l'
	DW       OFFSET SetOpt6, 0    ;truncate lines

        DB      'r'
	DW       0, REM_SPC           ;remove trailing spaces

        DB      'b'
	DW       OFFSET SetOpt3, 0    ;byte to end input lines

        DB      's'
	DW       0, SAV_CR            ;save CR's

        DB      'z'
	DW       0, SKP_EOF           ;ignore input EOF

        DB      'Z' 
	DW       0, SUP_EOF           ;suppress output EOF

        DB      'i'
	DW       OFFSET SetOpt1,  0   ;input buffer size (20000)

        DB      'o'
	DW       OFFSET SetOpt2,  0   ;output buffer size (20000)

        DB      '?'
	DW       OFFSET SetOpt9,  0   ;display help

        DB      'h'
	DW       OFFSET SetOpt9,  0   ;display help

        DB      0

_DATA   ends

_TEXT   segment


;   Main program.

;   set up stack and reduce memory allocation

FiltStart:
    lea     bx, EndStack     ;end of program
    mov     cl, 4
    shr     bx, cl          ;adjust to paragraph
    inc     bx              ;round up
    mov     ax, ss
    add     bx, ax
    mov     ax, ds
    sub     bx, ax
    mov     ah, 4ah         ;function
    int     21h             ;execute

    ;    initialize

    mov     dx, DGROUP
    mov     ds, dx
    mov     PSP, es         ;saved Program Segment Prefix
    mov     es, dx
    mov     dx, MAXLIN      ;max margin spaces
    lea     di, Margin      ;margin area
    call    Spaces          ;store spaces
    call    TabReset        ;set default tab stops
    call    ParseCmd        ;parse command line

    ;     input read buffer

    lea     bx, InpBlk      ;control block
    call    FileAlloc       ;set up buffer
    jc      main3

    ;     output write buffer

    lea     bx, OutBlk      ;control block
    call    FileAlloc       ;set up buffer
    jc      main3

    ;     process file

    call    ProcDoc         ;process document

    test    InpSta, INP_ERR
    jnz     main4
    test    InpSta, OUT_ERR
    jnz     main5

    ;     close input buffer

    lea     bx, InpBlk      ;control block
    call    FileFree        ;close buffer

    ;     close output buffer

    lea     bx, OutBlk      ;control block
    call    FileFlush       ;flush file first
    jc      main5
    call    FileFree        ;close buffer

    mov     ax, 4c00h
    int     21h

    ;     not enough memory

main3:
    mov     al, 1
    call   ErrorExit

    ;     error reading input file

main4:
    mov     al, 2
    call   ErrorExit

    ;     error writing output file

main5:
    mov     al, 3
    call   ErrorExit

;   Error routine.
;
;   Input
;      al - local error number

    call   ErrorExit                ;error routine

_TEXT    ends

END    FiltStart
