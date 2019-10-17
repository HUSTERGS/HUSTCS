/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stbsputn.cpp                                             |*/
/*|                                                              |*/
/*|     Class streambuf                                          |*/
/*|          int streambuf::sputn( const char *, int )           |*/
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
 * The following functions are expected to be inline, but just in case
 * they aren't, and they generate a LOT of code, here they are as
 * global closed subroutines.
 */

int streambuf::sputn(const char* s, int n)
{
    if( n <= (epptr_ - pptr_) )
        {
        memcpy(pptr_, s, n);
        pbump(n);
        return n;
        }
    return do_sputn(s, n);
}

