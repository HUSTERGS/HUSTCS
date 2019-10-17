/*[]----------------------------------------------------------------[]*/
/*|                                                                  |*/
/*|     srbctr4.cpp                                                  |*/
/*|                                                                  |*/
/*|     Class strstreambuf                                           |*/
/*|     strstreambuf::strstreambuf( signed char*, int, signed char* )|*/
/*|                                                                  |*/
/*[]----------------------------------------------------------------[]*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <ioconfig.h>
#include <strstrea.h>

strstreambuf::strstreambuf( signed char* ptr, int n, signed char* pstart )
{
    init(ptr, n, pstart);
}


