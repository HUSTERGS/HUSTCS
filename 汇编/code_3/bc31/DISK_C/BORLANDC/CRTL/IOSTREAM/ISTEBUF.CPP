/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     istebuf.cpp                                              |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          istream& istream::operator>> ( streambuf * )        |*/
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

// extract from this istream, insert into streambuf

istream _FAR & istream::operator>> (streambuf* s)
{
    enum errkind { noerr, nodata, putfail } err;
    if( ipfx0() )
        {
        err = nodata;
        int c;
        while( (c = bp->sgetc()) != EOF )
            {
            if( s->sputc(c) == EOF )
                {
                err = putfail;
                break;
                }
            err = noerr;
            bp->stossc();
            }
        int errstate = ( err == noerr ) ? 0 : ios::failbit;
        if( c == EOF )
            {
            errstate |= ios::eofbit;
            if( err == nodata )
                errstate |= ios::badbit;
            }
        if( errstate )
            setstate(errstate);
        }
    return *this;
}
