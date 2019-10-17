/*------------------------------------------------------------------------*/
/*                                                                        */
/*  DEQUES.H                                                              */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __DEQUES_H )
#define __DEQUES_H

#if !defined( __DEFS_H )
#include <_defs.h>
#endif  // __DEFS_H

#if !defined( __CHECKS_H )
#include <Checks.h>
#endif  // __CHECKS_H

#if !defined( __SHDDEL_H )
#include <ShdDel.h>
#endif  // __SHDDEL_H

#if !defined( __VECTIMP_H )
#include <VectImp.h>
#endif  // __VECTIMP_H

#if !defined( __DLISTIMP_H )
#include <DListImp.h>
#endif  // __DLISTIMP_H

#if !defined( __CONTAIN_H )
#include <Contain.h>
#endif  // __CONTAIN_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class Vect, class T> class BI_DequeAsVectorImp              */
/*                                                                        */
/*  Implements the fundamental dequeue operations, using a vector         */
/*  as the underlying implementation.  The type Vect specifies the        */
/*  form of the vector, either a BI_VectorImp<T0> or a                    */
/*  BI_IVectorImp<T0>.  The type T specifies the type of the              */
/*  objects to be put in the dequeue.  When using BI_VectorImp<T0>,       */
/*  T should be the same as T0. When using BI_IVectorImp<T0>, T           */
/*  should be of type pointer to T0.  See BI_QueueAsVector and            */
/*  BI_IQueueAsVector for examples.                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class Vect, class T> class _CLASSTYPE BI_DequeAsVectorImp
{

public:

    BI_DequeAsVectorImp( unsigned max = DEFAULT_DEQUE_SIZE ) :
        data(max+1),
        left(0),
        right(0)
        {
        }

    T peekLeft() const
        {
        PRECONDITION( !isEmpty() );
        return data[left];
        }

    T peekRight() const
        {
        PRECONDITION( !isEmpty() );
        return data[prev(right)];
        }

    T getLeft();
    T getRight();

    void putLeft( T );
    void putRight( T );

    void flush( TShouldDelete::DeleteType = TShouldDelete::DefDelete )
        {
        left = right = 0;
        }

    int isFull() const
        {
        return right == prev( left );
        }

    int isEmpty() const
        {
        return right == left;
        }

    int getItemsInContainer() const
        {
        return (right>=left) ? right - left : data.limit()-(left-right);
        }

protected:

    Vect data;
    unsigned left;
    unsigned right;

    unsigned prev( unsigned index ) const
        {
        if( index == 0 )
            index = data.limit();
        return --index;
        }

    unsigned next( unsigned index ) const
        {
        index++;
        if( index == data.limit() )
            index = 0;
        return index;
        }

};

template <class Vect, class T> T BI_DequeAsVectorImp<Vect,T>::getRight()
{
    PRECONDITION( !isEmpty() );
    right = prev(right);
    return data[right];
}

template <class Vect, class T>
void BI_DequeAsVectorImp<Vect,T>::putRight( T t )
{
    PRECONDITION( !isFull() );
    data[right] = t;
    right = next(right);
}

template <class Vect, class T> T BI_DequeAsVectorImp<Vect,T>::getLeft()
{
    PRECONDITION( !isEmpty() );
    T t = data[left];
    left = next(left);
    return t;
}

template <class Vect, class T>
void BI_DequeAsVectorImp<Vect,T>::putLeft( T t )
{
    PRECONDITION( !isFull() );
    left = prev(left);
    data[left] = t;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_DequeAsVectorIteratorImp                  */
/*                                                                        */
/*  Implements an iterator for the family of Deques as Vectors.           */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class I, class V, class T>
class _CLASSTYPE BI_DequeAsVectorIteratorImp
{

public:

    BI_DequeAsVectorIteratorImp( const V _FAR &, unsigned l, unsigned r );

    operator int();
    T current();
    T operator ++ ( int );
    T operator ++ ();
    void restart();

private:

    unsigned left;
    unsigned right;
    const V _FAR *vect;
    I iter;
    int second;

    void nextBlock();

};

template <class I, class V, class T>
BI_DequeAsVectorIteratorImp<I,V,T>::BI_DequeAsVectorIteratorImp( const V _FAR &v,
                                                               unsigned l,
                                                               unsigned r
                                                             ) :
    iter( v )
{
    vect = &v;
    left = l;
    right = r;
    restart();
}

