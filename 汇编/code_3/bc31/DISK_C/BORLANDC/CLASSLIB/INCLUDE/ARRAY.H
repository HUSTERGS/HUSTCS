/*------------------------------------------------------------------------*/
/*                                                                        */
/*  ARRAY.H                                                               */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __ARRAY_H )
#define __ARRAY_H

#if defined( TEMPLATES )

    #if !defined( __ARRAYS_H )
    #include <Arrays.h>
    #endif  // __ARRAYS_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    #define Array   BI_TCArrayAsVector
    #define PArray  PBI_TCArrayAsVector
    #define RArray  RBI_TCArrayAsVector
    #define RPArray RPBI_TCArrayAsVector
    #define PCArray PCBI_TCArrayAsVector
    #define RCArray RCBI_TCArrayAsVector

    _CLASSDEF( BI_TCArrayAsVector )

    #define ArrayIterator   BI_TCArrayAsVectorIterator
    #define PArrayIterator  PBI_TCArrayAsVectorIterator
    #define RArrayIterator  RBI_TCArrayAsVectorIterator
    #define RPArrayIterator RPBI_TCArrayAsVectorIterator
    #define PCArrayIterator PCBI_TCArrayAsVectorIterator
    #define RCArrayIterator RCBI_TCArrayAsVectorIterator

    _CLASSDEF( BI_TCArrayAsVectorIterator )

#else   // TEMPLATES

    #if !defined( __CLSTYPES_H )
    #include <ClsTypes.h>
    #endif  // __CLSTYPES_H

    #if !defined( __OBJECT_H )
    #include <Object.h>
    #endif  // __OBJECT_H

    #if !defined( __ABSTARRY_H )
    #include <AbstArry.h>
    #endif  // __ABSTARRY_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    _CLASSDEF(Array)

    class _CLASSTYPE Array : public AbstractArray

    {

    public:

        Array( int upper, int lower = 0, sizeType aDelta = 0 ) :
            AbstractArray( upper, lower, aDelta )
            {
            }

        virtual void add( Object _FAR & );
        void addAt( Object _FAR &, int );

        virtual classType isA() const
            {
            return arrayClass;
            }

        virtual char _FAR *nameOf() const
            {
            return "Array";
            }

    };

#endif  // TEMPLATES

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __ARRAY_H

