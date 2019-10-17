/*------------------------------------------------------------------------*/
/*                                                                        */
/*  SORTARRY.CPP                                                          */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __SORTARRY_H )
#include <SortArry.h>
#endif  // __SORTARRY_H

#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#if !defined( __IOSTREAM_H )
#include <iostream.h>
#endif  // __IOSTREAM_H

void SortedArray::add( Object& toAdd )
{
    if( toAdd.isSortable() )
        {
        if( lastElementIndex == upperbound )
            {
            reallocate( arraySize() + 1 );
            }
        int insertionPoint = lowerbound;
        while( insertionPoint <= lastElementIndex &&
               (Sortable&)objectAt( insertionPoint ) < (Sortable&)toAdd
             )
            insertionPoint++;

        insertEntry( insertionPoint );
        setData( insertionPoint, &toAdd );
        itemsInContainer++;
        lastElementIndex++;
        }
    else
        ClassLib_error( __ENOTSORT );
}

void SortedArray::detach( Object& toDetach, DeleteType dt )
{
    int detachPoint = find( toDetach );
    if( detachPoint != INT_MIN )
        {
        if( delObj(dt) )
            delete ptrAt( detachPoint );
        removeEntry( detachPoint );
        itemsInContainer--;
        if( detachPoint <= lastElementIndex )
            lastElementIndex--;
        }
}

