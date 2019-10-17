/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     srbfreez.cpp                                             |*/
/*|                                                              |*/
/*|     Class strstreambuf                                       |*/
/*|          void strstreambuf::freeze( int )                    |*/
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

void strstreambuf::freeze( int n )
{
    if( ssbflags & dynamic )
        {
        if( n )
            ssbflags |= frozen;
        else
            ssbflags &= ~frozen;
        }
}


