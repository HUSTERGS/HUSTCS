/*------------------------------------------------------------------------*/
/*                                                                        */
/*  BTREEINN.CPP                                                          */
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

//====== InnerNode functions ======

InnerNode::InnerNode(InnerNode* P, Btree* T) : Node(0,P,T)
{
    item = new Item[maxIndex()+1];
    if( item == 0 )
        ClassLib_error( __ENOMEMIA );
}

InnerNode::InnerNode(InnerNode* Parent, Btree* Tree, Node* oldroot)
                : Node(0, Parent, Tree)
{
    // called only by Btree to initialize the InnerNode that is
    // about to become the root.
    item = new Item[maxIndex()+1];
    if( item == 0 )
        ClassLib_error( __ENOMEMIA );
    append( 0, oldroot );
}

InnerNode::~InnerNode()
{
    if( last > 0 )
        delete item[0].tree;
    for( int i = 1; i <= last; i++ )
        {
        delete item[i].tree;
        if( tree->ownsElements() )
            delete item[i].key;
        }
    delete [] item;
}

// for quick (human reader) lookup, functions are in alphabetical order

void InnerNode::add( Sortable *obj, int index )
{
    // this is called only from Btree::add()
    PRECONDITION( index >= 1 );
    LeafNode* ln = getTree(index-1)->lastLeafNode();
    ln->add( obj, ln->last+1 );
}

void InnerNode::addElt( Item& itm, int at )
{
    PRECONDITION( 0 <= at && at <= last+1 );
    PRECONDITION( last < maxIndex() );
    for( int i = last+1; i > at ; i-- )
        getItem(i) = getItem(i-1);
    setItem( at, itm );
    last++;
}

void InnerNode::addElt( int at, Sortable* k, Node* t)
{
    Item newitem( k, t );
    addElt( newitem, at );
}

void InnerNode::add( Item& itm, int at )
{
    addElt( itm, at );
    if( isFull() )
        informParent();
}

void InnerNode::add( int at, Sortable* k, Node* t)
{
    Item newitem( k, t );
    add( newitem, at );
}

void InnerNode::appendFrom( InnerNode* src, int start, int stop )
{
    // this should never create a full node
    // that is, it is not used anywhere where THIS could possibly be
    // near full.
    if( start > stop )
        return;
    PRECONDITION( 0 <= start && start <= src->last );
    PRECONDITION( 0 <= stop  && stop  <= src->last );
    PRECONDITION( last + stop - start + 1 < maxIndex() ); // full-node check
    for( int i = start; i <= stop; i++ )
        setItem( ++last, src->getItem(i) );
}

void InnerNode::append( Sortable* D, Node* N )
{
    // never called from anywhere where it might fill up THIS
    PRECONDITION( last < maxIndex() );
    setItem( ++last, D, N );
}

void InnerNode::append( Item& itm )
{
    PRECONDITION( last < maxIndex() );
    setItem( ++last, itm );
}

void InnerNode::balanceWithLeft( InnerNode* leftsib, int pidx )
{
    // THIS has more than LEFTSIB;  move some item from THIS to LEFTSIB.
    // PIDX is the index of the parent item that will change when keys
    // are moved.
    PRECONDITION( Vsize() >= leftsib->Psize() );
    PRECONDITION( parent->getTree(pidx) == this );
    int newThisSize = (Vsize() + leftsib->Psize())/2;
    int noFromThis = Psize() - newThisSize;
    pushLeft( noFromThis, leftsib, pidx );
}

void InnerNode::balanceWithRight( InnerNode* rightsib, int pidx )
{
    // THIS has more than RIGHTSIB;  move some items from THIS to RIGHTSIB.
    // PIDX is the index of the parent item that will change when keys
    // are moved.
    PRECONDITION( Psize() >= rightsib->Vsize() );
    PRECONDITION( parent->getTree(pidx) == rightsib );
    int newThisSize = (Psize() + rightsib->Vsize())/2;
    int noFromThis = Psize() - newThisSize;
    pushRight( noFromThis, rightsib, pidx );

}

void InnerNode::balanceWith( InnerNode* rightsib, int pindx )
{
    // PINDX is the index of the parent item whose key will change when
    // keys are shifted from one InnerNode to the other.
    if( Psize() < rightsib->Vsize() )
        rightsib->balanceWithLeft( this, pindx );
    else
        balanceWithRight( rightsib, pindx );
}

