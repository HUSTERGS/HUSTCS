/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     istdipfx.cpp                                             |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          int istream::ipfx( int )                            |*/
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

// implementation of ipfx
// flush tied stream if needed, skip whitespace if needed

int istream::ipfx(int need)
{
    gcount_ = 0;

    if( ! good() )
        return 0;

    // flush tied stream if needed
    if ( tie()  &&  (! need  ||  need > bp->in_avail()) )
        tie()->flush();

    if( ! need  &&  (ispecial & skipping) )
        eatwhite();

    return good();
}


