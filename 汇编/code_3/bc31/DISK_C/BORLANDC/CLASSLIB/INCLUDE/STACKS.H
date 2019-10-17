/*------------------------------------------------------------------------*/
/*                                                                        */
/*  STACKS.H                                                              */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __STACKS_H )
#define __STACKS_H

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

#if !defined( __LISTIMP_H )
#include <ListImp.h>
#endif  // __LISTIMP_H

#if !defined( __CONTAIN_H )
#include <Contain.h>
#endif  // __CONTAIN_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class Vect, class T> class BI_StackAsVectorImp              */
/*                                                                        */
/*  Implements the fundamental stack operations, using a vector           */
/*  as the underlying implementation.  The type Vect specifies the        */
/*  form of the vector, either a BI_VectorImp<T0> or a                    */
/*  BI_IVectorImp<T0>.  The type T specifies the type of the              */
/*  objects to be put on the stack.  When using BI_VectorImp<T0>,         */
/*  T should be the same as T0. When using BI_IVectorImp<T0>, T           */
/*  should be of type pointer to T0.  See BI_StackAsVector and            */
/*  BI_IStackAsVector for examples.                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class Vect, class T> class _CLASSTYPE BI_StackAsVectorImp
{

public:

    BI_StackAsVectorImp( unsigned max = DEFAULT_STACK_SIZE ) :
        data(max),
        current(0)
        {
        }

    void push( T t )
        {
        PRECONDITION( current < data.limit() );
        data[current++] = t;
        }

    T pop()
        {
        PRECONDITION( current > 0 );
        return data[--current];
        }

    T top() const
        {
        PRECONDITION( current > 0 );
        return data[current-1];
        }

    int isEmpty() const
        {
        return current == 0;
        }

    int isFull() const
        {
        return current == data.limit();
        }

    int getItemsInContainer() const
        {
        return current;
        }

    void flush( TShouldDelete::DeleteType = TShouldDelete::DefDelete )
        {
        current = 0;
        }

protected:

    Vect data;
    unsigned current;

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_StackAsVector                             */
/*                                                                        */
/*  Implements a stack of objects of type T, using a vector as            */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_StackAsVector :
    public BI_StackAsVectorImp<BI_VectorImp<T>,T>
{

public:

    friend class _CLASSTYPE BI_StackAsVectorIterator<T>;

    BI_StackAsVector( unsigned max = DEFAULT_STACK_SIZE ) :
        BI_StackAsVectorImp<BI_VectorImp<T>,T>( max )
        {
        }

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        if( !isEmpty() )
            data.forEach( f, args, 0, current );
        }

    T _FAR *firstThat( int (_FAR *f)(const T _FAR &, void _FAR *),
                       void _FAR *args
                     ) const
        {
        if( isEmpty() )
            return 0;
        return data.firstThat( f, args, 0, current );
        }

    T _FAR *lastThat( int (_FAR * f)(const T _FAR &, void _FAR *),
                      void _FAR *args
                    ) const
        {
        if( isEmpty() )
            return 0;
        return data.lastThat( f, args, 0, current );
        }

};

