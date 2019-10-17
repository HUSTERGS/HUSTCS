
;   FILENAME: IWHGLOBL.INC
;
;   Copyright (c) 1988, 1990 by Borland International, Inc.
;
;   DESCRIPTION: This include file declares all the public symbols used by
;   the WHEREIS program. It also contains some data structure definitions
;   used by the various modules.

; Public symbols

global  LocateString:proc
global  PspAddress:word
global  DisplayPage:byte
global  IsDelimiter:proc
global  ParamCount:proc
global  ParamString:proc
global  DisplayErrorMsg:proc
global  FindFiles:proc
global  Terminate:proc
global  FindBytePos:proc
global  FindAndReplace:proc
global  ByteCopy:proc
global  WritePascalString:proc
global  WriteChar:proc
global  SkipSpaces:proc
global  GetASCIIZStrLen:proc
global  ParseFilename:proc
global  WriteASCIIZString:proc
global  FileSpecCounter:byte
global  FileSpec:byte:MAX_FILE_SPECS     ;dup (FILE_SPEC_SIZE dup (0))
global  DeleteChar:proc
global  Drive:byte
global  SwitchChar:byte

global  ParseDosCommand:proc
global  ExecuteDosCommand:proc

; Equates

MAX_PATH_LENGTH = 80

FILE_SPEC_SIZE  = 15

; Up to 15 different filespecs may be specified.
MAX_FILE_SPECS  = 15

