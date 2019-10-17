/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     isteldbl.cpp                                             |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          istream& istream::operator>> ( long double& )       |*/
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
 * If you have an optimized strtod() routine (or atof() or equivalent),
 * you may wish to extract characters into a local string and call
 * strtod() with that string instead of using the code given here.
 *
 * We take care to avoid floating-point overflow and underflow during all
 * calculations and set errno to ERANGE on overflow and underflow, but
 * we do not raise any error signals.
 * You can speed up the code by removing the checks if they don't matter
 * in your system.
 *
 * This code uses type long double exclusively, under the assumption
 * that the math chips and the software floating-point library all
 * convert all floats and doubles to long double internally.  It makes
 * more sense to do this conversion once on input and once on output
 * rather than multiple times.
 */

#include <ioconfig.h>
#include <iostream.h>
#include <ctype.h>
#include <float.h>  // for characteristics of floating types
#include <math.h>      // for HUGE_VAL
#include <errno.h>  // for reporting range errors



/*
 * The following defines are for type long double.
 * If you want to do float or long separately,
 * you will need to supply the appropriate values
 */
#define Dbigexp 49320L      // much bigger than any power 10 exponent
#define Dmaxint 493200L     // (10*Dbigexp)
#define Dfixexp 2466L       // about max_10_exp / 2
#define Dfixval 1.0e2466    // 10 ** Dfixexp


istream _FAR & istream::operator>> (long double _FAR & val)
{
    if( ipfx0() )
        {     // verify file state and possibly skip white

        int c;          // current input character
        int negval;     // entire value is negative
        int negexp;     // exponent is negative
        long exp;       // accumulated exponent
        int formok;     // floating-point number format is valid

        formok = 0;     // until proven otherwise
        c = bp->sgetc();    // look at first character

        // get leading sign
        negval = c == '-';
        if( c == '+'  ||  negval )
            c = bp->snextc();
        else if( c == EOF )
            setstate(ios::badbit);  // no characters extracted

        // scan off digits up to decimal point
        val = 0.0;
        if( isdigit(c) )
            {
            formok = 1;
            do  {
                c -= '0';
                val = 10.0 * val + c;
                c = bp->snextc();
                } while( isdigit(c) );
            }

        // scan off fractional digits, keeping count
        exp = 0;
        if( c == '.' )
            {
            c = bp->snextc();
            if( isdigit(c) )
                {
                formok = 1;
                do  {
                    c -= '0';
                    val = 10.0 * val + c;
                    --exp;
                    c = bp->snextc();
                    } while( isdigit(c) );
                }
            }

        // look for possibly-signed exponent
        if( formok  &&  (c == 'e'  ||  c == 'E') )
            {
            c = bp->snextc();
            formok = isdigit(c)  ||  c == '+'  ||  c == '-';

            long givenexp = 0;  // exponent given in E... part of number
            if( ! formok )
                val = 0.0;
            else
                {
                // convert possibly-signed exponent
                negexp = c == '-';  // here we mean the given exponent
                if( c == '+'  ||  negexp )
                    c = bp->snextc();
                formok = isdigit(c);
                if( ! formok )
                    val = 0.0;
                else
                    {
                    do  {
                        if( givenexp < Dbigexp )
                            {
                            c -= '0';
                            givenexp = 10 * givenexp + c;
                            }
                        c = bp->snextc();
                        } while( isdigit(c) );
                    }
                }

            // adjust exponent by given exponent, watching for overflow
            if( negexp )
                {
                if( givenexp - Dmaxint < exp )
                    exp -= givenexp;
                else
                    exp = - Dmaxint;
                }
            else
                {
                if( Dmaxint - givenexp > exp )
                    exp += givenexp;
                else
                    exp = Dmaxint;
                }
        }

    // try to salvage some underflow
    if( exp <= LDBL_MIN_10_EXP )
        {
        val /= Dfixval;
        exp += Dfixexp;;
        }

    // final calculation
    if( exp < LDBL_MIN_10_EXP )
        {
        val = 0.0;
        errno = ERANGE;
        }
    else if( exp > LDBL_MAX_10_EXP )
        {
        val = HUGE_VAL;
        errno = ERANGE;
        }
    else if( formok )
        {
        int overflow = 0;           // did overflow occur
        long double adjust = 1.0;   // amount to adjust because of exponent
        long double power = 10.0;   // used in building adjust
        negexp = exp < 0;           // negexp now refers to net exponent
        if( negexp )
            exp = -exp;     // exp is now absolute value

        // compute val * (10 ** exp)
        while( exp > 0 )
            {
            if( exp & 1 )
                {
                if( LDBL_MAX / adjust >= power )
                    adjust *= power;
                else
                    overflow = 1;
                }
            exp >>= 1;
            if( exp > 0 )
                {
                if( LDBL_MAX / power >= power )
                    power *= power;
                else
                    overflow = 1;
                }
            }

        if( ! overflow )
            {
            if( adjust != 1.0 )
                {
                if( negexp )
                    val /= adjust;
                else if( val <= 1.0 )
                    val *= adjust;
                else if( LDBL_MAX / val >= adjust )
                    val *= adjust;
                else
                    overflow = 1;
                }
            }
        if( overflow )
            {
            if( negexp )
                val = 0.0;
            else
                val = HUGE_VAL;
            errno = ERANGE;
            }
        }

    if( formok )
        {
        if( negval )
            val = -val; // adjust the sign
        }
    else if( c == EOF)
        setstate(ios::eofbit | ios::failbit);
    else
        setstate(ios::failbit);
    }

    return *this;
}
