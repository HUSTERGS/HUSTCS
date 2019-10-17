
;   FILENAME: IDOS.INC
;
;   Copyright (c) 1988, 1990 by Borland International, Inc.
;
;   DESCRIPTION: This module declares various equates, macros, structures
;   and unions useful in communicating with DOS. This include file uses
;   ideal mode syntax.

struc   PascalString    ; Structure representing a Turbo Pascal string
    LengthByte  db  ?               ; Leading length byte(<= 255)
    Contents    db  255 dup (?) ; Contents of the string
ends    ; PascalString

struc   Psp ; Structure representing DOS's Program Segment Prefix(Psp)
    Int20h              dw  ?   ; Int 20h
    EndOfAllocation dw  ?   ; Segment, end of allocation block
    Reserved1           db  ?   ; Reserved by DOS
    MsDosDispatcher db  5h  dup (?) ; Long call to MS-DOS function
                                        ; dispatcher
    OldTermination      dd  ?   ; Previous contents of termination handler
                                ; interrupt vector(Int 22h)
    OldCtrlCHandler dd  ?   ; Previous contents of CTRL-C interrupt
                                ; vector(Int 23h)
    OldCriticalError    dd  ?   ; Previous contents of critical-error
                                ; interrupt vector(Int 24h)
    Reserved2           db  16h dup (?) ; Reserved by DOS
    EnvironmentBlock    dw  ?           ; Segment address of environment block
    Reserved3           db  2Eh dup (?) ; Reserved by DOS
    Fcb1                db  10h dup (?) ; Default File Control Block(FCB) #1
    Fcb2                db  14h dup (?) ; Default File Control Block(FCB) #2
    CommandTail PascalString <> ; Command tail and default Dta
ends    ; Psp

; The following record type represents the file attributes field in a
; DOS directory entry.

record  FileAttribType  UnUsed:2, Archive:1, Directory:1, Volume:1, System:1, Hidden:1, ReadOnly:1

struc   Dta ; Structure representing the DOS Data Transfer Area(Dta)
    Reserved        db  15h dup (?)     ; Used by Find Next function
    FileAttribute   FileAttribType  <>  ; Attribute of file that was found
    ;         BIT       Meaning
    ; 7 6 5 4 3 2 1 0
    ;               1   Read only
    ;             1     Hidden
    ;           1       System
    ;         1         Volume label
    ;       1           Subdirectory
    ;     1             Archive
    ;   1               Unused
    ; 1                 Unused
    Filetime        dw  ?               ; Time of file modification
    Filedate        dw  ?               ; Date of file modification
    Filesize        dd  ?               ; File size in bytes
    Filename        db  13  dup (?)     ; File name(ASCIIZ string)
ends    ; Dta

DTA_SIZE    equ 15h + 1 + 2 + 2 + 4 + 13    ; Size of DTA struc
