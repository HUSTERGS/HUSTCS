/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stusize.cpp                                              |*/
/*|                                                              |*/
/*|     Class ios                                                |*/
/*|          void ios::usersize( int )                           |*/
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
#include "user.h"

// allocate or resize user array -- we assume i > nwords

void ios::usersize(int i)
{
    // allocate space for new array
    ios_user_union *p = new ios_user_union[i];

    if( ! p )
        return;     // cannot enlarge array

    if( nwords )
        {  // copy old array to new one
        memcpy(p, userwords, nwords * sizeof(ios_user_union));
        delete userwords;
        }
    userwords = p;
    do  {        // set new words to zero
        p[nwords].lword = 0;
        } while( ++nwords < i );
}


