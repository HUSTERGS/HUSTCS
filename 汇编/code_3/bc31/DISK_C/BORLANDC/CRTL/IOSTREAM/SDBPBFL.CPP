/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     sdbpbfl.cpp                                              |*/
/*|                                                              |*/
/*|     Class stdiobuf                                           |*/
/*|          int stdiobuf::pbackfail( int )                      |*/
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

int stdiobuf::pbackfail(int c)
{
    return ungetc(c, sio);
}


