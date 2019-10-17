/*------------------------------------------------------------------------*/
/*                                                                        */
/*  ARRAYS.H                                                              */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __ARRAYS_H )
#define __ARRAYS_H

#define TEMPLATES

#if !defined( __DEFS_H )
#include <_defs.h>
#endif  // __DEFS_H

#if !defined( __RESOURCE_H )
#include <Resource.h>
#endif  // __RESOURCE_H

#if !defined( __COLLECT_H )
#include <Collect.h>
#endif  // __COLLECT_H

#if !defined( __MEM_H )
#include <Mem.h>
#endif  // __MEM_H

#if !defined( __VECTIMP_H )
#include <VectImp.h>
#endif  // __VECTIMP_H

#if !defined( __SORTABLE_H )
#include <Sortable.h>
#endif  // __SORTABLE_H

#if !defined( __ABSTARRY_H )
#include <AbstArry.h>
#endif  // __ABSTARRY_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

#pragma warn -ncf

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class Vect, class T> class BI_ArrayAsVectorImp              */
/*                                                                        */
/*  Implements the fundamental array operations, using a vector           */
/*  as the underlying implementation.  The type Vect specifies the        */
/*  form of the vector, either a BI_CVectorImp<T0> or a                   */
/*  BI_IVectorImp<T0>.  The type T specifies the type of the              */
/*  objects to be put in the array.  When using BI_CVectorImp<T0>,        */
/*  T should be the same as T0. When using BI_ICVectorImp<T0>, T          */
/*  should be of type pointer to T0.  See BI_ArrayAsVector and            */
/*  BI_IArrayAsVector for examples.                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class Vect, class T>
class _CLASSTYPE BI_ArrayAsVectorImp
{

public:

    BI_ArrayAsVectorImp( int upper, int lower, int delta ) :
        data( upper-lower+1,delta),
        lowerbound(lower)
        {
        }

    int lowerBound() const
        {
        return lowerbound;
        }

    int upperBound() const
        {
        return boundBase(data.limit())-1;
        }

    sizeType arraySize() const
        {
        return data.limit();
        }

    void add( T t )
        {
        data.add( t );
        }

    void addAt( T t, int loc )
        {
        data.addAt( t, zeroBase(loc) );
        }

    void detach( T t, TShouldDelete::DeleteType dt = TShouldDelete::NoDelete )
        {
        data.detach( t, dt );
        }

    void detach( int loc,
                 TShouldDelete::DeleteType dt =TShouldDelete::NoDelete
               )
        {
        data.detach( zeroBase(loc), dt );
        }

    void destroy( int i )
        {
        detach( i, TShouldDelete::Delete );
        }

    void flush( TShouldDelete::DeleteType dt = TShouldDelete::DefDelete )
        {
        data.flush( dt );
        }

    int isFull() const
        {
        return data.getDelta() == 0 && data.count() >= data.limit();
        }

    int hasMember( T t ) const
        {
        return data.find(t) != UINT_MAX;
        }

    int isEmpty() const
        {
        return data.count() == 0;
        }

    countType getItemsInContainer() const
        {
        return data.count();
        }

protected:

    T itemAt( int i ) const
        {
        return data[ zeroBase(i) ];
        }

    int find( const T t ) const
        {
        return boundBase(data.find( t ));
        }

    void reallocate( sizeType sz, sizeType offset = 0 )
        {
        data.resize( sz, offset );
        }


    void setData( int loc, T t )
        {
        PRECONDITION( loc >= lowerbound && loc <= upperBound() );
        data[ zeroBase(loc) ] = t;
        }

    void insertEntry( int loc )
        {
        PRECONDITION( loc >= lowerbound && loc <= upperBound() );
        T t;
        data.addAt( t, zeroBase(loc) );
        }

    void removeEntry( int loc )
        {
        squeezeEntry( zeroBase(loc) );
        }

    void squeezeEntry( unsigned loc )
        {
        PRECONDITION( loc < data.count() );
        data.detach( loc );
        }

    unsigned zeroBase( int loc ) const
        {
        return loc - lowerbound;
        }

    int boundBase( unsigned loc ) const
        {
        return loc == UINT_MAX ? INT_MAX : loc + lowerbound;
        }

    void grow( int loc )
        {
        if( loc < lowerBound() )
            reallocate( arraySize() + (loc - lowerbound) );
        else if( loc >= boundBase(data.limit()) )
            reallocate( zeroBase(loc) );
        }

    int lowerbound;

    Vect data;

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_ArrayAsVector                             */
/*                                                                        */
/*  Implements an array of objects of type T, using a vector as           */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_ArrayAsVector :
    public BI_ArrayAsVectorImp<BI_CVectorImp<T>,T>
{

public:

    friend class _CLASSTYPE BI_ArrayAsVectorIterator<T>;

    BI_ArrayAsVector( int upper, int lower = 0, int delta = 0 ) :
        BI_ArrayAsVectorImp<BI_CVectorImp<T>,T>( upper, lower, delta )
        {
        }

    T& operator []( int loc )
        {
        grow( loc+1 );
        return data[zeroBase(loc)];
        }

    T& operator []( int loc ) const
        {
        PRECONDITION( loc >= lowerbound && loc < data.count() );
        return data[zeroBase(loc)];
        }

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        if( !isEmpty() )
            data.forEach( f, args );
        }

    T _FAR *firstThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        if( isEmpty() )
            return 0;
        return data.firstThat( f, args );
        }

    T _FAR *lastThat( int (_FAR * f)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        if( isEmpty() )
            return 0;
        return data.lastThat( f, args );
        }

};

