/*------------------------------------------------------------------------*/
/*                                                                        */
/*  BAG.H                                                                 */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __BAG_H )
#define __BAG_H

#if defined( TEMPLATES )

    #if !defined( __BAGS_H )
    #include <Bags.h>
    #endif  // __BAGS_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    #define Bag   BI_TCBagAsVector
    #define PBag  PBI_TCBagAsVector
    #define RBag  RBI_TCBagAsVector
    #define RPBag RPBI_TCBagAsVector
    #define PCBag PCBI_TCBagAsVector
    #define RCBag RCBI_TCBagAsVector

    _CLASSDEF( BI_TCBagAsVector )

    #define BagIterator   BI_TCBagAsVectorIterator
    #define PBagIterator  PBI_TCBagAsVectorIterator
    #define RBagIterator  RBI_TCBagAsVectorIterator
    #define RPBagIterator RPBI_TCBagAsVectorIterator
    #define PCBagIterator PCBI_TCBagAsVectorIterator
    #define RCBagIterator RCBI_TCBagAsVectorIterator

    _CLASSDEF( BI_TCBagAsVectorIterator )

#else   // TEMPLATES

    #if !defined( __RESOURCE_H )
    #include <Resource.h>
    #endif  // __RESOURCE_H

    #if !defined( __CLSTYPES_H )
    #include <ClsTypes.h>
    #endif  // __CLSTYPES_H

    #if !defined( __HASHTBL_H )
    #include <HashTbl.h>
    #endif  // __HASHTBL_H

    #pragma option -Vo-
    #if defined( __BCOPT__ ) && !defined( _ALLOW_po )
    #pragma option -po-
    #endif

    _CLASSDEF(Bag)

    class _CLASSTYPE Bag : public Collection
    {

    public:

        Bag( sizeType bagSize = DEFAULT_BAG_SIZE ) :
            table( bagSize )
            {
            }

        virtual void add( Object _FAR & o )
            {
            table.add( o );
            }

        virtual void detach( Object _FAR & o, DeleteType dt = NoDelete )
            {
            table.detach( o, dt );
            }

        virtual void flush( DeleteType dt = DefDelete )
            {
            table.flush( dt );
            }

        virtual int isEmpty() const
            {
            return table.isEmpty();
            }

        virtual countType getItemsInContainer() const
            {
            return table.getItemsInContainer();
            }

        void forEach( void (_FAR *f)(Object _FAR &, void _FAR *),
                      void _FAR *args
                    )
            {
            table.forEach( f, args );
            }

        Object _FAR& firstThat( int (_FAR*f)(const Object _FAR&, void _FAR*),
                                void _FAR *args
                              ) const
            {
            return table.firstThat( f, args );
            }

        Object _FAR& lastThat( int (_FAR*f)(const Object _FAR&, void _FAR*),
                               void _FAR *args
                             ) const
            {
            return table.lastThat( f, args );
            }

        virtual int hasMember( Object _FAR & o ) const
            {
            return table.hasMember( o );
            }

        virtual Object _FAR & findMember( Object _FAR & o ) const
            {
            return table.findMember(o);
            }

        virtual ContainerIterator _FAR & initIterator() const
            {
            return table.initIterator();
            }

        virtual classType isA() const
            {
            return bagClass;
            }

        virtual char _FAR *nameOf() const
            {
            return "Bag";
            }

        int ownsElements()
            {
            return table.ownsElements();
            }

        void ownsElements( int del )
            { 
            table.ownsElements( del );
            }

    private:

        HashTable table;

    };

#endif  // TEMPLATES

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __BAG_H

