/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stbsgetn.cpp                                             |*/
/*|                                                              |*/
/*|     Class streambuf                                          |*/
/*|          int streambuf::sgetn( char *, int )                 |*/
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

int streambuf::sgetn(char* s, int n)
{
    if( n <= (egptr_ - gptr_) )
        {
        memcpy(s, gptr_, n);
        gbump(n);
        return n;
        }
    return do_sgetn(s, n);
}