template <class T> class _CLASSTYPE BI_ArrayAsVectorIterator :
    public BI_VectorIteratorImp<T>
{

public:

    BI_ArrayAsVectorIterator( const BI_ArrayAsVector<T> _FAR & a ) :
        BI_VectorIteratorImp<T>(a.data) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IArrayAsVector                            */
/*                                                                        */
/*  Implements an indirect array of objects of type T, using a vector as  */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_IArrayAsVector :
    public BI_ArrayAsVectorImp<BI_ICVectorImp<T>,T _FAR *>,
    public virtual TShouldDelete
{

public:

    friend class _CLASSTYPE BI_IArrayAsVectorIterator<T>;

    BI_IArrayAsVector( int upper, int lower = 0, int delta = 0 ) :
        BI_ArrayAsVectorImp<BI_ICVectorImp<T>,T _FAR *>( upper, lower, delta )
        {
        }

    ~BI_IArrayAsVector()
        {
        flush();
        }

    T _FAR * _FAR & operator []( int loc )
        {
        grow( loc+1 );
        return data[zeroBase(loc)];
        }

    T _FAR * _FAR & operator []( int loc ) const
        {
        PRECONDITION( loc >= lowerbound && zeroBase(loc) < data.limit() );
        return data[zeroBase(loc)];
        }

    void add( T _FAR *t )
        {
        BI_ArrayAsVectorImp<BI_ICVectorImp<T>,T _FAR *>::add(t);
        }

    void addAt( T _FAR *t, int loc )
        {
        BI_ArrayAsVectorImp<BI_ICVectorImp<T>,T _FAR *>::addAt(t,loc);
        }

    void detach( int loc, DeleteType dt = NoDelete )
        {
        data.detach( zeroBase(loc), delObj(dt) );
        }

    void detach( T _FAR *t, DeleteType dt = NoDelete )
        {
        unsigned loc = data.find( t );
        if( loc == UINT_MAX )
            return;
        data.detach( loc, delObj(dt) );
        }

    void flush( DeleteType dt = DefDelete )
        {
        data.flush( delObj(dt), data.limit(), 0 );
        }

    int find( const T *t ) const
        {
        return boundBase(data.find( (T *)t ));
        }

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        if( !isEmpty() )
            data.forEach( f, args );
        }

    T _FAR *firstThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        if( isEmpty() )
            return 0;
        return data.firstThat( f, args );
        }

    T _FAR *lastThat( int (_FAR * f)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        if( isEmpty() )
            return 0;
        return data.lastThat( f, args );
        }

};

