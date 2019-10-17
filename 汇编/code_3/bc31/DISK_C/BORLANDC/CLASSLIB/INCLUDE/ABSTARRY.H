/*------------------------------------------------------------------------*/
/*                                                                        */
/*  ABSTARRY.H                                                            */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __ABSTARRY_H )
#define __ABSTARRY_H

#if defined( TEMPLATES )

    #if !defined( __COLLECT_H )
    #include <Collect.h>
    #endif  // __COLLECT_H

    #if !defined( __MEM_H )
    #include <Mem.h>
    #endif  // __MEM_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    _CLASSDEF(ostream)
    _CLASSDEF(ContainerIterator)
    _CLASSDEF(AbstractArray)
    _CLASSDEF(ArrayIterator)

    class _CLASSTYPE AbstractArray:  public Collection
    {

    public:

        friend class ArrayIterator;

        virtual Object _FAR & operator []( int loc ) = 0;

        virtual int lowerBound() const = 0;
        virtual int upperBound() const = 0;
        virtual sizeType arraySize() const = 0;

        virtual void detach( int loc, DeleteType dt = NoDelete ) = 0;
        virtual void detach( Object _FAR &, DeleteType dt = NoDelete ) = 0;
        void destroy( int i )
            {
            detach( i, Delete );
            }

        int isEqual( const Object _FAR & ) const;
        void printContentsOn( ostream _FAR & ) const;

    };

#else   // TEMPLATES

    #if !defined( __COLLECT_H )
    #include <Collect.h>
    #endif  // __COLLECT_H

    #if !defined( __MEM_H )
    #include <Mem.h>
    #endif  // __MEM_H

    #if !defined( __CHECKS_H )
    #include <Checks.h>
    #endif	// __CHECKS_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    _CLASSDEF(ostream)
    _CLASSDEF(ContainerIterator)
    _CLASSDEF(AbstractArray)
    _CLASSDEF(ArrayIterator)

    class _CLASSTYPE AbstractArray:  public Collection
    {

    public:

        AbstractArray( int, int = 0, sizeType = 0 );
        virtual ~AbstractArray();

        Object _FAR & operator []( int ) const;

        int lowerBound() const
            {
            return lowerbound;
            }

        int upperBound() const
            {
            return upperbound;
            }

        sizeType arraySize() const;

        virtual void detach( Object _FAR &, DeleteType = NoDelete );
        virtual void detach( int, DeleteType = NoDelete );
        void destroy( int i ) { detach( i, DefDelete ); }
        virtual void flush( DeleteType = DefDelete );

        virtual int isEqual( const Object _FAR & ) const;
        virtual void printContentsOn( ostream _FAR & ) const;

        virtual ContainerIterator _FAR & initIterator() const;

    protected:

        Object _FAR & objectAt( int i ) const
            {
            return *theArray[ zeroBase(i) ];
            }

        Object _FAR *ptrAt( int i ) const
            {
            return theArray[ zeroBase(i) ];
            }

        int find( const Object _FAR & );

        void reallocate( sizeType );

        void setData( int, Object _FAR * );

        void insertEntry( int );
        void removeEntry( int );
        void squeezeEntry( int );

        sizeType delta;
        int lowerbound;
        int upperbound;
        int lastElementIndex;

    private:

        Object _FAR * _FAR *theArray;

        int zeroBase( int loc ) const
            {
            PRECONDITION( loc >= lowerbound && loc <= upperbound );
            return loc - lowerbound;
            }

        int boundBase( unsigned loc ) const
            {
            PRECONDITION( loc == UINT_MAX || loc <= upperbound - lowerbound );
            return loc == UINT_MAX ? INT_MAX : loc + lowerbound;
            }

        friend class ArrayIterator;

    };

    inline Object _FAR & AbstractArray::operator [] ( int atIndex ) const
    {
        return objectAt( atIndex );
    }

    inline sizeType AbstractArray::arraySize() const
    {
        return sizeType( upperbound - lowerbound + 1 );
    }

    class _CLASSTYPE ArrayIterator : public ContainerIterator
    {

    public:

        ArrayIterator( const AbstractArray _FAR & );
        virtual ~ArrayIterator();

        virtual operator int();
        virtual Object _FAR & current();
        virtual Object _FAR & operator ++( int );
        virtual Object _FAR & operator ++();
        virtual void restart();

    private:

        int currentIndex;
        const AbstractArray _FAR & beingIterated;

        void scan();

    };

#endif  // TEMPLATES

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __ABSTARRY_H

