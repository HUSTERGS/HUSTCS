/*------------------------------------------------------------------------
 * filename - farheap.cpp
 *
 * function(s)
 *        farmalloc  - allocate far heap space
 *        farcalloc  - allocate far heap space and zero fill
 *        farfree    - free far heap space
 *        farrealloc - resize far heap block
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <windows.h>
#include <alloc.h>
#include <dos.h>
#include <mem.h>

extern "C"
{
    extern unsigned _WinAllocFlag;

    void far * _farmallocf (unsigned long size, unsigned flags);
    void far * _farcallocf (unsigned long nitems,
                       unsigned long size, unsigned flags);
    void _farfreef (void far *block, unsigned flags);
    void far * _farreallocf (void far *block, unsigned long size,
                    unsigned flags);
}

void far *farmalloc(unsigned long size)
{
    return _farmallocf(size, _WinAllocFlag);
}

void far *farcalloc(unsigned long nitems, unsigned long size)
{
    return _farcallocf(nitems, size, _WinAllocFlag);
}

void farfree(void far *block)
{
    _farfreef(block, _WinAllocFlag);
}

void far *farrealloc(void far *block, unsigned long size)
{
    return _farreallocf(block, size, _WinAllocFlag);
}
