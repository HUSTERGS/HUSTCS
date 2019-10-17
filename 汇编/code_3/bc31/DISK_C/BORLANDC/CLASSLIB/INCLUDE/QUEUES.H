/*------------------------------------------------------------------------*/
/*                                                                        */
/*  QUEUES.H                                                              */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __QUEUES_H )
#define __QUEUES_H

#if !defined( __DEFS_H )
#include <_defs.h>
#endif  // __DEFS_H

#if !defined( __DEQUES_H )
#include <Deques.h>
#endif  // __DEQUES_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_QueueAsVector                             */
/*                                                                        */
/*  Implements a queue of objects of type T, using a vector as            */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_QueueAsVector :
    public BI_DequeAsVector<T>
{

public:

    BI_QueueAsVector( unsigned sz = DEFAULT_QUEUE_SIZE ) :
        BI_DequeAsVector<T>(sz)
        {
        }

    T get()
        {
        return BI_DequeAsVector<T>::getRight();
        }

    void put( T t )
        {
        BI_DequeAsVector<T>::putLeft( t );
        }

private:

    T getLeft();
    T getRight();

    void putLeft( T );
    void putRight( T );

};

template <class T> class _CLASSTYPE BI_QueueAsVectorIterator :
    public BI_DequeAsVectorIterator<T>
{

public:

    BI_QueueAsVectorIterator( const BI_DequeAsVector<T> _FAR &q ) :
        BI_DequeAsVectorIterator<T>(q) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IQueueAsVector                            */
/*                                                                        */
/*  Implements a queue of pointers to objects of type T,                  */
/*  using a vector as the underlying implementation.                      */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_IQueueAsVector :
    public BI_IDequeAsVector<T>
{

public:

    BI_IQueueAsVector( unsigned sz = DEFAULT_QUEUE_SIZE ) :
        BI_IDequeAsVector<T>(sz)
        {
        }

    T _FAR *get()
        {
        return BI_IDequeAsVector<T>::getRight();
        }

    void put( T _FAR *t )
        {
        BI_IDequeAsVector<T>::putLeft( t );
        }

private:

    T _FAR *getLeft();
    T _FAR *getRight();

    void putLeft( T _FAR * );
    void putRight( T _FAR * );

};

template <class T> class _CLASSTYPE BI_IQueueAsVectorIterator :
    public BI_IDequeAsVectorIterator<T>
{

public:

    BI_IQueueAsVectorIterator( const BI_IDequeAsVector<T> _FAR &q ) :
        BI_IDequeAsVectorIterator<T>(q) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_OQueueAsVector                                               */
/*                                                                        */
/*  Implements a queue of pointers to Object,                             */
/*  using a vector as the underlying implementation.                      */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_OQueueAsVector : public BI_ODequeAsVector
{

public:

    BI_OQueueAsVector( unsigned sz = DEFAULT_QUEUE_SIZE ) :
        BI_ODequeAsVector(sz)
        {
        }

    Object _FAR *get()
        {
        return BI_ODequeAsVector::getRight();
        }

    void put( Object _FAR *t )
        {
        BI_ODequeAsVector::putLeft( t );
        }

private:

    Object _FAR *getLeft();
    Object _FAR *getRight();

    void putLeft( Object _FAR * );
    void putRight( Object _FAR * );

};

class _CLASSTYPE BI_OQueueAsVectorIterator :
    public BI_ODequeAsVectorIterator
{

public:

    BI_OQueueAsVectorIterator( const BI_ODequeAsVector _FAR &q ) :
        BI_ODequeAsVectorIterator(q) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_TCQueueAsVector                                              */
/*                                                                        */
/*  Implements an Object queue, with the full semantics of                */
/*  the BC 2.0 style queue, using a vector as the underlying              */
/*  implementation.                                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_TCQueueAsVector : public BI_TCDequeAsVector
{

public:

    BI_TCQueueAsVector( unsigned sz = DEFAULT_QUEUE_SIZE ) :
        BI_TCDequeAsVector(sz)
        {
        }

    Object _FAR & get()
        {
        return BI_TCDequeAsVector::getRight();
        }

    void put( Object _FAR & t )
        { BI_TCDequeAsVector::putLeft( t );
        }

    virtual classType isA() const
        {
        return queueClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "BI_TCQueueAsDoubleList";
        }

    virtual ContainerIterator _FAR & initIterator() const;

private:

    Object _FAR & getLeft();
    Object _FAR & getRight();

    void putLeft( Object _FAR & );
    void putRight( Object _FAR & );

};

class _CLASSTYPE BI_TCQueueAsVectorIterator :
    public BI_TCDequeAsVectorIterator
{

public:

    BI_TCQueueAsVectorIterator( const BI_TCQueueAsVector _FAR &q ) :
        BI_TCDequeAsVectorIterator(q)
        {
        }

};

inline ContainerIterator _FAR & BI_TCQueueAsVector::initIterator() const
{
    return *new BI_TCQueueAsVectorIterator( *this );
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_QueueAsDoubleList                         */
/*                                                                        */
/*  Implements a queue of objects of type T, using a double linked list   */
/*  as the underlying implementation.                                     */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_QueueAsDoubleList :
    public BI_DequeAsDoubleList<T>
{

public:

    T get()
        {
        return BI_DequeAsDoubleList<T>::getRight();
        }

    void put( T t )
        {
        BI_DequeAsDoubleList<T>::putLeft( t );
        }

private:

    T getLeft();
    T getRight();

    void putLeft( T );
    void putRight( T );

};

template <class T> class _CLASSTYPE BI_QueueAsDoubleListIterator :
    public BI_DequeAsDoubleListIterator<T>
{

public:

    BI_QueueAsDoubleListIterator( const BI_QueueAsDoubleList<T> _FAR & q ) :
        BI_DequeAsDoubleListIterator<T>(q)
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IQueueAsDoubleList                        */
/*                                                                        */
/*  Implements a queue of pointers to objects of type T,                  */
/*  using a double linked list as the underlying implementation.          */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_IQueueAsDoubleList :
    public BI_IDequeAsDoubleList<T>
{

public:

    T _FAR *get()
        {
        return BI_IDequeAsDoubleList<T>::getRight();
        }

    void put( T _FAR *t )
        {
        BI_IDequeAsDoubleList<T>::putLeft( t );
        }

private:

    T _FAR *getLeft();
    T _FAR *getRight();

    void putLeft( T _FAR * );
    void putRight( T _FAR * );

};

template <class T> class _CLASSTYPE BI_IQueueAsDoubleListIterator :
    public BI_IDequeAsDoubleListIterator<T>
{

public:

    BI_IQueueAsDoubleListIterator( const BI_IQueueAsDoubleList<T> _FAR& q ) :
        BI_IDequeAsDoubleListIterator<T>(q) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_OQueueAsDoubleList                                           */
/*                                                                        */
/*  Implements a queue of pointers to Object,                             */
/*  using a double linked list as the underlying implementation.          */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_OQueueAsDoubleList : public BI_ODequeAsDoubleList
{

public:

    Object _FAR *get()
        {
        return BI_ODequeAsDoubleList::getRight();
        }

    void put( Object _FAR *t )
        {
        BI_ODequeAsDoubleList::putLeft( t );
        }

private:

    Object _FAR *getLeft();
    Object _FAR *getRight();

    void putLeft( Object _FAR * );
    void putRight( Object _FAR * );

};

class _CLASSTYPE BI_OQueueAsDoubleListIterator :
    public BI_ODequeAsDoubleListIterator
{

public:

    BI_OQueueAsDoubleListIterator( const BI_OQueueAsDoubleList _FAR & q ) :
        BI_ODequeAsDoubleListIterator(q) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_TCQueueAsDoubleList                                          */
/*                                                                        */
/*  Implements an Object queue, with the full semantics of                */
/*  the BC 2.0 style queue, using a double linked list as the underlying  */
/*  implementation.                                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_TCQueueAsDoubleList : public BI_TCDequeAsDoubleList
{

public:

    Object _FAR & get()
        {
        return BI_TCDequeAsDoubleList::getRight();
        }

    void put( Object _FAR & t )
        {
        BI_TCDequeAsDoubleList::putLeft( t );
        }

    virtual classType isA() const
        {
        return queueClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "BI_TCQueueAsDoubleList";
        }

    virtual ContainerIterator _FAR & initIterator() const;

private:

    Object _FAR & getLeft();
    Object _FAR & getRight();

    void putLeft( Object _FAR & );
    void putRight( Object _FAR & );

};

class _CLASSTYPE BI_TCQueueAsDoubleListIterator :
    public BI_TCDequeAsDoubleListIterator
{

public:

    BI_TCQueueAsDoubleListIterator( const BI_TCQueueAsDoubleList _FAR &q ) :
        BI_TCDequeAsDoubleListIterator(q) {}

};

inline ContainerIterator _FAR & BI_TCQueueAsDoubleList::initIterator() const
{
    return *new BI_TCQueueAsDoubleListIterator( *this );
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __QUEUES_H

