/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     osrctr1.cpp                                              |*/
/*|                                                              |*/
/*|     Class ostrstream                                         |*/
/*|          ostrstream::ostrstream( char *, int, int )          |*/
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

ostrstream::ostrstream(signed char* str, int len, int omode) :
        strstreambase(str, len, str),
        ostream(strstreambase::rdbuf())
{
    if( omode & (ios::ate | ios::app) )
    strstreambase::rdbuf()->seekoff(strlen(str), ios::beg, ios::out);
}

ostrstream::ostrstream(unsigned char* str, int len, int omode) :
        strstreambase((signed char *)str, len, (signed char *)str),
        ostream(strstreambase::rdbuf())
{
    if( omode & (ios::ate | ios::app) )
    strstreambase::rdbuf()->seekoff(strlen(str), ios::beg, ios::out);
}


