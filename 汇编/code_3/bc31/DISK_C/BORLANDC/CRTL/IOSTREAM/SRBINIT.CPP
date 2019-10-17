/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     srbinit.cpp                                              |*/
/*|                                                              |*/
/*|    Class strstreambuf                                        |*/
/*|    void strstreambuf::init( signed char*, int, signed char* )|*/
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
#include <limits.h>
#include <string.h>

/*
    If n is negative, the provided buffer is supposed to be unlimited.
    As a practical way to handle this, the buffer is arbitrarily defined
    to be size INT_MAX.  (It really should be the max value supported by
    type size_t, but AT&T defined all sizes to be int.)
*/

void strstreambuf::init( signed char* ptr, int n, signed char* pstart )
{
    ssbflags = 0;
    if( n == 0 )
        n = strlen((char*)ptr);
    else if( n < 0 )
        {
        n = INT_MAX;
        ssbflags |= unlimited;  // distinguish it from merely large
        }

    setb((char*)ptr, (char*)ptr+n, 0);
    if( pstart )
        {
        setp((char*)pstart, ebuf());
        setg((char*)ptr, (char*)ptr, (pstart > ptr+n) ?
                                     (char *)ptr+n: (char*)pstart);
        }
    else
        setg((char*)ptr, (char*)ptr, (char*)ebuf());

    allocf = 0;
    freef = 0;
}


