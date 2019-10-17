/*------------------------------------------------------------------------*/
/*                                                                        */
/*  DEQUE.CPP                                                             */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __DEQUE_H )
#include <Deque.h>
#endif	// __DEQUE_H

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

Object& Deque::getLeft()
{
    Object& temp = list.peekAtHead();
    if( temp != NOOBJECT )
        {
        list.detachFromHead( temp );
        itemsInContainer--;
        }
    return temp;
}

Object& Deque::getRight()
{
    Object& temp = list.peekAtTail();
    if( temp != NOOBJECT )
        {
        list.detachFromTail( temp );
        itemsInContainer--;
        }
    return temp;
}

ContainerIterator& Deque::initIterator() const
{
    return *((ContainerIterator *)new DoubleListIterator(list));
}


