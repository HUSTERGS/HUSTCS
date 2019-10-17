/*------------------------------------------------------------------------
 * filename - heap.cpp
 *
 * function(s)
 *        malloc  - allocate heap space
 *        calloc  - allocate heap space and zero fill
 *        free    - free heap space
 *        realloc - resize heap block
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

// HEAP.CPP

#include <windows.h>
#include <alloc.h>
#include <dos.h>

extern "C" unsigned _WinAllocFlag;

#ifndef LDATA
#if defined(__LARGE__) || defined(__HUGE__) || defined(__COMPACT__)
#define LDATA 1
#else
#define LDATA 0
#endif
#endif

extern "C"
{
    void far  * _Cdecl _farcallocf (unsigned long __nunits,
                                   unsigned long __unitsz,
                                   unsigned __flags);
    void        _Cdecl _farfreef (void far *__block, unsigned __flags);
    void far  * _Cdecl _farmallocf (unsigned long __nbytes,
                                   unsigned __flags);
    void far  * _Cdecl _farreallocf (void far *__oldblock,
                                    unsigned long __nbytes,
                                    unsigned __flags);
}

void *malloc(size_t size)
{
#if (LDATA)
    return(_farmallocf(size, _WinAllocFlag));
#else
    return((void *)LocalAlloc(LMEM_FIXED, size));
#endif
}


void *realloc(void *block, size_t size)
{
#if (LDATA)
    return(_farreallocf(block, size, _WinAllocFlag));
#else
    if(block == 0)
        return malloc(size);
    else
        if(size == 0)
            {
            free(block);
            return 0;
            }
        else
            return((void *)LocalReAlloc((HANDLE) block, size, LMEM_MOVEABLE));
#endif
}


void *calloc(size_t nitems, size_t size)
{
#if (LDATA)
    return(_farcallocf(nitems, size, _WinAllocFlag));
#else
    return((void *)LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, size * nitems));
#endif
}


void free(void *block)
{
#if (LDATA)
    _farfreef(block, _WinAllocFlag);
#else
    if (block)
        LocalFree((HANDLE)block);
#endif
}

