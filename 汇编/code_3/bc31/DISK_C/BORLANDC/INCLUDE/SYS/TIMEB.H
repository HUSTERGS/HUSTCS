/*  timeb.h

    Struct and function declarations for ftime().

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#if !defined(__TIMEB_H)
#define __TIMEB_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

struct timeb {
      long  time;
      short millitm;
#if defined(_RTLDLL)
      short _timezone;
#else
      short timezone;
#endif
      short dstflag;
      };

#ifdef __cplusplus
extern "C" {
#endif
void _Cdecl _FARFUNC ftime(struct timeb _FAR *);
#ifdef __cplusplus
}
#endif

#endif  /* __TIMEB_H */
