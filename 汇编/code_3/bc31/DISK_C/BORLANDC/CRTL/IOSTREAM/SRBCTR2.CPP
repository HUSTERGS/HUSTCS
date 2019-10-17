/*[]-----------------------------------------------------------------[]*/
/*|                                                                   |*/
/*|     srbctr2.cpp                                                   |*/
/*|                                                                   |*/
/*|     Class strstreambuf                                            |*/
/*|     strstreambuf::strstreambuf( void *(*)(long), void (*)(void*) )|*/
/*|                                                                   |*/
/*[]-----------------------------------------------------------------[]*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <ioconfig.h>
#include <strstrea.h>

strstreambuf::strstreambuf(void* (*a)(long), void (*f)(void*))
{
    allocf = a;
    freef = f;
    next_alloc = 0;
    ssbflags = dynamic;
}