template <class T> class _CLASSTYPE BI_IArrayAsVectorIterator :
    public BI_IVectorIteratorImp<T>
{

public:

    BI_IArrayAsVectorIterator( const BI_IArrayAsVector<T> _FAR &a ) :
        BI_IVectorIteratorImp<T>(a.data) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_OArrayAsVector                                               */
/*                                                                        */
/*  Implements an array of pointers to Object,                            */
/*  using a vector as the underlying implementation.                      */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_OArrayAsVector
{

public:

    friend class _CLASSTYPE BI_OArrayAsVectorIterator;

    BI_OArrayAsVector() : oarray( DEFAULT_ARRAY_SIZE )
        {
        }

    BI_OArrayAsVector( int upr, int lwr = 0, unsigned delta = 0 ) :
        oarray( upr, lwr, delta )
        {
        }

    Object *operator [] (int loc)
        {
        return oarray[loc];
        }

    Object *operator [] (int loc) const
        {
        return oarray[loc];
        }

    int lowerBound() const
        {
        return oarray.lowerBound();
        }

    int upperBound() const
        {
        return oarray.upperBound();
        }

    sizeType arraySize() const
        {
        return oarray.arraySize();
        }

    void add( Object _FAR *o )
        {
        oarray.add(o);
        }

    void addAt( Object _FAR *o, int loc )
        {
        oarray.addAt(o,loc);
        }

    void detach( int loc,
                 TShouldDelete::DeleteType dt = TShouldDelete::NoDelete
               )
        {
        oarray.detach( loc, dt );
        }

    void detach( Object _FAR *o,
                 TShouldDelete::DeleteType dt = TShouldDelete::NoDelete
               )
        {
        oarray.detach( o, dt );
        }

    void destroy( int i )
        {
        oarray.destroy( i );
        }

    void flush( TShouldDelete::DeleteType dt = TShouldDelete::DefDelete )
        {
        oarray.flush( dt );
        }

    int hasMember( Object _FAR *o ) const
        {
        return oarray.hasMember(o);
        }

    Object _FAR *findMember( Object _FAR *o ) const
        {
        int loc = oarray.find(o);
        return loc != INT_MAX ? oarray[loc] : 0;
        }

    int isEmpty() const
        {
        return oarray.isEmpty();
        }

    int isFull() const
        {
        return oarray.isFull();
        }

    void forEach( void (_FAR*f)(Object _FAR &, void _FAR*), void _FAR*args )
        {
        oarray.forEach( f, args );
        }

    Object _FAR *firstThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                            void _FAR *args
                          ) const
        {
        return oarray.firstThat( f, args );
        }

    Object _FAR *lastThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                           void _FAR *args
                         ) const
        {
        return oarray.lastThat( f, args );
        }

    int getItemsInContainer() const
        {
        return oarray.getItemsInContainer();
        }

    int ownsElements()
        {
        return oarray.ownsElements();
        }

    void ownsElements( int del )
        {
        oarray.ownsElements( del );
        }

protected:

    BI_IArrayAsVector<Object> oarray;

};

