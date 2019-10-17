/*------------------------------------------------------------------------*/
/*                                                                        */
/*  COLLECT.H                                                             */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __COLLECT_H )
#define __COLLECT_H

#if !defined( __CLSTYPES_H )
#include <ClsTypes.h>
#endif  // __CLSTYPES_H

#if !defined( __OBJECT_H )
#include <Object.h>
#endif  // __OBJECT_H

#if !defined( __CONTAIN_H )
#include <Contain.h>
#endif  // __CONTAIN_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

_CLASSDEF(ContainerIterator)
_CLASSDEF(Collection)

class _CLASSTYPE Collection : public Container
{

public:

    virtual void add( Object _FAR & ) = 0;
    virtual void detach( Object _FAR &, DeleteType = NoDelete ) = 0;
    void destroy( Object _FAR & o )
        {
        detach( o, DefDelete );
        }

    virtual int hasMember( Object _FAR & obj ) const
        {
        return findMember( obj ) != NOOBJECT;
        }

    virtual Object _FAR & findMember( Object _FAR & ) const;

};

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif
