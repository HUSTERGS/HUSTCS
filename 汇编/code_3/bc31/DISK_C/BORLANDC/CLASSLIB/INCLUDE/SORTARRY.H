/*------------------------------------------------------------------------*/
/*                                                                        */
/*  SORTARRY.H                                                            */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __SORTARRY_H )
#define __SORTARRY_H

#if defined( TEMPLATES )

    #if !defined( __ARRAYS_H )
    #include <Arrays.h>
    #endif  // __ARRAYS_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    #define SortedArray   BI_TCSArrayAsVector
    #define PSortedArray  PBI_TCSArrayAsVector
    #define RSortedArray  RBI_TCSArrayAsVector
    #define RPSortedArray RPBI_TCSArrayAsVector
    #define PCSortedArray PCBI_TCSArrayAsVector
    #define RCSortedArray RCBI_TCSArrayAsVector

    _CLASSDEF( BI_TCSArrayAsVector )

    #define SortedArrayIterator   BI_TCSArrayAsVectorIterator
    #define PSortedArrayIterator  PBI_TCSArrayAsVectorIterator
    #define RSortedArrayIterator  RBI_TCSArrayAsVectorIterator
    #define RPSortedArrayIterator RPBI_TCSArrayAsVectorIterator
    #define PCSortedArrayIterator PCBI_TCSArrayAsVectorIterator
    #define RCSortedArrayIterator RCBI_TCSArrayAsVectorIterator

    _CLASSDEF( BI_TCSArrayAsVectorIterator )

#else   // TEMPLATES

    #if !defined( __CLSTYPES_H )
    #include <ClsTypes.h>
    #endif  // __CLSTYPES_H

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

    _CLASSDEF(SortedArray)

    class _CLASSTYPE SortedArray : public AbstractArray
    {

    public:

        SortedArray( int upper, int lower = 0, sizeType aDelta = 0 );

        virtual void add( Object _FAR & );
        virtual void detach( Object _FAR &, DeleteType = NoDelete );

        virtual classType isA() const
            {
            return sortedArrayClass;
            }

        virtual char _FAR *nameOf() const
            {
            return "SortedArray";
            }

    };

    inline SortedArray::SortedArray( int upper, int lower, sizeType aDelta ) :
        AbstractArray( upper, lower, aDelta )
    {
    }

#endif  // TEMPLATES

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __SORTARRY_H

