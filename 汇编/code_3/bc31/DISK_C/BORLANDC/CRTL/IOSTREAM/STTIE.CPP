/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     sttie.cpp                                                |*/
/*|                                                              |*/
/*|     Class ios                                                |*/
/*|          ostream *ios::tie( ostream * )                      |*/
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

ostream* ios::tie(ostream* s)
{
    ostream *x = x_tie;
    // documentation doesn't state whether to flush old tied stream
    if( x )
        x->flush();
    x_tie = s;
    if( s )
        {
        ispecial |= tied;
        ospecial |= tied;
        }
    else
        {
        ispecial &= ~tied;
        ospecial &= ~tied;
        }
    return x;
}


