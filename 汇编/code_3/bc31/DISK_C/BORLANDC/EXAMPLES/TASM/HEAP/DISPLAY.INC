; FILE: DISPLAY.INC

CR  = 0DH
LF  = 0AH

DOSPRINTSTRING     =   09H
DOSPRINTCHAR       =   02H

DOSINT             =   21H

   global ShowHexByte:proc
   global ShowHexWord:proc
   global Show_Bracket:proc
   global Show_Endbracket:proc
   global CRLF:proc

