/*------------------------------------------------------------------------*/
/*                                                                        */
/*  SET.H                                                                 */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __SET_H )
#define __SET_H

#if defined( TEMPLATES )

    #if !defined( __SETS_H )
    #include <Sets.h>
    #endif  // __SETS_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    #define Set   BI_TCSetAsVector
    #define PSet  PBI_TCSetAsVector
    #define RSet  RBI_TCSetAsVector
    #define RPSet RPBI_TCSetAsVector
    #define PCSet PCBI_TCSetAsVector
    #define RCSet RCBI_TCSetAsVector

    _CLASSDEF( BI_TCSetAsVector )

    #define SetIterator   BI_TCSetAsVectorIterator
    #define PSetIterator  PBI_TCSetAsVectorIterator
    #define RSetIterator  RBI_TCSetAsVectorIterator
    #define RPSetIterator RPBI_TCSetAsVectorIterator
    #define PCSetIterator PCBI_TCSetAsVectorIterator
    #define RCSetIterator RCBI_TCSetAsVectorIterator

    _CLASSDEF( BI_TCSetAsVectorIterator )

#else   // TEMPLATES

    #if !defined( __RESOURCE_H )
    #include <Resource.h>
    #endif  // __RESOURCE_H

    #if !defined( __CLSTYPES_H )
    #include <ClsTypes.h>
    #endif  // __CLSTYPES_H

    #if !defined( __BAG_H )
    #include <Bag.h>
    #endif  // __BAG_H

    _CLASSDEF(Set)

    class _CLASSTYPE Set : public Bag
    {

    public:

        Set( sizeType setSize = DEFAULT_SET_SIZE ) :
            Bag( setSize )
            {
            }

        virtual void add( Object _FAR & toAdd )
            {
            if( !(Bag::hasMember( toAdd )) )
                {
                Bag::add( toAdd );
                }
            }
        virtual classType isA() const
            {
            return setClass;
            }

        virtual char _FAR *nameOf() const
            {
            return "Set";
            }

    };

#endif  // TEMPLATES

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __SET_H

