/*------------------------------------------------------------------------*/
/*                                                                        */
/*  BAGS.H                                                                */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __BAGS_H )
#define __BAGS_H

#if !defined( __CHECKS_H )
#include <Checks.h>
#endif  // __CHECKS_H

#if !defined( __SHDDEL_H )
#include <ShdDel.h>
#endif  // __SHDDEL_H

#if !defined( __VECTIMP_H )
#include <VectImp.h>
#endif  // __VECTIMP_H

#if !defined( __RESOURCE_H )
#include <Resource.h>
#endif  // __RESOURCE_H

#if !defined( __COLLECT_H )
#include <Collect.h>
#endif  // __COLLECT_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class Vect, class T> class BI_BagAsVectorImp                */
/*                                                                        */
/*  Implements a bag, using a vector as the underlying implementation.    */
/*  The type Vect specifies the form of the vector, either a              */
/*  BI_CVectorImp<T0> or a BI_ICVectorImp<T0>.  The type T specifies the  */
/*  type of the objects to be put in the bag.  When using                 */
/*  BI_VectorImp<T0>, T should be the same as T0. When using              */
/*  BI_IVectorImp<T0>, T should be of type pointer to T0.  See            */
/*  BI_BagAsVector and BI_IBagAsVector for examples.                      */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class Vect, class T> class _CLASSTYPE BI_BagAsVectorImp
{

public:

    BI_BagAsVectorImp( unsigned sz = DEFAULT_BAG_SIZE ) :
        data(sz,1)
        {
        }

    void add( T t )
        {
        data.add( t );
        }

    void detach( T t, TShouldDelete::DeleteType = TShouldDelete::NoDelete )
        {
        data.detach( t );
        }

    void flush( TShouldDelete::DeleteType = TShouldDelete::DefDelete )
        {
        data.flush();
        }

    int hasMember( T t ) const
        {
        return data.find(t) != UINT_MAX;
        }

    T findMember( T t ) const
        {
        PRECONDITION( hasMember(t) );
        return data[data.find(t)];
        }

    int isEmpty() const
        {
        return data.isEmpty();
        }

    int isFull() const
        { return 0;
        }

    int getItemsInContainer() const
        {
        return data.top();
        }

protected:

    Vect data;

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_BagAsVector                               */
/*                                                                        */
/*  Implements a bag of objects of type T, using a vector as              */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_BagAsVector :
    public BI_BagAsVectorImp<BI_CVectorImp<T>,T>
{

public:

    friend class _CLASSTYPE BI_BagAsVectorIterator<T>;

    BI_BagAsVector( unsigned sz = DEFAULT_BAG_SIZE ) :
        BI_BagAsVectorImp<BI_CVectorImp<T>,T>( sz )
        {
        }

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        data.forEach( f, args, 0, data.top() );
        }

    T _FAR *firstThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        return data.firstThat( f, args, 0, data.top() );
        }

    T _FAR *lastThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        return data.lastThat( f, args, 0, data.top() );
        }

protected:

    virtual T _FAR *find( T ) const;

};

template <class T> T _FAR *BI_BagAsVector<T>::find( T t ) const
{
    if( isEmpty() )
        return 0;
    for( int index = 0; index < data.top(); index++ )
        if( data[index] == t )
            return &(data[index]);
    return 0;
}

template <class T> class _CLASSTYPE BI_BagAsVectorIterator :
    public BI_VectorIteratorImp<T>
{

public:

    BI_BagAsVectorIterator( const BI_BagAsVector<T> _FAR & b ) :
        BI_VectorIteratorImp<T>(b.data,0,b.data.top()) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IBagAsVector                              */
/*                                                                        */
/*  Implements a bag of pointers to objects of type T,                    */
/*  using a vector as the underlying implementation.                      */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_IBagAsVector :
    public BI_BagAsVectorImp<BI_ICVectorImp<T>,T _FAR *>,
    public virtual TShouldDelete
{

public:

    friend class _CLASSTYPE BI_IBagAsVectorIterator<T>;

    BI_IBagAsVector( unsigned sz = DEFAULT_BAG_SIZE ) :
        BI_BagAsVectorImp<BI_ICVectorImp<T>,T _FAR *>(sz)
        {
        }

    ~BI_IBagAsVector()
        {
        flush();
        }

    void add( T _FAR *t )
        {
        BI_BagAsVectorImp<BI_ICVectorImp<T>,T _FAR *>::add(t);
        }

    void detach( T _FAR *t, DeleteType dt = NoDelete )
        {
        data.detach( t, delObj(dt) );
        }

    void flush( TShouldDelete::DeleteType dt = TShouldDelete::DefDelete )
        {
        data.flush( delObj(dt), data.top(), 0 );
        }

    T _FAR *findMember( T _FAR *t ) const
        {
        unsigned loc = data.find(t);
        return (T _FAR *)( loc == UINT_MAX ? 0 : data[loc] );
        }

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        data.forEach( f, args, 0, data.top() );
        }

    T _FAR *firstThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        return data.firstThat( f, args, 0, data.top() );
        }

    T _FAR *lastThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        return data.lastThat( f, args, 0, data.top() );
        }

};

