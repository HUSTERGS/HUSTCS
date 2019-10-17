/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     iosrctr2.cpp                                             |*/
/*|                                                              |*/
/*|     Class strstream                                          |*/
/*|          strstream::strstream( char *, int, int )            |*/
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
#include <strstrea.h>
#include <string.h>

strstream::strstream(char* str, int size, int omode) :
        strstreambase(str, size, str),
        iostream(strstreambase::rdbuf())
{
    if( omode & (ios::ate | ios::app) )
    strstreambase::rdbuf()->seekoff(strlen(str), ios::beg, ios::out);
}