void InnerNode::decrNofKeys( Node *that )
{
    // THAT is a child of THIS that has just shrunk by 1
    int i = indexOf( that );
    item[i].nofKeysInTree--;
    if( parent != 0 )
        parent->decrNofKeys( this );
    else
        tree->decrNofKeys();
}

long InnerNode::findRank( Sortable* what ) const
{
    // recursively look for WHAT starting in the current node

    if ( *what < *getKey(1) )
        return getTree(0)->findRank(what);
    long sum = getNofKeys(0);
    for( int i = 1; i < last; i++ )
        {
        if( *what == *getKey(i) )
            return sum;
        sum++;
        if( *what < *getKey(i+1) )
            return sum + getTree(i)->findRank(what);
        sum += getNofKeys(i);
        }
    if( *what == *getKey(last) )
        return sum;
    sum++;
    // *what > getKey(last), so recurse on last item.tree
    return sum + getTree(last)->findRank(what);
}

long InnerNode::findRank_bu( const Node *that ) const
{
    // findRank_bu is findRank in reverse.
    // whereas findRank looks for the object and computes the rank
    // along the way while walking DOWN the tree, findRank_bu already
    // knows where the object is and has to walk UP the tree from the
    // object to compute the rank.
    int L = indexOf( that );
    long sum = 0;
    for( int i = 0; i < L; i++ )
        sum += getNofKeys(i);
    return sum + L + (parent == 0 ? 0 : parent->findRank_bu( this ));
}

LeafNode*InnerNode::firstLeafNode()
{
    return getTree(0)->firstLeafNode();
}

Object& InnerNode::found(Sortable* what, Node** which, int* where )
{
    // recursively look for WHAT starting in the current node
    for( int i = 1 ; i <= last; i++ )
        {
        if( *getKey(i) == *what )
            {
            // then could go in either item[i].tree or item[i-1].tree
            // should go in one with the most room, but that's kinda
            // hard to calculate, so we'll stick it in item[i].tree
            *which = this;
            *where = i;
            return *getKey(i);
            }
        if( *getKey(i) > *what )
            return getTree(i-1)->found(what, which, where);
        }
    // *what > *(*this)[last].key, so recurse on last item.tree
    return getTree(last)->found( what, which, where );
}

void InnerNode::incrNofKeys( Node *that )
{
    // THAT is a child of THIS that has just grown by 1
    int i = indexOf( that );
    item[i].nofKeysInTree++;
    if( parent != 0 )
        parent->incrNofKeys( this );
    else
        tree->incrNofKeys();
}

#pragma warn -rvl

int InnerNode::indexOf( const Node *that ) const
{
    // returns a number in the range 0 to this->last
    // 0 is returned if THAT == tree[0]
    for( int i = 0; i <= last; i++ )
        if( getTree(i) == that )
            return i;
    CHECK( 0 );
}

#pragma warn .rvl

void InnerNode::informParent()
{
    if( parent == 0 )
        {
        // then this is the root of the tree and nees to be split
        // inform the btree.
        PRECONDITION( tree->root == this );
        tree->rootIsFull();
        }
    else
        parent->isFull( this );
}

