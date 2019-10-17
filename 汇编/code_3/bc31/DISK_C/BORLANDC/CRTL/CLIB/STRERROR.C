/*-----------------------------------------------------------------------*
 * filename - strerror.c
 *
 * function(s)
 *    strerror  - returns pointer to error message string
 *    _maperror - internal function
 *    _strerror - internal function
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <RtlData.h>

/* The local buffer should be able to contain :     */
/*  94 characters   Max User string         */
/*   2      semicolon and space     */
/*  64      Max sys_errlist string      */
/*   2      \n and NULL terminator      */

#if !defined( _RTLDLL )
static char strbuf[94 + 2 + 64 + 1];
#endif

static char * near pascal _maperror(int errnum, const char *s)
{
    char    *cp;
    _QRTLDataBlock;

    if (errnum < sys_nerr && errnum >= 0)
        cp = sys_errlist[errnum];
    else
        cp = "Unknown error";
    if (s && *s)
        sprintf(_QRTLInstanceData(strbuf), "%s: %s\n", s, cp);
    else
        sprintf(_QRTLInstanceData(strbuf), "%s\n", cp);
    return _QRTLInstanceData(strbuf);
}



char * _FARFUNC _strerror(const char *s)
{
    return _maperror(errno, s);
}

/*---------------------------------------------------------------------*

Name            strerror - returns pointer to error message string

Usage           char *strerror(char *str);

Prototype in    string.h

Description     strerror allows you to generate customized error
                messages; it returns a pointer to a null-terminated string
                containing an error message.

                If str is NULL, the return value contains the most recently
                generated system error message; this string is null-terminated.

                If str is not NULL, the return value contains str (your
                customized error message), a colon, a space, the most recently
                generated system error message, and a newline.

                The length of str should be 94 characters or less.

                strerror is different from perror in that it does not print
                error messages.

                For accurate error handling, strerror should be called as soon
                as a library routine generates an error return.

Return value    strerror returns a pointer to a constructed error
                string. The error message string is constructed in a static
                buffer that is over-written with each call to perror.

*---------------------------------------------------------------------*/
char * _FARFUNC strerror(int errnum)
{
    return  _maperror(errnum, NULL);
}