class _CLASSTYPE BI_OArrayAsVectorIterator :
    public BI_IArrayAsVectorIterator<Object>
{

public:

    BI_OArrayAsVectorIterator( const BI_OArrayAsVector _FAR &a ) :
        BI_IArrayAsVectorIterator<Object>(a.oarray)
        {
        restart();
        }

    void restart()
        {
        BI_IArrayAsVectorIterator<Object>::restart();
        if( current() == 0 )
            (*this)++;
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_TCArrayAsVector                                              */
/*                                                                        */
/*  Implements an Object array, with the full semantics of                */
/*  the BC 2.0 style array, using a vector as the underlying              */
/*  implementation.                                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_TCArrayAsVector : public AbstractArray
{

public:

    friend class _CLASSTYPE BI_TCArrayAsVectorIterator;

    BI_TCArrayAsVector( int upper, int lower = 0, sizeType delta = 0 ) :
        array( upper, lower, delta )
        {
        }

    virtual Object& operator []( int loc )
        {
        return ptrToRef(array[loc]);
        }

    virtual Object& operator []( int loc ) const
        {
        return ptrToRef(array[loc]);
        }

    virtual int lowerBound() const
        {
        return array.lowerBound();
        }

    virtual int upperBound() const
        {
        return array.upperBound();
        }

    virtual sizeType arraySize() const
        {
        return array.arraySize();
        }

    void add( Object _FAR &o )
        {
        array.add(&o);
        }

    void addAt( Object _FAR &o, int loc )
        {
        array.addAt(&o,loc);
        }

    virtual void detach( int loc, DeleteType dt = NoDelete )
        {
        array.detach( loc, dt );
        }

    void detach( Object _FAR &o,
                 TShouldDelete::DeleteType dt = TShouldDelete::NoDelete
               )
        {
        array.detach( &o, dt );
        }

    void flush( TShouldDelete::DeleteType dt = TShouldDelete::DefDelete )
        {
        array.flush( dt );
        }

    int hasMember( Object _FAR &o ) const
        {
        return array.hasMember(&o);
        }

    Object _FAR &findMember( Object _FAR &o ) const
        {
        return ptrToRef(array.findMember(&o));
        }

    int isEmpty() const
        {
        return array.isEmpty();
        }

    int isFull() const
        {
        return array.isFull();
        }

    void forEach( void (_FAR*f)(Object _FAR &, void _FAR*), void _FAR*args )
        {
        array.forEach( f, args );
        }

    Object _FAR &firstThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                            void _FAR *args
                          ) const
        {
        return ptrToRef(array.firstThat( f, args ));
        }

    Object _FAR &lastThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                           void _FAR *args
                         ) const
        {
        return ptrToRef(array.lastThat( f, args ));
        }

    int getItemsInContainer() const
        {
        return array.getItemsInContainer();
        }

    virtual classType isA() const
        {
        return arrayClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "BI_TCArrayAsVector";
        }

    int ownsElements()
        {
        return array.ownsElements();
        }

    void ownsElements( int del )
        {
        array.ownsElements( del );
        }

    ContainerIterator _FAR &initIterator() const;

private:

    BI_OArrayAsVector array;

};

class _CLASSTYPE BI_TCArrayAsVectorIterator : public ContainerIterator
{

public:

    BI_TCArrayAsVectorIterator( const BI_TCArrayAsVector _FAR &a ) :
        iter(a.array)
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

    BI_OArrayAsVectorIterator iter;

};

inline ContainerIterator _FAR & BI_TCArrayAsVector::initIterator() const
        { return *new BI_TCArrayAsVectorIterator( *this ); }

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_SArrayAsVector                            */
/*                                                                        */
/*  Implements a sorted array of objects of type T, using a vector as     */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_SArrayAsVector :
    public BI_ArrayAsVectorImp<BI_SVectorImp<T>,T>
{

public:

    friend class _CLASSTYPE BI_SArrayAsVectorIterator<T>;

    BI_SArrayAsVector( int upper, int lower = 0, int delta = 0 ) :
        BI_ArrayAsVectorImp<BI_SVectorImp<T>,T>( upper, lower, delta )
        {
        }

    T& operator []( int loc )
        {
        grow( loc+1 );
        return data[zeroBase(loc)];
        }

    T& operator []( int loc ) const
        {
        PRECONDITION( loc >= lowerbound && loc < data.count() );
        return data[zeroBase(loc)];
        }

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        if( !isEmpty() )
            data.forEach( f, args );
        }

    T _FAR *firstThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        if( isEmpty() )
            return 0;
        return data.firstThat( f, args );
        }

    T _FAR *lastThat( int (_FAR * f)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        if( isEmpty() )
            return 0;
        return data.lastThat( f, args );
        }

};

