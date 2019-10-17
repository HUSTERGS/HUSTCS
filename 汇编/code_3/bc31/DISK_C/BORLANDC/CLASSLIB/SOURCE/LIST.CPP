/*------------------------------------------------------------------------*/
/*                                                                        */
/*  LIST.CPP                                                              */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __RESOURCE_H )
#include <Resource.h>
#endif  // __RESOURCE_H

#if !defined( __LIST_H )
#include <List.h>
#endif  // __LIST_H

unsigned ListBlockInitializer::count = 0;

MemBlocks *List::ListElement::mgr = 0;

void List::add( Object& toAdd )
{
    ListElement *newElement = new ListElement( &toAdd, head->next );
    CHECK( newElement != 0 );
    head->next = newElement;
    itemsInContainer++;
}

List::ListElement *List::findPred( const Object& o )
{
    tail->data = (Object *)&o;
    ListElement *cursor = head;
    while( o != *(cursor->next->data) )
        cursor = cursor->next;
    tail->data = 0;
    return cursor;
}

void List::detach( Object& toDetach, DeleteType dt )
{
    ListElement *pred = findPred( toDetach );
    ListElement *item = pred->next;
    if( delObj(dt) && pred->next != tail )
        delete item->data;
    pred->next = pred->next->next;
    if( item != tail )
        {
        itemsInContainer--;
        delete item;
        }
}

void List::flush( DeleteType dt )
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
    itemsInContainer = 0;
}

ContainerIterator& List::initIterator() const
{
    return *( (ContainerIterator *)new ListIterator( *this ) );
}

ListIterator::~ListIterator()
{
}

ListIterator::operator int()
{
    return currentElement->next != currentElement;
}

Object& ListIterator::current()
{
    return currentElement->data == 0 ? NOOBJECT : *(currentElement->data);
}

Object& ListIterator::operator ++ ( int )
{
    Object *data = currentElement->data;
    currentElement = currentElement->next;
    return data == 0 ? NOOBJECT : *data;
}

Object& ListIterator::operator ++ ()
{
    currentElement = currentElement->next;
    return currentElement->data == 0 ? NOOBJECT : *(currentElement->data);
}

void ListIterator::restart()
{
    currentElement = startingElement;
}


