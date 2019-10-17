/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     fsbdtr.cpp                                               |*/
/*|                                                              |*/
/*|     Class filebuf                                            |*/
/*|          filebuf::~filebuf()                                 |*/
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

// We assume that mode==0 means that we attached to an already-open file,
// and should not now close it.  We do flush it in any case.

filebuf::~filebuf()
{
    if( mode )
        close();
    else
        overflow(EOF);
}

const int filebuf::openprot = P_default;
