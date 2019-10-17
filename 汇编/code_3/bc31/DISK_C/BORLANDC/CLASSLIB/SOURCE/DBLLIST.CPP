/*------------------------------------------------------------------------*/
/*                                                                        */
/*  DBLLIST.CPP                                                           */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __RESOURCE_H )
#include <Resource.h>
#endif  // __RESOURCE_H

#if !defined( __DBLLIST_H )
#include <DblList.h>
#endif  // __DBLLIST_H

#ifndef __IOSTREAM_H
#include <iostream.h>
#define __IOSTREAM_H
#endif

unsigned DoubleListBlockInitializer::count = 0;

MemBlocks _FAR *DoubleList::ListElement::mgr = 0;

void DoubleList::flush( DeleteType dt )
{
    ListElement *current = head->next;
    while( current != tail )
        {
        ListElement *temp = current;
        current = current->next;
        if( delObj(dt) )
            delete temp->data;
        delete temp;
        }
    head->next = tail;
    tail->prev = head;
    itemsInContainer = 0;
}

void DoubleList::addAtHead( Object& toAdd )
{
    ListElement *newElement =
        new ListElement( &toAdd, head, head->next );
    CHECK( newElement != 0 );

    head->next->prev = newElement;
    head->next = newElement;

    itemsInContainer++;
}

void DoubleList::addAtTail( Object& toAdd )
{
    ListElement *newElement =
        new ListElement( &toAdd, tail->prev, tail );
    CHECK( newElement != 0 );

    tail->prev->next = newElement;
    tail->prev = newElement;

    itemsInContainer++;
}

void DoubleList::detach( Object& toDetach, DeleteType dt )
{
    detachFromHead( toDetach, dt );
}

void DoubleList::detachFromHead( Object& toDetach, DeleteType dt )
{
    tail->data = &toDetach;
    ListElement *current = head->next;
    while( *(current->data) != toDetach )
        current = current->next;
    tail->data = 0;

    if( current->data == 0 )    // not found
        return;

    current->next->prev = current->prev;
    current->prev->next = current->next;

    if( delObj(dt) )
        delete current->data;
    delete current;

    itemsInContainer--;
}

void DoubleList::detachFromTail( Object& toDetach, DeleteType dt )
{
    head->data = &toDetach;
    ListElement *current = tail->prev;
    while( *(current->data) != toDetach )
        current = current->prev;
    head->data = 0;

    if( current->data == 0 )    // not found
        return;

    current->next->prev = current->prev;
    current->prev->next = current->next;

    if( delObj(dt) )
        delete current->data;
    delete current;

    itemsInContainer--;
}

ContainerIterator& DoubleList::initIterator() const
{
    return *( (ContainerIterator *)new DoubleListIterator( *this ) );
}

ContainerIterator& DoubleList::initReverseIterator() const
{
    return *( (ContainerIterator *)new DoubleListIterator( *this, 0 ) );
}

DoubleListIterator::operator int()
{
    return currentElement != currentElement->next &&
           currentElement != currentElement->prev;
}

Object& DoubleListIterator::current()
{
    return *(currentElement->data);
}

Object& DoubleListIterator::operator ++ ( int )
{
    if( currentElement != currentElement->next )
        {
        currentElement = currentElement->next;
        return *(currentElement->prev->data);
        }
    else
        return NOOBJECT;
}

Object& DoubleListIterator::operator ++ ()
{
    currentElement = currentElement->next;

    if( currentElement != currentElement->next )
        return *(currentElement->data);
    else
        return NOOBJECT;
}

void DoubleListIterator::restart()
{
    currentElement = startingElement;
}

Object& DoubleListIterator::operator -- ( int )
{
    if( currentElement != currentElement->prev )
        {
        currentElement = currentElement->prev;
        return *(currentElement->next->data);
        }
    else
        return NOOBJECT;
}

Object& DoubleListIterator::operator -- ()
{
    currentElement = currentElement->prev;

    if( currentElement != currentElement->prev )
        return *(currentElement->data);
    else
        return NOOBJECT;
}

DoubleListIterator::~DoubleListIterator()
{
}