template <class T> class _CLASSTYPE BI_SArrayAsVectorIterator :
    public BI_VectorIteratorImp<T>
{

public:

    BI_SArrayAsVectorIterator( const BI_SArrayAsVector<T> _FAR & a ) :
        BI_VectorIteratorImp<T>(a.data) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_ISArrayAsVector                           */
/*                                                                        */
/*  Implements an indirect sorted array of objects of type T, using a     */
/*  vector as the underlying implementation.                              */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_ISArrayAsVector :
    public BI_ArrayAsVectorImp<BI_ISVectorImp<T>,T _FAR *>,
    public virtual TShouldDelete
{

public:

    friend class _CLASSTYPE BI_ISArrayAsVectorIterator<T>;

    BI_ISArrayAsVector( int upper, int lower = 0, int delta = 0 ) :
        BI_ArrayAsVectorImp<BI_ISVectorImp<T>,T _FAR*>( upper, lower, delta )
        {
        }

    ~BI_ISArrayAsVector()
        {
        flush();
        }

    T _FAR * _FAR & operator []( int loc )
        {
        grow( loc+1 );
        return data[zeroBase(loc)];
        }

    T _FAR * _FAR & operator []( int loc ) const
        {
        PRECONDITION( loc >= lowerbound && loc < data.count() );
        return data[zeroBase(loc)];
        }

    void add( T _FAR *t )
        {
        BI_ArrayAsVectorImp<BI_ISVectorImp<T>,T _FAR *>::add(t);
        }

    void addAt( T _FAR *t, int loc )
        {
        BI_ArrayAsVectorImp<BI_ISVectorImp<T>,T _FAR *>::addAt(t,loc);
        }

    void detach( int loc, DeleteType dt = NoDelete )
        {
        data.detach( loc, delObj(dt) );
        }

    void detach( T _FAR *t, DeleteType dt = NoDelete )
        {
        unsigned loc = data.find( t );
        if( loc == UINT_MAX )
            return;
        data.detach( loc, delObj(dt) );
        }

    void flush( DeleteType dt = DefDelete )
        {
        data.flush( delObj(dt), data.limit(), 0 );
        }

    int find( const T *t ) const
        {
        return boundBase( data.find( (T *)t ) );
        }

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        if( !isEmpty() )
            data.forEach( f, args );
        }

    T _FAR *firstThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        if( isEmpty() )
            return 0;
        return data.firstThat( f, args );
        }

    T _FAR *lastThat( int (_FAR * f)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        if( isEmpty() )
            return 0;
        return data.lastThat( f, args );
        }

};

