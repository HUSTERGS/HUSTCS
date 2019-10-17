/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     isteflt.cpp                                              |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          istream& istream::operator>> ( float& )             |*/
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
#include <float.h>  // for characteristics of floating types
#include <errno.h>  // for reporting range errors



/*
 * We assume that extracting a long double and casting to float is not
 * significantly more expensive than working only with floats.
 */
istream _FAR & istream::operator>> (float _FAR & f)
{
    long double x;

    *this >> x;     // extract the value
    if( ! fail() )
        {    // value returned only if no failure
        if( x < -FLT_MAX )
            {
            errno = ERANGE;
            f = -FLT_MAX;
            }
        else if( FLT_MAX < x )
            {
            errno = ERANGE;
            f = FLT_MAX;
            }
        else
            f = float(x);
        }
    return *this;
}