template <class T> class _CLASSTYPE BI_StackAsVectorIterator :
    public BI_VectorIteratorImp<T>
{

public:

    BI_StackAsVectorIterator( const BI_StackAsVector<T> _FAR & s ) :
        BI_VectorIteratorImp<T>(s.data,0,s.current)
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IStackAsVector                            */
/*                                                                        */
/*  Implements a stack of pointers to objects of type T,                  */
/*  using a vector as the underlying implementation.                      */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_IStackAsVector :
    public BI_StackAsVectorImp<BI_IVectorImp<T>, T _FAR * >,
    public virtual TShouldDelete
{

public:

    friend class _CLASSTYPE BI_IStackAsVectorIterator<T>;

    BI_IStackAsVector( unsigned max = DEFAULT_STACK_SIZE ) :
        BI_StackAsVectorImp<BI_IVectorImp<T>,T _FAR *>( max )
        {
        }

    ~BI_IStackAsVector()
        {
        flush();
        }

    void push( T _FAR *t )
        {
        BI_StackAsVectorImp<BI_IVectorImp<T>,T _FAR *>::push( t );
        }

    T _FAR *pop()

        {
        return (T _FAR *)BI_StackAsVectorImp<BI_IVectorImp<T>,T _FAR *>::pop();
        }

    T _FAR *top() const
        {
        return (T _FAR *)BI_StackAsVectorImp<BI_IVectorImp<T>,T _FAR *>::top();
        }

    void forEach( void (_FAR *f)(T _FAR &, void _FAR *), void _FAR *args )
        {
        if( !isEmpty() )
            data.forEach( f, args, 0, current );
        }

    T _FAR *firstThat( int (_FAR *f)(const T _FAR &, void _FAR *), void _FAR *args ) const
        {
        if( isEmpty() )
            return 0;
        return data.firstThat( f, args, 0, current );
        }

    T _FAR *lastThat( int (_FAR *f)(const T _FAR &, void _FAR *), void _FAR *args ) const
        {
        if( isEmpty() )
            return 0;
        return data.lastThat( f, args, 0, current );
        }

    void flush( DeleteType dt = DefDelete )
        {
        data.flush( delObj(dt), current );
        BI_StackAsVectorImp<BI_IVectorImp<T>,T _FAR *>::flush();
        }

};

template <class T> class _CLASSTYPE BI_IStackAsVectorIterator :
    public BI_IVectorIteratorImp<T>
{

public:

    BI_IStackAsVectorIterator( const BI_IStackAsVector<T> _FAR & s ) :
        BI_IVectorIteratorImp<T>(s.data,0,s.current)
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_OStackAsVector                                               */
/*                                                                        */
/*  Implements a stack of pointers to Object,                             */
/*  using a vector as the underlying implementation.                      */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_OStackAsVector : private BI_IStackAsVector<Object>
{

public:

    friend class _CLASSTYPE BI_OStackAsVectorIterator;

    BI_OStackAsVector( unsigned max = DEFAULT_STACK_SIZE ) :
        BI_IStackAsVector<Object>( max )
        {
        }


    void push( Object _FAR *t )
        {
        BI_IStackAsVector<Object>::push( t );
        }

    Object _FAR *pop()
        {
        return (Object _FAR *)(BI_IStackAsVector<Object>::pop());
        }

    Object _FAR *top() const
        {
        return (Object _FAR *)(BI_IStackAsVector<Object>::top());
        }

    int isEmpty() const
        {
        return BI_IStackAsVector<Object>::isEmpty();
        }

    int isFull() const
        {
        return BI_IStackAsVector<Object>::isFull();
        }

    void forEach( void (_FAR*f)(Object _FAR &, void _FAR*), void _FAR*args )
        {
        BI_IStackAsVector<Object>::forEach( f, args );
        }

    Object _FAR *firstThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                            void _FAR *args
                          ) const
        {
        return BI_IStackAsVector<Object>::firstThat( f, args );
        }

    Object _FAR *lastThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                           void _FAR *args
                         ) const
        {
        return BI_IStackAsVector<Object>::lastThat( f, args );
        }

    void flush( TShouldDelete::DeleteType dt )
        {
        BI_IStackAsVector<Object>::flush( dt );
        }

    int getItemsInContainer() const
        {
        return BI_IStackAsVector<Object>::getItemsInContainer();
        }

};

