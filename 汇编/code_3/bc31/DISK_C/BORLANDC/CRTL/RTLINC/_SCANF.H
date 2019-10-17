/*------------------------------------------------------------------------
 * filename - _scanf.h
 *
 *      Data types and prototypes for scanning functions
 *-----------------------------------------------------------------------*/

/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     C/C++ Run Time Library - Version 4.0                     |*/
/*|                                                              |*/
/*|                                                              |*/
/*|     Copyright (c) 1987, 1991 by Borland International        |*/
/*|     All Rights Reserved.                                     |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

#ifndef __SCANF_H
#define __SCANF_H

#if !defined(__STDARG_H)
#include <stdarg.h>
#endif

typedef enum
{
    isSuppressed = 1,
    isHalf       = 2,
    isLong       = 4,
    isLongDouble = 8,
    isExclusive  = 16,
    isFarPtr     = 32
} flagBits;


#ifdef __cplusplus
extern "C" {
#endif
int near _scanner( int   (near *__Get)   (void *__srceP),
                   void  (near *__UnGet) (int __ch, void *__srceP),
                   void       *__srceP,
                   const char *__formP,
                   va_list     __varPP );

long double near _scantod( int  (near *__Get)   (void *__srceP),
                       void (near *__UnGet) (int __ch, void *__srceP),
                       const void *__srceP,
                       int         __width,
                       int        *__countP,
                       int        *__statusP );

long near _scantol( int   (near *__Get)   (void *__srceP),
                    void  (near *__UnGet) (int __ch, void *__srceP),
                    const void   *__srceP,
                    int           __radix,
                    int           __width,
                    int      *__countP,
                    int      *__statusP );

void near _scanpop (void);

void near _scanrslt (void *__rsltP, int __rsltType);

/*
  Internal RTL function to perform double/float truncations.
*/
#define FLT 0
#define DBL 1
double near pascal __ldtrunc(int __flag, long double __x, double __xhuge);

#ifdef __cplusplus
}
#endif

#endif
