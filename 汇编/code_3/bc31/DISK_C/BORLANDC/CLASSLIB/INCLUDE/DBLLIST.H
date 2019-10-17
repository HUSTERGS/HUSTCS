/*------------------------------------------------------------------------*/
/*                                                                        */
/*  DBLLIST.H                                                             */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __DBLLIST_H )
#define __DBLLIST_H

#if !defined( __CLSTYPES_H )
#include <ClsTypes.h>
#endif  // __CLSTYPES_H

#if !defined( __OBJECT_H )
#include <Object.h>
#endif  // __OBJECT_H

#if !defined( __COLLECT_H )
#include <Collect.h>
#endif  // __COLLECT_H

#if !defined( __MEMMGR_H )
#include <MemMgr.h>
#endif  // __MEMMGR_H

#if !defined( __SHDDEL_H )
#include <ShdDel.h>
#endif  // __SHDDEL_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

_CLASSDEF(DoubleList)
_CLASSDEF(DoubleListIterator)

class _CLASSTYPE DoubleListBlockInitializer
{

protected:

    DoubleListBlockInitializer();
    ~DoubleListBlockInitializer();

    static unsigned count;

};

class _CLASSTYPE DoubleList : 
    public Collection, 
    private DoubleListBlockInitializer
{

public:

    DoubleList() :
        headEntry( 0, &headEntry, &tailEntry ),
        tailEntry( 0, &headEntry, &tailEntry ),
        head( &headEntry ),
        tail( &tailEntry ),
        itemsInContainer(0)
        {
        }

    ~DoubleList()
        {
        flush();
        }

    Object _FAR & peekAtHead() const
        {
        return ptrToRef(head->next->data);
        }

    Object _FAR & peekAtTail() const
        {
        return ptrToRef(tail->prev->data);
        }

    virtual void add( Object _FAR & toAdd )
        {
        addAtHead( toAdd );
        }

    virtual void detach( Object _FAR &, DeleteType = NoDelete );
    virtual void flush( DeleteType = DefDelete );

    void addAtHead( Object _FAR & );
    void addAtTail( Object _FAR & );
    void destroyFromHead( Object _FAR & );
    void destroyFromTail( Object _FAR & );
    void detachFromHead( Object _FAR &, DeleteType = NoDelete );
    void detachFromTail( Object _FAR &, DeleteType = NoDelete );

    int isEmpty() const
        {
        return itemsInContainer == 0;
        }

    countType getItemsInContainer() const
        {
        return itemsInContainer;
        }

    virtual ContainerIterator _FAR & initIterator() const;
    ContainerIterator _FAR & initReverseIterator() const;

    virtual classType isA() const
        {
        return doubleListClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "DoubleList";
        }

private:

    class _CLASSTYPE ListElement
    {

    public:

        ListElement( Object _FAR *o,
                     ListElement _FAR *p = 0,
                     ListElement _FAR *n = 0
                   )
            {
            data = o;
            prev = p;
            next = n;
            }

    private:

        ListElement _FAR *next;
        ListElement _FAR *prev;
        Object _FAR *data;

        void _FAR *operator new( size_t sz )
            {
            PRECONDITION( mgr != 0 );
            return mgr->allocate( sz );
            }
        void operator delete( void _FAR *b )
            {
            PRECONDITION( mgr != 0 );
            mgr->free( b );
            }

        static MemBlocks _FAR *mgr;

        friend class DoubleList;
        friend class DoubleListIterator;
        friend class DoubleListBlockInitializer;

    };

    ListElement _FAR *head;
    ListElement _FAR *tail;

    ListElement headEntry, tailEntry;

    unsigned itemsInContainer;

    friend class DoubleListIterator;
    friend class DoubleListBlockInitializer;

};

inline DoubleListBlockInitializer::DoubleListBlockInitializer()
{
    PRECONDITION( count != UINT_MAX );
    if( count++ == 0 )
        DoubleList::ListElement::mgr = 
            new MemBlocks( sizeof(DoubleList::ListElement), 20 );
}

inline DoubleListBlockInitializer::~DoubleListBlockInitializer()
{
    PRECONDITION( count != 0 );
    if( --count == 0 )
        {
        delete DoubleList::ListElement::mgr;
        DoubleList::ListElement::mgr = 0;
        }
}

inline void DoubleList::destroyFromHead( Object _FAR & toDestroy )
{
    detachFromHead( toDestroy, DefDelete );
}

inline void DoubleList::destroyFromTail( Object _FAR & toDestroy )
{
    detachFromTail( toDestroy, DefDelete );
}

class _CLASSTYPE DoubleListIterator : public ContainerIterator
{

public:

    DoubleListIterator( const DoubleList _FAR &, int = 1 );
    virtual ~DoubleListIterator();

    virtual operator int();
    virtual Object _FAR & current();
    virtual Object _FAR & operator ++ ( int );
    virtual Object _FAR & operator ++ ();
    Object _FAR & operator -- ( int );
    Object _FAR & operator -- ();

    virtual void restart();

private:

    DoubleList::ListElement _FAR *currentElement;
    DoubleList::ListElement _FAR *startingElement;

};

inline
DoubleListIterator::DoubleListIterator( const DoubleList _FAR & toIterate,
                                        int atHead
                                      )
{
    if ( atHead == 1 )
        {
        startingElement = currentElement = toIterate.head->next;
        }
    else
        {
        startingElement = currentElement = toIterate.tail->prev;
        }
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __DBLLIST_H

