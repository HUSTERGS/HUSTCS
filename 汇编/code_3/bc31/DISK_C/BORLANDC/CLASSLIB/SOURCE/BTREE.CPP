/*------------------------------------------------------------------------*/
/*                                                                        */
/*  BTREE.CPP                                                             */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( CHECKS_H )
#include <Checks.h>
#endif  // CHECKS_H

#if !defined( __BTREE_H )
#include <BTree.h>
#endif  // __BTREE_H

#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

/*

Implementation notes:

This implements B-trees with several refinements.  Most of them can be found
in Knuth Vol 3, but some were developed to adapt to restrictions imposed
by C++.  First, a restatement of Knuth's properties that a B-tree must
satisfy, assuming we make the enhancement he suggests in the paragraph
at the bottom of page 476.  Instead of storing null pointers to non-existent
nodes (which Knuth calls the leaves) we utilize the space to store keys.
Therefore, what Knuth calls level (l-1) is the bottom of our tree, and
we call the nodes at this level LeafNodes.  Other nodes are called InnerNodes.
The other enhancement we have adopted is in the paragraph at the bottom of
page 477: overflow control.

The following are modifications of Knuth's properties on page 478:

i)  Every InnerNode has at most Order keys, and at most Order+1 sub-trees.
ii) Every LeafNode has at most 2*(Order+1) keys.
iii)An InnerNode with k keys has k+1 sub-trees.
iv) Every InnerNode that is not the root has at least InnerLowWaterMark keys.
v)  Every LeafNode that is not the root has at least LeafLowWaterMark keys.
vi) If the root is a LeafNode, it has at least one key.
vii)If the root is an InnerNode, it has at least one key and two sub-trees.
viii)All LeafNodes are the same distance from the root as all the other
    LeafNodes.
ix) For InnerNode n with key n[i].key, then sub-tree n[i-1].tree contains
    all keys <= n[i].key, and sub-tree n[i].tree contains all keys >= n[i].key.
x)  Order is at least 3.

The values of InnerLowWaterMark and LeafLowWaterMark may actually be set
by the user when the tree is initialized, but currently they are set
automatically to:
        InnerLowWaterMark = ceiling(Order/2)
        LeafLowWaterMark  = Order - 1

If the tree is only filled, then all the nodes will be at least 2/3 full.
They will almost all be exactly 2/3 full if the elements are added to the
tree in order (either increasing or decreasing).  [Knuth says McCreight's
experiments showed almost 100% memory utilization.  I don't see how that
can be given the algorithms that Knuth gives.  McCreight must have used
a different scheme for balancing.  [ No, he used a different scheme for
splitting: he did a two-way split instead of the three way split as we do
here.  Which means that McCreight does better on insertion of ordered data,
but we should do better on insertion of random data.]]

It must also be noted that B-trees were designed for DISK access algorithms,
not necessarily in-memory sorting, as we intend it to be used here.  However,
if the order is kept small (< 6?) any inefficiency is negligible for
in-memory sorting.  Knuth points out that balanced trees are actually
preferable for memory sorting.  I'm not sure that I believe this, but
it's interesting.  Also, deleting elements from balanced binary trees, being
beyond the scope of Knuth's book (p. 465), is beyond my scope.  B-trees
are good enough.


A B-tree is declared to be of a certain ORDER (4 by default).  This number
determines the number of keys contained in any interior node of the tree.
Each interior node will contain ORDER keys, and therefore ORDER+1 pointers
to sub-trees.  The keys are numbered and indexed 1 to ORDER while the
pointers are numbered and indexed 0 to ORDER.  The 0th ptr points to the
sub-tree of all elements that are less than key[1].  Ptr[1] points to the
sub-tree that contains all the elements greater than key[1] and less than
key[2].  etc.  The array of pointers and keys is allocated as ORDER+1
pairs of keys and nodes, meaning that one key field (key[0]) is not used
and therefore wasted.  Given that the number of interior nodes is
small, that this waste allows fewer cases of special code, and that it
is useful in certain of the methods, it was felt to be a worthwhile waste.

The size of the exterior nodes (leaf nodes) does not need to be related to
the size of the interior nodes at all.  Since leaf nodes contain only
keys, they may be as large or small as we like independent of the size
of the interior nodes.  For no particular reason other than it seems like
a good idea, we will allocate 2*(ORDER+1) keys in each leaf node, and they
will be numbered and indexed from 0 to 2*ORDER+1.  It does have the advantage
of keeping the size of the leaf and interior arrays the same, so that if we
find allocation and de-allocation of these arrays expensive, we can modify
their allocation to use a garbage ring, or something.

Both of these numbers will be run-time constants associated with each tree
(each tree at run-time can be of a different order).  The variable `order'
is the order of the tree, and the inclusive upper limit on the indices of
the keys in the interior nodes.  The variable `order2' is the inclusive
upper limit on the indices of the leaf nodes, and is designed
    (1) to keep the sizes of the two kinds of nodes the same;
    (2) to keep the expressions involving the arrays of keys looking
        somewhat the same:   lower limit        upper limit
          for inner nodes:        1                order
          for leaf  nodes:        0                order2
        Remember that index 0 of the inner nodes is special.

Currently, order2 = 2*(order+1).

 picture: (also see Knuth Vol 3 pg 478)

           +--+--+--+--+--+--...
           |  |  |  |  |  |
 parent--->|  |     |     |
           |  |     |     |
           +*-+*-+*-+--+--+--...
            |  |  |
       +----+  |  +-----+
       |       +-----+  |
       V             |  V
       +----------+  |  +----------+
       |          |  |  |          |
 this->|          |  |  |          |<--sib
       +----------+  |  +----------+
                     V
                    data

It is conceptually VERY convenient to think of the data as being the
very first element of the sib node.  Any primitive that tells sib to
perform some action on n nodes should include this `hidden' element.
For InnerNodes, the hidden element has (physical) index 0 in the array,
and in LeafNodes, the hidden element has (virtual) index -1 in the array.
Therefore, there are two `size' primitives for nodes:
Psize       - the physical size: how many elements are contained in the
              array in the node.
Vsize       - the `virtual' size; if the node is pointed to by
              element 0 of the parent node, then Vsize == Psize;
              otherwise the element in the parent item that points to this
              node `belongs' to this node, and Vsize == Psize+1;

Parent nodes are always InnerNodes.

These are the primitive operations on Nodes:

append(elt)     - adds an element to the end of the array of elements in a
                  node.  It must never be called where appending the element
                  would fill the node.
split()         - divide a node in two, and create two new nodes.
splitWith(sib)  - create a third node between this node and the sib node,
                  divvying up the elements of their arrays.
pushLeft(n)     - move n elements into the left sibling
pushRight(n)    - move n elements into the right sibling
balanceWithRight() - even up the number of elements in the two nodes.
balanceWithLeft()  - ditto


To allow this implementation of btrees to also be an implementation of
sorted arrays/lists, the overhead is included to allow O(log n) access
of elements by their rank (`give me the 5th largest element').
Therefore, each Item keeps track of the number of keys in and below it
in the tree (remember, each item's tree is all keys to the RIGHT of the
item's own key).

[ [ < 0 1 2 3 > 4 < 5 6 7 > 8 < 9 10 11 12 > ] 13 [ < 14 15 16 > 17 < 18 19 20 > ] ]
   4  1 1 1 1   4   1 1 1   5   1  1  1  1      7  3   1  1  1    4    1  1  1
*/

