/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stbdsptn.cpp                                             |*/
/*|                                                              |*/
/*|     Class streambuf                                          |*/
/*|          int streambuf::do_sputn( const char *, int )        |*/
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

// called by sputn when more chars are needed than are in the buffer

int streambuf::do_sputn(const char* s, int n)
{
    int i;

    i = (int)(epptr_ - pptr_);
    if( i > 0 )
        {
        memcpy(pptr_, s, i);
        s += i;
        pbump(i);
        }
    while( i < n  &&  sputc(*s++) != EOF )
        ++i;
    return i;
}


