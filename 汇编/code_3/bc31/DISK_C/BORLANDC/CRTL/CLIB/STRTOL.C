/*------------------------------------------------------------------------
 * filename - strtol.c
 *
 * function(s)
 *        Get    - gets the next character in a string
 *        UnGet  - moves a character pointer one position forward
 *        strtol - convert a string to a long integer
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>
#include <_scanf.h>
#include <stddef.h>

/*---------------------------------------------------------------------*

Name            Get - gets the next character in a string

Usage           static int Get(char **strPP);

Return value    the next character in a string.  It return -1 if the next
                character is the null character.

*---------------------------------------------------------------------*/
static int near Get(char **strPP)
{
        register    unsigned    c;

        return ((c = *((*strPP) ++)) == 0) ? -1 : c;
}


/*---------------------------------------------------------------------*

Name            UnGet - moves a character pointer one position forward

Usage           static void UnGet(char c, char **strPP);

Description     decrements a character pointer

*---------------------------------------------------------------------*/
#pragma argsused
static void near UnGet(char c, char **strPP)
{
        --(*strPP);         /* ignore c, we don't allow the string to change */
}


/*--------------------------------------------------------------------------*

Name            strtol - convert a string to a long integer

Usage           long strtol(const char *strP, char **suffixPP, int radix);

Prototype in    stdlib.h

Description     Convert  a string  to a   long integer.  The syntax  of the
                string must be:

                long     ::= [isspace]* [sign] numeral;

                numeral  ::= { '0' ['x'|'X'] digit [digit]* } |
                             { digit [digit] }

                "strP"  is a  pointer to  the ASCII  string to  be scanned.
                "suffixPP" is a pointer to  a string pointer to be updated.
                If suffixPP  is not NULL  then the updated  pointer will be
                set to point  to the first character following  the section
                of  the string  which was   consumed. Thus  the caller  can
                easily analyze subsequent contents of the string.

                The radix may be zero, or any number 2..36. If the radix is
                zero, then a radix will be chosen from the possibilities 8,
                10, or 16, by the usual "C" rules for distinguishing octal,
                decimal, and hex numerals.

                If radix > 10 then the  letters of the alphabet "A..Z" form
                the extended set of valid digits.

Return value    If the  radix is invalid or  no number could be  found then
                the result  value is zero   and the next  char pointer will
                equal the starting string pointer.

                If  the  number  overflows,  LONG_MAX  or  LONG_MIN will be
                returned and errno will be set to ERANGE.

*---------------------------------------------------------------------------*/
long _FARFUNC strtol(const char *strP, char **suffixPP, int radix)
{
        int     charCt = 0;
        int     status;
        int     is_signed;
        long    result;

        errno = 0;

        while (isspace(*strP))
        {
                strP++;
                charCt++;
        }
        is_signed = *strP == '-';

        result = _scantol (
                (int near (*)(void *))Get,
                (void near (*)(int, void *))UnGet,
                &strP,
                radix,
                0x7FFF,
                &charCt,
                &status
                );

        if (status <= 0)
                strP -= charCt;
        else if (status == 2)
                errno = ERANGE;
        else if (status == 1 && (result >= 0) == is_signed)
        {
                errno = ERANGE;
                result = is_signed ? LONG_MIN : LONG_MAX;
        }

        if (suffixPP != NULL)
                *suffixPP = (char *)strP;

        return (result);
}
