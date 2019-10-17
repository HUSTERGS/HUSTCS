/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     fsbctr1.cpp                                              |*/
/*|                                                              |*/
/*|     Class filebuf                                            |*/
/*|          filebuf::filebuf()                                  |*/
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

// make a closed filebuf

filebuf::filebuf()
{
    xfd = EOF;
    mode = 0;
    opened = 0;
    last_seek = 0;
    char* p = new char[B_size];
    if( p )
        {
        setb(p, p+B_size, 1);   // ~streambuf() will delete buffer
        setp(p+4, p+4);
        setg(p, p+4, p+4);
        }
}


