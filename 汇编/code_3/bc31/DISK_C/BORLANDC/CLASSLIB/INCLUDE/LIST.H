/*------------------------------------------------------------------------*/
/*                                                                        */
/*  LIST.H                                                                */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __LIST_H )
#define __LIST_H

#if !defined( __MEMMGR_H )
#include <MemMgr.h>
#endif  // __MEMMGR_H

#if !defined( __COLLECT_H )
#include <Collect.h>
#endif  // __COLLECT_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

_CLASSDEF(List)
_CLASSDEF(ListIterator)

class _CLASSTYPE ListBlockInitializer
{

protected:

    ListBlockInitializer();
    ~ListBlockInitializer();

    static unsigned count;

};

class _CLASSTYPE List : public Collection, private ListBlockInitializer
{

public:

    List() :
        headEntry( 0, &tailEntry ),
        tailEntry( 0, &tailEntry ),
        head(&headEntry),
        tail(&tailEntry),
        itemsInContainer(0)
        {
        }

    virtual ~List()
        {
        flush();
        }
    
    Object _FAR & peekHead() const
        {
        return ptrToRef(head->next->data);
        }

    void add( Object _FAR & );
    virtual void detach( Object _FAR &, DeleteType = NoDelete );
    virtual void flush( DeleteType = DefDelete );

    virtual int isEmpty() const
        {
        return itemsInContainer == 0;
        }

    virtual countType getItemsInContainer() const
        {
        return itemsInContainer;
        }

    virtual ContainerIterator _FAR & initIterator() const;

    virtual classType isA() const
        {
        return listClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "List";
        }

private:

    class _CLASSTYPE ListElement
    {

    public:

        ListElement( Object _FAR *o, ListElement _FAR *n = 0 )
            {
            data = o; next = n;
            }

    private:

        ListElement _FAR *next;
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

        friend class List;
        friend class ListIterator;
        friend class ListBlockInitializer;

    };

    ListElement _FAR *head;
    ListElement _FAR *tail;

    ListElement headEntry, tailEntry;

    unsigned itemsInContainer;

    ListElement _FAR *findPred( const Object _FAR & o );

    friend class ListIterator;
    friend class ListBlockInitializer;

};

inline ListBlockInitializer::ListBlockInitializer()
{
    PRECONDITION( count != UINT_MAX );
    if( count++ == 0 )
        List::ListElement::mgr = 
            new MemBlocks( sizeof(List::ListElement), 20 );
}

inline ListBlockInitializer::~ListBlockInitializer()
{
    PRECONDITION( count != 0 );
    if( --count == 0 )
        {
        delete List::ListElement::mgr;
        List::ListElement::mgr = 0;
        }
}

class _CLASSTYPE ListIterator : public ContainerIterator
{

public:

    ListIterator( const List _FAR & );
    virtual ~ListIterator();

    virtual operator int();
    virtual Object _FAR & current();
    virtual Object _FAR & operator ++ ( int );
    virtual Object _FAR & operator ++ ();
    virtual void restart();

private:

    List::ListElement _FAR *currentElement;
    List::ListElement _FAR *startingElement;
};

inline ListIterator::ListIterator( const List _FAR & toIterate )
{
    startingElement = currentElement = toIterate.head->next;
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __LIST_H

