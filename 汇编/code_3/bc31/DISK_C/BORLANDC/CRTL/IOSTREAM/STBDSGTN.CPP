/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stbdsgtn.cpp                                             |*/
/*|                                                              |*/
/*|     Class streambuf                                          |*/
/*|          int streambuf::do_sgetn( char *, int )              |*/
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

// called when sgetn finds not enough chars in the get area

int streambuf::do_sgetn(char* s, int n)
{
    int c, i;

    i = in_avail();
    if( i > 0 )
        {
        memcpy(s, gptr_, i);
        s += i;
        gbump(i);
        }
    while( i < n  &&  (c = sbumpc()) != EOF )
        {
        *s++ = c;
        ++i;
        }
    return i;
}


