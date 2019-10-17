/*------------------------------------------------------------------------
 * filename - _printf.h
 *
 *      definitions for formatted printing functions
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


#ifndef __PRINTF_H
#define __PRINTF_H

#if !defined(__STDARG_H)
#include <stdarg.h>
#endif

#define __XCVTDIG__  40   /* xcvt() maximum digits supported    */
#define __XCVTMAX__  47   /* bytes for longest xcvt() string    */
#define __LTOAMAX__  32   /* bytes for radix 2 longtoa() string */
#define __CVTMAX__   48   /* MAX of the above, + 1 for \0       */

typedef unsigned pascal near putnF (const void *ptr, unsigned n, void *fp);

/*
    Defining the symbol FLOATS_32_BIT enables recognition of
    32 bit floats on the stack by using the 'h' size modifier.
    YOU, must FORCE the float to be pushed as a 32 bit number
    though!  The compiler normally widens floats to 64 bit doubles.

    example:
            union {
                float f;
                long l
                } u;
            printf("%hg\n", u.l);

    This feature can be DISABLED by default for strict ANSI compatability.
*/
#define FLOATS_32_BIT       1

/*
    Floating point parameter types to formatting functions.
    The numbers are the offset of the fraction in the data type.
*/
#define F_4byteFloat    2
#define F_8byteFloat    6
#define F_10byteFloat   8

/* These must NEVER be the same as an unnormalized 87' exponent! */

#define NAN_number  32766   /* xcvt() -> as NAN exponent    */
#define INF_number  32767   /* xcvt() -> as INF exponent    */


#ifdef __cplusplus
extern "C" {
#endif

#ifdef __OS2__
int pascal near __vprinter(putnF *__putter, void *__outP, const char *__formatP, va_list __argP );
#else
int pascal near __vprinter(putnF near *__putter, void *__outP, const char *__formatP, void _ss *__argP );
#endif

char *pascal near __longtoa(long __value, 
                            char *__S, 
                            int __radix, 
                            char __maybeSigned, 
                            char __hexStyle
                           );

void pascal near __realcvt(void *__valueP, 
                           int __ndec, 
                           char *__strP, 
                           char __formCh, 
                           char __altFormat, 
                           int __type
                          );

char * pascal near __utoa(unsigned __value, char *__buf);

int pascal near __xcvt(void *__valP, 
                       int __digits, 
                       int *__signP, 
                       char *__strP, 
                       int __ftype
                      );

#ifdef __cplusplus
}
#endif

#endif
