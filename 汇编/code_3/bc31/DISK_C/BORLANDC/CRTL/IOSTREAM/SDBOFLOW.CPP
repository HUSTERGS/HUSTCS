/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     sdboflow.cpp                                             |*/
/*|                                                              |*/
/*|     Class stdiobuf                                           |*/
/*|          int stdiobuf::overflow( int )                       |*/
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
#include <filesys.h>
#include <stdiostr.h>

int stdiobuf::overflow(int c)
{
    if ( ferror(sio) )
        return EOF;

    char *p;
    int count = out_waiting();
    if( count > 0 )
        {
        p = pbase();
        do  {
            putc(*p, sio);
            ++p;
            } while( --count );
        }
    if( c != EOF )
        putc(c, sio);

    char *b = base();
    setp(b+4, b+blen());
    setg(b, b+4, b+4);

    return ferror(sio) ? EOF : 1;
}


