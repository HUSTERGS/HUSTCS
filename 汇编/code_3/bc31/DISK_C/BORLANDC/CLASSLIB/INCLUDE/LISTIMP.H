/*------------------------------------------------------------------------*/
/*                                                                        */
/*  LISTIMP.H                                                             */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __LISTIMP_H )
#define __LISTIMP_H

#if !defined( __DEFS_H )
#include <_defs.h>
#endif  // __DEFS_H

#if !defined( __MEMMGR_H )
#include <MemMgr.h>
#endif  // __MEMMGR_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_ListElement                               */
/*                                                                        */
/*  Node for templates BI_ListImp<T> and BI_IListImp<T>                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_ListImp;

template <class T> class _CLASSTYPE BI_ListBlockInitializer
{

protected:

    BI_ListBlockInitializer()
        {
        PRECONDITION( count != UINT_MAX );
        if( count++ == 0 )
            BI_ListElement<T>::mgr = 
                new MemBlocks( sizeof(BI_ListElement<T>), 20 );
        }

    ~BI_ListBlockInitializer()
        {
        PRECONDITION( count != 0 );
        if( --count == 0 )
            {
            delete BI_ListElement<T>::mgr;
            BI_ListElement<T>::mgr = 0;
            }
        }

    static unsigned count;

};

template <class T> unsigned BI_ListBlockInitializer<T>::count = 0;

template <class T> class _CLASSTYPE BI_ListElement
{

public:

    BI_ListElement( T t, BI_ListElement<T> _FAR *p ) :
        data(t)
        {
        next = p->next;
        p->next = this;
        }

    BI_ListElement();

    BI_ListElement<T> _FAR *next;
    T data;

    void _FAR *operator new( size_t sz );
    void operator delete( void _FAR * );

private:

    friend class BI_ListBlockInitializer<T>;

    static MemBlocks *mgr;

};

template <class T> MemBlocks *BI_ListElement<T>::mgr = 0;

inline BI_ListElement<void _FAR *>::BI_ListElement()
{
    next = 0;
    data = 0;
}

template <class T> inline BI_ListElement<T>::BI_ListElement()
{
    next = 0;
}

template <class T> void _FAR *BI_ListElement<T>::operator new( size_t sz )
{
    PRECONDITION( mgr != 0 );
    return mgr->allocate( sz );
}

template <class T> void BI_ListElement<T>::operator delete( void _FAR *b )
{
    PRECONDITION( mgr != 0 );
    mgr->free( b );
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_ListImp                                   */
/*                                                                        */
/*  Implements a list of objects of type T.  Assumes that                 */
/*  T has meaningful copy semantics and a default constructor.            */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_ListIteratorImp;

template <class T> class _CLASSTYPE BI_ListImp : 
    private BI_ListBlockInitializer<T>
{

public:

    friend class BI_ListIteratorImp<T>;

    BI_ListImp()
        {
        initList();
        }

    ~BI_ListImp()
        {
        flush();
        }

    T peekHead() const
        {
        return head.next->data;
        }

    void add( T );
    void detach( T, int = 0 );
    void flush( int del = 0 );

    int isEmpty() const
        {
        return head.next == &tail;
        }

    void forEach( void (_FAR *)(T _FAR &, void _FAR *), void _FAR * );
    T _FAR *firstThat( int (_FAR *)(const T _FAR &, void _FAR *),
                       void _FAR *
                     ) const;
    T _FAR *lastThat( int (_FAR *)(const T _FAR &, void _FAR *),
                      void _FAR *
                    ) const;

protected:

    BI_ListElement<T> head, tail;

    virtual BI_ListElement<T> _FAR *findDetach( T t )
        {
        return findPred(t);
        }

    virtual BI_ListElement<T> _FAR *findPred( T );

private:

    virtual void removeData( BI_ListElement<T> _FAR * )
        {
        }

    void initList();

};

template <class T> void BI_ListImp<T>::initList()
{
    head.next = &tail;
    tail.next = &tail;
}

template <class T> void BI_ListImp<T>::add( T toAdd )
{
    new BI_ListElement<T>( toAdd, &head );
}

template <class T> BI_ListElement<T> _FAR *BI_ListImp<T>::findPred( T t )
{
    tail.data = t;
    BI_ListElement<T> _FAR *cursor = &head;
    while( !(t == cursor->next->data) )
        cursor = cursor->next;
    return cursor;
}

