/*------------------------------------------------------------------------*/
/*                                                                        */
/*  BTREE.H                                                               */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __BTREE_H )
#define __BTREE_H

#if !defined( __CHECKS_H )
#include <Checks.h>
#endif  // __CHECKS_H

#if !defined( __SORTABLE_H )
#include <Sortable.h>
#endif  // __SORTABLE_H

#if !defined( __COLLECT_H )
#include <Collect.h>
#endif  // __COLLECT_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

_CLASSDEF(Node)
_CLASSDEF(Item)
_CLASSDEF(Btree)
_CLASSDEF(InnerNode)
_CLASSDEF(LeafNode)
_CLASSDEF(BtreeIterator)

class _CLASSTYPE Node
{

public:

    Node( int b, InnerNode _FAR * P, Btree _FAR * T = 0 );
    virtual ~Node();

    virtual void add( Sortable _FAR *, int ) = 0;
    virtual void remove( int ) = 0;

    virtual Object _FAR & operator[]( long i ) const = 0;
    virtual Object _FAR & found( Sortable _FAR *,
                                 Node _FAR * _FAR *,
                                 int _FAR *
                               ) = 0;

    virtual long findRank( Sortable _FAR * ) const = 0;
    virtual long nofKeys() const = 0; // # keys in or below this node

    virtual LeafNode _FAR * firstLeafNode() = 0;
    virtual LeafNode _FAR * lastLeafNode() = 0;

    virtual void split() = 0;

    virtual void printOn(ostream _FAR &) const = 0;
    friend ostream _FAR & operator <<( ostream _FAR &, const Node _FAR & );

    int last;   // for inner node 1 <= last <= InnerMaxIndex
                // for leaf node  1 <= last <= LeafMaxIndex
                // (last==0 only temporarily while the tree is being
                //  updated)
    InnerNode _FAR *parent; // a parent is always an inner node (or 0 for the root)
    Btree _FAR *tree;   // the tree of which this node is a part
    int isLeaf; // run-time type flag

};

class _CLASSTYPE Item
{

public:

    Item();
    Item(Node _FAR * n, Sortable _FAR * o);
    Item(Sortable _FAR * o, Node _FAR * n);
    ~Item();
    // data
    long nofKeysInTree; // tree can have more than 32K elements
    Sortable _FAR *key;
    Node _FAR *tree;

};

class _CLASSTYPE InnerNode : public Node
{

public:

    InnerNode( InnerNode _FAR *, Btree _FAR * = 0 );
    InnerNode( InnerNode _FAR *, Btree _FAR *, Node _FAR * );
    ~InnerNode();

    void add( Sortable _FAR *, int );
    void add( Item _FAR &, int );
    void add( int, Sortable _FAR *, Node _FAR * );
    void addElt( Item _FAR &, int );
    void addElt( int, Sortable _FAR *, Node _FAR * );
    void remove( int );
    void removeItem( int );

    Object _FAR & operator[]( long i ) const;
    Object _FAR & found( Sortable _FAR *, Node _FAR * _FAR *, int _FAR * );

    long nofKeys( int i ) const;
    void setTree( int i, Node _FAR * node );
    void setKey( int i, Sortable _FAR * obj );
    void setItem( int i, Item _FAR & itm );
    void setItem( int i, Sortable _FAR * obj, Node _FAR * node );
    long getNofKeys( int i ) const;
    void setNofKeys( int i, long r );
    long incNofKeys( int i, long N=1 );
    long decNofKeys( int i, long N=1 );
    long findRank( Sortable _FAR * ) const;
    long findRank_bu( const Node _FAR * ) const;
    Node _FAR *getTree( int i ) const;
    Sortable _FAR *getKey( int i ) const;
    Item _FAR & getItem( int i ) const;


    int  indexOf( const Node _FAR * ) const;
    void incrNofKeys( Node _FAR * np );
    void decrNofKeys( Node _FAR * np );
    long nofKeys() const;

    LeafNode _FAR *firstLeafNode();
    LeafNode _FAR *lastLeafNode();

    void informParent();

