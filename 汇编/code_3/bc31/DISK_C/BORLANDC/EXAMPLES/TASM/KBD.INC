
;   FILENAME: KBD.INC
;
;   Copyright (c) 1988, 1990 by Borland International, Inc.
;
;   DESCRIPTION: This include file is comprised of equates representing
;   all the non-alpha numeric scan codes returned by the IBM-PC keyboard.


; Control characters

CTRL@           = 00h
NULL            = CTRL@
CTRLA           = 01h
CTRLB           = 02h
CTRLC           = 03h
CTRLD           = 04h
CTRLE           = 05h
CTRLF           = 06h
CTRLG           = 07h
BELL            = CTRLG
CTRLH           = 08h
BACKSPACE       = CTRLH
CTRLI           = 09h
TAB             = CTRLI
CTRLJ           = 0Ah
LINEFEED        = CTRLJ
CTRLK           = 0Bh
CTRLL           = 0Ch
CTRLM           = 0Dh
RETURN          = CTRLM
CTRLN           = 0Eh
CTRLO           = 0Fh
CTRLP           = 10h
CTRLQ           = 11h
CTRLR           = 12h
CTRLS           = 13h
CTRLT           = 14h
CTRLU           = 15h
CTRLV           = 16h
CTRLW           = 17h
CTRLX           = 18h
CTRLY           = 19h
CTRLZ           = 1Ah
ESCAPE          = 1Bh
CTRL_BACK_SLASH = 1Ch
CTRL_RIGHT_BRACKET    = 1Dh
CTRL_CARRET           = 1Eh
CTRL_UNDERSCORE       = 1Fh

; ASCII characters

SPACE           = 20h
EXCLAMATION     = 21h
DOUBLE_QUOTE    = 22h
POUND           = 23h
DOLLAR          = 24h
PERCENT         = 25h
AMPERSAND       = 26h
SINGLE_QUOTE    = 27h
LEFT_PAREN      = 28h
RIGHT_PAREN     = 29h
STAR            = 2Ah
PLUS            = 2Bh
COMMA           = 2Ch
HYPHEN          = 2Dh
PERIOD          = 2Eh
FORWARD_SLASH   = 2Fh
ASCII_ZERO      = 30h
ASCII_ONE       = 31h
ASCII_TWO       = 32h
ASCII_THREE     = 33h
ASCII_FOUR      = 34h
ASCII_FIVE      = 35h
ASCII_SIX       = 36h
ASCII_SEVEN     = 37h
ASCII_EIGHT     = 38h
ASCII_NINE      = 39h
COLON           = 3Ah
SEMICOLON       = 3Bh
LESS_THEN       = 3Ch
EQUAL           = 3Dh
GREATER_THEN    = 3Eh
QUESTION_MARK   = 3Fh
AT              = 40h
UPPER_A         = 41h
UPPER_B         = 42h
UPPER_C         = 43h
UPPER_D         = 44h
UPPER_E         = 45h
UPPER_F         = 46h
UPPER_G         = 47h
UPPER_H         = 48h
UPPER_I         = 49h
UPPER_J         = 4Ah
UPPER_K         = 4Bh
UPPER_L         = 4Ch
UPPER_M         = 4Dh
UPPER_N         = 4Eh
UPPER_O         = 4Fh
UPPER_P         = 50h
UPPER_Q         = 51h
UPPER_R         = 52h
UPPER_S         = 53h
UPPER_T         = 54h
UPPER_U         = 55h
UPPER_V         = 56h
UPPER_W         = 57h
UPPER_X         = 58h
UPPER_Y         = 59h
UPPER_Z         = 5Ah

LEFT_SQUARE_BRACKET = 5Bh
BACKSLASH           = 5Ch
RIGHT_SQUARE_BRACKET    = 5Dh
CARRET          = 5Eh
UNDERSCORE      = 5Fh
BACKWARD_QUOTE  = 60h
LEFT_CURLY_BRACKET      = 7Bh
PIPE            = 7Ch
RIGHT_CURLY_BRACKET = 7Dh
TILDE           = 7Eh
DEL             = 7Fh

LOWER_A         = 61h
LOWER_B         = 62h
LOWER_C         = 63h
LOWER_D         = 64h
LOWER_E         = 65h
LOWER_F         = 66h
LOWER_G         = 67h
LOWER_H         = 68h
LOWER_I         = 69h
LOWER_J         = 6Ah
LOWER_K         = 6Bh
LOWER_L         = 6Ch
LOWER_M         = 6Dh
LOWER_N         = 6Eh
LOWER_O         = 6Fh
LOWER_P         = 70h
LOWER_Q         = 71h
LOWER_R         = 72h
LOWER_S         = 73h
LOWER_T         = 74h
LOWER_U         = 75h
LOWER_V         = 76h
LOWER_W         = 77h
LOWER_X         = 78h
LOWER_Y         = 79h
LOWER_Z         = 7Ah