template <class T> class _CLASSTYPE BI_ISArrayAsVectorIterator :
    public BI_IVectorIteratorImp<T>
{

public:

    BI_ISArrayAsVectorIterator( const BI_ISArrayAsVector<T> _FAR &a ) :
        BI_IVectorIteratorImp<T>(a.data) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_ISObjectVector                                               */
/*                                                                        */
/*  Implements a sorted vector of pointers to Object.                     */
/*  This is implemented through the template BI_ISVectorImp<Object>.      */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_ISObjectVector :
    public BI_InternalIVectorImp<Object, BI_ISVectorImp<void _FAR *> >
{

public:

    BI_ISObjectVector( unsigned sz, unsigned d = 0 ) :
        BI_InternalIVectorImp<Object, BI_ISVectorImp<void _FAR *> >(sz)
        {
        delta = d;
        }

    ~BI_ISObjectVector()
        {
        flush();
        }

    void add( Object _FAR *o );

    void addAt( Object _FAR *t, unsigned loc )
        {
        BI_InternalIVectorImp<Object, BI_ISVectorImp<void _FAR *> >::addAt(t,loc);
        }

    void detach( unsigned loc, int del = 0 )
        {
        BI_InternalIVectorImp<Object, BI_ISVectorImp<void _FAR *> >::detach( loc, del );
        }

    void detach( Object _FAR *t, int del = 0 )
        {
        unsigned loc = find( t );
        if( loc == UINT_MAX )
            return;
        BI_InternalIVectorImp<Object, BI_ISVectorImp<void _FAR *> >::detach( loc, del );
        }

    void flush( int del = 0 )
        {
        BI_InternalIVectorImp<Object, BI_ISVectorImp<void _FAR *> >::flush( del );
        }

    unsigned find( Object _FAR *t ) const
        {
        return find( (void _FAR *)t );
        }

protected:

    unsigned find( void _FAR *t ) const;

private:

    virtual void removeData( void _FAR *t )
        {
        delete (Object _FAR *)t;
        }

};

class _CLASSTYPE BI_ISObjectVectorIterator :
    public BI_IVectorIteratorImp<Object>
{

public:

    BI_ISObjectVectorIterator( const BI_ISObjectVector _FAR &a ) :
        BI_IVectorIteratorImp<Object>(a) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_ISObjectArray                                                */
/*                                                                        */
/*  Implements an indirect sorted array of pointers to Object, using a    */
/*  vector as the underlying implementation.                              */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_ISObjectArray :
    public BI_ArrayAsVectorImp<BI_ISObjectVector,Object _FAR *>,
    public virtual TShouldDelete
{

public:

    friend class _CLASSTYPE BI_ISObjectArrayIterator;

    BI_ISObjectArray( int upr, int lwr = 0, int delta = 0 ) :
        BI_ArrayAsVectorImp<BI_ISObjectVector,Object _FAR*>( upr, lwr, delta )
        {
        }

    ~BI_ISObjectArray()
        {
        flush();
        }

    Object _FAR * _FAR & operator []( int loc )
        {
        grow( loc+1 );
        return data[zeroBase(loc)];
        }

    Object _FAR * _FAR & operator []( int loc ) const
        {
        PRECONDITION( loc >= lowerbound && zeroBase(loc) < data.count() );
        return data[zeroBase(loc)];
        }

    void add( Object _FAR *t )
        {
        BI_ArrayAsVectorImp<BI_ISObjectVector,Object _FAR *>::add(t);
        }

    void addAt( Object _FAR *t, int loc )
        {
        BI_ArrayAsVectorImp<BI_ISObjectVector,Object _FAR *>::addAt(t,loc);
        }

    void detach( int loc, DeleteType dt = NoDelete )
        {
        data.detach( zeroBase(loc), delObj(dt) );
        }

    void detach( Object _FAR *t, DeleteType dt = NoDelete )
        {
        data.detach( t, delObj(dt) );
        }

    void flush( DeleteType dt = DefDelete )
        {
        data.flush( delObj(dt) );
        }

    int find( const Object *t ) const
        {
        return boundBase(data.find( (Object *)t ));
        }

    void forEach( void (_FAR*f)(Object _FAR &, void _FAR*), void _FAR*args )
        {
        if( !isEmpty() )
            data.forEach( f, args );
        }

    Object _FAR *firstThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                            void _FAR *args
                          ) const
        {
        if( isEmpty() )
            return 0;
        return data.firstThat( f, args );
        }

    Object _FAR *lastThat( int (_FAR * f)(const Object _FAR &, void _FAR *),
                           void _FAR *args
                         ) const
        {
        if( isEmpty() )
            return 0;
        return data.lastThat( f, args );
        }

};

class _CLASSTYPE BI_ISObjectArrayIterator :
    public BI_ISObjectVectorIterator
{

public:

    BI_ISObjectArrayIterator( const BI_ISObjectArray _FAR &a ) :
        BI_ISObjectVectorIterator(a.data) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_OSArrayAsVector                                              */
/*                                                                        */
/*  Implements a sorted array of pointers to Object,                      */
/*  using a vector as the underlying implementation.                      */
/*                                                                        */
/*  Although the interface is written to take pointers to Object, in      */
/*  fact, pointers to Sortable are required.                              */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_OSArrayAsVector
{

public:

    friend class _CLASSTYPE BI_OSArrayAsVectorIterator;

    BI_OSArrayAsVector() : oarray( DEFAULT_ARRAY_SIZE, 0, 0 )
        {
        }

    BI_OSArrayAsVector( int upr, int lwr = 0, unsigned delta = 0 ) :
        oarray( upr, lwr, delta )
        {
        }

    Object *operator [] (int loc)
        {
        return oarray[loc];
        }

    Object *operator [] (int loc) const
        {
        return oarray[loc];
        }

    int lowerBound() const
        {
        return oarray.lowerBound();
        }

    int upperBound() const
        {
        return oarray.upperBound();
        }

    sizeType arraySize() const
        {
        return oarray.arraySize();
        }

    void add( Object _FAR *o )
        {
        PRECONDITION( o->isSortable() );
        oarray.add(o);
        }

    void addAt( Object _FAR *o, int loc )
        {
        PRECONDITION( o->isSortable() );
        oarray.addAt(o,loc);
        }

    void detach( int loc,
                 TShouldDelete::DeleteType dt = TShouldDelete::NoDelete
               )
        {
        oarray.detach( loc, dt );
        }

    void detach( Object _FAR *o,
                 TShouldDelete::DeleteType dt = TShouldDelete::NoDelete
               )
        {
        PRECONDITION( o->isSortable() );
        oarray.detach( o, dt );
        }

    void flush( TShouldDelete::DeleteType dt = TShouldDelete::DefDelete )
        {
        oarray.flush( dt );
        }

    int hasMember( Object _FAR *o ) const
        {
        PRECONDITION( o->isSortable() );
        return oarray.hasMember(o);
        }

    Object _FAR *findMember( Object _FAR *o ) const
        {
        PRECONDITION( o->isSortable() );
        int loc = oarray.find(o);
        return loc != INT_MAX ? oarray[loc] : 0;
        }

    int isEmpty() const
        {
        return oarray.isEmpty();
        }

    int isFull() const
        {
        return oarray.isFull();
        }

    void forEach( void (_FAR*f)(Object _FAR &, void _FAR*), void _FAR*args )
        {
        oarray.forEach( f, args );
        }

    Object _FAR *firstThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                            void _FAR *args
                          ) const
        {
        return oarray.firstThat( f, args );
        }

    Object _FAR *lastThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                           void _FAR *args
                         ) const
        {
        return oarray.lastThat( f, args );
        }

    int getItemsInContainer() const
        {
        return oarray.getItemsInContainer();
        }

    int ownsElements()
        {
        return oarray.ownsElements();
        }

    void ownsElements( int del )
        {
        oarray.ownsElements( del );
        }

protected:

    BI_ISObjectArray oarray;

};

