/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     fsbattch.cpp                                             |*/
/*|                                                              |*/
/*|     Class filebuf                                            |*/
/*|          filebuf* filebuf::attach( int )                     |*/
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

// attach this filebuf to open file descriptor -- assume fd is actually open

filebuf* filebuf::attach(int f)
{
    if( opened )
        return 0;

    xfd = f;        // assumed to be valid
    opened = 1;     // unless we can find out otherwise
    mode = 0;       // unless we can find out otherwise
    char *b = base();       // buffer address
    if( ! b )
        {
        b = new char[B_size];
        if( b )
            setb(b, b+B_size, 1);   // ~streambuf() will delete buffer
        }
    int pb = b ? ((blen() > 8) ? 4 : 1) : 0;    // putback area size
    setp(b+pb, b+pb);
    setg(b, b+pb, b+pb);
    return this;
}


