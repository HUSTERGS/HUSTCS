/*------------------------------------------------------------------------*/
/*                                                                        */
/*  STACK.H                                                               */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __STACK_H )
#define __STACK_H

#if defined( TEMPLATES )

    #if !defined( __STACKS_H )
    #include <Stacks.h>
    #endif  // __STACKS_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    #define Stack   BI_TCStackAsList
    #define PStack  PBI_TCStackAsList
    #define RStack  RBI_TCStackAsList
    #define RPStack RPBI_TCStackAsList
    #define PCStack PCBI_TCStackAsList
    #define RCStack RCBI_TCStackAsList

    _CLASSDEF( BI_TCStackAsList )

    #define StackIterator   BI_TCStackAsListIterator
    #define PStackIterator  PBI_TCStackAsListIterator
    #define RStackIterator  RBI_TCStackAsListIterator
    #define RPStackIterator RPBI_TCStackAsListIterator
    #define PCStackIterator PCBI_TCStackAsListIterator
    #define RCStackIterator RCBI_TCStackAsListIterator

    _CLASSDEF( BI_TCStackAsListIterator )

#else   // TEMPLATES

    #if !defined( __CLSTYPES_H )
    #include <ClsTypes.h>
    #endif  // __CLSTYPES_H

    #if !defined( __CONTAIN_H )
    #include <Contain.h>
    #endif  // __CONTAIN_H

    #if !defined( __LIST_H )
    #include <List.h>
    #endif  // __LIST_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    _CLASSDEF(Stack)

    class _CLASSTYPE Stack : public Container
    {

    public:

        void push( Object _FAR & );
        Object _FAR & pop();
        Object _FAR & top() const
            {
            return list.peekHead();
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
            return stackClass;
            }

        virtual char _FAR *nameOf() const
            {
            return "Stack";
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

        virtual ContainerIterator _FAR & initIterator() const;

        int ownsElements()
            {
            return list.ownsElements();
            }

        void ownsElements( int del )
            { 
            list.ownsElements( del );
            }

    private:

        List list;

    };

#endif  // TEMPLATES

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __STACK_H

