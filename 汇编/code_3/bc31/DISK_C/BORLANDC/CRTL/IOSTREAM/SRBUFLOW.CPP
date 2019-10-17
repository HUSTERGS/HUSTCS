/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     srbuflow.cpp                                             |*/
/*|                                                              |*/
/*|     Class strstreambuf                                       |*/
/*|          int strstreambuf::underflow()                       |*/
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
#include <strstrea.h>

int strstreambuf::underflow()
{
    if( egptr() > gptr() )
        return (unsigned char) *gptr();

    if( base()  &&  ! unbuffered()  &&  pptr() > pbase() )
        {
        if( ! gptr()  ||  gptr() < pbase() )
            {
            // initialize get area to current put area
            setg(base(), pbase(), pptr());
            return (unsigned char) *gptr();
            }
        if( gptr() < pptr() )
            {
            // extend get area to match put area
            setg(eback(), gptr(), pptr());
            return (unsigned char) *gptr();
            }
        // else no more chars
        }

    return EOF;
}


