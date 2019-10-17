/*------------------------------------------------------------------------*/
/*                                                                        */
/*  STRNG.H                                                               */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( _STRNG_H )
#define _STRNG_H

#if !defined( __CLSTYPES_H )
#include <ClsTypes.h>
#endif  // __CLSTYPES_H

#if !defined( __SORTABLE_H )
#include <Sortable.h>
#endif  // __SORTABLE_H

#if !defined( __STRING_H )
#include <string.h>
#endif  // __STRING_H

#if !defined( __CHECKS_H )
#include <Checks.h>
#endif  // __CHECKS_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

_CLASSDEF(ostream)
_CLASSDEF(String)

class _CLASSTYPE String : public Sortable
{

public:

    String( const char _FAR * = "" );
    String( const String _FAR & );
    virtual ~String()
        {
        delete theString;
        }


    String& operator = ( const String _FAR & );
    operator const char _FAR *() const;

    virtual int isEqual( const Object _FAR & ) const;
    virtual int isLessThan( const Object _FAR & ) const;\

    virtual classType isA() const
        {
        return stringClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "String";
        }

    virtual hashValueType hashValue() const;
    virtual void printOn( ostream _FAR & ) const;

private:

    sizeType len;
    char _FAR *theString;

};

inline String::operator const char _FAR *() const
{
    return theString;
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif
