/*  utime.h

    Definitions for utime() function.

    Copyright (c) 1991, 1992 by Borland International
    All Rights Reserved.
*/

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#ifndef  _TIME_T
#define  _TIME_T
typedef long time_t;
#endif

/* Structure passed to utime containing file times
 */
struct utimbuf
{
        time_t  actime;         /* access time (not used on DOS) */
        time_t  modtime;        /* modification time */
};

#ifdef __cplusplus
extern "C" {
#endif

int    _Cdecl _FARFUNC utime(char _FAR *__path, struct utimbuf _FAR *__times);

#ifdef __cplusplus
}
#endif