template <class T> void BI_ListImp<T>::detach( T toDetach, int del )
{
    BI_ListElement<T> _FAR *pred = findDetach( toDetach );
    BI_ListElement<T> _FAR *item = pred->next;
    if( item != &tail )
        {
        pred->next = pred->next->next;
        if( del != 0 )
            removeData( item );
        delete item;
        }
}

template <class T> void BI_ListImp<T>::flush( int del )
{
    BI_ListElement<T> _FAR *current = head.next;
    while( current != &tail )
        {
        BI_ListElement<T> _FAR *temp = current;
        current = current->next;
        if( del != 0 )
            removeData( temp );
        delete temp;
        }
    initList();
}

template <class T>
void BI_ListImp<T>::forEach( void (_FAR *f)(T _FAR &, void _FAR *),
                             void _FAR *args
                           )
{
    BI_ListElement<T> _FAR *cur = head.next;
    while( cur->next != cur )
        {
        f( cur->data, args );
        cur = cur->next;
        }
}

template <class T>
T _FAR *BI_ListImp<T>::firstThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                                  void _FAR *args
                                ) const
{
    BI_ListElement<T> _FAR *cur = head.next;
    while( cur->next != cur )
        if( cond( cur->data, args ) != 0 )
            return &(cur->data);
        else
            cur = cur->next;
    return 0;
}