//====== Btree functions ========

void Btree::finishInit( int O )
{
    if( O < 3 )
        ClassLib_error( __EORDER3 );
    ownsElements( 0 );
    root = 0;
    Order = O;
    Order2 = 2 * (O+1);
    Leaf_MaxIndex = Order2 - 1;     // item[0..Order2-1]
    Inner_MaxIndex = Order;         // item[1..Order]
    //
    // the low water marks trigger an exploration for balancing
    // or merging nodes.
    // When the size of a node falls below X, then it must be possible to
    // either balance this node with another node, or it must be possible
    // to merge this node with another node.
    // This can be guaranteed only if (this->size() < (maxSize()-1)/2).
    //
    //
    Leaf_LowWaterMark = ((Leaf_MaxIndex+1            // == maxSize()
                                         )-1) / 2    // satisfies the above
                                                  - 1; // because we compare
                                                     // lowwatermark with last

    Inner_LowWaterMark = (Order-1) / 2;
}

Btree::Btree(int O) : itemsInContainer(0)
{
    finishInit(O);
}

Btree::~Btree(void)
{
    if( root != 0 )
        delete root;
}

void Btree::flush( DeleteType dt )
{
    int oldValue = ownsElements();
    ownsElements( delObj(dt) );
    if( root != 0 )
        delete root;
    itemsInContainer = 0;
    root = 0;
    ownsElements( oldValue );
}

int Btree::hasMember( Object& o ) const
{
    if( !o.isSortable() )
        ClassLib_error( __ENOTSORT );
    if( root == 0 )
        return 0;
    else
        {
        Node* loc;
        int idx;
        return root->found(&(Sortable&)o, &loc, &idx) != NOOBJECT;
        }
}

long Btree::rank( const Object& o ) const
{
    if( !o.isSortable() )
        ClassLib_error( __ENOTSORT );
    if( root == 0 )
        return -1;
    else
        return root->findRank(&(Sortable&)o);
}

Object& Btree::findMember( Object& o ) const
{
    if( !o.isSortable() )
        ClassLib_error(__ENOTSORT);
    if( root == 0 )
        return NOOBJECT;
    else
        {
        Node* loc;
        int idx;
        return root->found(&(Sortable&)o, &loc, &idx);
        }
}

void Btree::printOn( ostream& out ) const
{
    if( root == 0 )
        out << "<empty>" ;
    else
        root->printOn(out);
}

