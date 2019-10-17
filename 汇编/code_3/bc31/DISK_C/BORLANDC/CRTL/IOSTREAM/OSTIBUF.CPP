/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     ostibuf.cpp                                              |*/
/*|                                                              |*/
/*|     Class ostream                                            |*/
/*|          ostream& ostream::operator<< ( streambuf * )        |*/
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

// extract from streambuf, insert into this ostream
ostream _FAR & ostream::operator<< (streambuf* s)
{
    if( opfx() )
        {
        int c;
        while( (c = s->sbumpc()) != EOF )
            {
            if( bp->sputc(c) == EOF )
                {
                setstate(ios::badbit);
                break;
                }
            }
        }
    osfx();
    return *this;
}
