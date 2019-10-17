/*-----------------------------------------------------------------------*
 * filename - sscanf.c
 *
 * function(s)
 *        Get     - gets a character from a string
 *        UnGet   - ungets a character from a string
 *        sscanf  - gets formatted input from a string
 *        vsscanf - gets formatted input from a string
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdarg.h>
#include <stdio.h>
#include <_scanf.h>

/*---------------------------------------------------------------------*

Name            Get - gets a character from a string

Usage           static  int    Get(char **strPP)

Description     gets a character from a string

Return value    the character read or -1 of the null character

*---------------------------------------------------------------------*/
static int near Get(char **strPP)
{
        register    unsigned  char  c;

        return  ((c = *((*strPP) ++)) == 0) ? -1 : c;
}


/*---------------------------------------------------------------------*

Name            UnGet - ungets a character from a string

Usage           static  void    UnGet(char c, char **strPP)

Description     decrements a character pointer

*---------------------------------------------------------------------*/
#pragma argsused
static void near UnGet(char c, char **strPP)
{
        --(*strPP);         /* ignore c, we don't allow the string to change */
}


/*---------------------------------------------------------------------*

Name            sscanf - gets formatted input from a string

Usage           int sscanf(const char *string,
                           const char *format[, argument ...])

Prototype in    stdio.h

Description     gets formatted input from a string

Return value    number of fields scanned and stored.  sscanf returns EOF
                if an attempt is made to read at end-of-string

*---------------------------------------------------------------------*/
int cdecl _FARFUNC sscanf(const char *buf, const char *fmt, ...)
{
        return  _scanner (
                (int near (*)(void *))Get,
                (void near (*)(int, void *))UnGet,
                &buf,
                fmt,
                _va_ptr
                );
}


/*---------------------------------------------------------------------*

Name            vsscanf - gets formatted input from a string

Usage           int vsscanf(const char *string,const char *format,
                            va_list argp)

Prototype in    stdio.h

Description     gets formatted input from a string

Return value    number of fields scanned and stored.  vsscanf returns EOF
                if an attempt is made to read at end-of-string

*---------------------------------------------------------------------*/

int cdecl _FARFUNC vsscanf(const char *buf, const char *fmt, va_list ap)
{
        return  _scanner(
                (int near (*)(void *))Get,
                (void near (*)(int, void *))UnGet,
                &buf,
                fmt,
                ap
                );
}