template <class I, class V, class T>
BI_DequeAsVectorIteratorImp<I,V,T>::operator int()
{
    return int(iter);
}

template <class I, class V, class T>
T BI_DequeAsVectorIteratorImp<I,V,T>::current()
{
    return iter.current();
}

template <class I, class V, class T>
T BI_DequeAsVectorIteratorImp<I,V,T>::operator ++ ( int )
{
    nextBlock();
    return iter++;
}

template <class I, class V, class T>
T BI_DequeAsVectorIteratorImp<I,V,T>::operator ++ ()
{
    T temp = ++iter;
    nextBlock();
    return temp;
}

template <class I, class V, class T>
void BI_DequeAsVectorIteratorImp<I,V,T>::restart()
{
    if( left <= right )
        iter.restart( left, right );
    else
        iter.restart( right, vect->limit() );
    second = 0;
}

template <class I, class V, class T>
void BI_DequeAsVectorIteratorImp<I,V,T>::nextBlock()
{
    if( int(iter) == 0 && !second && left > right )
        {
        iter.restart( 0, left );
        second = 1;
        }
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_DequeAsVector                             */
/*                                                                        */
/*  Implements a dequeue of objects of type T, using a vector as          */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_DequeAsVector :
    public BI_DequeAsVectorImp<BI_VectorImp<T>,T>
{

public:

    friend class _CLASSTYPE BI_DequeAsVectorIterator<T>;

    BI_DequeAsVector( unsigned max = DEFAULT_DEQUE_SIZE ) :
        BI_DequeAsVectorImp<BI_VectorImp<T>,T>( max )
        {
        }

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        data.forEach( f, args, left, right );
        }

    T _FAR *firstThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        return data.firstThat( f, args, left, right );
        }

    T _FAR *lastThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        return data.lastThat( f, args, left, right );
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_DequeAsVectorIterator                     */
/*                                                                        */
/*  Implements an iterator for a DequeAsVector.                           */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_DequeAsVectorIterator :
    public BI_DequeAsVectorIteratorImp<BI_VectorIteratorImp<T>,BI_VectorImp<T>,T>
{

public:

    BI_DequeAsVectorIterator( const BI_DequeAsVector<T> _FAR &d ) :
        BI_DequeAsVectorIteratorImp<BI_VectorIteratorImp<T>,BI_VectorImp<T>,T>( d.data,d.left,d.right )
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IDequeAsVector                            */
/*                                                                        */
/*  Implements a dequeue of pointers to objects of type T,                */
/*  using a vector as the underlying implementation.                      */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_IDequeAsVector :
    public BI_DequeAsVectorImp<BI_IVectorImp<T>,T _FAR *>,
    public virtual TShouldDelete
{

public:

    friend class _CLASSTYPE BI_IDequeAsVectorIterator<T>;

    BI_IDequeAsVector( unsigned sz = DEFAULT_DEQUE_SIZE ) :
        BI_DequeAsVectorImp<BI_IVectorImp<T>,T _FAR *>(sz)
        {
        }

    ~BI_IDequeAsVector()
        {
        flush();
        }

    T _FAR *peekLeft() const
        {
        return (T _FAR *)BI_DequeAsVectorImp<BI_IVectorImp<T>,T _FAR *>::peekLeft();
        }

    T _FAR *peekRight() const
        {
        return (T _FAR *)BI_DequeAsVectorImp<BI_IVectorImp<T>,T _FAR *>::peekRight();
        }

    T _FAR *getLeft()
        {
        return (T _FAR *)BI_DequeAsVectorImp<BI_IVectorImp<T>,T _FAR *>::getLeft();
        }

    T _FAR *getRight()
        {
        return (T _FAR *)BI_DequeAsVectorImp<BI_IVectorImp<T>,T _FAR *>::getRight();
        }

    void putLeft( T _FAR *t )
        {
        BI_DequeAsVectorImp<BI_IVectorImp<T>,T _FAR *>::putLeft( t );
        }

    void putRight( T _FAR *t )
        {
        BI_DequeAsVectorImp<BI_IVectorImp<T>,T _FAR *>::putRight( t );
        }

    void flush( TShouldDelete::DeleteType = TShouldDelete::DefDelete );

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        data.forEach( f, args, left, right );
        }

    T _FAR *firstThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        return data.firstThat( f, args, left, right );
        }

    T _FAR *lastThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        return data.lastThat( f, args, left, right );
        }

};

