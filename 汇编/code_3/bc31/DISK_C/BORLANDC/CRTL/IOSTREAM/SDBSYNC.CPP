/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     sdbsync.cpp                                              |*/
/*|                                                              |*/
/*|     Class stdiobuf                                           |*/
/*|          int stdiobuf::sync()                                |*/
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

int stdiobuf::sync()
{
    int count;
    if( out_waiting() )
        {
        if( overflow(EOF) == EOF )
            return EOF;
        }
    else if( (count = in_avail()) > 0 )
        {
        char *p = egptr();
        do  {
            --p;
            ungetc(*p, sio);
            --count;
            } while( count );
        p = egptr();
        setp(p, p);
        setg(eback(), p, p);
        }
    /*
     * We assume that fseek() does any needed synchronization.
     */
    fseek(sio, 0L, SEEK_CUR);   // should flush stdio buffer
    return ferror(sio) ? EOF : 0;
}


