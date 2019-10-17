/*------------------------------------------------------------------------*/
/*                                                                        */
/*  DLISTIMP.H                                                            */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __DLISTIMP_H )
#define __DLISTIMP_H

#if !defined( __MEMMGR_H )
#include <MemMgr.h>
#endif  // __MEMMGR_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_DoubleListElement                         */
/*                                                                        */
/*  Node for templates BI_DoubleListImp<T> and BI_IDoubleListImp<T>       */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_DoubleListImp;

template <class T> class _CLASSTYPE BI_DoubleListBlockInitializer
{

protected:

    BI_DoubleListBlockInitializer()
        {
        PRECONDITION( count != UINT_MAX );
        if( count++ == 0 )
            BI_DoubleListElement<T>::mgr = 
                new MemBlocks( sizeof(BI_DoubleListElement<T>), 20 );
        }

    ~BI_DoubleListBlockInitializer()
        {
        PRECONDITION( count != 0 );
        if( --count == 0 )
            {
            delete BI_DoubleListElement<T>::mgr;
            BI_DoubleListElement<T>::mgr = 0;
            }
        }

    static unsigned count;

};

template <class T> unsigned BI_DoubleListBlockInitializer<T>::count = 0;

template <class T> class _CLASSTYPE BI_DoubleListElement
{

public:

    BI_DoubleListElement( T t, BI_DoubleListElement<T> _FAR *p ) :
        data(t)
        {
        next = p->next;
        prev = p;
        p->next = this;
        next->prev = this;
        }

    BI_DoubleListElement();

    BI_DoubleListElement<T> _FAR *next;
    BI_DoubleListElement<T> _FAR *prev;
    T data;

    void _FAR *operator new( size_t sz );
    void operator delete( void _FAR * );

private:

    friend class BI_DoubleListBlockInitializer<T>;

    static MemBlocks _FAR *mgr;

};

template <class T> MemBlocks _FAR *BI_DoubleListElement<T>::mgr = 0;

inline BI_DoubleListElement<void _FAR *>::BI_DoubleListElement()
{
    next = prev = 0;
    data = 0;
}

template <class T> inline BI_DoubleListElement<T>::BI_DoubleListElement()
{
    next = prev = 0;
}

template <class T>
void _FAR *BI_DoubleListElement<T>::operator new( size_t sz )
{
    PRECONDITION( mgr != 0 );
    return mgr->allocate( sz );
}

template <class T>
void BI_DoubleListElement<T>::operator delete( void _FAR *b )
{
    PRECONDITION( mgr != 0 );
    mgr->free( b );
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_DoubleListImp                             */
/*                                                                        */
/*  Implements a double-linked list of objects of type T.  Assumes that   */
/*  T has meaningful copy semantics and a default constructor.            */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_DoubleListIteratorImp;

template <class T> class _CLASSTYPE BI_DoubleListImp :
    private BI_DoubleListBlockInitializer<T>
{

public:

    friend class BI_DoubleListIteratorImp<T>;

    BI_DoubleListImp()
        {
        initList();
        }

    ~BI_DoubleListImp()
        {
        flush();
        }

    T peekHead() const
        {
        return head.next->data;
        }

    T peekTail() const
        {
        return tail.prev->data;
        }

    void add( T );
    void addAtTail( T );
    void detach( T, int = 0 );
    void flush( int = 0 );

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

    BI_DoubleListElement<T> head, tail;

    virtual BI_DoubleListElement<T> _FAR *findDetach( T t )
        {
        return findPred(t);
        }

    virtual BI_DoubleListElement<T> _FAR *findPred( T );

private:

    virtual void removeData( BI_DoubleListElement<T> _FAR * )
        {
        }

    void initList();

};

template <class T> void BI_DoubleListImp<T>::initList()
{
    head.next = &tail;
    head.prev = &head;
    tail.prev = &head;
    tail.next = &tail;
}

template <class T> void BI_DoubleListImp<T>::add( T toAdd )
{
    new BI_DoubleListElement<T>( toAdd, &head );
}

template <class T>
BI_DoubleListElement<T> _FAR *BI_DoubleListImp<T>::findPred( T t )
{
    tail.data = t;
    BI_DoubleListElement<T> _FAR *cursor = &head;
    while( !(t == cursor->next->data) )
        cursor = cursor->next;
    return cursor;
}

template <class T> void BI_DoubleListImp<T>::addAtTail( T toAdd )
{
    new BI_DoubleListElement<T>( toAdd, tail.prev );
}

template <class T> void BI_DoubleListImp<T>::detach( T toDetach, int del )
{
    BI_DoubleListElement<T> _FAR *pred = findDetach( toDetach );
    BI_DoubleListElement<T> _FAR *item = pred->next;
    if( item != &tail )
        {
        pred->next = pred->next->next;
        pred->next->prev = pred;
        if( del != 0 )
            removeData( item );
        delete item;
        }
}

template <class T> void BI_DoubleListImp<T>::flush( int del )
{
    BI_DoubleListElement<T> _FAR *current = head.next;
    while( current != &tail )
        {
        BI_DoubleListElement<T> _FAR *temp = current;
        current = current->next;
        if( del != 0 )
            removeData( temp );
        delete temp;
        }
    initList();
}

template <class T>
void BI_DoubleListImp<T>::forEach( void (_FAR *f)(T _FAR &, void _FAR *),
                                   void _FAR *args
                                 )
{
    BI_DoubleListElement<T> _FAR *cur = head.next;
    while( cur->next != cur )
        {
        f( cur->data, args );
        cur = cur->next;
        }
}

template <class T>
T _FAR *BI_DoubleListImp<T>::firstThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                                   void _FAR *args
                                 ) const
{
    BI_DoubleListElement<T> _FAR *cur = head.next;
    while( cur->next != cur )
        if( cond( cur->data, args ) != 0 )
            return &(cur->data);
        else
            cur = cur->next;
    return 0;
}