template <class T>
void BI_IDequeAsVector<T>::flush( TShouldDelete::DeleteType dt )
{
    if( delObj(dt) != 0 )
        {
        if( left <= right )
            data.flush( 1, right, left );
        else
            {
            data.flush( 1, data.limit(), left );
            data.flush( 1, right - 1, 0 );
            }
        }
    BI_DequeAsVectorImp<BI_IVectorImp<T>,T _FAR *>::flush();
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IDequeAsVectorIterator                    */
/*                                                                        */
/*  Implements an iterator for the family of IDeques as Vectors.          */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_IDequeAsVectorIterator :
    public BI_DequeAsVectorIteratorImp<BI_IVectorIteratorImp<T>,BI_IVectorImp<T>,T _FAR *>
{

public:

    BI_IDequeAsVectorIterator( const BI_IDequeAsVector<T> _FAR &d ) :
        BI_DequeAsVectorIteratorImp<BI_IVectorIteratorImp<T>,BI_IVectorImp<T>,T _FAR *>(d.data,d.left,d.right) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_ODequeAsVector                                               */
/*                                                                        */
/*  Implements a dequeue of pointers to Object,                           */
/*  using a vector as the underlying implementation.                      */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_ODequeAsVector : protected BI_IDequeAsVector<Object>
{

public:

    friend class _CLASSTYPE BI_ODequeAsVectorIterator;

    BI_ODequeAsVector( unsigned sz = DEFAULT_DEQUE_SIZE ) :
        BI_IDequeAsVector<Object>( sz )
        {
        }

    Object _FAR *peekLeft() const
        {
        return BI_IDequeAsVector<Object>::peekLeft();
        }

    Object _FAR *peekRight() const
        {
        return BI_IDequeAsVector<Object>::peekRight();
        }

    Object _FAR *getLeft()
        {
        return BI_IDequeAsVector<Object>::getLeft();
        }

    Object _FAR *getRight()
        {
        return BI_IDequeAsVector<Object>::getRight();
        }

    void putLeft( Object _FAR *o )
        {
        BI_IDequeAsVector<Object>::putLeft( o );
        }

    void putRight( Object _FAR *o )
        {
        BI_IDequeAsVector<Object>::putRight( o );
        }

    void flush( TShouldDelete::DeleteType dt = TShouldDelete::DefDelete )
        {
        BI_IDequeAsVector<Object>::flush( dt );
        }

    int isFull() const
        {
        return BI_IDequeAsVector<Object>::isFull();
        }

    int isEmpty() const
        {
        return BI_IDequeAsVector<Object>::isEmpty();
        }

    void forEach( void (_FAR*f)(Object _FAR &, void _FAR*), void _FAR*args )
        {
        BI_IDequeAsVector<Object>::forEach( f, args );
        }

    Object _FAR *firstThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                            void _FAR *args
                          ) const
        {
        return BI_IDequeAsVector<Object>::firstThat( f, args );
        }

    Object _FAR *lastThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                           void _FAR *args
                         ) const
        {
        return BI_IDequeAsVector<Object>::lastThat( f, args );
        }

    int getItemsInContainer() const
        {
        return BI_IDequeAsVector<Object>::getItemsInContainer();
        }

};

