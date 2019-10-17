/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     osttellp.cpp                                             |*/
/*|                                                              |*/
/*|     Class ostream                                            |*/
/*|          streampos ostream::tellp()                          |*/
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

// read the put pointer's position
streampos ostream::tellp()
{
    streampos p = EOF;
    if( bad()  ||  (p = bp->seekoff(0, ios::cur, ios::out)) == EOF )
        setstate(ios::failbit);
    return p;
}


