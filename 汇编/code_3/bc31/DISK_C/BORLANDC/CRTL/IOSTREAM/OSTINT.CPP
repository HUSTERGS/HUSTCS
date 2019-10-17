/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ostint.cpp                                               |*/
/*|                                                              |*/
/*|     Class ostream                                            |*/
/*|          ostream& ostream::operator<< (long l)               |*/
/*|          ostream& ostream::operator<< (unsigned long ul)     |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <ioconfig.h>
#include <iostream.h>

/*
 * Convert val>=0 to ascii in buffer b, with implied numeric base.
 * Digits are acquired in reverse order, so we start at the end of the
 * buffer and work forward.
 * 'b' initially points to the end of the buffer, and is assumed big enough.
 * Return a pointer to the beginning address of the null-terminated string.
 */

// decimal conversion

static char* todec(char *b, unsigned long val)
{
    *b = '\0';
    do  {
        *--b = ((int) (val % 10)) + '0';
        val /= 10;
        } while( val );
    return b;
}

// octal conversion

static char* tooct(char *b, unsigned long val)
{
    *b = '\0';
    do  {
        *--b = (val & 7) + '0';
        val /= 8;   // let compiler make this a shift if appropriate
        } while( val );
    return b;
}

// hex conversion, with indicator for uppercase or lowercase letters

static char *tohex(char *b, unsigned long val, int upper)
{
    static char digits[2][16] = {
    {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'},
    {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}
    };
    char *d = upper ? &digits[1][0] : &digits[0][0];
    *b = '\0';
    do  {
        *--b = d[(int)val & 0xf];
        val /= 16;  // let compiler make this a shift if appropriate
        } while( val );
    return b;
}


// format and insert a signed long

ostream _FAR & ostream::operator<< (long l)
{
    char buf[MaxCharsInLong];   // result of conversion
    char *prefix = 0;           // displayed numeric prefix string
    char *p;

    // find conversion base
    int base = (flags() & ios::hex) ? 16 : ((flags() & ios::oct) ? 8 : 10);

    // do we treat this as negative?  (oct and hex are unsigned)
    int neg = base == 10  &&  l < 0;

    // value to use, exclusive of sign
    unsigned long ul = neg ? -l : l;

    if( base == 10 )
        {
        p = todec(buf + MaxCharsInLong - 1, ul);

        // compute any sign prefix
        if( ul )
            if( neg )
                prefix = "-";
            else if( flags() & ios::showpos )
                prefix = "+";
        }
    else if( base == 16 )
        {
        int upper = (flags() & ios::uppercase) != 0;
        p = tohex(buf + MaxCharsInLong - 1, ul, upper);

        // compute any base prefix
        if( flags() & ios::showbase )
            prefix = upper ? "0X" : "0x";
        }
    else /* base == 8 */
        {
        p = tooct(buf + MaxCharsInLong - 1, ul);

        // compute any base prefix
        if( flags() & ios::showbase )
            prefix = "0";
        }

    // now we have a formatted string for output, to be possibly padded
    outstr((char*)p, prefix);
    return *this;
}


// format and insert an unsigned long
ostream _FAR & ostream::operator<< (unsigned long ul)
{
    char buf[MaxCharsInLong];
    char *prefix = 0;       // displayed numeric prefix string
    char *p;


    if( flags() & ios::hex )
        {
        int upper = (flags() & ios::uppercase) != 0;
        p = tohex(buf + MaxCharsInLong - 1, ul, upper);

        // compute any base prefix
        if( flags() & ios::showbase )
            prefix = upper ? "0X" : "0x";
        }
    else if( flags() & ios::oct )
        {
        p = tooct(buf + MaxCharsInLong - 1, ul);

        // compute any base prefix
        if( flags() & ios::showbase )
            prefix = "0";
        }
    else
        {
        p = todec(buf + MaxCharsInLong - 1, ul);

        // compute any sign prefix
        if( ul  &&  (flags() & ios::showpos) )
            prefix = "+";
        }

    // now we have a formatted string for output, to be possibly padded
    outstr((char*)p, prefix);
    return *this;
}