template <class T> class _CLASSTYPE BI_IBagAsVectorIterator :
    public BI_IVectorIteratorImp<T>
{

public:

    BI_IBagAsVectorIterator( const BI_IBagAsVector<T> _FAR & s ) :
        BI_IVectorIteratorImp<T>(s.data,0,s.data.top()) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_OBagAsVector                                                 */
/*                                                                        */
/*  Implements a bag of pointers to Object,                               */
/*  using a vector as the underlying implementation.                      */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_OBagAsVector
{

public:

    friend class _CLASSTYPE BI_OBagAsVectorIterator;

    BI_OBagAsVector( unsigned sz = DEFAULT_BAG_SIZE ) :
        obag( sz )
        {
        }

    void add( Object _FAR *o )
        {
        obag.add(o);
        }

    void detach( Object _FAR *o,
                 TShouldDelete::DeleteType dt = TShouldDelete::NoDelete
               )
        {
        obag.detach( o, dt );
        }

    void flush( TShouldDelete::DeleteType dt = TShouldDelete::DefDelete )
        {
        obag.flush( dt );
        }

    int hasMember( Object _FAR *o ) const
        {
        return obag.hasMember(o);
        }

    Object _FAR *findMember( Object _FAR *o ) const
        {
        Object _FAR *obj = obag.findMember( o );
        return obj != 0 ? obj : 0;
        }

    int isEmpty() const
        {
        return obag.isEmpty();
        }

    int isFull() const
        {
        return obag.isFull();
        }

    void forEach( void (_FAR*f)(Object _FAR &, void _FAR*), void _FAR*args )
        {
        obag.forEach( f, args );
        }

    Object _FAR *firstThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                            void _FAR *args
                          ) const
        {
        return obag.firstThat( f, args );
        }

    Object _FAR *lastThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                           void _FAR *args
                         ) const
        {
        return obag.lastThat( f, args );
        }

    int getItemsInContainer() const
        {
        return obag.getItemsInContainer();
        }

    int ownsElements()
        {
        return obag.ownsElements();
        }

    void ownsElements( int del )
        {
        obag.ownsElements( del );
        }

protected:

    BI_IBagAsVector<Object> obag;

};

class _CLASSTYPE BI_OBagAsVectorIterator :
    public BI_IBagAsVectorIterator<Object>
{

public:

    BI_OBagAsVectorIterator( const BI_OBagAsVector _FAR & b ) :
        BI_IBagAsVectorIterator<Object>(b.obag)
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_TCBagAsVector                                                */
/*                                                                        */
/*  Implements an Object bag, with the full semantics of                  */
/*  the BC 2.0 style Bag, using a vector as the underlying                */
/*  implementation.                                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_TCBagAsVector : public Collection
{

public:

    friend class _CLASSTYPE BI_TCBagAsVectorIterator;

    BI_TCBagAsVector( int sz = DEFAULT_BAG_SIZE ) :
        bag(sz)
        {
        }

    virtual void add( Object _FAR & o )
        {
        bag.add( &o );
        }

    virtual void detach( Object _FAR & o,
                    TShouldDelete::DeleteType dt = TShouldDelete::NoDelete )
        {
        bag.detach( &o, dt );
        }

    virtual void flush(TShouldDelete::DeleteType dt=TShouldDelete::DefDelete )
        {
        bag.flush( dt );
        }

    virtual int isEmpty() const
        {
        return bag.isEmpty();
        }

    virtual countType getItemsInContainer() const
        {
        return bag.getItemsInContainer();
        }

    void forEach( void (_FAR*f)(Object _FAR &, void _FAR*), void _FAR*args )
        {
        bag.forEach( f, args );
        }

    Object _FAR & firstThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                             void _FAR *args
                           ) const
        {
        return ptrToRef(bag.firstThat( f, args ));
        }

    Object _FAR & lastThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                            void _FAR *args
                          ) const
        {
        return ptrToRef(bag.lastThat( f, args ));
        }

    virtual int hasMember( Object _FAR & o ) const
        {
        return bag.hasMember( &o );
        }

    virtual Object _FAR & findMember( Object _FAR & o ) const
        {
        return ptrToRef(bag.findMember(&o));
        }

    virtual ContainerIterator _FAR & initIterator() const;

    virtual classType isA() const
        {
        return bagClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "BI_TCBagAsVector";
        }

    int ownsElements()
        {
        return bag.ownsElements();
        }

    void ownsElements( int del )
        {
        bag.ownsElements( del );
        }

protected:

    BI_OBagAsVector bag;

};

class _CLASSTYPE BI_TCBagAsVectorIterator : public ContainerIterator
{

public:

    BI_TCBagAsVectorIterator( const BI_TCBagAsVector _FAR &b ) :
        iter(b.bag)
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

    BI_OBagAsVectorIterator iter;

};

inline ContainerIterator _FAR & BI_TCBagAsVector::initIterator() const
{
    return *new BI_TCBagAsVectorIterator( *this );
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __BAGS_H

