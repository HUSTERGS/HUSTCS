/*  time.h

    Struct and function declarations for dealing with time.

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __TIME_H
#define __TIME_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#ifndef  _TIME_T
#define  _TIME_T
typedef long time_t;
#endif

#ifndef  _CLOCK_T
#define  _CLOCK_T
typedef long clock_t;

#define CLOCKS_PER_SEC 18.2
#define CLK_TCK        18.2

#endif  /* _TIME_T */

struct tm
{
  int   tm_sec;
  int   tm_min;
  int   tm_hour;
  int   tm_mday;
  int   tm_mon;
  int   tm_year;
  int   tm_wday;
  int   tm_yday;
  int   tm_isdst;
};

#ifdef __cplusplus
extern "C" {
#endif
char _FAR *     _Cdecl _FARFUNC asctime(const struct tm _FAR *__tblock);
char _FAR *     _Cdecl _FARFUNC ctime(const time_t _FAR *__time);
double      _Cdecl difftime(time_t __time2, time_t __time1);
struct tm _FAR * _Cdecl _FARFUNC gmtime(const time_t _FAR *__timer);
struct tm _FAR * _Cdecl _FARFUNC localtime(const time_t _FAR *__timer);
time_t      _Cdecl time(time_t _FAR *__timer);
time_t      _Cdecl _FARFUNC mktime(struct tm _FAR *__timeptr);
clock_t     _Cdecl clock(void);
size_t      _Cdecl _FARFUNC strftime(char _FAR *__s, size_t __maxsize,
                        const char _FAR *__fmt, const struct tm _FAR *__t);

#if !__STDC__

#if !defined(_RTLDLL)

extern int  _Cdecl  daylight;
extern long _Cdecl  timezone;
extern char _FAR * const _Cdecl tzname[2];

#else

int  far * far _Cdecl       __getDaylight(void);
long far * far _Cdecl       __getTimezone(void);
char far * far * far _Cdecl __getTzname(void);

#define daylight (*__getDaylight())
#define timezone (*__getTimezone())
#define tzname   (__getTzname())

#endif  /* _RTLDLL */

int         _Cdecl  stime(time_t _FAR *__tp);
void        _Cdecl  _FARFUNC tzset(void);
char _FAR * _Cdecl  _FARFUNC _strdate(char _FAR *datestr);
char _FAR * _Cdecl  _FARFUNC _strtime(char _FAR *timestr);
#endif

#ifdef __cplusplus
}
#endif

#endif
