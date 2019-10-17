/*-----------------------------------------------------------------------*
 * filename - ltoa1.c
 *
 * function(s)
 *        itoa      - converts an integer to a string
 *        ltoa      - converts a long to a string
 *        ultoa     - converts an unsigned long to a string
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdlib.h>
#include <_printf.h>

/*-----------------------------------------------------------------------*

Name            itoa  - converts an integer to a string
                ltoa  - converts a long to a string
                ultoa - converts an unsigned long to a string

Usage           char *itoa(int value, char *strP, int radix);
                char *ltoa(long value, char *strP, int radix);
                char *ultoa(unsigned long value, char *strP, int radix);

Prototype in    stdlib.h
                _printf.h for __longtoa

Description     These functions  convert value to a  null-terminated string
                and  store the  result in  string. With  itoa, value  is an
                integer;  with ltoa  it is  a  long;  with ultoa  it is  an
                unsigned long.  __longtoa is the  internal routine used for
                all these conversions to ASCII (in longtoa.cas).

                radix specifies the base to be used in converting value. it
                must be between  2 and 36 (inclusive). With  itoa and ltoa,
                if value is negative, and  radix is 10, the first character
                of string is  the minus sign (-). This does  not occur with
                ultoa. Also, ultoa performs no overflow checking.

                maybeSigned is treated as a boolean. If false then value is
                treated  as unsigned  long and  no sign  will be  placed in
                *strP.

                hexStyle  may take  the values  'a' or  'A' and  determines
                whether lower or  upper case alphabetics are used  when the
                radix is 11 or greater.

                Note: The space  allocated for string must be  large enough
                to hold the returned  string including the terminating null
                character (\0).  itoa can return  up to 17  bytes; ltoa and
                ultoa, up to 33 bytes.

Return value    All these functions return a pointer to string. There is no
                error return.

*------------------------------------------------------------------------*/
char * _CType _FARFUNC itoa(int value, char *strP, int radix)
{
#define dword   unsigned long

        return  __longtoa ((radix == 10) ? (long) value :
                           (dword)((unsigned)value), strP, radix, 1, 'a');
}



/*-----------------------------------------------------------------------*

Name            ultoa - converts an unsigned long to a string

Usage           char *ultoa(unsigned long value, char *string, int radix);

Prototype in    stdlib.h

Description     see itoa

*------------------------------------------------------------------------*/
char * _CType _FARFUNC ultoa(unsigned long value, char *strP, int radix)
{
        return  __longtoa (value, strP, radix, 0, 'a');
}



/*-----------------------------------------------------------------------*

Name            ltoa - converts a long to a string

Usage           char *ltoa(long value, char *string, int radix);

Prototype in    stdlib.h

Description     see itoa

*------------------------------------------------------------------------*/
char * _CType _FARFUNC ltoa(long value, char *strP, int radix)
{
        return  __longtoa (value, strP, radix, (radix == 10), 'a');
}