    void split();
    void splitWith( InnerNode _FAR *, int );
    void mergeWithRight( InnerNode _FAR *, int );
    void balanceWithLeft( InnerNode _FAR *, int );
    void balanceWithRight( InnerNode _FAR *, int );
    void balanceWith( InnerNode _FAR *, int );
    void pushLeft( int cnt, InnerNode _FAR * leftsib, int parentIdx );
    void pushRight( int cnt, InnerNode _FAR * rightsib, int parentIdx );
    void appendFrom( InnerNode _FAR *, int, int );
    void append( Sortable _FAR *, Node _FAR * );
    void append( Item _FAR & );
    void shiftLeft( int );

    int Psize() const;
    int Vsize() const;
    int maxIndex() const;
    int maxPsize() const;

    void printOn(ostream&) const;

    int isFull() const;
    void isFull( Node _FAR * );
    int isAlmostFull() const;
    int isLow() const;
    void isLow( Node _FAR * );

private:

    Item _FAR *item; // actually items[maxIndex()+1] is desired

};

class _CLASSTYPE LeafNode : public Node
{

public:

    LeafNode(InnerNode _FAR * P, Sortable _FAR * obj = 0, Btree _FAR * T = 0 );
    ~LeafNode();

    void add( Sortable _FAR * , int );
    void remove( int i );
    void removeItem( int i);

    Object _FAR & operator[]( long i ) const;
    Object _FAR & found( Sortable _FAR *, Node _FAR * _FAR *, int _FAR * );

    long nofKeys( int i ) const;
    long nofKeys() const;
    long findRank( Sortable _FAR * ) const;
    Sortable _FAR *getKey( int idx ) { return item[idx]; }
    void setKey( int idx, Sortable _FAR * obj ) { item[idx] = obj; }

    int indexOf( const Sortable _FAR * ) const;

    LeafNode _FAR *firstLeafNode();
    LeafNode _FAR *lastLeafNode();

    void split();
    void splitWith( LeafNode _FAR *, int );
    void mergeWithRight( LeafNode _FAR *, int );
    void balanceWithLeft( LeafNode _FAR *, int );
    void balanceWithRight( LeafNode _FAR *, int );
    void balanceWith( LeafNode _FAR *, int );
    void pushLeft( int cnt, LeafNode _FAR *, int parentIndex );
    void pushRight( int cnt, LeafNode _FAR *, int parentIndex );
    void appendFrom( LeafNode _FAR *, int, int );
    void append( Sortable _FAR * );
    void shiftLeft ( int );

    int Psize() const;
    int Vsize() const;
    int maxIndex() const;
    int maxPsize() const;

    void printOn(ostream _FAR &) const;

    int isFull() const;
    int isAlmostFull() const;
    int isLow() const;

    Sortable _FAR * _FAR *item; // actually Sortable* item[maxIndex()+1] is desired

};

class _CLASSTYPE Btree : public Collection
{

public:

    Btree( int ordern = 3 );//-create a Btree of order n
    ~Btree();

    void add( Object _FAR & );
    void detach( Object _FAR &, DeleteType = NoDelete );
    void flush( DeleteType = DefDelete );
    virtual int hasMember( Object _FAR & ) const;
    virtual Object _FAR & findMember( Object _FAR & ) const;

    virtual int isEmpty() const { return itemsInContainer == 0; }
    virtual countType getItemsInContainer() const { return itemsInContainer; }

    virtual classType isA() const { return btreeClass; }
    virtual char _FAR *nameOf() const { return "Btree"; }
    virtual int isEqual( const Object _FAR & ) const;
    virtual void printOn( ostream _FAR & ) const;
    virtual ContainerIterator _FAR & initIterator() const;



    int order();
    Object _FAR & operator[]( long i ) const;
    long rank( const Object _FAR & ) const;

protected:

    void incrNofKeys() { itemsInContainer++; }
    void decrNofKeys() { itemsInContainer--; }

    long i_add( const Object _FAR & );
         //-add the object to the tree; return the index
         // in the tree at which the object was inserted
         // (C++ doesn't allow signatures
         // to differ in only the return value).
         // NOTE: other insertions and deletions may
         // change this object's index.
private:

    int Order;          //-the order of the tree (should be > 2)
    int Order2;         //-always == order*2+1 (assumes a memory access
                        // is cheaper than a multiply and increment by one
    int Inner_LowWaterMark;
    int Leaf_LowWaterMark;
    int Inner_MaxIndex;
    int Leaf_MaxIndex;