class _CLASSTYPE BI_ODequeAsVectorIterator :
    public BI_IDequeAsVectorIterator<Object>
{

public:

    BI_ODequeAsVectorIterator( const BI_ODequeAsVector _FAR &d ) :
        BI_IDequeAsVectorIterator<Object>((const BI_IDequeAsVector<Object>&)d)
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_TCDequeAsVector                                              */
/*                                                                        */
/*  Implements an Object dequeue, with the full semantics of              */
/*  the BC 2.0 style deque, using a vector as the underlying              */
/*  implementation.                                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_TCDequeAsVector : 
    public Container, 
    protected BI_ODequeAsVector
{

public:

    friend class _CLASSTYPE BI_TCDequeAsVectorIterator;

    BI_TCDequeAsVector( int sz = DEFAULT_DEQUE_SIZE ) :
        BI_ODequeAsVector(sz)
        {
        }

    Object _FAR & peekLeft() const
        {
        return ptrToRef(BI_ODequeAsVector::peekLeft());
        }

    Object _FAR & peekRight() const
        {
        return ptrToRef(BI_ODequeAsVector::peekRight());
        }

    Object _FAR & getLeft()
        {
        return ptrToRef(BI_ODequeAsVector::getLeft());
        }

    Object _FAR & getRight()
        {
        return ptrToRef(BI_ODequeAsVector::getRight());
        }

    void putLeft( Object _FAR & o )
        {
        BI_ODequeAsVector::putLeft( &o );
        }

    void putRight( Object _FAR & o )
        {
        BI_ODequeAsVector::putRight( &o );
        }

    virtual void flush( DeleteType dt = DefDelete )
        {
        BI_ODequeAsVector::flush(dt);
        }

    virtual int isEmpty() const
        {
        return BI_ODequeAsVector::isEmpty();
        }

    virtual countType getItemsInContainer() const
        {
        return BI_ODequeAsVector::getItemsInContainer();
        }

    void forEach( void (_FAR*f)(Object _FAR &, void _FAR*), void _FAR*args )
        {
        BI_ODequeAsVector::forEach( f, args );
        }

    Object _FAR & firstThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                             void _FAR *args
                           ) const
        {
        return ptrToRef(BI_ODequeAsVector::firstThat( f, args ));
        }

    Object _FAR & lastThat( int ( _FAR *f)(const Object _FAR &, void _FAR *),
                            void _FAR *args
                          ) const
        {
        return ptrToRef(BI_ODequeAsVector::lastThat( f, args ));
        }

    virtual ContainerIterator _FAR & initIterator() const;

    virtual classType isA() const
        {
        return dequeClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "BI_TCDequeAsVector";
        }

};

class _CLASSTYPE BI_TCDequeAsVectorIterator : public ContainerIterator
{

public:

    BI_TCDequeAsVectorIterator( const BI_TCDequeAsVector _FAR &d ) :
        iter((const BI_ODequeAsVector&)d)
        {
        }

    virtual operator int()
        {
        return int(iter);
        }

    virtual Object _FAR & current()
        {
        return Object::ptrToRef(iter.current());
        }

    virtual Object _FAR & operator ++ ( int )
        {
        return Object::ptrToRef(iter++);
        }

    virtual Object _FAR & operator ++ ()
        {
        return Object::ptrToRef(++iter);
        }

    virtual void restart()
        {
        iter.restart();
        }

private:

    BI_ODequeAsVectorIterator iter;

};

inline ContainerIterator _FAR & BI_TCDequeAsVector::initIterator() const
{
    return *new BI_TCDequeAsVectorIterator( *this );
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class Lst, class T> class BI_DequeAsDoubleListImp           */
/*                                                                        */
/*  Implements the fundamental dequeue operations, using a list           */
/*  as the underlying implementation.  The type Lst specifies the         */
/*  form of the list, either a BI_DoubleListImp<T0> or a                  */
/*  BI_IDoubleListImp<T0>.  The type T specifies the type of the          */
/*  objects to be put in the deque.  When using BI_DoubleListImp<T0>,     */
/*  T should be the same as T0. When using BI_IDoubleListImp<T0>, T       */
/*  should be of type pointer to T0.  See BI_DequeAsDoubleList and        */
/*  BI_IDequeAsDoubleList for examples.                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class Lst, class T> class _CLASSTYPE BI_DequeAsDoubleListImp
{

public:

    BI_DequeAsDoubleListImp() :
        itemsInContainer( 0 )
        {
        }

    T peekLeft() const
        {
        PRECONDITION( !isEmpty() );
        return data.peekTail();
        }

    T peekRight() const
        {
        PRECONDITION( !isEmpty() );
        return data.peekHead();
        }

    T getLeft()
        {
        PRECONDITION( !isEmpty() );
        T t = peekLeft();
        data.detach( t, 0 );
        itemsInContainer--;
        return t;
        }

    T getRight()
        {
        PRECONDITION( !isEmpty() );
        T t = peekRight();
        data.detach( t, 0 );
        itemsInContainer--;
        return t;
        }

    void putLeft( T t )
        {
        data.addAtTail( t );
        itemsInContainer++;
        }

    void putRight( T t )
        {
        data.add( t );
        itemsInContainer++;
        }

    void flush( int del )
        {
        data.flush( del ); 
        itemsInContainer = 0;
        }

    int isFull() const
        {
        return 0;
        }

    int isEmpty() const
        {
        return itemsInContainer == 0;
        }

    int getItemsInContainer() const
        {
        return itemsInContainer;
        }

protected:

    Lst data;
    int itemsInContainer;

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_DequeAsDoubleList                         */
/*                                                                        */
/*  Implements a dequeue of objects of type T, using a double-linked list */
/*  as the underlying implementation.                                     */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_DequeAsDoubleList :
    public BI_DequeAsDoubleListImp<BI_DoubleListImp<T>,T>
{

public:

    friend class _CLASSTYPE BI_DequeAsDoubleListIterator<T>;

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        data.forEach( f, args );
        }

    T _FAR *firstThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        return data.firstThat( f, args );
        }

    T _FAR *lastThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        return data.lastThat( f, args );
        }

};

