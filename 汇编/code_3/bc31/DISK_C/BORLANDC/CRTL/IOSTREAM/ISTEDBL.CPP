/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     istedbl.cpp                                              |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          istream& istream::operator>> ( double& )            |*/
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
 * We assume that extracting a long double and casting to double is not
 * significantly more expensive than working only with doubles.
 */
istream _FAR & istream::operator>> (double _FAR & d)
{
    long double x;

    *this >> x;     // extract the value
    if( ! fail() )
        {    // value returned only if no failure
        if( x < -DBL_MAX )
            {
            errno = ERANGE;
            x = -DBL_MAX;
            }
        else if( DBL_MAX < x )
            {
            errno = ERANGE;
            x = DBL_MAX;
            }
        else
            d = double(x);
        }
    return *this;
}