void InnerNode::isFull(Node *that)
{
    // the child node THAT is full.   We will either redistribute elements
    // or create a new node and then redistribute.
    // In an attempt to minimize the number of splits, we adopt the following
    // strategy:
    //  * redistribute if possible
    //  * if not possible, then split with a sibling
    if( that->isLeaf )
        {
        LeafNode *leaf = (LeafNode *)that;
        LeafNode *left, *right;
        // split LEAF only if both sibling nodes are full.
        int leafidx = indexOf(leaf);
        int hasRightSib = (leafidx < last)
                                && ((right=(LeafNode*)getTree(leafidx+1))
                                          != 0);
        int hasLeftSib  = (leafidx > 0)
                                && ((left=(LeafNode*)getTree(leafidx-1))
                                         != 0);
        int rightSibFull = (hasRightSib && right->isAlmostFull());
        int leftSibFull  = (hasLeftSib  && left->isAlmostFull());
        if( rightSibFull )
            {
            if( leftSibFull )
                {
                // both full, so pick one to split with
                left->splitWith( leaf, leafidx );
                }
            else if( hasLeftSib )
                {
                // left sib not full, so balance with it
                leaf->balanceWithLeft( left, leafidx );
                }
            else
                {
                // there is no left sibling, so split with right
                leaf->splitWith( right, leafidx+1 );
                }
            }
        else if( hasRightSib )
            {
            // right sib not full, so balance with it
            leaf->balanceWithRight( right, leafidx+1 );
            }
        else if( leftSibFull )
            {
            // no right sib, and left sib is full, so split with it
            left->splitWith( leaf, leafidx );
            }
        else if( hasLeftSib )
            {
            // left sib not full so balance with it
            leaf->balanceWithLeft( left, leafidx );
            }
        else
            {
            // neither a left or right sib; should never happen
            CHECK(0);
            }
        }
    else {
        InnerNode *inner = (InnerNode *)that;
        // split INNER only if both sibling nodes are full.
        int inneridx = indexOf(inner);
        InnerNode *left, *right;
        int hasRightSib = (inneridx < last)
                                && ((right=(InnerNode*)getTree(inneridx+1))
                                          != 0);
        int hasLeftSib  = (inneridx > 0)
                                && ((left=(InnerNode*)getTree(inneridx-1))
                                         != 0);
        int rightSibFull = (hasRightSib && right->isAlmostFull());
        int leftSibFull  = (hasLeftSib  && left->isAlmostFull());
        if( rightSibFull )
            {
            if( leftSibFull )
                {
                left->splitWith( inner, inneridx );
                }
            else if( hasLeftSib )
                {
                inner->balanceWithLeft( left, inneridx );
                }
            else
                {
                // there is no left sibling
                inner->splitWith(right, inneridx+1);
                }
            }
        else if( hasRightSib )
            {
            inner->balanceWithRight( right, inneridx+1 );
            }
        else if( leftSibFull )
            {
            left->splitWith( inner, inneridx );
            }
        else if( hasLeftSib )
            {
            inner->balanceWithLeft( left, inneridx );
            }
        else {
            CHECK(0);
            }
        }
}

void InnerNode::isLow( Node *that )
{
    // the child node THAT is <= half full.  We will either redistribute
    // elements between children, or THAT will be merged with another child.
    // In an attempt to minimize the number of mergers, we adopt the following
    // strategy:
    //  * redistribute if possible
    //  * if not possible, then merge with a sibling
    if( that->isLeaf )
        {
        LeafNode *leaf = (LeafNode *)that;
        LeafNode *left, *right;
        // split LEAF only if both sibling nodes are full.
        int leafidx = indexOf(leaf);
        int hasRightSib = (leafidx < last)
                                && ((right=(LeafNode*)getTree(leafidx+1))
                                          != 0);
        int hasLeftSib  = (leafidx > 0)
                                && ((left=(LeafNode*)getTree(leafidx-1))
                                         != 0);
        if( hasRightSib
            && (leaf->Psize() + right->Vsize()) >= leaf->maxPsize())
            {
            // then cannot merge,
            // and balancing this and rightsib will leave them both
            // more than half full
            leaf->balanceWith( right, leafidx+1 );
            }
        else if( hasLeftSib
            && (leaf->Vsize() + left->Psize()) >= leaf->maxPsize())
            {
            // ditto
            left->balanceWith( leaf, leafidx );
            }
        else if( hasLeftSib )
            {
            // then they should be merged
            left->mergeWithRight( leaf, leafidx );
            }
        else if( hasRightSib )
            {
            leaf->mergeWithRight( right, leafidx+1 );
            }
        else
            {
            CHECK(0); // should never happen
            }
        }
    else
        {
        InnerNode *inner = (InnerNode *)that;
        //
        int inneridx = indexOf(inner);
        InnerNode *left, *right;
        int hasRightSib = (inneridx < last)
                                && ((right=(InnerNode*)getTree(inneridx+1))
                                          != 0);
        int hasLeftSib  = (inneridx > 0)
                                && ((left=(InnerNode*)getTree(inneridx-1))
                                         != 0);
        if( hasRightSib
            && (inner->Psize() + right->Vsize()) >= inner->maxPsize())
            {
            // cannot merge
            inner->balanceWith( right, inneridx+1 );
            }
        else if( hasLeftSib
            && (inner->Vsize() + left->Psize()) >= inner->maxPsize())
            {
            // cannot merge
            left->balanceWith( inner, inneridx );
            }
        else if( hasLeftSib )
            {
            left->mergeWithRight( inner, inneridx );
            }
        else if( hasRightSib )
            {
            inner->mergeWithRight( right, inneridx+1 );
            }
        else
            {
            CHECK(0);
            }
        }
}

