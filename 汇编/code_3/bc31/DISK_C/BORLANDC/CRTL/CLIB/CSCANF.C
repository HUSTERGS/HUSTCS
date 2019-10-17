/*------------------------------------------------------------------------
 * filename - cscanf.c
 *
 * function(s)
 *        cscanf - performs formatted input from console
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <conio.h>
#include <stdio.h>
#include <_stdio.h>
#include <_scanf.h>


/*--------------------------------------------------------------------------*

Name            cscanf - performs formatted input from console

Usage           int cscanf(char *format[,argument, ...]);

Prototype in    conio.h

Description     cscanf,  as  all  ...scanf  family  functions,  scans input
                fields,  one  character  at   a  time,  and  converts  them
                according to a given format; these functions all:

                . accept  a format  string  that  determines how  the input
                fields are  to be interpreted.

                . apply  the format  string to  a variable  number of input
                fields in order to format the input

                . store  the  formatted  input  in  the  addresses given as
                arguments  after  the  format  string.


Return value    cscanf  returns  the  number  of  input fields successfully
                scanned, converted  and stored. If cscanf  attempts to read
                an end-of-file, the return value  is EOF. If no fields were
                stored, the return value is 0.

*---------------------------------------------------------------------------*/
int cdecl cscanf (const char *fmt, ...)
{
        return  _scanner (
                (int near (*)(void *))_Ngetche,
                (void near (*)(int, void *))_Nungetch,
                NULL,
                fmt,
                _va_ptr
                );
}
