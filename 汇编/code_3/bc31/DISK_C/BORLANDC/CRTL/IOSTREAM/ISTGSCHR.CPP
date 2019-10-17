/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     filename - istgschr.cpp                                  |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          istream& istream::get( signed char& )               |*/
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

istream _FAR & istream::get(signed char _FAR & c)
{
    if( ipfx1() )
        {
        if( bp->in_avail())
            {
            gcount_ = 1;
            c = bp->sbumpc();
            }
        else
            c = do_get();
        }
    else
        setstate(ios::failbit);

    return *this;
}


