/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     fsbclose.cpp                                             |*/
/*|                                                              |*/
/*|     Class filebuf                                            |*/
/*|          filebuf* filebuf::close()                           |*/
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

// flush and close file

filebuf* filebuf::close()
{
    if( xfd == EOF )
        opened = 0;     // consistency check

    if( ! opened )
        return 0;       // nothing to do

    int ores = 0;       // result of overflow()
    if( out_waiting() )
        ores = (overflow(EOF) == EOF) ? 1 : 0;
    int cres = ::close(xfd);    // result of system ::close()

    xfd = EOF;
    opened = 0;
    return (ores | cres) ? 0 : this;
}