class _CLASSTYPE BI_OStackAsVectorIterator :
    public BI_IStackAsVectorIterator<Object>
{

public:

    BI_OStackAsVectorIterator( const BI_OStackAsVector _FAR & s ) :
        BI_IStackAsVectorIterator<Object>((const BI_IStackAsVector<Object>&)s)
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_TCStackAsVector                                              */
/*                                                                        */
/*  Implements an Object stack, with the full semantics of                */
/*  the BC 2.0 style stack, using a vector as the underlying              */
/*  implementation.                                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_TCStackAsVector : 
    public Container, 
    private BI_OStackAsVector
{

public:

    friend class _CLASSTYPE BI_TCStackAsVectorIterator;

    BI_TCStackAsVector( unsigned lim = DEFAULT_STACK_SIZE ) :
        BI_OStackAsVector(lim)
        {
        }

    void push( Object _FAR & o )
        {
        BI_OStackAsVector::push( &o );
        }

    Object _FAR & pop()
        {
        return ptrToRef(BI_OStackAsVector::pop());
        }

    Object _FAR & top() const
        {
        return ptrToRef(BI_OStackAsVector::top());
        }

    virtual int isEmpty() const
        {
        return BI_OStackAsVector::isEmpty();
        }

    virtual countType getItemsInContainer() const
        {
        return BI_OStackAsVector::getItemsInContainer();
        }

    virtual void flush( DeleteType dt = DefDelete )
        {
        BI_OStackAsVector::flush( dt );
        }

    virtual ContainerIterator _FAR & initIterator() const;

    virtual classType isA() const
        {
        return stackClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "BI_TCStackAsVector";
        }

    virtual void forEach( iterFuncType f, void _FAR *args )
        {
        BI_OStackAsVector::forEach( f, args );
        }

    virtual Object _FAR & firstThat( condFuncType f, void _FAR *args ) const
        {
        return ptrToRef(BI_OStackAsVector::firstThat( f, args ));
        }

    virtual Object _FAR & lastThat( condFuncType f, void _FAR *args ) const
        {
        return ptrToRef(BI_OStackAsVector::lastThat( f, args ));
        }

};

class _CLASSTYPE BI_TCStackAsVectorIterator : public ContainerIterator
{

public:

    BI_TCStackAsVectorIterator( const BI_TCStackAsVector _FAR & s ) :
        iter((const BI_OStackAsVector&)s)
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

    BI_OStackAsVectorIterator iter;

};

inline ContainerIterator _FAR & BI_TCStackAsVector::initIterator() const
{
    return *new BI_TCStackAsVectorIterator( *this );
}

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class Stk, class T> class BI_StackAsListImp                 */
/*                                                                        */
/*  Implements the fundamental stack operations, using a stack            */
/*  as the underlying implementation.  The type Stk specifies the         */
/*  form of the stack, either a BI_StackImp<T0> or a                      */
/*  BI_IStackImp<T0>.  The type T specifies the type of the               */
/*  objects to be put on the stack.  When using BI_StackImp<T0>,          */
/*  T should be the same as T0. When using BI_IStackImp<T0>, T            */
/*  should be of type pointer to T0.  See BI_StackAsList and              */
/*  BI_IStackAsList for examples.                                         */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class Stk, class T> class _CLASSTYPE BI_StackAsListImp
{

public:

    BI_StackAsListImp() :
        itemsInContainer(0)
        {
        }

    void push( T t )
        {
        data.add( t );
        itemsInContainer++;
        }

    T pop()
        {
        T t = top();
        data.detach( t, 0 );
        itemsInContainer--;
        return t;
        }

    T top() const
        {
        PRECONDITION( !data.isEmpty() );
        return data.peekHead();
        }

    int isEmpty() const
        {
        return data.isEmpty();
        }

    int isFull() const
        {
        return 0;
        }

    void flush( TShouldDelete::DeleteType = TShouldDelete::DefDelete )
        {
        data.flush( 0 );
        itemsInContainer = 0;
        }

    int getItemsInContainer() const
        {
        return itemsInContainer;
        }

protected:

    Stk data;
    int itemsInContainer;

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_StackAsList                               */
/*                                                                        */
/*  Implements a stack of objects of type T, using a list as              */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_StackAsList :
    public BI_StackAsListImp<BI_ListImp<T>,T>
{

public:

    friend class _CLASSTYPE BI_StackAsListIterator<T>;

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

template <class T> class _CLASSTYPE BI_StackAsListIterator :
    public BI_ListIteratorImp<T>
{

public:

    BI_StackAsListIterator( const BI_StackAsList<T> _FAR & s ) :
        BI_ListIteratorImp<T>(s.data)
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_IStackAsList                              */
/*                                                                        */
/*  Implements a stack of pointers to objects of type T,                  */
/*  using a linked list as the underlying implementation.                 */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_IStackAsList :
    public BI_StackAsListImp<BI_IListImp<T>,T _FAR *>,
    public virtual TShouldDelete
{

public:

    friend class _CLASSTYPE BI_IStackAsListIterator<T>;

    ~BI_IStackAsList()
        {
        flush();
        }

    void push( T _FAR *t )
        {
        BI_StackAsListImp<BI_IListImp<T>,T _FAR *>::push( t );
        }

    T _FAR *pop()
        {
        return (T _FAR *)BI_StackAsListImp<BI_IListImp<T>,T _FAR *>::pop();
        }

    T _FAR *top() const
        {
        return (T _FAR *)BI_StackAsListImp<BI_IListImp<T>,T _FAR *>::top();
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

    void flush( DeleteType dt = DefDelete )
        { data.flush( delObj(dt) ); }
};

template <class T> class _CLASSTYPE BI_IStackAsListIterator :
    public BI_IListIteratorImp<T>
{

public:

    BI_IStackAsListIterator( const BI_IStackAsList<T> _FAR & s ) :
        BI_IListIteratorImp<T>(s.data)
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_OStackAsList                                                 */
/*                                                                        */
/*  Implements a stack of pointers to Object,                             */
/*  using a list as the underlying implementation.                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_OStackAsList : private BI_IStackAsList<Object>
{

public:

    friend class _CLASSTYPE BI_OStackAsListIterator;

    void push( Object _FAR *t )
        {
        BI_IStackAsList<Object>::push( t );
        }

    Object _FAR *pop()
        {
        return (Object _FAR *)(BI_IStackAsList<Object>::pop());
        }

    Object _FAR *top() const
        {
        return (Object _FAR *)(BI_IStackAsList<Object>::top());
        }

    int isEmpty() const
        {
        return BI_IStackAsList<Object>::isEmpty();
        }

    int isFull() const
        {
        return BI_IStackAsList<Object>::isFull();
        }

    void forEach( void (_FAR*f)(Object _FAR &, void _FAR*), void _FAR*args )
        {
        BI_IStackAsList<Object>::forEach( f, args );
        }

    Object _FAR *firstThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                            void _FAR *args
                          ) const
        {
        return BI_IStackAsList<Object>::firstThat( f, args );
        }

    Object _FAR *lastThat( int (_FAR *f)(const Object _FAR &, void _FAR *),
                           void _FAR *args
                         ) const
        {
        return BI_IStackAsList<Object>::lastThat( f, args );
        }

    void flush( TShouldDelete::DeleteType dt = TShouldDelete::DefDelete )
        {
        BI_IStackAsList<Object>::flush( dt );
        }

    int getItemsInContainer() const
        {
        return BI_IStackAsList<Object>::getItemsInContainer();
        }

};

class _CLASSTYPE BI_OStackAsListIterator :
    public BI_IStackAsListIterator<Object>
{

public:

    BI_OStackAsListIterator( const BI_OStackAsList _FAR & s ) :
        BI_IStackAsListIterator<Object>((const BI_IStackAsList<Object>&)s)
        {
        }

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_TCStackAsList                                                */
/*                                                                        */
/*  Implements an Object stack, with the full semantics of                */
/*  the BC 2.0 style stack, using a list as the underlying                */
/*  implementation.                                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_TCStackAsList : public Container, private BI_OStackAsList
{

public:

    friend class _CLASSTYPE BI_TCStackAsListIterator;

    void push( Object _FAR & o )
        {
        BI_OStackAsList::push( &o );
        }

    Object _FAR & pop()
        {
        return ptrToRef(BI_OStackAsList::pop());
        }

    Object _FAR & top() const
        {
        return ptrToRef(BI_OStackAsList::top());
        }

    virtual int isEmpty() const
        {
        return BI_OStackAsList::isEmpty();
        }

    virtual countType getItemsInContainer() const
        {
        return BI_OStackAsList::getItemsInContainer();
        }

    virtual void flush( DeleteType dt = DefDelete )
        {
        BI_OStackAsList::flush( dt );
        }

    virtual ContainerIterator _FAR & initIterator() const;

    virtual classType isA() const
        {
        return stackClass;
        }

    virtual char _FAR * nameOf() const
        {
        return "BI_TCStackAsList";
        }

    virtual void forEach( iterFuncType f, void _FAR *args )
        {
        BI_OStackAsList::forEach( f, args );
        }

    virtual Object _FAR & firstThat( condFuncType f, void _FAR *args ) const
        {
        return ptrToRef(BI_OStackAsList::firstThat( f, args ));
        }

    virtual Object _FAR & lastThat( condFuncType f, void _FAR *args ) const
        {
        return ptrToRef(BI_OStackAsList::lastThat( f, args ));
        }

};

class _CLASSTYPE BI_TCStackAsListIterator : public ContainerIterator
{

public:

    BI_TCStackAsListIterator( const BI_TCStackAsList _FAR & s ) :
        iter((const BI_OStackAsList&)s)
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

    BI_OStackAsListIterator iter;

};

inline ContainerIterator _FAR & BI_TCStackAsList::initIterator() const
{
    return *new BI_TCStackAsListIterator( *this );
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __STACKS_H

