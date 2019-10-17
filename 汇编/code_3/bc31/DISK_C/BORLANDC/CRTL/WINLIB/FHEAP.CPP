/*------------------------------------------------------------------------
 * filename - fheap.cpp
 *
 * function(s)
 *        _farmallocf  - allocate far heap space
 *        _farcallocf  - allocate far heap space and zero fill
 *        _farfreef    - free far heap space
 *        _farreallocf - resize far heap block
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

// FHEAP.CPP

#include <windows.h>
#include <alloc.h>
#include <dos.h>
#include <mem.h>

extern "C"
{
    extern unsigned _WinAllocFlag;

    void far _RLSMEM();
    void far _GETMEM();
    void far _SIZMEM();

    void far * _farmallocf (unsigned long size, unsigned flags);
    void far * _farcallocf (unsigned long nitems,
                            unsigned long size, unsigned flags);
    void _farfreef (void far *block, unsigned flags);
    void far * _farreallocf (void far *block, unsigned long size,
                             unsigned flags);
}

void far * _FARFUNC _farmallocf(unsigned long size, unsigned flags)
{
    if (size == 0)
        return NULL;

    unsigned OldWinAllocFlags = _WinAllocFlag;
    _WinAllocFlag = flags;

    _DX = (unsigned short)(size >> 16);
    _AX = (unsigned short)size;

    asm push si
    _GETMEM();
    asm pop si

    void far * pMem = (void _es *)_DI;

    _WinAllocFlag = OldWinAllocFlags;

    return pMem;
}


void far * _FARFUNC _farcallocf(unsigned long nitems, unsigned long size,
                               unsigned flags)
{
    unsigned long RealSize = size * nitems;

    unsigned OldWinAllocFlags = _WinAllocFlag;
    _WinAllocFlag = flags | GMEM_ZEROINIT;

    _DX = (unsigned short)(RealSize >> 16);
    _AX = (unsigned short)RealSize;

    asm push si
    _GETMEM();
    asm pop si

    void far * pMem = (void _es *)_DI;

    if (RealSize < 0xFFFF && pMem)
        _fmemset(pMem, 0, (size_t)RealSize);

    _WinAllocFlag = OldWinAllocFlags;

    return pMem;
}


void _FARFUNC _farfreef(void far *block, unsigned flags)
{
    if (block)
    {
    unsigned OldWinAllocFlags = _WinAllocFlag;
    _WinAllocFlag = flags;

    _ES = FP_SEG(block);
    _DI = FP_OFF(block);

    asm push si
    _RLSMEM();
    asm pop si

    block = 0L;

    _WinAllocFlag = OldWinAllocFlags;
    }
}


void far * _FARFUNC _farreallocf(void far *block, unsigned long size,
                                 unsigned flags)
{
    if (block == 0L)
        return _farmallocf(size, flags);
    else
    {
       if (size == 0L)
          _farfreef(block, flags);       // falls through to return NULL
       else
       {
#if defined(_Windows)
      // Check for a non-suballocated allocation.  The offset
      // of blocks allocated by Windows are currently always 0.
      // We can use this fact to let Windows do the reallocation.
      if ((unsigned short)block == 0)   // Windows allocated
      {
          HANDLE h;
          if ((h = (HANDLE)GlobalHandle(FP_SEG(block))) != 0)
          {
              GlobalUnlock(h);
              if ((h = GlobalReAlloc(h, size,
                  GMEM_MOVEABLE | _WinAllocFlag)) != 0)
                   return GlobalLock(h);
          }
      }
      else
#endif
      {
          // a quick and dirty realloc
          void far *TempPtr = _farmallocf(size, flags);
          unsigned long TempSize;

          if (TempPtr)
          {
              _ES = FP_SEG(block);
              _DI = FP_OFF(block);

              asm push si
              _SIZMEM();
              asm pop si

              TempSize = (unsigned long)((void _seg *)(_DX)+(void near *)(_AX));
              _fmemcpy(TempPtr, block,
                  (size_t) (size > TempSize ? TempSize : size));
              _farfreef(block, flags);
              return TempPtr;
          }
      }
       }
    }
    return NULL;        // catch all.
}
