/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     fsbctr2.cpp                                              |*/
/*|                                                              |*/
/*|     Class filebuf                                            |*/
/*|          filebuf::filebuf( int )                             |*/
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
#include "filesys.h"
#include <fstream.h>

// make a filebuf attached to an open fd -- assume fd is actually open

filebuf::filebuf(int f)
{
    xfd = f;        // assumed to be valid
    opened = 1;     // unless we can find out otherwise
    mode = 0;       // unless we can find out otherwise
    last_seek = 0;
    char* p = new char[B_size];
    if( p )
        {
        setb(p, p+B_size, 1);   // ~streambuf() will delete buffer
        setp(p+4, p+4);
        setg(p, p+4, p+4);
        }
}


