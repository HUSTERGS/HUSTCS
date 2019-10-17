/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stdtr.cpp                                                |*/
/*|                                                              |*/
/*|     Class ios                                                |*/
/*|          ios::~ios()                                         |*/
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

ios::~ios()
{
    if( userwords )
        delete (void *) userwords;
}

// static members of ios

const long ios::basefield = ios::dec | ios::oct | ios::hex;
const long ios::adjustfield = ios::left | ios::right | ios::internal;
const long ios::floatfield = ios::scientific | ios::fixed;
long ios::nextbit = 16;
int ios::usercount = 0;
void _Cdecl (*ios::stdioflush)();

