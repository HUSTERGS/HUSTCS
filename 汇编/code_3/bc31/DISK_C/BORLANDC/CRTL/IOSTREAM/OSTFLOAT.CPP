/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ostfloat.cpp                                             |*/
/*|                                                              |*/
/*|     Class ostream                                            |*/
/*|          ostream& ostream::operator<< ( long double )        |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

/*
    This code assumes the IEEE Standard 754-1985 model of floating-point
    numbers, but makes no assumptions about the details of the floating-point
    representation.  There are several IEEE kinds (classes) of number.
    Positive or Negative Infinity result on overflow, and propagate
    as a mathematical infinity does.  Overflow and underflow may or may not
    produce a signal (interrupt).  Operations on infinities may or may not
    produce a signal.
    An undefined operation, such as (0.0 / 0.0) or (0.0 * Infinity),
    produces a special value called Not-A-Number, or NaN.
    Any operation on a NaN results in a NaN.  Production of or operations on
    a NaN may or may not produce a signal (interrupt).
    When a result is smaller in magnitude than the smallest standard value
    but is not zero, it may be represented as a Denormalized number.
    Operations on denormalized numbers may or may not produce a signal.

    The IEEE standard recommends that any implementation supply certain
    auxiliary functions to help in working with special values.  These
    recommended functions are in a header file called <fakeieee.h>.

    This code uses the following IEEE functions:
    // return the kind of number
    int fpclass( long double );

    // return the first value with the sign of the second,
    // even if one is Infinity or NaN, which would otherwise be
    // an illegal operation
    long double fpcopysign( long double, long double );

    // return true if -INFINITY < parameter < +INFINITY
    int fpfinite( long double );

    // return true if parameter is a NaN
    int fpisnan( long double );

    In addition, we generate special strings for +Infinity, -Infinity,
    and NotANumber.  You may wish to generate other strings, or just
    set Infinities to HUGE_VAL and emit them normally.  It is not
    obvious what to do about NaN's in that case.

    If your system does not have an <ieee.h> or equivalent header, or
    if your floating-point system does not fit this model, you may as
    an expedient define the macro name _NOIEEE_ immediately below, and
    use a simplified header "fakeieee.h" supplied with this package.
    You will later want to go through the code to provide any needed
    functionality depending on your floating-point model.

    Long doubles are not directly supported by this package.  The
    modifications to support them should be obvious and straightforward.

    NOTES:
    1.  Function "round" below contains a rounding table which must
    have as many entries as there are significant decimal digits in
    the floating-point representation.  IEEE double-precision provides
    about 16 significant decimal digits.
    2.  Function "eout" below assumes that the maximum exponent of 10
    which can be represented is no bigger than 999.  This may not be
    true for long doubles, and provision for extra digits will be
    needed.


    This code has now been modified to use type long double exclusively,
    under the assumption that the math chips and the software floating-
    point library all convert all floats and doubles to long double
    internally.  It makes more sense to do this conversion once on input
    and once on output rather than multiple times.
*/

#define _NOIEEE_

#include <ioconfig.h>
#include <iostream.h>
#include <string.h>
#include <math.h>

#ifdef _NOIEEE_
#   include "fakeieee.h"
#else
#   include <ieee.h>
#endif

static char Infinity[]    = "[+Infinity]";
static char NegInfinity[] = "[-Infinity]";
static char NotANumber[]  = "[NotANumber]";

// structure used to pass around the current status of the value

struct float_data {
    int exp;        // the power of 10
    long double remain; // normalized range [1.0, 10.0), unprinted digits
    int is_neg;     // is this a negative value
    int is_zero;    // is value zero
    int showpoint;  // do we force display of decimal point
    int precision;  // precision to display (number of digits)
    int expchar;    // 'e' or 'E' in scientific format
};


/*
 * Funny version of frexp() for long doubles which just returns
 * the exponent.  We don't have long double format published in any
 * header, so we just use non-portable magic code to do the job.
 * Some day we may have a real library version of frexpl(), which
 * should then be used.
 */

static int lfrexp(long double x)
{
    // get last 15 bits of the long double
    int res = (((unsigned int*) &x)[4]) & 0x7FFF;
    return (res == 0) ? 0 : res - 0x3FFF;
}

//  Normalize representation of floating value as signed magnitude in
//  range [1.0, 10.0) times 10^exp, or as 0.0

static void normalize( long double val, float_data& eval )
{
    eval.is_neg = 0;
    eval.is_zero = 0;
    eval.exp = 0;

    switch( fpclass(val) )
        {
        case FPSIGNAN:
        case FPQUIETNAN:
            break;              // cannot process NaN's

        case FPNEGINF:
            eval.is_neg = 1;
            val = fpcopysign(val, 1.0); // make into positive infinity
            // fall through

        case FPPOSINF:
            break;

        case FPNEGZERO:
            eval.is_neg = 1;
            val = 0.0;          // make into non-negative zero
            // fall through

        case FPPOSZERO:
            eval.is_zero = 1;
            break;

        case FPNEG:
        case FPNEGDENOR:
            eval.is_neg = 1;
            val = -val;         // make positive
            // fall through

        case FPPOSDENOR:
        case FPPOS:
        // processing for non-special values

            // this calculation is not exact, but we fix it up later
            int exp = lfrexp(val);             // get exponent base 2
            exp = (int) (((long) exp * 2466L) / 8192); // approx exponent base 10
            eval.exp = exp;

            if( exp != 0 )
                {
                int neg = 0;
                if( exp < 0 )
                    {
                    exp = -exp;
                    neg = 1;
                    }
                long double power = 1.0;
                long double temp = 10.0;
                do  {
                    while( exp != 0  &&  (exp & 1) == 0 )
                        {
                        temp *= temp;
                        exp >>= 1;
                        }
                    power *= temp;
                    exp--;
                    } while( exp != 0 );
                if( neg )
                    val *= power;
                else
                    val /= power;
                }

            // fix up if out of range (we know it can't be >= 10.0)
            if( val < 1.0 )
                {
                val *= 10.0L;
                eval.exp -= 1;
                }
            break;
        }

    eval.remain = val;
}