template <class T> class _CLASSTYPE BI_DequeAsDoubleListIterator :
    public BI_DoubleListIteratorImp<T>
{

public:

    BI_DequeAsDoubleListIterator( const BI_DequeAsDoubleList<T> _FAR & s ) :
        BI_DoubleListIteratorImp<T>(s.data)
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IDequeAsDoubleList                        */
/*                                                                        */
/*  Implements a dequeue of pointers to objects of type T,                */
/*  using a double-linked list as the underlying implementation.          */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T>
class _CLASSTYPE BI_IDequeAsDoubleList :
    public BI_DequeAsDoubleListImp<BI_IDoubleListImp<T>,T _FAR *>,
    public virtual TShouldDelete
{

public:


    friend class _CLASSTYPE BI_IDequeAsDoubleListIterator<T>;

    T _FAR *peekLeft() const
        {
        PRECONDITION( !isEmpty() );
        return (T _FAR *)BI_DequeAsDoubleListImp<BI_IDoubleListImp<T>,T _FAR *>::peekLeft();
        }

    T _FAR *peekRight() const
        {
        PRECONDITION( !isEmpty() );
        return (T _FAR *)BI_DequeAsDoubleListImp<BI_IDoubleListImp<T>,T _FAR *>::peekRight();
        }

    T _FAR *getLeft()
        {
        return (T _FAR *)BI_DequeAsDoubleListImp<BI_IDoubleListImp<T>,T _FAR *>::getLeft();
        }

    T _FAR *getRight()
        {
        return (T _FAR *)BI_DequeAsDoubleListImp<BI_IDoubleListImp<T>,T _FAR *>::getRight();
        }

    void putLeft( T _FAR *t )
        {
        BI_DequeAsDoubleListImp<BI_IDoubleListImp<T>,T _FAR *>::putLeft( t );
        }

    void putRight( T _FAR *t )
        {
        BI_DequeAsDoubleListImp<BI_IDoubleListImp<T>,T _FAR *>::putRight( t );
        }

    void flush( TShouldDelete::DeleteType dt = TShouldDelete::DefDelete )
        {
        BI_DequeAsDoubleListImp<BI_IDoubleListImp<T>,T _FAR *>::flush( delObj(dt) );
        }

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        data.forEach( f, args );
        }

    T _FAR *firstThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        return data.firstThat( f, args );
        }

    T _FAR *lastThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        return data.lastThat( f, args );
        }

};

template <class T> class _CLASSTYPE BI_IDequeAsDoubleListIterator :
    public BI_IDoubleListIteratorImp<T>
{

public:

    BI_IDequeAsDoubleListIterator( const BI_IDequeAsDoubleList<T> _FAR& s ) :
        BI_IDoubleListIteratorImp<T>(s.data)
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_ODequeAsDoubleList                                           */
/*                                                                        */
/*  Implements a dequeue of pointers to Object,                           */
/*  using a double-linked list as the underlying implementation.          */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_ODequeAsDoubleList : 
    protected BI_IDequeAsDoubleList<Object>
{

public:

    friend class _CLASSTYPE BI_ODequeAsDoubleListIterator;

    ~BI_ODequeAsDoubleList()
        {
        flush();
        }

    Object _FAR *peekLeft() const
        {
        return BI_IDequeAsDoubleList<Object>::peekLeft();
        }

    Object _FAR *peekRight() const
        {
        return BI_IDequeAsDoubleList<Object>::peekRight();
        }

    Object _FAR *getLeft()
        {
        return BI_IDequeAsDoubleList<Object>::getLeft();
        }

    Object _FAR *getRight()
        {
        return BI_IDequeAsDoubleList<Object>::getRight();
        }

    void putLeft( Object _FAR *o )
        {
        BI_IDequeAsDoubleList<Object>::putLeft( o );
        }

    void putRight( Object _FAR *o )
        {
        BI_IDequeAsDoubleList<Object>::putRight( o );
        }

    void flush( TShouldDelete::DeleteType dt = TShouldDelete::DefDelete )
        {
        BI_IDequeAsDoubleList<Object>::flush( dt );
        }

    int isFull() const
        {
        return BI_IDequeAsDoubleList<Object>::isFull();
        }

    int isEmpty() const
        {
        return BI_IDequeAsDoubleList<Object>::isEmpty();
        }

    void forEach( void (_FAR*f)(Object _FAR &, void _FAR*), void _FAR*args )
        {
        BI_IDequeAsDoubleList<Object>::forEach( f, args );
        }

    Object _FAR *firstThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                            void _FAR *args
                          ) const
        {
        return BI_IDequeAsDoubleList<Object>::firstThat( f, args );
        }

    Object _FAR *lastThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                           void _FAR *args
                         ) const
        {
        return BI_IDequeAsDoubleList<Object>::lastThat( f, args );
        }

    int getItemsInContainer() const { return BI_IDequeAsDoubleList<Object>::getItemsInContainer(); }

};

