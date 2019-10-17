/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     srbdtr.cpp                                               |*/
/*|                                                              |*/
/*|     Class strstreambuf                                       |*/
/*|          strstreambuf::~strstreambuf()                       |*/
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
#include <strstrea.h>


#define expandable ((ssbflags&(dynamic|frozen))==dynamic)

strstreambuf::~strstreambuf()
{
    if( expandable )
        {
        if( freef )
            (*freef)((void*)base());
        else
            delete base();
        }
}


