/*------------------------------------------------------------------------*/
/*                                                                        */
/*  BTREELFN.CPP                                                          */
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

//====== LeafNode functions =======

LeafNode::LeafNode(InnerNode* P, Sortable* O, Btree* T): Node(1, P, T)
{
    item = new Sortable *[maxIndex()+1];
    if( item == 0 )
        ClassLib_error( __ENOMEMLN );
    if( O != 0 )
        item[++last] = O;
}

LeafNode::~LeafNode()
{
    if( tree->ownsElements() )
        {
        for( int i = 0; i <= last; i++ )
            delete item[i];
        }
    delete [] item;
}

void LeafNode::add(Sortable *obj, int index)
{
    // add the object OBJ to the leaf node, inserting it at location INDEX
    // in the item array
    PRECONDITION( 0 <= index && index <= last+1 );
    PRECONDITION( last <= maxIndex() );
    for( int i = last+1; i > index ; i-- )
        item[i] = item[ i - 1 ];
    item[ index ] = obj;
    last++;

    // check for overflow
    if( parent == 0 )
        tree->incrNofKeys( );
    else
        parent->incrNofKeys( this );

    if( isFull() )
        {
        // it's full; tell parent node
        if( parent == 0 )
            {
            // this occurs when this leaf is the only node in the
            // btree, and this->tree->root == this
            CHECK( tree->root == this );
            // in which case we inform the btree, which can be
            // considered the parent of this node
            tree->rootIsFull();
            }
        else
            {
            // the parent is responsible for splitting/balancing subnodes
            parent->isFull( this );
            }
        }
}

void LeafNode::appendFrom( LeafNode* src, int start, int stop )
{
    // A convenience function, does not worry about the element in
    // the parent, simply moves elements from SRC[start] to SRC[stop]
    // into the current array.
    // This should never create a full node.
    // That is, it is not used anywhere where THIS could possibly be
    // near full.
    // Does NOT handle nofKeys.
    if( start > stop )
        return;
    PRECONDITION( 0 <= start && start <= src->last );
    PRECONDITION( 0 <= stop  && stop  <= src->last );
    PRECONDITION( last + stop - start + 1 < maxIndex() ); // full-node check
    for( int i = start; i <= stop; i++ )
        item[++last] = src->item[i];
    CHECK( last < maxIndex() );
}

void LeafNode::append( Sortable* D )
{
    // never called from anywhere where it might fill up THIS
    // does NOT handle nofKeys.
    item[++last] = D;
    CHECK( last < maxIndex() );
}


void LeafNode::balanceWithLeft( LeafNode* leftsib, int pidx )
{
    // THIS has more than LEFTSIB;  move some items from THIS to LEFTSIB.
    PRECONDITION( Vsize() >= leftsib->Psize() );
    int newThisSize = (Vsize() + leftsib->Psize())/2;
    int noFromThis  = Psize() - newThisSize;
    pushLeft( noFromThis, leftsib, pidx );
}

void LeafNode::balanceWithRight( LeafNode* rightsib, int pidx )
{
    // THIS has more than RIGHTSIB;  move some items from THIS to RIGHTSIB.
    PRECONDITION( Psize() >= rightsib->Vsize() );
    int newThisSize = (Psize() + rightsib->Vsize())/2;
    int noFromThis  = Psize() - newThisSize;
    pushRight( noFromThis, rightsib, pidx );
}

void LeafNode::balanceWith( LeafNode* rightsib, int pidx )
{
    // PITEM is the parent item whose key will change when keys are shifted
    // from one LeafNode to the other.
    if( Psize() < rightsib->Vsize() )
        rightsib->balanceWithLeft( this, pidx );
    else
        balanceWithRight( rightsib, pidx );
}

long LeafNode::findRank( Sortable* what ) const
{
    // WHAT was not in any inner node; it is either here, or it's
    // not in the tree
    for( int i = 0; i <= last; i++ )
        {
        if( *item[i] == *what )
            return i;
        if( *item[i] >= *what )
            return -1;
        }
    return -1;
}

LeafNode *LeafNode::firstLeafNode()
{
    return this;
}

Object& LeafNode::found(Sortable* what, Node** which, int* where )
{
    // WHAT was not in any inner node; it is either here, or it's
    // not in the tree
    for( int i = 0; i <= last; i++ )
        {
        if( *item[i] == *what )
            {
            *which = this;
            *where = i;
            return *item[i];
            }
        if( *item[i] >= *what )
            {
            *which = this;
            *where = i;
            return NOOBJECT;
            }
        }
    *which = this;
    *where = last+1;
    return NOOBJECT;
}

#pragma warn -rvl

int LeafNode::indexOf( const Sortable *that ) const
{
    // returns a number in the range 0 to maxIndex()
    for( int i = 0; i <= last; i++ )
        {
        if( item[i] == that )
            return i;
        }
    CHECK(0);
}

#pragma warn .rvl

LeafNode *LeafNode::lastLeafNode()
{
    return this;
}

void LeafNode::mergeWithRight( LeafNode* rightsib, int pidx )
{
    PRECONDITION( Psize() + rightsib->Vsize() < maxPsize() );
    rightsib->pushLeft( rightsib->Psize(), this, pidx );
    append( parent->getKey( pidx ) );
    parent->setNofKeys( pidx-1, nofKeys() );
    // cout << "in mergeWithRight:\n" << *parent << "\n";
    parent->removeItem( pidx );
    delete rightsib;
    // cout << "in mergeWithRight:\n" << *parent << "\n";
}