template <class T>
T _FAR *BI_ListImp<T>::lastThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                                 void _FAR *args
                               ) const
{
    T _FAR *res = 0;
    BI_ListElement<T> _FAR *cur = head.next;
    while( cur->next != cur )
        {
        if( cond( cur->data, args ) != 0 )
            res = &(cur->data);
        cur = cur->next;
        }
    return res;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_SListImp                                  */
/*                                                                        */
/*  Implements a sorted list of objects of type T.  Assumes that          */
/*  T has meaningful copy semantics, a meaningful < operator, and a       */
/*  default constructor.                                                  */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_SListImp : public BI_ListImp<T>
{

public:

    void add( T );

protected:

    virtual BI_ListElement<T> _FAR *findDetach( T t );
    virtual BI_ListElement<T> _FAR *findPred( T );

};

template <class T> void BI_SListImp<T>::add( T t )
{
    new BI_ListElement<T>( t, findPred(t) );
}

template <class T> BI_ListElement<T> _FAR *BI_SListImp<T>::findDetach( T t )
{
    BI_ListElement<T> _FAR *res = findPred(t);
    if( res->next->data == t )
        return res;
    else
        return &tail;
}

template <class T> BI_ListElement<T> _FAR *BI_SListImp<T>::findPred( T t )
{
    tail.data = t;
    BI_ListElement<T> _FAR *cursor = &head;
    while( cursor->next->data < t )
        cursor = cursor->next;
    return cursor;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_ListIteratorImp                           */
/*                                                                        */
/*  Implements a list iterator.  This iterator works with any direct      */
/*  list.  For indirect lists, see BI_IListIteratorImp.                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_ListIteratorImp
{

public:

    BI_ListIteratorImp( const BI_ListImp<T> _FAR &l )
        {
        list = &l;
        cur = list->head.next;
        }

    operator int()
        {
        return cur != &(list->tail);
        }

    T current()
        {
        return cur->data;
        }

    T operator ++ ( int )
        {
        BI_ListElement<T> _FAR *temp = cur;
        cur = cur->next;
        return temp->data;
        }

    T operator ++ ()
        {
        cur = cur->next;
        return cur->data;
        }

    void restart()
        {
        cur = list->head.next;
        }

private:

    const BI_ListImp<T> _FAR *list;
    BI_ListElement<T> _FAR *cur;

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T, class Vect> class BI_InternalIListImp              */
/*                                                                        */
/*  Implements a list of pointers to objects of type T.                   */
/*  This is implemented through the form of BI_ListImp specified by List. */
/*  Since pointers always have meaningful copy semantics, this class      */
/*  can handle any type of object.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T, class List> class _CLASSTYPE BI_InternalIListImp :
    public List
{
public:

    T _FAR *peekHead() const
        {
        return (T _FAR *)List::peekHead();
        }

    void add( T _FAR *t )
        {
        List::add( t );
        }

    void detach( T _FAR *t, int del = 0 )
        {
        List::detach( t, del );
        }

    void forEach( void (_FAR *)(T _FAR &, void _FAR *), void _FAR * );
    T _FAR *firstThat( int (_FAR *)(const T _FAR &, void _FAR *),
                       void _FAR *
                     ) const;
    T _FAR *lastThat( int (_FAR *)(const T _FAR &, void _FAR *),
                      void _FAR *
                    ) const;

protected:

    virtual BI_ListElement<void _FAR *> _FAR *findPred( void _FAR * ) = 0;

private:

    virtual void removeData( BI_ListElement<void _FAR *> _FAR *block )
        {
        delete (T _FAR *)(block->data);
        }
};

template <class T, class List>
void BI_InternalIListImp<T, List>::forEach( void (_FAR *f)(T _FAR &, void _FAR *),
                                            void _FAR *args
                                          )
{
    BI_ListElement<void _FAR *> _FAR *cur = head.next;
    while( cur->next != cur )
        {
        f( *(T _FAR *)cur->data, args );
        cur = cur->next;
        }
}

template <class T, class List>
T _FAR *BI_InternalIListImp<T, List>::firstThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                                            void _FAR *args
                                          ) const
{
    BI_ListElement<void _FAR *> _FAR *cur = head.next;
    while( cur->next != cur )
        if( cond( *(T _FAR *)(cur->data), args ) != 0 )
            return (T _FAR *)cur->data;
        else
            cur = cur->next;
    return 0;
}

template <class T, class List>
T _FAR *BI_InternalIListImp<T, List>::lastThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                                           void _FAR *args
                                         ) const
{
    T _FAR *res = 0;
    BI_ListElement<void _FAR *> _FAR *cur = head.next;
    while( cur->next != cur )
        {
        if( cond( *(T _FAR *)(cur->data), args ) != 0 )
            res = (T _FAR *)(cur->data);
        cur = cur->next;
        }
    return res;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IListImp                                  */
/*                                                                        */
/*  Implements a list of pointers to objects of type T.                   */
/*  This is implemented through the template BI_InternalIListImp.  Since  */
/*  pointers always have meaningful copy semantics, this class            */
/*  can handle any type of object.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_IListImp :
    public BI_InternalIListImp<T, BI_ListImp<void _FAR *> >
{

protected:

    virtual BI_ListElement<void _FAR *> _FAR *findPred( void _FAR * );

};

template <class T>
BI_ListElement<void _FAR *> _FAR *BI_IListImp<T>::findPred( void _FAR *t )
{
    tail.data = t;
    BI_ListElement<void _FAR *> _FAR *cursor = &head;
    while( !(*(T _FAR *)t == *(T _FAR *)(cursor->next->data)) )
        cursor = cursor->next;
    return cursor;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_ISListImp                                 */
/*                                                                        */
/*  Implements a sorted list of pointers to objects of type T.            */
/*  This is implemented through the template BI_InternalIListImp.  Since  */
/*  pointers always have meaningful copy semantics, this class            */
/*  can handle any type of object.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_ISListImp :
    public BI_InternalIListImp<T, BI_SListImp<void _FAR *> >
{

protected:

    virtual BI_ListElement<void _FAR *> _FAR *findDetach( void _FAR * );
    virtual BI_ListElement<void _FAR *> _FAR *findPred( void _FAR * );

};

template <class T>
BI_ListElement<void _FAR *> _FAR *BI_ISListImp<T>::findDetach( void _FAR *t )
{
    BI_ListElement<void _FAR *> _FAR *res = findPred(t);
    if( *(T _FAR *)(res->next->data) == *(T _FAR *)t )
        return res;
    else
        return &tail;
}

template <class T>
BI_ListElement<void _FAR *> _FAR *BI_ISListImp<T>::findPred( void _FAR *t )
{
    tail.data = t;
    BI_ListElement<void _FAR *> _FAR *cursor = &head;
    while( *(T _FAR *)(cursor->next->data) < *(T _FAR *)t )
        cursor = cursor->next;
    return cursor;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IListIteratorImp                          */
/*                                                                        */
/*  Implements a list iterator.  This iterator works with any indirect    */
/*  list.  For direct lists, see BI_ListIteratorImp.                      */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T>
class _CLASSTYPE BI_IListIteratorImp : public BI_ListIteratorImp<void _FAR *>
{

public:

   BI_IListIteratorImp( const BI_ListImp<void _FAR *> _FAR &l ) :
        BI_ListIteratorImp<void _FAR *>(l) {}

   T _FAR *current()
        {
        return (T _FAR *)BI_ListIteratorImp<void _FAR *>::current();
        }

   T _FAR *operator ++ (int)
        {
        return (T _FAR *)BI_ListIteratorImp<void _FAR *>::operator ++ (1);
        }

   T _FAR *operator ++ ()
        {
        return (T _FAR *)BI_ListIteratorImp<void _FAR *>::operator ++ ();
        }


};

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __LISTIMP_H

