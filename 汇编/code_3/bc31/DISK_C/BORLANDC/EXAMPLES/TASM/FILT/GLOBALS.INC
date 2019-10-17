; This file declares procedures and symbols needed by the modules of
; FILT.ASM
; Copyright (c) 1988, 1990 by Borland International, Inc.

%TabSize  4    ;set the tab column width to 4 in the listing file

;Defining constants
INP_EOF EQU     0002H   ;end of file
INP_ERR EQU     4000H   ;input error
OUT_ERR EQU     8000H   ;output error
LAS_LET EQU     0004H   ;last byte was letter
INP_EOL EQU     0001H   ;end of line
CR      EQU     13      ;carriage return
LF      EQU     10      ;line feed
TAB     EQU     9       ;tab character
MAXLIN  EQU     600     ;maximum line length
BUFLEN  =       130     ;length of CMDBUF

global    ByteHigh:PROC
global    ByteLow:PROC
global    ByteNorm:PROC
global    CMDBUF:BYTE:130
global    CmdNum:PROC
global    EOF:ABS
global    EOL:BYTE
global    ErrorExit:PROC
global    ErrTbl:BYTE
global    FileAlloc:PROC
global    FileFill:PROC
global    FileFlush:PROC
global    FileFree:PROC
global    FileRead:PROC
global    FileWrite:PROC
global    Help:BYTE
global    InpBlk:WORD
global    InpBuf:BYTE
global    InpSta:WORD
global    LeftDel:WORD
global    LeftMar:WORD
global    LinBuf:BYTE:MAXLIN+2
global    LoCase:PROC
global    MAK_CAP:ABS
global    MAK_LWR:ABS
global    MAK_UPR:ABS
global    mess1:BYTE
global    Options:WORD
global    OptTab:BYTE
global    OutBlk:WORD
global    ParseCmd:PROC
global    ProcByte:PROC
global    ProcDoc:PROC
global    ProcLine:PROC
global    PSP:WORD
global    REM_SPC:ABS 
global    REP_SPC:ABS
global    REP_TAB:ABS
global    SAV_CR:ABS
global    SetOpt1:PROC
global    SetOpt2:PROC
global    SetOpt3:PROC
global    SetOpt4:PROC
global    SetOpt5:PROC
global    SetOpt6:PROC
global    SetOpt7:PROC
global    SetOpt8:PROC
global    SetOpt9:PROC
global    SKP_EOF:ABS
global    Spaces:PROC
global    SpcCnt:WORD
global    StoreSpc:PROC
global    StoreTab:PROC
global    STR_BIT:ABS
global    STR_HIB:ABS
global    STR_LOB:ABS
global    SUP_EOF:ABS
global    TabClear:PROC
global    TabEnd:ABS
global    TabNext:PROC
global    TabOff:WORD     
global    TabReset:PROC
global    TabSet:PROC
global    TabTbl:BYTE:MAXLIN
global    Trunc:WORD
global    UpCase:PROC

_TEXT   segment byte    public  'CODE'
_TEXT   ends
_DATA   segment word    public  'DATA'
_DATA   ends
_STACK  segment PARA    stack   'STACK'
_STACK  ends

DGROUP  GROUP _DATA, _STACK
ASSUME  cs:_TEXT, ds:DGROUP, ss:DGROUP    ; segment definitions.

