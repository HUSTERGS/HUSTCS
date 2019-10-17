/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     filename - istread.cpp                                   |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          istream& istream::read( signed char* , int )        |*/
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

istream _FAR & istream::read(signed char* p, int len)
{
    if( ipfx1() )
        {
        int c = 0;
        while( --len >= 0  &&  (c = bp->sgetc()) != EOF )
            {
            *p++ = c;
            ++gcount_;
            bp->stossc();
            }
        if( c == EOF )
            setstate((len >= 0) ? (ios::eofbit | ios::failbit) : ios::eofbit);
        }
    return *this;
}


