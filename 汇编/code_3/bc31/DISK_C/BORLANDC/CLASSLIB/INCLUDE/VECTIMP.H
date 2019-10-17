/*------------------------------------------------------------------------*/
/*                                                                        */
/*  VECTIMP.H                                                             */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __VECTIMP_H )
#define __VECTIMP_H

#if !defined( __LIMITS_H )
#include <Limits.h>
#endif  // __LIMITS_H

#if !defined( __CHECKS_H )
#include <Checks.h>
#endif  // __CHECKS_H

#if !defined( __STDTEMPL_H )
#include <StdTempl.h>
#endif  // __STDTEMPL_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_VectorImp                                 */
/*                                                                        */
/*  Implements a vector of objects of type T.  Assumes that               */
/*  T has meaningful copy semantics and a default constructor.            */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_VectorImp
{

public:

    friend class _CLASSTYPE BI_VectorIteratorImp<T>;

    BI_VectorImp() :
        data(0),
        lim(0)
        {
        }

    BI_VectorImp( unsigned sz, unsigned = 0 ) :
        data( new T[sz] ),
        lim(sz)
        {
        }

    BI_VectorImp( const BI_VectorImp<T> _FAR & );

    const BI_VectorImp<T> _FAR & operator = ( const BI_VectorImp<T> _FAR & );

    ~BI_VectorImp()
        {
        delete [] data;
        }

    T _FAR & operator [] ( unsigned index ) const
        {
        PRECONDITION( lim > 0 && data != 0 && index < lim );
        return data[index];
        }

    unsigned limit() const
        {
        return lim;
        }

    virtual unsigned top() const
        {
        return lim;
        }

    void resize( unsigned, unsigned = 0 );

    void flush( unsigned = 0, unsigned = UINT_MAX, unsigned = 0 ) {}

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        forEach( f, args, 0, lim );
        }

    void forEach( void (_FAR *)(T _FAR &, void _FAR *),
                  void _FAR *,
                  unsigned,
                  unsigned
                );

    T _FAR *firstThat( int (_FAR *)(const T _FAR &, void _FAR *),
                       void _FAR *,
                       unsigned,
                       unsigned
                     ) const;

    T _FAR *firstThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        return firstThat( cond, args, 0, lim );
        }

    T _FAR *lastThat( int (_FAR *)(const T _FAR &, void _FAR *),
                      void _FAR *,
                      unsigned,
                      unsigned
                    ) const;

    T _FAR *lastThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        return lastThat( cond, args, 0, lim );
        }

    virtual unsigned getDelta() const
        {
        return 0;
        }

protected:

    T _FAR * data;
    unsigned lim;

    virtual void zero( unsigned, unsigned )
        {
        }

    virtual void removeData( T )
        {
        }

};

template <class T>
BI_VectorImp<T>::BI_VectorImp( const BI_VectorImp<T> _FAR & v ) :
    data( new T[v.lim] ),
    lim(v.lim)
{
    PRECONDITION( lim == 0 || (data != 0 && v.data != 0) );
    for( unsigned i = 0; i < lim; i++ )
        data[i] = v.data[i];
}

template <class T>
const BI_VectorImp<T> _FAR & BI_VectorImp<T>::operator = ( const BI_VectorImp<T> _FAR & v )
{
    if( data != v.data )
        {
        delete [] data;
        data = new T[v.lim];
        CHECK( data != 0 );
        lim = v.lim;
        for( unsigned i = 0; i < lim; i++ )
            data[i] = v.data[i];
        }
    return *this;
}

inline unsigned nextDelta( unsigned sz, unsigned delta )
{
    return (sz%delta) ? ((sz+delta)/delta)*delta : sz;
}

template <class T>
void BI_VectorImp<T>::resize( unsigned newSz, unsigned offset )
{
    if( newSz <= lim || getDelta() == 0 )
        return;
    unsigned sz = lim + nextDelta( newSz - lim, getDelta() );
    T _FAR *temp = new T[sz];
    unsigned last = min( sz-offset, lim );
    for( unsigned i = 0; i < last; i++ )
        temp[i+offset] = data[i];
    delete [] data;
    data = temp;
    lim = sz;
    zero( last+offset, sz );
}

