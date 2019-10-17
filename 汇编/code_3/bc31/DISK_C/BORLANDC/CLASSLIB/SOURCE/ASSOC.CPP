/*------------------------------------------------------------------------*/
/*                                                                        */
/*  ASSOC.CPP                                                             */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( CHECKS_H )
#include <Checks.h>
#endif  // CHECKS_H

#if !defined( __ASSOC_H )
#include <Assoc.h>
#endif  // __ASSOC_H

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

Association::~Association()
{
    if( !ownsElements() )
        return;
    if( &aKey != ZERO )
        delete &aKey;
    if( &aValue != ZERO )
        delete &aValue;
}

void Association::printOn( ostream& outputStream ) const
{
    outputStream << " " << nameOf() << " { ";
    aKey.printOn( outputStream );
    outputStream << ", ";
    aValue.printOn( outputStream );
    outputStream << " }\n";
}

int Association::isEqual( const Object& toObject ) const
{
    return aKey == ( (Association&)toObject ).key();
}