// Return the ASCII representation of the next digit of the value,
// adjusting remainder.

static char next_digit( float_data& eval )
{
    int digit;

    digit = (int) eval.remain;
    eval.remain = 10.0L * (eval.remain - (long double) digit);
    return digit + '0';
}


// Generate ASCII digits for value in float_data.
// Return pointer to the end of the string.

static char* flt_out( float_data& eval, char *pt )
{
    int count, exp;
#pragma -eff
    if( fpisnan(eval.remain) )
        {
        strcpy(pt, NotANumber);
        pt += strlen(pt);
        }
#pragma .eff

    else if( ! fpfinite(eval.remain) )
        {
        if( eval.is_neg )
            strcpy(pt, NegInfinity);
        else
            strcpy(pt, Infinity);
        pt += strlen(pt);
        }
    else
        {
        // integer portion
        exp = eval.exp + 1; // add 1 to make subsequent tests cheaper
        if( exp <= 0 )
            *(pt++) = '0';
        else
            for( ;  exp > 0;  exp-- )
                *(pt++) = next_digit(eval);

        // possible decimal point
        if( eval.precision  ||  eval.showpoint )
            *(pt++) = '.';

        // fraction portion
        for( count = eval.precision;  count > 0;  count-- )
            {
            if( exp < 0 )
                {
                *(pt++) = '0';
                exp++;
                }
            else
                *(pt++) = next_digit(eval);
            }

        // maybe strip trailing fractional zeros
        if( eval.precision  &&  ! eval.showpoint )
            {
            while( pt[-1] == '0' )
                --pt;
            if( pt[-1] == '.' )
                --pt;   // don't leave a bare decimal point
            }

        *pt = '\0';
        }

    return pt;
}


// "digits" = normalized fraction digits affected by rounding.

static void round( float_data& eval, int digits )
{
    // roundamt[n] == 1/2 of nth digit
    const int sigdig = 20;  // see note in introduction
    static long double roundamt[sigdig+1] =
    { 5.0e-1,  5.0e-2,  5.0e-3,  5.0e-4,  5.0e-5,  5.0e-6,
      5.0e-7,  5.0e-8,  5.0e-9,  5.0e-10, 5.0e-11, 5.0e-12,
      5.0e-13, 5.0e-14, 5.0e-15, 5.0e-16, 5.0e-17, 5.0e-18,
      5.0e-19, 5.0e-20, 5.0e-21
    };

    switch( fpclass(eval.remain) )
        {
        case FPSIGNAN:
        case FPQUIETNAN:
        case FPNEGINF:
        case FPNEGZERO:
        case FPPOSZERO:
        case FPPOSINF:
            break;      // no rounding needed or possible

        default:      // finite value may require rounding
            if(digits >= 0 && digits <= sigdig)
                {
                eval.remain += roundamt[digits];
                if( eval.remain >= 10.0L )
                    {
                    eval.remain /= 10.0L;
                    eval.exp++;
                    }
                }
            break;
        }
}


// generate a number in scientific format
// if values greater than 10^999 are possible, see note in introduction

static void eout( float_data& eval, char* buf )
{
    // rounding can affect exponent, so do it first
    round(eval, eval.precision);

    // save exponent data
    int negexp = 0;     // is exponent negative
    int exp = eval.exp;     // absolute value of exponent
    if( exp < 0 )
        {
        negexp = 1;
        exp = -exp;
        }

    // generate digits field
    eval.exp = 0;   // for flt_out
    char* pt = flt_out(eval, buf);

    if( fpfinite(eval.remain) )
        {
        // generate exponent field
        *(pt++) = eval.expchar;
        if( negexp )
            *(pt++) = '-'; // always a sign
        else
            *(pt++) = '+';
        if(exp >= 100)
            {
            if (exp >= 1000)
                {
                *(pt++) = '0' + exp / 1000; // fourth digit needed
                exp %= 1000;
                }
            *(pt++) = '0' + exp / 100;      // third digit needed
            exp %= 100;
            }
        *(pt++) = '0' + exp / 10;           // at least two digits
        *(pt++) = '0' + exp % 10;
        *(pt++) = '\0';
        }
}


ostream _FAR & ostream::operator<< (long double d)
{
    float_data eval;
    char buf[60];   // big enough for any floating result

    normalize(d, eval);
    eval.expchar = (flags() & ios::uppercase) ? 'E' : 'e';
    eval.precision = precision();
    if( eval.precision <= 0 )
        eval.precision = 6; // default value for precision
    eval.showpoint = (flags() & ios::showpoint) != 0;

    if( flags() & ios::fixed )
        {
        round(eval, eval.exp + eval.precision);
        flt_out(eval, buf);
        }
    else if( flags() & ios::scientific )
        eout(eval, buf);
    else if( eval.exp < -4  ||  eval.precision < eval.exp )
        eout(eval, buf);    // default to scientific
    else
        {          // default to fixed
        round(eval, eval.exp + eval.precision);
        flt_out(eval, buf);
        }

    char* prefix = 0;
    if( eval.is_neg )
        prefix = "-";
    else if( ! eval.is_zero  &&  (flags() & ios::showpos) )
        prefix = "+";

    // now we have a formatted string for output, to be possibly padded
    outstr(buf, prefix);
    return *this;
}