long LeafNode::nofKeys( int ) const
{
    return 1;
}

long LeafNode::nofKeys() const
{
    return Psize();
}

void LeafNode::printOn(ostream& out) const
{
    out << " < ";
    for( int i = 0; i <= last; i++ )
        out << *item[i] << " " ;
    out << "> ";
}

void LeafNode::pushLeft( int noFromThis, LeafNode* leftsib, int pidx )
{
    // noFromThis==1 => moves the parent item into the leftsib,
    // and the first item in this's array into the parent item
    PRECONDITION( noFromThis > 0 && noFromThis <= Psize() );
    PRECONDITION( noFromThis + leftsib->Psize() < maxPsize() );
    PRECONDITION( parent->getTree(pidx) == this );
    leftsib->append( parent->getKey(pidx) );
    if( noFromThis > 1 )
        leftsib->appendFrom( this, 0, noFromThis-2 );
    parent->setKey( pidx, item[noFromThis-1] );
    shiftLeft( noFromThis );
    parent->setNofKeys( pidx-1, leftsib->nofKeys() );
    parent->setNofKeys( pidx, nofKeys() );
}

void LeafNode::pushRight( int noFromThis, LeafNode* rightsib, int pidx )
{
    // noFromThis==1 => moves the parent item into the
    // rightsib, and the last item in this's array into the parent
    // item
    PRECONDITION(noFromThis > 0 && noFromThis <= Psize());
    PRECONDITION(noFromThis + rightsib->Psize() < maxPsize());
    PRECONDITION(parent->getTree(pidx) == rightsib);
    // The operation is five steps:
    //  Step I.  Make room for the incoming keys in RIGHTSIB.
    //  Step II. Move the key in the parent into RIGHTSIB.
    //  Step III.Move the items from THIS into RIGHTSIB.
    //  Step IV. Move the item from THIS into the parent.
    //  Step V.  Update the length of THIS.
    //
    // Step I.: make space for noFromThis items
    //
    int start = last - noFromThis + 1;
    int tgt, src;
    tgt = rightsib->last + noFromThis;
    src = rightsib->last;
    rightsib->last = tgt;
    while (src >= 0)
        rightsib->item[tgt--] = rightsib->item[src--];

    // Step II. Move the key from the parent into place
    rightsib->item[ tgt-- ] = parent->getKey( pidx );

    // Step III.Move the items from THIS into RIGHTSIB
    for( int i = last; i > start; i-- )
        rightsib->item[tgt--] = item[i];
    CHECK( tgt == -1 );

    // Step IV.
    parent->setKey( pidx, item[ start ] );

    // Step V.
    last -= noFromThis;

    // Step VI.  update nofKeys
    parent->setNofKeys( pidx-1, nofKeys() );
    parent->setNofKeys( pidx, rightsib->nofKeys() );
}

void LeafNode::remove( int index )
{
    PRECONDITION( index >= 0 && index <= last );
    for( int to = index; to < last; to++ )
        item[to] = item[to+1];
    last--;
    if( parent == 0 )
        tree->decrNofKeys();
    else
        parent->decrNofKeys( this );
    if( isLow() )
        {
        if( parent == 0 )
            {
            // then this is the root; when no keys left, inform the tree
            if( Psize() == 0 )
                tree->rootIsEmpty();
            }
        else
            parent->isLow( this );
        }
}

void LeafNode::shiftLeft( int cnt )
{
    if( cnt <= 0 )
        return;
    for( int i = cnt; i <= last; i++ )
        item[i-cnt] = item[i];
    last -= cnt;
}

void LeafNode::split()
{
    // this function is called only when THIS is the only descendent
    // of the root node, and THIS needs to be split.
    // assumes that idx of THIS in Parent is 0.
    LeafNode* newnode = new LeafNode( parent );
    CHECK( newnode != 0 );
    parent->append( item[last--], newnode );
    parent->setNofKeys( 0, parent->getTree(0)->nofKeys() );
    parent->setNofKeys( 1, parent->getTree(1)->nofKeys() );
    balanceWithRight( newnode, 1 );
}

void LeafNode::splitWith( LeafNode *rightsib, int keyidx )
{
    PRECONDITION(parent == rightsib->parent);
    PRECONDITION(keyidx > 0 && keyidx <= parent->last);
    int nofKeys        = Psize() + rightsib->Vsize();
    int newSizeThis    = nofKeys / 3;
    int newSizeNew     = (nofKeys - newSizeThis) / 2;
    int newSizeSib     = (nofKeys - newSizeThis - newSizeNew);
    int noFromThis     = Psize() - newSizeThis;
    int noFromSib      = rightsib->Vsize() - newSizeSib;
    CHECK(noFromThis >= 0);
    CHECK(noFromSib >= 1);
    LeafNode* newNode  = new LeafNode(parent);
    CHECK( newNode != 0 );
    parent->addElt( keyidx, item[last--], newNode );
    parent->setNofKeys( keyidx, 0 );
    parent->decNofKeys( keyidx-1 );
    this->pushRight( noFromThis-1, newNode, keyidx );
    rightsib->pushLeft( noFromSib, newNode, keyidx+1 );
    if( parent->isFull() )
        parent->informParent();
}
