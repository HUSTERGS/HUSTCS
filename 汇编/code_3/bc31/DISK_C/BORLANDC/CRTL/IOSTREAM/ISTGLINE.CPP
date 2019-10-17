/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     filename - istgline.cpp                                  |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          istream& istream::getline( signed char*, int, char )|*/
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

// extract characters into an array, reading and discarding delimiter d

istream _FAR & istream::getline(signed char* p, int len, char d)
{
    if( ipfx1() )
        {
        signed char* op = p;
        int c = 0;
        while( --len > 0  &&  (c = bp->sgetc()) != EOF )
            {
            ++gcount_;
            bp->stossc();
            if( c == d )
                break;
            *p++ = c;
            }
        if( c == EOF )
            setstate((p == op) ? (ios::eofbit | ios::failbit) : ios::eofbit);
        }
    else
        setstate(ios::failbit);

    *p = 0; // always terminate with a null
    return *this;
}


