/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     isteatwh.cpp                                             |*/
/*|                                                              |*/
/*|     Class istream                                            |*/
/*|          void istream::eatwhite()                            |*/
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
#include <ctype.h>

// extract consecutive whitespace

//  NOTE: technically, eating whitespace shouldn't cause a failure,
//  but because eatwhite() is only called in the context of another
//  extractor, it's quicker to set failbit here rather than have
//  every extractor set failbit if ipfx() fails.

void istream::eatwhite()
{
    int c;
    while( (c = bp->sgetc()), isspace(c) )
        {
        bp->stossc();
        ++gcount_;
        }

    if( c == EOF )
        setstate(ios::eofbit|ios::failbit);
}


