/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stbsync.cpp                                              |*/
/*|                                                              |*/
/*|     Class streambuf                                          |*/
/*|          int streambuf::sync()                               |*/
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
#include <iostream.h>

int streambuf::sync()
{
     return (in_avail() == 0  &&  out_waiting() == 0) ? 0 : EOF;
}
