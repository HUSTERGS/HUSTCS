/*------------------------------------------------------------------------*/
/*                                                                        */
/*  ABSTARRY.CPP                                                          */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

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

AbstractArray::AbstractArray( int anUpper, int aLower, sizeType aDelta )
{
    PRECONDITION( anUpper >= aLower );
    lastElementIndex = aLower - 1;
    lowerbound = aLower;
    upperbound = anUpper;
    delta = aDelta;

    theArray = new Object *[ arraySize() ];
    if( theArray == 0 )
        ClassLib_error(__ENOMEM);

    for( int i = 0; i < arraySize(); i++ )
        {
        theArray[ i ] = ZERO;
        }
}

AbstractArray::~AbstractArray()
{
    PRECONDITION( theArray != 0 );
    if( ownsElements() )
        for( int i = 0; i < arraySize(); i++ )
            if( theArray[ i ] != ZERO )
                delete theArray[ i ];
    delete [] theArray;
}

void AbstractArray::detach( Object& toDetach, DeleteType dt )
{
    detach( find( toDetach ), dt );
}

void AbstractArray::detach( int atIndex, DeleteType dt )
{
    PRECONDITION( atIndex >= lowerbound &&
                  atIndex <= upperbound && theArray != 0
                );

    if( ptrAt(atIndex) != ZERO )
        {
        if( delObj(dt) )
            delete ptrAt(atIndex);
        itemsInContainer--;
        }
    removeEntry(atIndex);
    if( atIndex <= lastElementIndex )
        lastElementIndex--;
    CHECK( itemsInContainer != UINT_MAX );
}

void AbstractArray::flush( DeleteType dt )
{
    if( delObj(dt) )
        for( unsigned i = 0; i <= zeroBase(upperbound); i++ )
            if( theArray[i] != ZERO )
                delete theArray[i];

    for( unsigned i = 0; i <= zeroBase(upperbound); i++ )
        theArray[i] = ZERO;

    itemsInContainer = 0;
    lastElementIndex = lowerbound-1;
}

inline unsigned nextDelta( unsigned sz, unsigned delta )
{
    return (sz%delta) ? ((sz+delta)/delta)*delta : sz;
}

void AbstractArray::reallocate( sizeType newSize )
{
    PRECONDITION( newSize > arraySize() );
    if( delta == 0 )
        ClassLib_error(__EEXPANDFS);

    sizeType adjustedSize = arraySize() +
                            nextDelta( newSize - arraySize(), delta );
    Object **newArray = new Object *[ adjustedSize ];
    if( newArray == 0 )
        ClassLib_error(__ENOMEM);

    memcpy( newArray, theArray, arraySize() * sizeof( theArray[0] ) );

    for( int i = arraySize(); i < adjustedSize; i++ )
        newArray[i] = ZERO;

    delete [] theArray;
    theArray = newArray;
    upperbound = adjustedSize + lowerbound - 1;
}

void AbstractArray::setData( int loc, Object *data )
{
    PRECONDITION( loc >= lowerbound && loc <= upperbound );
    theArray[ zeroBase(loc) ] = data;
}

void AbstractArray::insertEntry( int loc )
{
    PRECONDITION( loc >= lowerbound && loc <= upperbound );
    memmove( theArray + zeroBase(loc) + 1,
             theArray + zeroBase(loc),
             (upperbound - loc)*sizeof( theArray[0] )
           );
}

void AbstractArray::removeEntry( int loc )
{
    if( loc >= lastElementIndex )
        theArray[zeroBase(loc)] = ZERO;
    else
        squeezeEntry( zeroBase(loc) );
}

void AbstractArray::squeezeEntry( int squeezePoint )
{
    PRECONDITION( squeezePoint >= 0 &&
                  squeezePoint <= zeroBase(lastElementIndex)
                );

    memmove( theArray + squeezePoint,
             theArray + squeezePoint + 1,
             (zeroBase(lastElementIndex)-squeezePoint)*sizeof( theArray[0] )
           );
        theArray[zeroBase(lastElementIndex)] = ZERO;
}

int AbstractArray::find( const Object& o )
{
    if( o == NOOBJECT )
        return INT_MIN;

    for( int index = 0; index < arraySize(); index++ )
        if( *(theArray[index]) == o )
            return boundBase(index);
    return INT_MIN;
}

inline int isZero( const Object *o )
{
    return o == &NOOBJECT;
}

int AbstractArray::isEqual( const Object& testObject ) const
{
    PRECONDITION( isA() == testObject.isA() );
    AbstractArray& test = (AbstractArray&)testObject;
    if( lowerbound != test.lowerbound || upperbound != test.upperbound )
        return 0;

    for( int i = 0; i < arraySize(); i++ )
        {
        if( isZero(theArray[i]) != isZero(test.theArray[i]) )
            return 0;
        if( *(theArray[i]) != *(test.theArray[i]) )
            return 0;
        }
    return 1;
}

ContainerIterator& AbstractArray::initIterator() const
{
    return *( (ContainerIterator *)new ArrayIterator( *this ) );
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

ArrayIterator::ArrayIterator( const AbstractArray& toIterate ) :
    beingIterated( toIterate ),
    currentIndex( toIterate.lowerbound )
{
    restart();
}

ArrayIterator::~ArrayIterator()
{
}

ArrayIterator::operator int()
{
    return currentIndex <= beingIterated.upperbound;
}

Object& ArrayIterator::current()
{
    if ( currentIndex <= beingIterated.upperbound )
        return beingIterated.objectAt( currentIndex );
    else
        return NOOBJECT;
}

void ArrayIterator::scan()
{
    if( currentIndex > beingIterated.upperbound )
        return;

    while( ++currentIndex <= beingIterated.upperbound &&
           beingIterated.objectAt( currentIndex ) == NOOBJECT )
        ;   // empty body
}

void ArrayIterator::restart()
{
    currentIndex = beingIterated.lowerbound;
    if( beingIterated.objectAt( currentIndex ) == NOOBJECT )
        scan();
}

Object& ArrayIterator::operator ++ ( int )
{
    Object& res = (currentIndex <= beingIterated.upperbound) ?
        beingIterated.objectAt( currentIndex ) : NOOBJECT;

    scan();

    return res;
}

Object& ArrayIterator::operator ++ ()
{
    scan();
    return (currentIndex <= beingIterated.upperbound) ?
        beingIterated.objectAt( currentIndex ) : NOOBJECT;
}