template <class T>
T _FAR *BI_DoubleListImp<T>::lastThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                                  void _FAR *args
                                ) const
{
    T _FAR *res = 0;
    BI_DoubleListElement<T> _FAR *cur = head.next;
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
/*  template <class T> class BI_SDoubleListImp                            */
/*                                                                        */
/*  Implements a sorted double-linked list of objects of type T.          */
/*  Assumes that T has meaningful copy semantics, a meaningful            */
/*  < operator, and a default constructor.                                */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_SDoubleListImp :
    public BI_DoubleListImp<T>
{

public:

    void add( T );

protected:

    virtual BI_DoubleListElement<T> _FAR *findDetach( T );
    virtual BI_DoubleListElement<T> _FAR *findPred( T );

};

template <class T> void BI_SDoubleListImp<T>::add( T t )
{
    new BI_DoubleListElement<T>( t, findPred(t) );
}

template <class T>
BI_DoubleListElement<T> _FAR *BI_SDoubleListImp<T>::findDetach( T t )
{
    BI_DoubleListElement<T> _FAR *res = findPred(t);
    if( res->next->data == t )
        return res;
    else
        return &tail;
}

template <class T>
BI_DoubleListElement<T> _FAR *BI_SDoubleListImp<T>::findPred( T t )
{
    tail.data = t;
    BI_DoubleListElement<T> _FAR *cursor = &head;
    while( cursor->next->data < t )
        cursor = cursor->next;
    return cursor;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_DoubleListIteratorImp                     */
/*                                                                        */
/*  Implements a double list iterator.  This iterator works with any      */
/*  direct double list.  For indirect lists, see                          */
/*  BI_IDoubleListIteratorImp.                                            */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_DoubleListIteratorImp
{

public:

    BI_DoubleListIteratorImp( const BI_DoubleListImp<T> _FAR &l )
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
        BI_DoubleListElement<T> _FAR *temp = cur;
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

    const BI_DoubleListImp<T> _FAR *list;
    BI_DoubleListElement<T> _FAR *cur;

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_InternalIDoubleListImp                    */
/*                                                                        */
/*  Implements a double-linked list of pointers to objects of type T.     */
/*  This is implemented through the form of BI_DoubleListImp specified by */
/*  List.  Since pointers always have meaningful copy semantics,          */
/*  this class can handle any type of object.                             */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T, class List> class _CLASSTYPE BI_InternalIDoubleListImp :
    public List
{

public:

    T _FAR *peekHead() const { return (T _FAR *)head.next->data; }
    T _FAR *peekTail() const { return (T _FAR *)tail.prev->data; }

    void add( T _FAR *t ) { List::add( t ); }
    void addAtTail( T _FAR *t ) { List::addAtTail( t ); }
    void detach( T _FAR *t, int del = 0 ) { List::detach( t, del ); }

    void forEach( void (_FAR *)(T _FAR &, void _FAR *), void _FAR * );
    T _FAR *firstThat( int (_FAR *)(const T _FAR &, void _FAR *),
                       void _FAR *
                     ) const;
    T _FAR *lastThat( int (_FAR *)(const T _FAR &, void _FAR *),
                      void _FAR *
                    ) const;

protected:

    virtual BI_DoubleListElement<void _FAR*> _FAR*findPred( void _FAR* ) = 0;

private:

    virtual void removeData( BI_DoubleListElement<void _FAR *> _FAR *block )
        {
        delete (T _FAR *)(block->data);
        }

};

template <class T, class List>
void BI_InternalIDoubleListImp<T,List>::forEach( void (_FAR *f)(T _FAR &, void _FAR *),
                                                 void _FAR *args
                                               )
{
    BI_DoubleListElement<void _FAR *> _FAR *cur = head.next;
    while( cur->next != cur )
        {
        f( *(T _FAR *)cur->data, args );
        cur = cur->next;
        }
}

template <class T, class List>
T _FAR *BI_InternalIDoubleListImp<T,List>::firstThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                                                 void _FAR *args
                                               ) const
{
    BI_DoubleListElement<void _FAR *> _FAR *cur = head.next;
    while( cur->next != cur )
        if( cond( *(T _FAR *)(cur->data), args ) != 0 )
            return (T _FAR *)cur->data;
        else
            cur = cur->next;
    return 0;
}

template <class T, class List>
T _FAR *BI_InternalIDoubleListImp<T,List>::lastThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                                                void _FAR *args
                                              ) const
{
    T _FAR *res = 0;
    BI_DoubleListElement<void _FAR *> _FAR *cur = head.next;
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
/*  template <class T> class BI_IDoubleListImp                            */
/*                                                                        */
/*  Implements a double-linked list of pointers to objects of             */
/*  type T.  This is implemented through the template                     */
/*  BI_InternalIDoubleListImp. Since pointers always have meaningful      */
/*  copy semantics, this class can handle any type of object.             */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_IDoubleListImp :
    public BI_InternalIDoubleListImp<T, BI_DoubleListImp<void _FAR *> >
{

protected:

    virtual BI_DoubleListElement<void _FAR *> _FAR *findPred( void _FAR * );

};

template <class T>
BI_DoubleListElement<void _FAR *> _FAR *BI_IDoubleListImp<T>::findPred( void _FAR *t )
{
    tail.data = t;
    BI_DoubleListElement<void _FAR *> _FAR *cursor = &head;
    while( !(*(T _FAR *)t == *(T _FAR *)(cursor->next->data)) )
        cursor = cursor->next;
    return cursor;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_ISDoubleListImp                           */
/*                                                                        */
/*  Implements a sorted double-linked list of pointers to objects of      */
/*  type T.  This is implemented through the template                     */
/*  BI_InternalIDoubleListImp. Since pointers always have meaningful      */
/*  copy semantics, this class can handle any type of object.             */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_ISDoubleListImp :
    public BI_InternalIDoubleListImp<T, BI_SDoubleListImp<void _FAR *> >
{

protected:

    virtual BI_DoubleListElement<void _FAR *> _FAR *findDetach( void _FAR * );
    virtual BI_DoubleListElement<void _FAR *> _FAR *findPred( void _FAR * );

};

template <class T>
BI_DoubleListElement<void _FAR *> _FAR *BI_ISDoubleListImp<T>::findDetach( void _FAR *t )
{
    BI_DoubleListElement<void _FAR *> _FAR *res = findPred(t);
    if( *(T _FAR *)(res->next->data) == *(T _FAR *)t )
        return res;
    else
        return &tail;
}

template <class T>
BI_DoubleListElement<void _FAR *> _FAR *BI_ISDoubleListImp<T>::findPred( void _FAR *t )
{
    tail.data = t;
    BI_DoubleListElement<void _FAR *> _FAR *cursor = &head;
    while( *(T _FAR *)(cursor->next->data) < *(T _FAR *)t )
        cursor = cursor->next;
    return cursor;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IDoubleListIteratorImp                    */
/*                                                                        */
/*  Implements a double list iterator.  This iterator works with any      */
/*  indirect double list.  For direct lists, see BI_DoubleListIteratorImp.*/
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T>
class _CLASSTYPE BI_IDoubleListIteratorImp :
    public BI_DoubleListIteratorImp<void _FAR *>
{

public:

    BI_IDoubleListIteratorImp( const BI_DoubleListImp<void _FAR*> _FAR &l ) :
        BI_DoubleListIteratorImp<void _FAR *>(l) {}

    T _FAR *current()
        {
        return (T _FAR *)BI_DoubleListIteratorImp<void _FAR *>::current();
        }

    T _FAR *operator ++ (int)
      {
      return (T _FAR *)BI_DoubleListIteratorImp<void _FAR *>::operator ++ (1);
      }

    T _FAR *operator ++ ()
        {
        return (T _FAR *)BI_DoubleListIteratorImp<void _FAR *>::operator ++ ();
        }


};

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __DLISTIMP_H

