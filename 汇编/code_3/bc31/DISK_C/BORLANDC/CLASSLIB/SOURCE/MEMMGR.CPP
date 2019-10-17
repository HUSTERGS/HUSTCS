/*------------------------------------------------------------------------*/
/*                                                                        */
/*  MEMMGR.CPP                                                            */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __STDTEMPL_H )
#include <StdTempl.h>
#endif	// __STDTEMPL_H

#if !defined( __CHECKS_H )
#include <Checks.h>
#endif	// __CHECKS_H

#if !defined( __MEMMGR_H )
#include <MemMgr.h>
#endif	// __MEMMGR_H

unsigned max( unsigned, unsigned );

int BaseMemBlocks::allocBlock( size_t sz )
{
    BlockList _FAR *temp = new( max(sz,blockSize) ) BlockList( curBlock-1 );
    if( temp == 0 )
        return 0;
    curBlock = temp+1;
    blockCount++;
    return 1;
}

void BaseMemBlocks::freeTo( unsigned term )
{
    PRECONDITION( blockCount >= term );
    while( blockCount > term )
        {
        BlockList _FAR *temp = curBlock-1;
        curBlock = (temp->next)+1;
        delete temp;
        blockCount--;
        }
}

void _FAR *MemStack::allocate( size_t sz )
{
    sz = max( 1, sz );
    if( sz > blockSize - curLoc )
        if( allocBlock( sz ) == 0 )
            return 0;
        else
            curLoc = 0;
    void _FAR *temp = block() + curLoc;
    curLoc += sz;
    return temp;
}

