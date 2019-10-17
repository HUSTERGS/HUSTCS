/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     filename - istign.cpp                                    |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          istream& istream::ignore( int, int )                |*/
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

// extract and discard n chars, or through delimiter, whichever is first

istream _FAR & istream::ignore(int n, int d)
{
    if( ipfx1() )
        {
        int c = 0;
        while( --n >= 0  &&  (c = bp->sgetc()) != EOF )
            {
            ++gcount_;
            bp->stossc();
            if( c == d )
                break;  // we DO consume the delimiter
            }
        if( c == EOF )
            setstate(ios::eofbit);
        }
    return *this;
}


