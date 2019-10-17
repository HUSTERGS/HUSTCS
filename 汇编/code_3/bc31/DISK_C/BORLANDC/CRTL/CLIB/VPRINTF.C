/*-----------------------------------------------------------------------*
 * filename - vprintf.c
 *
 * function(s)
 *        vprintf - send formatted output to stdout
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <_printf.h>
#include <_stdio.h>

/*---------------------------------------------------------------------*

Name            vprintf - send formatted output to stdout

Usage           int vprintf(const char *format, va_list param);

Prototype in    stdio.h

Description     see printf

*---------------------------------------------------------------------*/
int _CType _FARFUNC vprintf (const char *fmt, va_list ap)
{
        return( __vprinter ((putnF *)__fputn, stdout, fmt, (void _ss *) ap) );
}

