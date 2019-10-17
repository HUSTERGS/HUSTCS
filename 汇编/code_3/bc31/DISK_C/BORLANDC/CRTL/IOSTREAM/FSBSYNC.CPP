/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     fsbsync.cpp                                              |*/
/*|                                                              |*/
/*|     Class filebuf                                            |*/
/*|          int filebuf::sync()                                 |*/
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

int filebuf::sync()
{
    if (!opened)
        return EOF;

    int count = out_waiting();
    if( count )
        {
        if( ::write(xfd, pbase(), count) != count )
            return EOF;

        // reset get and put areas
        int pb = (blen() > 8) ? 4 : 1;  // putback area size
        char *b = base();
        setp(b+pb, b+blen());
        setg(b, b+pb, b+pb);
        }
    else if( in_avail() )
        {
        last_seek = ::lseek(xfd, long(-in_avail()), L_cur);
        setg(eback(), gptr(), gptr());
        setp(gptr(), gptr());
        if( last_seek == long(OS_err) )
            return EOF;
        }
    return 0;
}


