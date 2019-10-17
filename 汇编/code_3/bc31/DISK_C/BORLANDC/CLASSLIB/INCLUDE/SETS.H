/*------------------------------------------------------------------------*/
/*                                                                        */
/*  SETS.H                                                                */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __SETS_H )
#define __SETS_H

#if !defined( __CHECKS_H )
#include <Checks.h>
#endif  // __CHECKS_H

#if !defined( __RESOURCE_H )
#include <Resource.h>
#endif  // __RESOURCE_H

#if !defined( __BAGS_H )
#include <Bags.h>
#endif  // __BAGS_H

#if !defined( __COLLECT_H )
#include <Collect.h>
#endif  // __COLLECT_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_SetAsVector                               */
/*                                                                        */
/*  Implements a set of objects of type T, using a vector as              */
/*  the underlying implementation.                                        */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_SetAsVector : public BI_BagAsVector<T>
{

public:

    BI_SetAsVector( unsigned sz = DEFAULT_SET_SIZE ) :
        BI_BagAsVector<T>(sz)
        {
        }

    void add( T );

};

template <class T> void BI_SetAsVector<T>::add( T t )
{
    if( hasMember(t) )
        return;
    else
        BI_BagAsVector<T>::add(t);
}

template <class T> class BI_SetAsVectorIterator :
    public BI_BagAsVectorIterator<T>
{

public:

    BI_SetAsVectorIterator<T>( const BI_SetAsVector _FAR &s ) :
        BI_BagAsVectorIterator<T>(s) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  template <class T> class BI_ISetAsVector                              */
/*                                                                        */
/*  Implements a set of pointers to objects of type T,                    */
/*  using a vector as the underlying implementation.                      */
/*                                                                        */
/*------------------------------------------------------------------------*/

template <class T> class _CLASSTYPE BI_ISetAsVector :
    public BI_IBagAsVector<T>
{

public:

    BI_ISetAsVector( unsigned sz = DEFAULT_SET_SIZE ) :
        BI_IBagAsVector<T>(sz)
        {
        }

    void add( T _FAR * );

};

template <class T> void BI_ISetAsVector<T>::add( T _FAR *t )
{
    if( hasMember(t) )
        return;
    else
        BI_IBagAsVector<T>::add(t);
}

template <class T> class _CLASSTYPE BI_ISetAsVectorIterator :
    public BI_IBagAsVectorIterator<T>
{

public:

    BI_ISetAsVectorIterator( const BI_ISetAsVector<T> _FAR &s ) :
        BI_IBagAsVectorIterator<T>(s) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_OSetAsVector                                                 */
/*                                                                        */
/*  Implements a set of pointers to Object,                               */
/*  using a vector as the underlying implementation.                      */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_OSetAsVector : public BI_OBagAsVector
{

public:

    BI_OSetAsVector( unsigned sz = DEFAULT_SET_SIZE ) :
        BI_OBagAsVector(sz)
        {
        }

    void add( Object _FAR *o )
        {
        if( !hasMember(o) )
            BI_OBagAsVector::add(o);
        }


};

class BI_OSetAsVectorIterator : public BI_OBagAsVectorIterator
{

public:

    BI_OSetAsVectorIterator( const BI_OSetAsVector _FAR &s ) :
        BI_OBagAsVectorIterator(s) {}

};

/*------------------------------------------------------------------------*/
/*                                                                        */
/*  class BI_TCSetAsVector                                                */
/*                                                                        */
/*  Implements an Object set, with the full semantics of                  */
/*  the BC 2.0 style Set, using a vector as the underlying                */
/*  implementation.                                                       */
/*                                                                        */
/*------------------------------------------------------------------------*/

class _CLASSTYPE BI_TCSetAsVector : public BI_TCBagAsVector
{

public:

    BI_TCSetAsVector( unsigned sz = DEFAULT_SET_SIZE ) :
        BI_TCBagAsVector(sz)
        {
        }

    virtual void add( Object _FAR &o )
        {
        if( !hasMember(o) )
            BI_TCBagAsVector::add(o);
        }

    virtual classType isA() const
        {
        return setClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "BI_TCSetAsVector";
        }

    virtual ContainerIterator _FAR & BI_TCSetAsVector::initIterator() const;

};

class BI_TCSetAsVectorIterator : public BI_TCBagAsVectorIterator
{

public:

    BI_TCSetAsVectorIterator( const BI_TCSetAsVector _FAR &s ) :
        BI_TCBagAsVectorIterator(s)
        {
        }

};

inline ContainerIterator _FAR & BI_TCSetAsVector::initIterator() const
{
    return *new BI_TCSetAsVectorIterator( *this );
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __SETS_H

