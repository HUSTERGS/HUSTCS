/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     sdbuflow.cpp                                             |*/
/*|                                                              |*/
/*|     Class stdiobuf                                           |*/
/*|          int stdiobuf::underflow()                           |*/
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

int stdiobuf::underflow()
{
    if( in_avail() )    // no action needed
        return (unsigned char) *gptr();

    int c;  // the return value

    if ( ! unbuffered()  &&  base() )
        {     // this is buffered
        // flush any output buffer
        if( out_waiting() )
            if( overflow(EOF) == EOF )
                return EOF;

        // read in a character
        c = getc(sio);

        // find buffer
        char *b = base();
        *b = c;

        // set up get and put areas
        setg(b, b+4, b+5);
        setp(b+4, b+4);
        }
    else
        {      // this is not buffered
        // read in a character
        c = getc(sio);
        if( c == EOF )
            setg(0, 0, 0);
        else
            {
            lahead[0] = c;
            setg(lahead, lahead, lahead+1);
            }
        }

    return c;
}