LeafNode*InnerNode::lastLeafNode()
{
    return getTree(last)->lastLeafNode();
}

void InnerNode::mergeWithRight( InnerNode* rightsib, int pidx )
{
    PRECONDITION( Psize() + rightsib->Vsize() < maxIndex() );
    if( rightsib->Psize() > 0 )
        rightsib->pushLeft( rightsib->Psize(), this, pidx );
    rightsib->setKey( 0, parent->getKey( pidx ) );
    appendFrom( rightsib, 0, 0 );
    parent->incNofKeys( pidx-1, rightsib->getNofKeys(0)+1 );
    parent->removeItem( pidx );
    delete rightsib;
}

long InnerNode::nofKeys() const
{
    long sum = 0;
    for( int i = 0; i <= last; i++)
        sum += getNofKeys(i);
    return sum + Psize();
}

Object& InnerNode::operator[]( long idx ) const
{
    for( int j=0; j <= last; j++ )
        {
        long R;
        if( idx < (R = getNofKeys(j)) )
            return (*getTree(j))[idx];
        if( idx == R )
            {
            if( j == last )
                return NOOBJECT;
            else
                return *getKey(j+1);
            }
        idx -= R+1; // +1 because of the key in the node
        }
    return NOOBJECT;
}

void InnerNode::printOn(ostream& out) const
{
    out << " [ " << "/" << getNofKeys(0) << *getTree(0);
    for( int i = 1; i <= last; i++ )
        {
        if( i > 1 )
            CHECK( *getKey(i-1) <= *getKey(i) );
        out << *getKey(i) << "/" << getNofKeys(i) << *getTree(i);
        }
    out << " ] ";
}

void InnerNode::pushLeft( int noFromThis, InnerNode* leftsib, int pidx )
{
    // noFromThis==1 => moves the parent item into the leftsib,
    // and the first item in this's array into the parent item
    PRECONDITION( parent->getTree(pidx) == this );
    PRECONDITION( noFromThis > 0 && noFromThis <= Psize() );
    PRECONDITION( noFromThis + leftsib->Psize() < maxPsize() );
    setKey( 0, parent->getKey(pidx) ); // makes appendFrom's job easier
    leftsib->appendFrom( this, 0, noFromThis-1 );
    shiftLeft( noFromThis );
    parent->setKey( pidx, getKey(0) );
    parent->setNofKeys( pidx-1, leftsib->nofKeys() );
    parent->setNofKeys( pidx, nofKeys() );
}

void InnerNode::pushRight(int noFromThis, InnerNode* rightsib, int pidx)
{
    PRECONDITION( noFromThis > 0 && noFromThis <= Psize() );
    PRECONDITION( noFromThis + rightsib->Psize() < rightsib->maxPsize() );
    PRECONDITION( parent->getTree(pidx) == rightsib );
    //
    // The operation is three steps:
    //  Step I.  Make room for the incoming keys in RIGHTSIB.
    //  Step II. Move the items from THIS into RIGHTSIB.
    //  Step III.Update the length of THIS.
    //
    // Step I.: make space for noFromThis items
    //
    int start = last - noFromThis + 1;
    int tgt, src;
    tgt = rightsib->last + noFromThis;
    src = rightsib->last;
    rightsib->last = tgt;
    rightsib->setKey( 0, parent->getKey( pidx ) ); incNofKeys(0);
    while( src >= 0 )
        {
        // do this kind of assignment on InnerNode Items only when
        // the parent fields
        // of the moved items do not change, as they don't here.
        // Otherwise, use setItem so the parents are updated appropriately.
        rightsib->getItem(tgt--) = rightsib->getItem(src--);
        }

    // Step II.Move the items from THIS into RIGHTSIB
    for( int i = last; i >= start; i-- )
        {
        // this is the kind of assignment to use when parents change
        rightsib->setItem(tgt--, getItem(i));
        }
    parent->setKey( pidx, rightsib->getKey(0) );
    decNofKeys(0);
    CHECK( tgt == -1 );

    // Step III.
    last -= noFromThis;

    // Step VI.  update nofKeys
    parent->setNofKeys( pidx-1, nofKeys() );
    parent->setNofKeys( pidx, rightsib->nofKeys() );
}

void InnerNode::remove( int index )
{
    PRECONDITION( index >= 1 && index <= last );
    LeafNode* lf = getTree(index)->firstLeafNode();
    setKey( index, lf->item[0] );
    lf->removeItem(0);
}

