/*------------------------------------------------------------------------*/
/*                                                                        */
/*  DEQUE.H                                                               */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __DEQUE_H )
#define __DEQUE_H

#if defined( TEMPLATES )

    #if !defined( __DEQUES_H )
    #include <Deques.h>
    #endif  // __DEQUES_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    #define Deque   BI_TCDequeAsDoubleList
    #define PDeque  PBI_TCDequeAsDoubleList
    #define RDeque  RBI_TCDequeAsDoubleList
    #define RPDeque RPBI_TCDequeAsDoubleList
    #define PCDeque PCBI_TCDequeAsDoubleList
    #define RCDeque RCBI_TCDequeAsDoubleList

    _CLASSDEF( BI_TCDequeAsDoubleList )

    #define DequeIterator   BI_TCDequeAsDoubleListIterator
    #define PDequeIterator  PBI_TCDequeAsDoubleListIterator
    #define RDequeIterator  RBI_TCDequeAsDoubleListIterator
    #define RPDequeIterator RPBI_TCDequeAsDoubleListIterator
    #define PCDequeIterator PCBI_TCDequeAsDoubleListIterator
    #define RCDequeIterator RCBI_TCDequeAsDoubleListIterator

    _CLASSDEF( BI_TCDequeAsDoubleListIterator )

#else   // TEMPLATES

    #if !defined( __CLSTYPES_H )
    #include <ClsTypes.h>
    #endif  // __CLSTYPES_H

    #if !defined( __CONTAIN_H )
    #include <Contain.h>
    #endif  // __CONTAIN_H

    #if !defined( __DBLLIST_H )
    #include <DblList.h>
    #endif  // __DBLLIST_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    _CLASSDEF(Deque)

    class _CLASSTYPE Deque : public Container
    {

    public:

        ~Deque()
            {
            flush();
            }

        Object& peekLeft() const
            {
            return list.peekAtHead();
            }

        Object& peekRight() const
            {
            return list.peekAtTail();
            }

        Object& getLeft();
        Object& getRight();

        void putLeft( Object& o )
            {
            list.addAtHead( o );
            itemsInContainer++;
            }

        void putRight( Object& o )
            {
            list.addAtTail( o );
            itemsInContainer++;
            }

        virtual void flush( DeleteType dt = DefDelete )
            {
            list.flush( dt );
            }

        virtual int isEmpty() const
            {
            return list.isEmpty();
            }

        virtual countType getItemsInContainer() const
            {
            return list.getItemsInContainer();
            }

        virtual void forEach( iterFuncType f, void _FAR *arg )
            {
            list.forEach( f, arg );
            }

        virtual Object _FAR & firstThat( condFuncType f, void _FAR *arg ) const
            {
            return list.firstThat( f, arg );
            }

        virtual Object _FAR & lastThat( condFuncType f, void _FAR *arg ) const
            {
            return list.lastThat( f, arg );
            }

        virtual classType isA() const
            {
            return dequeClass;
            }

        virtual char _FAR *nameOf() const
            {
            return "Deque";
            }

        virtual hashValueType hashValue() const
            {
            return list.hashValue();
            }

        virtual int isEqual( const Object& obj ) const
            {
            return list.isEqual( obj );
            }

        virtual int isSortable() const
            {
            return list.isSortable();
            }

        virtual int isAssociation() const
            {
            return list.isAssociation();
            }

        virtual void printOn( ostream& os ) const
            {
            list.printOn( os );
            }

        virtual void printHeader( ostream& os ) const
            {
            list.printHeader( os );
            }

        virtual void printSeparator( ostream& os ) const
            {
            list.printSeparator( os );
            }

        virtual void printTrailer( ostream& os ) const
            {
            list.printTrailer( os );
            }

        virtual ContainerIterator& initIterator() const;

        int ownsElements()
            {
            return list.ownsElements();
            }

        void ownsElements( int del )
            { 
            list.ownsElements( del );
            }

    private:

        DoubleList list;

    };

#endif  // TEMPLATES

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __DEQUE_H

