/*------------------------------------------------------------------------*/
/*                                                                        */
/*  BDICT.CPP                                                             */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( TEMPLATES )
#define TEMPLATES
#endif

#if !defined( __ASSOC_H )
#include <Assoc.h>
#endif  // __ASSOC_H

#if !defined( __DICT_H )
#include <Dict.h>
#endif  // __DICT_H

#if !defined( __IOSTREAM_H )
#include <iostream.h>
#endif  // __IOSTREAM_H

#if !defined( __CLSTYPES_H )
#include <ClsTypes.h>
#endif  // __CLSTYPES_H

void Dictionary::add( Object& objectToAdd )
{
    if( !objectToAdd.isAssociation() )
        ClassLib_error( __ENOTASSOC );
    else
        Set::add( objectToAdd );
}

Association& Dictionary::lookup( const Object& toLookUp ) const
{
    Association toFind( (Object&)toLookUp, NOOBJECT );
    toFind.ownsElements(0);

    Association& found = (Association&)findMember( toFind );
    return found;
}