extern "C" void __ErrorMessage( const char * );

int Btree::isEqual( const Object& obj ) const
{
    if( obj.isA() == btreeClass )
        {
        __ErrorMessage( "Btree isEqual not implemented\n" );
        exit(1);
        }
    return 0;

    // two btrees are equal only if they have the same number of
    // elements, and they are all equal.  The structure of the tree
    // itself doesn't enter into it.
}


long Btree::i_add( const Object& o )
{
    long r;
    if( !o.isSortable() )
        ClassLib_error( __ENOTSORT );
    if( root == 0 )
        {
        root = new LeafNode( 0, &(Sortable&)o, this );
        CHECK( root != 0 );
        incrNofKeys();
        r = 0;
        }
    else
        {
        Node* loc;
        int idx;
        if( root->found(&(Sortable&)o, &loc, &idx) != NOOBJECT )
            {
            // loc and idx are set to either where the object
            // was found, or where it should go in the Btree.
            // Nothing is here now, but later we might give the user
            // the ability to declare a B-tree as `unique elements only',
            // in which case we would handle an exception here.
            // cerr << "Multiple entry warning\n";
            }
        else
            {
            CHECK( loc->isLeaf );
            }
        if( loc->isLeaf )
            {
            if( loc->parent == 0 )
                r = idx;
            else
                r = idx + loc->parent->findRank_bu( loc );
            }
        else
            {
            InnerNode *iloc = (InnerNode*)loc;
            r = iloc->findRank_bu( iloc->getTree( idx ) );
            }
        loc->add( &(Sortable&)o, idx );
        }
    CHECK( r == rank( (Sortable&)o ) || (Sortable&)o == (*this)[r] );
    return r;
}

void Btree::add( Object& o )
{
    if( !o.isSortable() )
        ClassLib_error( __ENOTSORT );
    if (root == 0)
        {
        root = new LeafNode( 0, &(Sortable&)o, this );
        CHECK( root != 0 );
        incrNofKeys();
        }
    else
        {
        Node* loc;
        int idx;
        if( root->found(&(Sortable&)o, &loc, &idx) != NOOBJECT )
            {
            // loc and idx are set to either where the object
            // was found, or where it should go in the Btree.
            // Nothing is here now, but later we might give the user
            // the ability to declare a B-tree as `unique elements only',
            // in which case we would handle an exception here.
            }
        loc->add( &(Sortable&)o, idx );
        }
}

void Btree::detach( Object& o, DeleteType dt )
{
    if( !o.isSortable() )
        ClassLib_error(__ENOTSORT);
    if( root == 0 )
        return;

    Node* loc;
    int idx;
    Object* obj = &(root->found( &(Sortable&)o, &loc, &idx ));
    if( *obj == NOOBJECT )
        return;
    loc->remove( idx );
    if( delObj(dt) )
        delete obj;
}

void Btree::rootIsFull()
{
    // the root of the tree is full; create an InnerNode that
    // points to it, and then inform the InnerNode that it is full.
    Node* oldroot = root;
    root = new InnerNode( 0, this, oldroot );
    CHECK( root != 0 );
    oldroot->split();
}

void Btree::rootIsEmpty()
{
    if( root->isLeaf )
        {
        LeafNode* lroot = (LeafNode*)root;
        CHECK( lroot->Psize() == 0 );
        delete lroot;
        root = 0;
        }
    else {
        InnerNode* iroot = (InnerNode*)root;
        CHECK(iroot->Psize() == 0);
        root = iroot->getTree(0);
        root->parent = 0;
        delete iroot;
        }
}

Item::Item()
{
    nofKeysInTree = 0;
    tree = 0;
    key = 0;
}

Item::Item(Node* n, Sortable* o)
{
    nofKeysInTree = n->nofKeys()+1;
    tree = n;
    key = o;
}

Item::Item(Sortable* o, Node* n)
{
    nofKeysInTree = n->nofKeys()+1;
    tree = n;
    key = o;
}

Item::~Item()
{
}

//
//====== Node functions ======
//

Node::Node(int isleaf, InnerNode* P, Btree* T)
{
    // nofElts = 0;
    last = -1;
    isLeaf = isleaf;
    parent = P;
    if( P == 0 )
        {
        CHECK( T != 0 );
        tree = T;
        }
    else
        tree = P->tree;
}

Node::~Node()
{
}

//
//===== BtreeIterator methods =====
//

void BtreeIterator::restart()
{
    index = 0;
}

Object& BtreeIterator::operator++()
{
    return beingIterated[++index];
}

Object& BtreeIterator::operator++( int )
{
    return beingIterated[index++];
}

Object& BtreeIterator::current()
{
    return beingIterated[index];
}


ContainerIterator&
Btree::initIterator() const
{
    return *( (ContainerIterator *)new BtreeIterator( *this ) );
}

BtreeIterator::~BtreeIterator()
{
}


BtreeIterator::operator int()
{
    return index < beingIterated.getItemsInContainer();
}
