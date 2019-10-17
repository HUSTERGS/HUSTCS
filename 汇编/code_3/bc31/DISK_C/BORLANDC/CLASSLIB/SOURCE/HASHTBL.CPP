/*------------------------------------------------------------------------*/
/*                                                                        */
/*  HASHTBL.CPP                                                           */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __HASHTBL_H )
#include <HashTbl.h>
#endif  // __HASHTBL_H

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

HashTable::HashTable( sizeType aPrime ) :
    size( aPrime ),
    table( aPrime ),
    itemsInContainer(0)
{
}

void HashTable::add( Object& objectToAdd )
{
    hashValueType index = getHashValue( objectToAdd );
    if( table[ index ] == 0 )
        table[index] = new List;
    ((List *)table[ index ])->add( objectToAdd );
    itemsInContainer++;
}

void HashTable::detach( Object& objectToDetach, DeleteType dt )
{
    hashValueType index = getHashValue( objectToDetach );
    if( table[ index ] != 0 )
        {
        unsigned listSize = ((List *)table[ index ])->getItemsInContainer();
        ((List *)table[ index ])->detach( objectToDetach, delItem(dt) );
        if( ((List *)table[ index ])->getItemsInContainer() != listSize )
            itemsInContainer--;
        }
}

static void setOwner( Object& list, void *owns )
{
    ((List&)list).ownsElements( *(TShouldDelete::DeleteType *)owns );
}

void HashTable::flush( DeleteType dt )
{
    int shouldDel = delObj( dt );
    table.forEach( setOwner, &shouldDel );
    table.flush( 1 );
    itemsInContainer = 0;
}

Object& HashTable::findMember( Object& testObject ) const
{
    hashValueType index = getHashValue( testObject );
    if( index >= table.limit() || table[ index ] == 0 )
        {
        return NOOBJECT;
        }
    return ((List *)table[ index ])->findMember( testObject );
}

ContainerIterator& HashTable::initIterator() const
{
    return *( (ContainerIterator *)new HashTableIterator( *this ) );
}

HashTableIterator::HashTableIterator( const HashTable& toIterate ) :
                                beingIterated( toIterate ),
                                listIterator(0)
{
    arrayIterator = new BI_IVectorIteratorImp<Object>( toIterate.table );
    restart();
}

HashTableIterator::~HashTableIterator()
{
    delete arrayIterator;
    delete listIterator;
}

Object& HashTableIterator::operator ++ ( int )
{
    Object& res = (listIterator == 0) ? NOOBJECT : listIterator->current();
    scan();
    return res;
}

Object& HashTableIterator::operator ++ ()
{
    scan();
    return (listIterator == 0) ? NOOBJECT : listIterator->current();
}

HashTableIterator::operator int()
{
    return int(*arrayIterator);
}

Object& HashTableIterator::current()
{
    return (listIterator == 0) ? NOOBJECT : listIterator->current();
}

void HashTableIterator::restart()
{
    delete listIterator;

    arrayIterator->restart();
    while( *arrayIterator != 0 && arrayIterator->current() == 0 )
        (*arrayIterator)++;

    if( *arrayIterator != 0 )
        {
        Object *curList = arrayIterator->current();
        listIterator = &(((List *)curList)->initIterator());
        if( listIterator->current() == NOOBJECT )
            scan();
        }
    else
        listIterator = 0;
}

void HashTableIterator::scan()
{
    if( listIterator == 0 )
        return;

    (*listIterator)++;
    while( listIterator != 0 && listIterator->current() == NOOBJECT )
        {
        delete listIterator;

        (*arrayIterator)++;
        while( *arrayIterator != 0 && arrayIterator->current() == 0 )
            (*arrayIterator)++;

        if( arrayIterator->current() != 0 )
            {
            Object *cur = arrayIterator->current();
            listIterator = &(((Container *)cur)->initIterator());
            }
        else
            listIterator = 0;
        }
}