void InnerNode::removeItem( int index )
{
    PRECONDITION( index >= 1 && index <= last );
    for( int to = index; to < last; to++ )
        item[to] = item[to+1];
    last--;
    if( isLow() )
        {
        if( parent == 0 )
            {
            // then this is the root; when only one child, make the child
            // the root
            if( Psize() == 0 )
                tree->rootIsEmpty();
            }
        else
            parent->isLow( this );
        }
}

void InnerNode::shiftLeft( int cnt )
{
    if( cnt <= 0 )
        return;
    for( int i = cnt; i <= last; i++ )
        getItem(i-cnt) = getItem(i);
    last -= cnt;
}

void InnerNode::split()
{
    // this function is called only when THIS is the only descendent
    // of the root node, and THIS needs to be split.
    // assumes that idx of THIS in Parent is 0.
    InnerNode* newnode = new InnerNode( parent );
    CHECK( newnode != 0 );
    parent->append( getKey(last), newnode );
    newnode->appendFrom( this, last, last );
    last--;
    parent->incNofKeys( 1, newnode->getNofKeys(0) );
    parent->decNofKeys( 0, newnode->getNofKeys(0) );
    balanceWithRight( newnode, 1 );
}

void
InnerNode::splitWith( InnerNode *rightsib, int keyidx )
{
    // THIS and SIB are too full; create a NEWnODE, and balance
    // the number of keys between the three of them.
    //
    // picture: (also see Knuth Vol 3 pg 478)
    //              keyidx keyidx+1
    //           +--+--+--+--+--+--...
    //           |  |  |  |  |  |
    // parent--->|  |     |     |
    //           |  |     |     |
    //           +*-+*-+*-+--+--+--...
    //            |  |  |
    //       +----+  |  +-----+
    //       |       +-----+  |
    //       V             |  V
    //       +----------+  |  +----------+
    //       |          |  |  |          |
    // this->|          |  |  |          |<--sib
    //       +----------+  |  +----------+
    //                     V
    //                    data
    //
    // keyidx is the index of where the sibling is, and where the
    // newly created node will be recorded (sibling will be moved to
    // keyidx+1)
    //
    PRECONDITION( keyidx > 0 && keyidx <= parent->last );
    // I would like to be able to prove that the following assertion
    // is ALWAYS true, but it is beyond my time limits.  If this assertion
    // ever comes up False, then the code to make it so must be inserted
    // here.
    // assert(parent->getKey(keyidx) == rightsib->getKey(0));
    // During debugging, this came up False, so
    rightsib->setKey(0,parent->getKey(keyidx));
    int nofKeys        = Psize() + rightsib->Vsize();
    int newSizeThis    = nofKeys / 3;
    int newSizeNew     = (nofKeys - newSizeThis) / 2;
    int newSizeSib     = (nofKeys - newSizeThis - newSizeNew);
    int noFromThis     = Psize() - newSizeThis;
    int noFromSib      = rightsib->Vsize() - newSizeSib;
    // because of their smaller size, this InnerNode may not have to
    // give up any elements to the new node.  I.e., noFromThis == 0.
    // This will not happen for LeafNodes.
    // We handle this by pulling an item from the rightsib.
    CHECK( noFromThis >= 0 );
    CHECK( noFromSib >= 1 );
    InnerNode* newNode = new InnerNode(parent);
    CHECK( newNode != 0 );
    if( noFromThis > 0 )
        {
        newNode->append( getItem(last) );
        parent->addElt( keyidx, getKey(last--), newNode );
        if( noFromThis > 2 )
            this->pushRight( noFromThis-1, newNode, keyidx );
        rightsib->pushLeft( noFromSib, newNode, keyidx+1 );
        }
    else
        {
        // pull an element from the rightsib
        newNode->append( rightsib->getItem(0) );
        parent->addElt( keyidx+1, rightsib->getKey(1), rightsib);
        rightsib->shiftLeft(1);
        parent->setTree( keyidx, newNode );
        rightsib->pushLeft( noFromSib-1, newNode, keyidx+1 );
        }
    parent->setNofKeys( keyidx-1, this->nofKeys() );
    parent->setNofKeys( keyidx, newNode->nofKeys() );
    parent->setNofKeys( keyidx+1, rightsib->nofKeys() );
    if( parent->isFull() )
        parent->informParent();
}