template <class T>
void BI_VectorImp<T>::forEach( void (_FAR *f)( T _FAR &, void _FAR * ),
                               void _FAR *args,
                               unsigned start,
                               unsigned stop
                             )
{
    for( unsigned cur = start; cur < stop; cur++ )
        f( data[cur], args );
}

template <class T>
T _FAR *BI_VectorImp<T>::firstThat( int (_FAR *cond)( const T _FAR &, void _FAR * ),
                               void _FAR *args,
                               unsigned start,
                               unsigned stop
                             ) const
{
    for( unsigned cur = start; cur < stop; cur++ )
        if( cond( data[cur], args ) != 0 )
            return &data[cur];
    return 0;
}

template <class T>
T _FAR *BI_VectorImp<T>::lastThat( int (_FAR *cond)( const T _FAR &, void _FAR * ),
                              void _FAR *args,
                              unsigned start,
                              unsigned stop
                            ) const
{
    T _FAR *res = 0;
    for( unsigned cur = start; cur < stop; cur++ )
        if( cond( data[cur], args ) != 0 )
            res = &data[cur];
    return res;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_CVectorImp                                */
/*                                                                        */
/*  Implements a counted vector of objects of type T.  Assumes that       */
/*  T has meaningful copy semantics and a default constructor.            */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_CVectorImp : public BI_VectorImp<T>
{

public:

    BI_CVectorImp() :
        count_(0),
        delta(0)
        {
        }

    BI_CVectorImp( unsigned sz, unsigned d = 0 ) :
        BI_VectorImp<T>( sz ),
        count_(0),
        delta(d)
        {
        }

    void add( T );
    void addAt( T, unsigned );
    void detach( T, int = 0 );
    void detach( unsigned, int = 0 );

    int isEmpty() const
        {
        return count_ == 0;
        }

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        forEach( f, args, 0, count_ );
        }

    void forEach( void (_FAR *func)(T _FAR &, void _FAR *),
                  void _FAR *args,
                  unsigned low,
                  unsigned high
                )
        {
        BI_VectorImp<T>::forEach( func, args, low, high );
        }

    T _FAR *firstThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        return firstThat( cond, args, 0, count_ );
        }

    T _FAR *firstThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                       void _FAR *args,
                       unsigned low,
                       unsigned high
                     ) const
        {
        return BI_VectorImp<T>::firstThat( cond, args, low, high );
        }

    T _FAR *lastThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        return lastThat( cond, args, 0, count_ );
        }

    T _FAR *lastThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                      void _FAR *args,
                      unsigned low,
                      unsigned high
                    ) const
        {
        return BI_VectorImp<T>::lastThat( cond, args, low, high );
        }

    void flush( unsigned del = 0,
                unsigned stop = UINT_MAX,
                unsigned start = 0
              )
        {
        BI_VectorImp<T>::flush( del, stop, start ); count_ = 0;
        }

    virtual unsigned find( T ) const;

    virtual unsigned top() const
        {
        return count_;
        }

    unsigned count() const
        {
        return count_;
        }

    virtual unsigned getDelta() const
        {
        return delta;
        }

protected:

    unsigned count_;
    unsigned delta;

};

template <class T> void BI_CVectorImp<T>::add( T t )
{
    if( ++count_ > lim )
        resize( count_ );
    data[count_-1] = t;
}

template <class T> void BI_CVectorImp<T>::addAt( T t, unsigned loc )
{
    if( loc >= lim )
        resize( loc+1 );
    data[loc] = t;
}

template <class T> void BI_CVectorImp<T>::detach( T t, int del )
{
    detach( find(t), del );
}

template <class T> void BI_CVectorImp<T>::detach( unsigned loc, int del )
{
    if( loc >= lim )
        return;
    if( del )
        removeData( data[loc] );
    if( loc >= count_ )
        {
        zero( loc, loc+1 ); // removing an element that's not
        return;             // in the counted portion
        }
    count_--;
    for( unsigned cur = loc; cur < count_; cur++ )
        data[cur] = data[cur+1];
    zero( count_, count_+1 );
}

