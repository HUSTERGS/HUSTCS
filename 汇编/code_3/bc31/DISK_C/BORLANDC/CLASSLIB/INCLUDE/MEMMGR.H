/*------------------------------------------------------------------------*/
/*                                                                        */
/*  MEMMGR.H                                                              */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __MEMMGR_H )
#define __MEMMGR_H

#if !defined( __STDTEMPL_H )
#include <StdTempl.h>
#endif  // __STDTEMPL_H

#if !defined( __RESOURCE_H )
#include <Resource.h>
#endif  // __RESOURCE_H

#if !defined( __STDLIB_H )
#include <StdLib.h>
#endif  // __STDLIB_H

#if !defined( __CHECKS_H )
#include <Checks.h>
#endif  // __CHECKS_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

_CLASSDEF(HeaderBlock)
_CLASSDEF(BlockList)
_CLASSDEF(BaseMemBlocks)
_CLASSDEF(MemStack)
_CLASSDEF(Marker)
_CLASSDEF(BMarker)

class _CLASSTYPE HeaderBlock
{

public:

    void _FAR *operator new( size_t, size_t );
    void _FAR *operator new( size_t );

};

inline void _FAR *HeaderBlock::operator new( size_t sz, size_t extra )
{
    return ::operator new( sz + extra );
}

inline void _FAR *HeaderBlock::operator new( size_t )
{
    CHECK(0);
    return 0;
}

class _CLASSTYPE BlockList : public HeaderBlock
{

public:

    BlockList( BlockList _FAR * );

private:

    BlockList _FAR *next;

    friend class BaseMemBlocks;

};

inline BlockList::BlockList( BlockList _FAR *nxt ) :
    next( nxt )
{
}

class _CLASSTYPE BaseMemBlocks
{

public:

    BaseMemBlocks( size_t = 8192 );
    ~BaseMemBlocks();

    char _FAR *block() const { return (char _FAR *)curBlock; }
    unsigned count() const { return blockCount; }
    allocBlock( size_t );
    void freeTo( unsigned );

protected:

    const size_t blockSize;

private:

    BlockList _FAR *curBlock;
    unsigned blockCount;

};

inline BaseMemBlocks::BaseMemBlocks( size_t sz ) :
    curBlock(0),
    blockCount(0),
    blockSize(sz)
{
    CHECK( sz != 0 );
}

inline BaseMemBlocks::~BaseMemBlocks()
{
#if !defined( WINDOWS_WEP_BUG )
    freeTo( 0 );
#endif
}

class _CLASSTYPE MemStack : public BaseMemBlocks
{

public:

    friend class Marker;

    MemStack( size_t = 8192 );

    void _FAR *allocate( size_t );

private:

    size_t curLoc;

};

inline void _FAR *operator new( size_t sz, MemStack& m )
{
    return m.allocate( sz );
}

inline MemStack::MemStack( size_t sz ) :
    BaseMemBlocks( sz ),
    curLoc(sz)
{
    CHECK( sz != 0 );
}

class _CLASSTYPE Marker
{

public:

    Marker( MemStack _FAR & ms ) :
        memstk(ms),
        blk(ms.count()),
        curLoc(ms.curLoc)
        {
        }

    ~Marker()
        {
        PRECONDITION( blk < memstk.count() ||
              (blk == memstk.count() && curLoc <= memstk.curLoc )
            );
        memstk.freeTo( blk );
        memstk.curLoc = curLoc;
        }


private:

    const unsigned blk;
    const size_t curLoc;
    MemStack& memstk;

};

class _CLASSTYPE MemBlocks
{

public:

    MemBlocks( size_t, unsigned = 100 );

    void _FAR *allocate( size_t );
    void free( void _FAR * );

private:

    void _FAR *freeList;
    MemStack mem;
    size_t size;

    friend class BMarker;

};

inline MemBlocks::MemBlocks( size_t sz, unsigned count ) :
    mem( sz*count ),
    freeList(0),
    size( max(sz, sizeof(void _FAR *)) )
{
    CHECK( sz != 0 && count != 0 );
}

#pragma argsused
inline void _FAR *MemBlocks::allocate( size_t sz )
{
    PRECONDITION( size == max(sz, sizeof(void _FAR *)) );
    if( freeList == 0 )
        return mem.allocate( size );
    else
        {
        void _FAR *temp = freeList;
        freeList = *(void _FAR * _FAR *)temp;
        return temp;
        }
}

inline void MemBlocks::free( void _FAR * block )
{
    *(void _FAR * _FAR *)block = freeList;
    freeList = block;
}

class _CLASSTYPE BMarker
{

public:

    BMarker( MemBlocks _FAR & mb ) :
        memstk(mb.mem),
        blk(mb.mem.count())
        {}

    ~BMarker()
        {
        PRECONDITION( blk <= memstk.count() );
        memstk.freeTo( blk );
        }


private:

    const unsigned blk;
    MemStack _FAR & memstk;

};

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __MEMMGR_H