    Node _FAR *root;

    void finishInit(int);
    void rootIsFull();   // called when the root node is full
    void rootIsEmpty();  // called when root is empty

    unsigned itemsInContainer;

    friend Node;
    friend InnerNode;
    friend LeafNode;

};


inline Node _FAR *InnerNode::getTree( int i ) const
{
    return item[i].tree;
}

inline Sortable _FAR * InnerNode::getKey( int i ) const
{
    return item[i].key;
}

inline Item _FAR & InnerNode::getItem( int i ) const
{
    return item[i];
}

inline void InnerNode::setTree( int i, Node _FAR * node )
{
    item[i].tree = node;
    node->parent = this;
}

inline void InnerNode::setKey( int i, Sortable _FAR * obj )
{
    item[i].key = obj;
}

inline void InnerNode::setItem( int i, Item _FAR & itm )
{
    item[i] = itm;
    itm.tree->parent = this;
}

inline void InnerNode::setItem( int i, Sortable _FAR * obj, Node _FAR * node )
{
    setTree(i, node);
    setKey(i, obj);
}

inline long InnerNode::getNofKeys( int i ) const
{
    PRECONDITION( i >= 0 && i <= last );
    return item[i].nofKeysInTree;
}

inline void InnerNode::setNofKeys( int i, long r )
{
    item[i].nofKeysInTree = r;
}

inline long InnerNode::incNofKeys( int i, long N )
{
    return ( item[i].nofKeysInTree += N );
}

inline long InnerNode::decNofKeys( int i, long N )
{
    return ( item[i].nofKeysInTree -= N );
}

inline long InnerNode::nofKeys( int i ) const
{
    return getNofKeys(i);
}

inline int InnerNode::Psize() const
{
    return last;
}

inline int InnerNode::Vsize() const
{
    PRECONDITION( parent != 0 && parent->getTree(0) != (Node _FAR *)this );
    return Psize()+1;
}

inline int InnerNode::maxIndex() const
{
    return tree->Inner_MaxIndex;
}

inline int InnerNode::maxPsize() const
{
    return tree->Inner_MaxIndex;
}

inline int InnerNode::isFull() const
{
    return last == maxIndex();
}

inline int InnerNode::isAlmostFull() const
{
    return last >= maxIndex() - 1;
}

inline int InnerNode::isLow() const
{
    return last < tree->Inner_LowWaterMark;
}

inline void LeafNode::removeItem( int i)
{
    remove(i);
}

inline Object _FAR & LeafNode::operator[]( long i ) const
{
    PRECONDITION( i >=0 && i <= last );
    return *((Object _FAR *)item[(int)i]);    // CHECK - cast to int OK?
}

inline int LeafNode::Psize() const
{
    return last+1;
}

inline int LeafNode::Vsize() const
{
    PRECONDITION( parent != 0 && parent->getTree(0) != (Node _FAR *)this );
    return Psize()+1;
}

inline int LeafNode::maxIndex() const
{
    return tree->Leaf_MaxIndex;
}

inline int LeafNode::maxPsize() const
{
    return tree->Leaf_MaxIndex + 1;
}

inline int LeafNode::isFull() const
{
    return last == maxIndex();
}

inline int LeafNode::isAlmostFull() const
{
    return last >= maxIndex() - 1;
}

inline int LeafNode::isLow() const
{
    return last < tree->Leaf_LowWaterMark;
}

inline int Btree::order()
{
    return Order;
}

inline ostream _FAR & operator <<( ostream& outputStream, const Node _FAR & aNode)
{
    aNode.printOn( outputStream );
    return outputStream;
}

class _CLASSTYPE BtreeIterator : public ContainerIterator
{
public:
            BtreeIterator( const Btree _FAR & );
    virtual ~BtreeIterator();

    virtual operator int();
    virtual Object _FAR & current();
    virtual Object _FAR & operator ++();
    virtual Object _FAR & operator ++( int );
    virtual void restart();

private:
    const   Btree _FAR & beingIterated;
            long index;
};

inline BtreeIterator::BtreeIterator( const Btree _FAR & toIterate ) :
    beingIterated( toIterate ), index( 0 )
{
}

inline Object _FAR & Btree::operator[]( long i ) const { return (*root)[i]; }

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif
