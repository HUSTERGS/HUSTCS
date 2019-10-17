
;   FILENAME: WHUSAGE.INC
;
;   Copyright (c) 1988, 1990 by Borland International, Inc.
;
;   DESCRIPTION: This include file declares pascal style strings representing
;   the programs usage or help screen.


; Define a Pascal string containing the syntax for the program.

COPYRIGHT    EQU <" Copyright (c) 1988, 1990 by Borland International, Inc.",13,10>
USAGE_SYNTAX EQU <"Syntax: WHEREIS [d:][path]filename filename filename [dos_command].....", 13, 10>
U2           EQU <"  dos_command is a command surrounded by """",'', or []. It will be called",13,10>
U3           EQU <"  for each file that is found. It should include at least one of these:",13,10>
U4           EQU <"     %1 - Insert full path, filename and extension",13,10>
U5           EQU <"     %2 - Filename and extension (no path)",13,10>
U6           EQU <"     %3 - Only the path.",13,10>
U7           EQU <"     %4 - Only the filename before the extension followed by a .",13,10>
U8           EQU <"     %5 - Only the extension, preceeded by a .",13,10>
U9           EQU <"  For example to delete all .BAK files:",13,10>
U10          EQU <"     WHEREIS  *.BAK [DEL %2]",13,10>
;MakePascalString Syntax, <"WHEREIS ",Version,COPYRIGHT,USAGE_SYNTAX,U2,U3,U4,U5,U6,U7>

Syntax       db  "WHEREIS ",ProgramVersion,COPYRIGHT,USAGE_SYNTAX,U2,U3,U4,U5,U6,U7,U8,U9,U10
             db  0

MakePascalString OnlyFirst,<"Only first parameter can have a drive and path on it.",13,10>
MakePascalString OnlyOneCommand,<"Only on DOS command can be given.",13,10>

; Define a pascal string representing a blank line
MakePascalString BlankLine, <13, 10>

