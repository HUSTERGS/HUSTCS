/*------------------------------------------------------------------------*/
/*                                                                        */
/*  COLLECT.CPP                                                           */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __COLLECT_H )
#include <Collect.h>
#endif	// __COLLECT_H

Object _FAR & Collection::findMember( Object _FAR & testObject ) const
{
    ContainerIterator& containerIterator = initIterator();
    while( containerIterator != 0 )
        {
        Object& listObject = containerIterator++;
        if( listObject == testObject )
            {
            delete &containerIterator;
            return listObject;
            }
        }
    delete &containerIterator;
    return NOOBJECT;
}

