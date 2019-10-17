/*------------------------------------------------------------------------*/
/*                                                                        */
/*  OBJECT.H                                                              */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __OBJECT_H )
#define __OBJECT_H

#if !defined( __CLSTYPES_H )
#include <ClsTypes.h>
#endif  // __CLSTYPES_H

#if !defined( __CLSDEFS_H )
#include <ClsDefs.h>
#endif  // __CLSDEFS_H

#if !defined( __STDDEF_H )
#include <StdDef.h>
#endif  // __STDDEF_H

#if !defined( __IOSTREAM_H )
#include <iostream.h>
#endif  // __IOSTREAM_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

_CLASSDEF(Object)
_CLASSDEF(Error)

class _CLASSTYPE Object
{

public:

    virtual ~Object()
        {
        }

    virtual classType isA() const = 0;
    virtual char _FAR *nameOf() const = 0;
    virtual hashValueType hashValue() const = 0;
    virtual int isEqual( const Object _FAR & ) const = 0;

    virtual int isSortable() const
        {
        return 0;
        }

    virtual int isAssociation() const
        {
        return 0;
        }

    virtual void forEach( iterFuncType, void _FAR * );
    virtual Object _FAR & firstThat( condFuncType, void _FAR * ) const;
    virtual Object _FAR & lastThat( condFuncType, void _FAR * ) const;
    virtual void printOn( ostream _FAR & ) const = 0;

    static Object _FAR *ZERO;

    static Object _FAR & ptrToRef( Object _FAR *p )
        { return p == 0 ? *ZERO : *p; }

    static const Object _FAR & ptrToRef( const Object _FAR *p )
        { return p == 0 ? *ZERO : *p; }

    friend ostream _FAR& operator << ( ostream _FAR&, const Object _FAR& );

};

#define NOOBJECT  (*(Object::ZERO))

inline void Object::forEach( iterFuncType func, void _FAR *args )
{
    ( *func )( *this, args );
}

inline Object _FAR & Object::firstThat( condFuncType func,
                                        void _FAR *args
                                      ) const
{
   return (*func)( *this, args ) == 0 ? NOOBJECT : (Object&)*this;
}

inline Object _FAR & Object::lastThat( condFuncType func,
                                       void _FAR *args
                                     ) const
{
    return Object::firstThat( func, args );
}

inline ostream _FAR& operator << ( ostream _FAR& out, const Object _FAR& obj )
{
    obj.printOn( out );
    return out;
}

inline int operator == ( const Object _FAR& test1, const Object _FAR& test2 )
{
    return (test1.isA() == test2.isA()) && test1.isEqual( test2 );
}

inline int operator !=( const Object _FAR& test1, const Object _FAR& test2 )
{
    return !( test1 == test2 );
}


class _CLASSTYPE Error : public Object
{

public:

    virtual classType isA() const
        {
        return errorClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "Error";
        }

    virtual hashValueType hashValue() const
        {
        return ERROR_CLASS_HASH_VALUE;
        }

    virtual int isEqual( const Object _FAR & ) const
        {
        return 1;
        }

    virtual void printOn( ostream _FAR & ) const;

    void operator delete( void _FAR * );

};


inline void Error::printOn( ostream _FAR & out ) const
{
    out << nameOf() << '\n';
}

inline void Error::operator delete( void _FAR * )
{
    ClassLib_error( __EDELERROR );
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif

