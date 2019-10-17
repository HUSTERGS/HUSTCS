/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stbsetg.cpp                                              |*/
/*|                                                              |*/
/*|     Class streambuf                                          |*/
/*|          void streambuf::setg( char *, char *, char * )      |*/
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

void streambuf::setg(char* eb, char* g, char* eg)
{
    eback_ = (g && eb) ? eb : g;
    gptr_ = g;
    egptr_ = (g && eg && (eg >= g)) ? eg : g;
 }