class _CLASSTYPE BI_ODequeAsDoubleListIterator :
    public BI_IDequeAsDoubleListIterator<Object>
{

public:

    BI_ODequeAsDoubleListIterator( const BI_ODequeAsDoubleList _FAR &d ) :
        BI_IDequeAsDoubleListIterator<Object>((const BI_IDequeAsDoubleList<Object>&)d)
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_TCDequeAsDoubleList                                          */
/*                                                                        */
/*  Implements an Object dequeue, with the full semantics of              */
/*  the BC 2.0 style stack, using a double-linked list as the underlying  */
/*  implementation.                                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_TCDequeAsDoubleList : 
    public Container,
    protected BI_ODequeAsDoubleList
{

public:

    friend class _CLASSTYPE BI_TCDequeAsDoubleListIterator;

    Object _FAR & peekLeft() const
        {
        return ptrToRef(BI_ODequeAsDoubleList::peekLeft());
        }

    Object _FAR & peekRight() const
        {
        return ptrToRef(BI_ODequeAsDoubleList::peekRight());
        }

    Object _FAR & getLeft()
        {
        return ptrToRef(BI_ODequeAsDoubleList::getLeft());
        }

    Object _FAR & getRight()
        {
        return ptrToRef(BI_ODequeAsDoubleList::getRight());
        }

    void putLeft( Object _FAR & o )
        {
        BI_ODequeAsDoubleList::putLeft( &o );
        }

    void putRight( Object _FAR & o )
        {
        BI_ODequeAsDoubleList::putRight( &o );
        }

    virtual void flush( DeleteType dt = DefDelete )
        {
        BI_ODequeAsDoubleList::flush( dt );
        }

    virtual int isEmpty() const
        {
        return BI_ODequeAsDoubleList::isEmpty();
        }

    virtual countType getItemsInContainer() const
        {
        return BI_ODequeAsDoubleList::getItemsInContainer();
        }

    void forEach( void (_FAR*f)(Object _FAR &, void _FAR*), void _FAR*args )
        {
        BI_ODequeAsDoubleList::forEach( f, args );
        }

    Object _FAR & firstThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                             void _FAR *args
                           ) const
        {
        return ptrToRef(BI_ODequeAsDoubleList::firstThat( f, args ));
        }

    Object _FAR & lastThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                            void _FAR *args
                          ) const
        {
        return ptrToRef(BI_ODequeAsDoubleList::lastThat( f, args ));
        }

    virtual ContainerIterator _FAR & initIterator() const;

    virtual classType isA() const
        {
        return dequeClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "BI_DequeAsDoubleList";
        }

};

class _CLASSTYPE BI_TCDequeAsDoubleListIterator : public ContainerIterator
{

public:

    BI_TCDequeAsDoubleListIterator( const BI_TCDequeAsDoubleList _FAR &o ) :
        iter((const BI_ODequeAsDoubleList&)o)
        {
        }

    virtual operator int()
        {
        return int(iter);
        }

    virtual Object _FAR & current()
        {
        return Object::ptrToRef(iter.current());
        }

    virtual Object _FAR & operator ++ ( int )
        {
        return Object::ptrToRef(iter++);
        }

    virtual Object _FAR & operator ++ ()
        {
        return Object::ptrToRef(++iter);
        }

    virtual void restart()
        {
        iter.restart();
        }

private:

    BI_ODequeAsDoubleListIterator iter;

};

inline ContainerIterator _FAR & BI_TCDequeAsDoubleList::initIterator() const
{
    return *new BI_TCDequeAsDoubleListIterator( *this );
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __DEQUES_H