template <class T> unsigned BI_CVectorImp<T>::find( T t ) const
{
    if( count_ != 0 )
        {
        for( unsigned loc = 0; loc < count_; loc++ )
            if( data[loc] == t )
                return loc;
        }
    return UINT_MAX;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_SVectorImp                                */
/*                                                                        */
/*  Implements a sorted vector of objects of type T.  Assumes that        */
/*  T has meaningful copy semantics, a meaningful < operator,             */
/*  and a default constructor.                                            */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_SVectorImp : public BI_CVectorImp<T>
{

public:

    BI_SVectorImp()
        {
        }

    BI_SVectorImp( unsigned sz, unsigned d = 0 ) :
        BI_CVectorImp<T>( sz, d )
        {
        }

    void add( T );

    virtual unsigned find( T ) const;

};

template <class T> void BI_SVectorImp<T>::add( T t )
{
    unsigned loc = count_++;
    if( count_ > lim )
        resize( count_ );
    while( loc > 0 && t < data[loc-1] )
        {
        data[loc] = data[loc-1];
        loc--;
        }
    data[loc] = t;
}

template <class T> unsigned BI_SVectorImp<T>::find( T t ) const
{
    unsigned lower = 0;
    unsigned upper = count_-1;
    if( count_ != 0 )
        {
        while( lower < upper && upper != UINT_MAX )
            {
            unsigned middle = (lower+upper)/2;
            if( data[middle] == t )
                return middle;
            if( data[middle] < t )
                lower = middle+1;
            else
                upper = middle-1;
            }
        }
    if( lower == upper && data[lower] == t )
        return lower;
    else
        return UINT_MAX;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_VectorIteratorImp                         */
/*                                                                        */
/*  Implements a vector iterator.  This iterator works with any direct    */
/*  vector.  For indirect vectors, see BI_IVectorIteratorImp.             */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_VectorIteratorImp
{

public:

    BI_VectorIteratorImp( const BI_VectorImp<T> _FAR &v )
        {
        vect = &v;
        restart(0,v.limit());
        }

    BI_VectorIteratorImp( const BI_VectorImp<T> _FAR &v,
                          unsigned start,
                          unsigned stop
                        )
        {
        vect = &v;
        restart( start, stop );
        }


    operator int()
        {
        return cur < upper;
        }

    T current()
        {
        return (cur < upper) ? (*vect)[cur] : (*vect)[upper-1];
        }

    T operator ++ ( int )
        {
        if( cur >= upper )
            return (*vect)[upper-1];
        else
            return (*vect)[cur++];
        }

    T operator ++ ()
        {
        if( cur < upper )
            cur++;
        if( cur >= upper )
            return (*vect)[upper-1];
        else
            return (*vect)[cur];
        }

    void restart()
        {
        restart(lower,upper);
        }

    void restart( unsigned start, unsigned stop )
        {
        cur = lower = start;
        upper = stop;
        }

private:

    const BI_VectorImp<T> _FAR *vect;
    unsigned cur;
    unsigned lower, upper;

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T, class Vect> class BI_InternalIVectorImp            */
/*                                                                        */
/*  Implements a vector of pointers to objects of type T.                 */
/*  This is implemented through the form of BI_VectorImp specified by     */
/*  Vect.  Since pointers always have meaningful copy semantics,          */
/*  this class can handle any type of object.                             */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T, class Vect> class _CLASSTYPE BI_InternalIVectorImp :
    public Vect
{

public:

    BI_InternalIVectorImp( unsigned sz, unsigned d = 0 ) :
        Vect( sz, d )
        {
        zero( 0, sz );
        }

    ~BI_InternalIVectorImp()
        {
        flush();
        }

    T _FAR * _FAR & operator [] ( unsigned index )
        {
        PRECONDITION( lim == 0 || data != 0 && index < lim );
        return (T _FAR *)(data[index]);
        }

    T _FAR * _FAR & operator [] ( unsigned index ) const
        {
        PRECONDITION( lim > 0 && data != 0 && index < lim );
        return (T _FAR *)(data[index]);
        }

    void flush( unsigned = 0, unsigned = UINT_MAX, unsigned = 0 );

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        forEach( f, args, 0, lim );
        }

    void forEach( void (_FAR *)(T _FAR &, void _FAR *),
                  void _FAR *,
                  unsigned,
                  unsigned
                );

    T _FAR *firstThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        return firstThat( cond, args, 0, lim );
        }

    T _FAR *firstThat( int (_FAR *)(const T _FAR &, void _FAR *),
                       void _FAR *,
                       unsigned,
                       unsigned
                     ) const;

    T _FAR *lastThat( int (_FAR *cond)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        return lastThat( cond, args, 0, lim );
        }

    T _FAR *lastThat( int (_FAR *)(const T _FAR &, void _FAR *),
                      void _FAR *,
                      unsigned,
                      unsigned
                    ) const;

    virtual void zero( unsigned, unsigned );

protected:

    virtual void removeData( void _FAR *t )
        {
        delete (T _FAR *)t;
        }

private:

    static void delObj( T _FAR &, void _FAR * );

};

template <class T, class Vect>
void BI_InternalIVectorImp<T,Vect>::delObj( T _FAR &tRef, void _FAR *vect )
{
    ((BI_InternalIVectorImp<T,Vect> *)vect)->removeData( &tRef );
}

template <class T, class Vect>
void BI_InternalIVectorImp<T,Vect>::flush(
                                           unsigned del,
                                           unsigned upr,
                                           unsigned lwr
                                         )
{
    upr = min( upr, limit() );
    if( del )
        forEach( delObj, this, lwr, upr );
    zero( lwr, upr );
    Vect::flush( del, upr, lwr );
}

template <class T, class Vect>
void BI_InternalIVectorImp<T,Vect>::forEach( void (_FAR *f)( T _FAR &, void _FAR * ),
                                             void _FAR *args,
                                             unsigned start,
                                             unsigned stop
                                           )
{
    for( unsigned cur = start; cur < stop; cur++ )
        if( data[cur] != 0 )
            f( *(T _FAR *)(data[cur]), args );
}

template <class T, class Vect>
T _FAR *BI_InternalIVectorImp<T,Vect>::firstThat( int (_FAR *cond)( const T _FAR &, void _FAR * ),
                                             void _FAR *args,
                                             unsigned start,
                                             unsigned stop
                                           ) const
{
    for( unsigned cur = start; cur < stop; cur++ )
        if( data[cur] != 0 && cond( *(T _FAR *)(data[cur]), args ) != 0 )
            return (T _FAR *)data[cur];
    return 0;
}

template <class T, class Vect>
T _FAR *BI_InternalIVectorImp<T,Vect>::lastThat( int (_FAR *cond)( const T _FAR &, void _FAR * ),
                                            void _FAR *args,
                                            unsigned start,
                                            unsigned stop
                                          ) const
{
    T _FAR *res = 0;
    for( unsigned cur = start; cur < stop; cur++ )
        if( data[cur] != 0 && cond( *(T _FAR *)(data[cur]), args ) != 0 )
            res = (T _FAR *)data[cur];
    return res;
}

template <class T, class Vect>
void BI_InternalIVectorImp<T,Vect>::zero( unsigned lwr, unsigned upr )
{
    for( unsigned i = lwr; i < min( limit(), upr ); i++ )
        data[i] = 0;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IVectorImp                                */
/*                                                                        */
/*  Implements a vector of pointers to objects of type T.                 */
/*  This is implemented through the template BI_InternalIVectorImp.       */
/*  Since pointers always have meaningful copy semantics, this class      */
/*  can handle any type of object.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_IVectorImp :
    public BI_InternalIVectorImp<T, BI_VectorImp<void _FAR *> >
{

public:

    BI_IVectorImp( unsigned sz ) :
        BI_InternalIVectorImp<T, BI_VectorImp<void _FAR *> >(sz)
        {
        }


};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_ICVectorImp                               */
/*                                                                        */
/*  Implements a counted vector of pointers to objects of type T.         */
/*  Since pointers always have meaningful copy semantics, this class      */
/*  can handle any type of object.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_ICVectorImp :
    public BI_InternalIVectorImp<T, BI_CVectorImp<void _FAR *> >
{

public:

    BI_ICVectorImp( unsigned sz, unsigned d = 0 ) :
        BI_InternalIVectorImp<T, BI_CVectorImp<void _FAR *> >(sz)
        {
        delta = d;
        }

    unsigned find( T _FAR *t ) const
        {
        return find( (void _FAR *)t );
        }

    void add( T _FAR *t );

protected:

    virtual unsigned find( void _FAR * ) const;

};

template <class T> unsigned BI_ICVectorImp<T>::find( void _FAR *t ) const
{
    if( limit() != 0 )
        {
        for( unsigned loc = 0; loc < limit(); loc++ )
            if( data[loc] &&
                *(const T _FAR *)(data[loc]) == *(const T _FAR *)t
              )
                return loc;
        }
    return UINT_MAX;
}

template <class T > void BI_ICVectorImp<T>::add( T _FAR *t )
{
    while( count_ < limit() && (*this)[count_] != 0 )
        count_++;
    BI_InternalIVectorImp<T, BI_CVectorImp<void _FAR *> >::add(t);
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_ISVectorImp                               */
/*                                                                        */
/*  Implements a sorted vector of pointers to objects of type T.          */
/*  This is implemented through the template BI_InternalIVectorImp.       */
/*  Since pointers always have meaningful copy semantics, this class      */
/*  can handle any type of object.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_ISVectorImp :
    public BI_InternalIVectorImp<T, BI_SVectorImp<void _FAR *> >
{

public:

    BI_ISVectorImp( unsigned sz, unsigned d = 0 ) :
        BI_InternalIVectorImp<T, BI_SVectorImp<void _FAR *> >(sz)
        {
        delta = d;
        }

    unsigned find( T _FAR *t ) const
        {
        return find( (void _FAR *)t );
        }

    void add( T _FAR *t );

protected:

    virtual unsigned find( void _FAR * ) const;

};

template <class T> unsigned BI_ISVectorImp<T>::find( void _FAR *t ) const
{
    unsigned lower = 0;
    unsigned upper = count_-1;
    if( count_ != 0 )
        {
        while( lower < upper )
            {
            unsigned middle = (lower+upper)/2;
            if( *(const T _FAR *)(data[middle]) == *(const T _FAR *)t )
                return middle;
            if( *(const T _FAR *)(data[middle]) < *(const T _FAR *)t )
                lower = middle+1;
            else
                upper = middle-1;
            }
        }
    if( lower == upper && *(const T _FAR*)(data[lower]) == *(const T _FAR*)t )
        return lower;
    else
        return UINT_MAX;
}

template <class T> void BI_ISVectorImp<T>::add( T _FAR *t )
{
    unsigned loc = count_++;
    if( count_ > lim )
        resize( count_ );
    while( loc > 0 && *t < *((T _FAR *)(*this)[loc-1]) )
        {
        data[loc] = data[loc-1];
        loc--;
        }
    data[loc] = t;
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IVectorIteratorImp                        */
/*                                                                        */
/*  Implements a vector iterator.  This iterator works with any indirect  */
/*  vector.  For direct vectors, see BI_VectorIteratorImp.                */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_IVectorIteratorImp :
    public BI_VectorIteratorImp<void _FAR *>
{

public:

    BI_IVectorIteratorImp( const BI_VectorImp<void _FAR *> _FAR &v ) :
        BI_VectorIteratorImp<void _FAR *>(v)
        {
        bump();
        }

    BI_IVectorIteratorImp( const BI_VectorImp<void _FAR *> _FAR &v,
                           unsigned l, unsigned u
                         ) :
        BI_VectorIteratorImp<void _FAR *>(v,l,u)
        {
        bump();
        }

    T _FAR *current()
        {
        return (T _FAR *)BI_VectorIteratorImp<void _FAR *>::current();
        }

    T _FAR *operator ++ ( int );
    T _FAR *operator ++ ();

    void restart()
        {
        BI_VectorIteratorImp<void _FAR *>::restart();
        bump();
        }

    void restart( unsigned start, unsigned stop )
        {
        BI_VectorIteratorImp<void _FAR *>::restart( start, stop );
        bump();
        }

private:

    void bump();

};

template <class T> T _FAR * BI_IVectorIteratorImp<T>::operator ++ ()
{
    BI_VectorIteratorImp<void _FAR *>::operator++();
    bump();
    return (T _FAR *)current();
}

template <class T> T _FAR * BI_IVectorIteratorImp<T>::operator ++ ( int )
{
    void *temp = current();
    BI_VectorIteratorImp<void _FAR *>::operator++(1);
    bump();
    return (T _FAR *)temp;
}

template <class T> void BI_IVectorIteratorImp<T>::bump()
{
    while( *this != 0 && current() == 0 )
        BI_VectorIteratorImp<void _FAR *>::operator++();
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif // __VECTIMP_H
