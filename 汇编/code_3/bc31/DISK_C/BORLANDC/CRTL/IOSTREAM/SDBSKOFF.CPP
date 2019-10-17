/*[]-------------------------------------------------------------------[]*/
/*|                                                                     |*/
/*|     sdbskoff.cpp                                                    |*/
/*|                                                                     |*/
/*|     Class stdiobuf                                                  |*/
/*|       streampos stdiobuf::seekoff( streamoff, ios::seek_dir, int )  |*/
/*|                                                                     |*/
/*[]-------------------------------------------------------------------[]*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <ioconfig.h>
#include <filesys.h>
#include <stdiostr.h>

streampos stdiobuf::seekoff(streamoff off, ios::seek_dir dir, int /*mode ignored*/)
{
    if( out_waiting()  ||  in_avail() )
        {
        if( sync() == EOF )
            return EOF;
        }

    int w;
    if( dir == ios::beg )
        w = SEEK_SET;
    else if( dir == ios::end )
        w = SEEK_END;
    else
        w = SEEK_CUR;
    w = fseek(sio, off, w);
    char *b = base();
    if( ! unbuffered()  &&  b )
        {   // reset get and put areas
        setp(b+4, b+4);
        setg(b, b+4, b+4);
        }
    return w ? EOF : ftell(sio);
}
