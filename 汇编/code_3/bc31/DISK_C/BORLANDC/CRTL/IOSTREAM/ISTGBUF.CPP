/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     istgbuf.cpp                                              |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          istream& istream::get( streambuf&, char )           |*/
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

// extract characters into a streambuf up to delimiter

istream _FAR & istream::get(streambuf _FAR & s, char d)
{
    if( ipfx1() )
        {
        int c;
        int err = 0;
        while( (c = bp->sgetc()) != d  &&  c != EOF )
            {
            if( s.sputc(c) == EOF )
                {
                err = 1;
                break;
                }
            ++gcount_;
            bp->stossc();
            }
        if( c == EOF )
            setstate(ios::eofbit);
        if( err )
            setstate(ios::failbit);
        }
    return *this;
}


