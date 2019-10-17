/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     filename - istget.cpp                                    |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          int istream::get()                                  |*/
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

int istream::get()
{
    if( ipfx1() )
        {
        int c = bp->sbumpc();
        if( c == EOF )
            setstate(ios::eofbit);
        else
            gcount_ = 1;
        return c;
        }
    else
        return EOF;
}
