/*  locale.h

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __LOCALE_H
#define __LOCALE_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#ifndef NULL
#include <_null.h>
#endif

#define LC_ALL      0
#define LC_COLLATE  1
#define LC_CTYPE    2
#define LC_MONETARY 3
#define LC_NUMERIC  4
#define LC_TIME     5

struct lconv
   {
   char _FAR *decimal_point;
   char _FAR *thousands_sep;
   char _FAR *grouping;
   char _FAR *int_curr_symbol;
   char _FAR *currency_symbol;
   char _FAR *mon_decimal_point;
   char _FAR *mon_thousands_sep;
   char _FAR *mon_grouping;
   char _FAR *positive_sign;
   char _FAR *negative_sign;
   char int_frac_digits;
   char frac_digits;
   char p_cs_precedes;
   char p_sep_by_space;
   char n_cs_precedes;
   char n_sep_by_space;
   char p_sign_posn;
   char n_sign_posn;
   };

#ifdef __cplusplus
extern "C" {
#endif
char _FAR * _Cdecl _FARFUNC setlocale( int __category, const char _FAR *__locale );
struct lconv _FAR * _Cdecl _FARFUNC localeconv( void );
#ifdef __cplusplus
}
#endif

#endif
