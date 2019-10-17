/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ostwrite.cpp                                             |*/
/*|                                                              |*/
/*|     Class ostream                                            |*/
/*|          ostream& ostream::write( const signed char *, int ) |*/
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

ostream _FAR & ostream::write(const signed char* s, int n)
{
    if( ! fail() )
        {
        if( bp->sputn((const char*)s, n) != n )
            setstate(badbit);
        }
    return *this;
}
