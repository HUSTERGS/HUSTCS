/*------------------------------------------------------------------------*/
/*                                                                        */
/*  DICT.H                                                                */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __DICT_H )
#define __DICT_H

#if !defined( __CLSTYPES_H )
#include <ClsTypes.h>
#endif  // __CLSTYPES_H

#if !defined( __OBJECT_H )
#include <Object.h>
#endif  // __OBJECT_H

#if !defined( __SET_H )
#include <Set.h>
#endif  // __SET_H

#if !defined( __STDLIB_H )
#include <stdlib.h>
#endif

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

_CLASSDEF(Association)
_CLASSDEF(Dictionary)

class _CLASSTYPE Dictionary : public Set
{

public:

    Dictionary( unsigned sz = DEFAULT_HASH_TABLE_SIZE ) :
        Set(sz)
        {
        }

    virtual void add( Object _FAR & );
    Association _FAR & lookup( const Object _FAR & ) const;

    virtual classType isA() const
        {
        return dictionaryClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "Dictionary";
        }

};

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __DICT_H

