/*------------------------------------------------------------------------*/
/*                                                                        */
/*  BABSTARY.CPP                                                          */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( TEMPLATES )
#define TEMPLATES
#endif

#if !defined( CHECKS_H )
#include <Checks.h>
#endif  // CHECKS_H

#if !defined( __ABSTARRY_H )
#include <AbstArry.h>
#endif  // __ABSTARRY_H

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#if !defined( __MEM_H )
#include <mem.h>
#endif  // __MEM_H

inline int isZero( const Object& o )
{
    return o == NOOBJECT;
}

int AbstractArray::isEqual( const Object& obj ) const
{
    PRECONDITION( isA() == obj.isA() );
    AbstractArray& test = (AbstractArray&)obj;
    if( lowerBound() != test.lowerBound() ||
        upperBound() != test.upperBound()
      )
        return 0;

    ContainerIterator& iter1 = initIterator();
    ContainerIterator& iter2 = test.initIterator();
    while( iter1 && iter2 )
        if( iter1.current() != iter2.current() )
            {
            delete &iter1;
            delete &iter2;
            return 0;
            }
        else
            {
            iter1++;
            iter2++;
            }

    delete &iter1;
    delete &iter2;
    return 1;
}

void AbstractArray::printContentsOn( ostream& outputStream ) const
{
    ContainerIterator& printIterator = initIterator();
    printHeader( outputStream );
    while( printIterator != 0 )
        {
        Object& arrayObject = printIterator++;
        if( arrayObject != NOOBJECT )
            {
            arrayObject.printOn( outputStream );
            if( printIterator != 0 )
                printSeparator( outputStream );
            else
                break;
            }
        }
    printTrailer( outputStream );
    delete &printIterator;
}

