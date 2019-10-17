/*  ctype.h

    Defines the ctype macros.

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __CTYPE_H
#define __CTYPE_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#define _IS_SP  1           /* is space */
#define _IS_DIG 2           /* is digit indicator */
#define _IS_UPP 4           /* is upper case */
#define _IS_LOW 8           /* is lower case */
#define _IS_HEX 16          /* [0..9] or [A-F] or [a-f] */
#define _IS_CTL 32          /* Control */
#define _IS_PUN 64          /* punctuation */

extern  char _Cdecl _ctype[];    /* Character type array */

#ifdef __cplusplus
extern "C" {
#endif
int _Cdecl isalnum (int __c);
int _Cdecl isalpha (int __c);
int _Cdecl isascii (int __c);
int _Cdecl iscntrl (int __c);
int _Cdecl isdigit (int __c);
int _Cdecl isgraph (int __c);
int _Cdecl islower (int __c);
int _Cdecl isprint (int __c);
int _Cdecl ispunct (int __c);
int _Cdecl isspace (int __c);
int _Cdecl isupper (int __c);
int _Cdecl isxdigit(int __c);
#ifdef __cplusplus
}
#endif

#define isalnum(c)  (_ctype[(c) + 1] & (_IS_DIG | _IS_UPP | _IS_LOW))
#define isalpha(c)  (_ctype[(c) + 1] & (_IS_UPP | _IS_LOW))
#define isascii(c)  ((unsigned)(c) < 128)
#define iscntrl(c)  (_ctype[(c) + 1] & _IS_CTL)
#define isdigit(c)  (_ctype[(c) + 1] & _IS_DIG)
#define isgraph(c)  ((c) >= 0x21 && (c) <= 0x7e)
#define islower(c)  (_ctype[(c) + 1] & _IS_LOW)
#define isprint(c)  ((c) >= 0x20 && (c) <= 0x7e)
#define ispunct(c)  (_ctype[(c) + 1] & _IS_PUN)
#define isspace(c)  (_ctype[(c) + 1] & _IS_SP)
#define isupper(c)  (_ctype[(c) + 1] & _IS_UPP)
#define isxdigit(c) (_ctype[(c) + 1] & (_IS_DIG | _IS_HEX))

#define toascii(c)  ((c) & 0x7f)

#if !__STDC__
#define _toupper(c) ((c) + 'A' - 'a')
#define _tolower(c) ((c) + 'a' - 'A')
#endif

#ifdef __cplusplus
extern "C" {
#endif
int _CType tolower(int __ch);
int _CType _ftolower(int __ch);
int _CType toupper(int __ch);
int _CType _ftoupper(int __ch);
#ifdef __cplusplus
}
#endif

#endif