class _CLASSTYPE BI_OSArrayAsVectorIterator :
    public BI_ISObjectArrayIterator
{

public:

    BI_OSArrayAsVectorIterator( const BI_OSArrayAsVector _FAR &a ) :
        BI_ISObjectArrayIterator(a.oarray)
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_TCSArrayAsVector                                             */
/*                                                                        */
/*  Implements a sorted Object array, with the full semantics of          */
/*  the BC 2.0 style sorted array, using a vector as the underlying       */
/*  implementation.                                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_TCSArrayAsVector : public AbstractArray
{

public:

    friend class _CLASSTYPE BI_TCSArrayAsVectorIterator;

    BI_TCSArrayAsVector( int upper = DEFAULT_ARRAY_SIZE,
                         int lower = 0,
                         sizeType delta = 0
                       ) :
        array( upper, lower, delta )
        {
        }

    virtual Object& operator []( int loc )
        {
        return ptrToRef(array[loc]);
        }

    virtual Object& operator []( int loc ) const
        {
        return ptrToRef(array[loc]);
        }

    virtual int lowerBound() const
        {
        return array.lowerBound();
        }

    virtual int upperBound() const
        {
        return array.upperBound();
        }

    virtual sizeType arraySize() const
        {
        return array.arraySize();
        }

    void add( Object _FAR &o )
        {
        array.add(&o);
        }

    void addAt( Object _FAR &o, int loc )
        {
        array.addAt(&o,loc);
        }

    virtual void detach( int loc, DeleteType dt = NoDelete )
        {
        array.detach( loc, dt );
        }

    void detach( Object _FAR &o, DeleteType dt = NoDelete )
        {
        array.detach( &o, dt );
        }

    void flush( TShouldDelete::DeleteType dt = DefDelete )
        {
        array.flush( dt );
        }

    int hasMember( Object _FAR &o ) const
        {
        return array.hasMember(&o);
        }

    Object _FAR &findMember( Object _FAR &o ) const
        {
        return ptrToRef(array.findMember(&o));
        }

    int isEmpty() const
        {
        return array.isEmpty();
        }

    int isFull() const
        {
        return array.isFull();
        }

    void forEach( void (_FAR*f)(Object _FAR &, void _FAR*), void _FAR*args )
        {
        array.forEach( f, args );
        }

    Object _FAR &firstThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                            void _FAR *args
                          ) const
        {
        return ptrToRef(array.firstThat( f, args ));
        }

    Object _FAR &lastThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                           void _FAR *args
                         ) const
        {
        return ptrToRef(array.lastThat( f, args ));
        }

    int getItemsInContainer() const
        {
        return array.getItemsInContainer();
        }

    virtual classType isA() const
        {
        return sortedArrayClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "BI_TCSArrayAsVector";
        }

    int ownsElements()
        {
        return array.ownsElements();
        }

    void ownsElements( int del )
        {
        array.ownsElements( del );
        }

    ContainerIterator _FAR & initIterator() const;

private:

    BI_OSArrayAsVector array;

};

class _CLASSTYPE BI_TCSArrayAsVectorIterator : public ContainerIterator
{

public:

    BI_TCSArrayAsVectorIterator( const BI_TCSArrayAsVector _FAR &a ) :
        iter(a.array)
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

    BI_OSArrayAsVectorIterator iter;

};

inline ContainerIterator _FAR & BI_TCSArrayAsVector::initIterator() const
        {
        return *new BI_TCSArrayAsVectorIterator( *this );
        }

#pragma warn .ncf

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __ARRAYS_H

