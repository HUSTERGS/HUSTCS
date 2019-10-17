/*------------------------------------------------------------------------
 * filename - fbrk.c
 *
 * function(s)
 *        normalize - normalize a pointer
 *        _brk      - changes data-segment space allocation
 *        _sbrk     - changes data-segment space allocation
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <alloc.h>
#include <dos.h>
#include <_fheap.h>

#define addressat(segment) ((void far*)((unsigned long)(segment) << 16))


/*---------------------------------------------------------------------*

Name            normalize - normalize a pointer

Usage           local to this module

Description     normalizes a far pointer

Return value    success : 1
                failure : 0

*---------------------------------------------------------------------*/
static  int near pascal normalize(char far *cp)
{
        extern  unsigned _psp;
        static  unsigned xsize = 0;
        unsigned size, result;

        size = 1 + FP_SEG(cp);
        size -= _psp;
        size = (size + 63) >> 6;        /* Convert size to 1K units */
        if (size == xsize)              /* Same as current size, do nothing */
        {
                _brklvl = cp;
                return(1);
        }
        size <<= 6;
        result = FP_SEG(_heaptop);
        if (size + _psp > result)
                size = result - _psp;
        result = setblock(_psp, size);
        if (result == 0xffff)
        {
                xsize = size >> 6;
                _brklvl = cp;
                return(1);
        }
        else    {
                _heaptop = addressat(_psp + result);
                /* If we fail, pass that back to the outer routines.
                   This only happens if we did an exec of a program that
                   did a keep.  Also, adjust the _heaptop to make future calls
                   faster. */
                return(0);
        }
}


/*--------------------------------------------------------------------------*

   In the large data models brk and sbrk are hooks to _brk and
   _sbrk respectively.  _brk and _sbrk work with the far heap.
   brk and sbrk are found in BRK.CAS

*---------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*

Name            _brk - changes data-segment space allocation

Usage           int _brk(void huge *addr);

Prototype in    alloc.h

Description     _brk sets the break value to addr and changes the
                allocated space accordingly

Return value    success : 0
                failure : -1 and errno set to ENOMEM (Not enough core)

*--------------------------------------------------------------------------*/
int cdecl near _brk(void huge *addr)
{
        if ((addr < _heapbase) || (addr > _heaptop) ||
                !normalize((char far *)addr))
                return(-1);
        else
                return(0);
}


/*---------------------------------------------------------------------*

Name            _sbrk - changes data-segment space allocation

Usage           void huge *_sbrk(long incr);

Prototype in    alloc.h

Description     _sbrk adds incr bytes to the break value and changes the
                allocated space accordingly. incr can be negative, in
                which case the amount of allocated space is decreased.

Return value    success : the old break value
                failure : -1 and errno set to ENOMEM (Not enough core)

*---------------------------------------------------------------------*/
void huge *cdecl near _sbrk(long incr)
{
        char    huge    *cp;
        char    huge    *old;

    if ((((long)FP_SEG(_brklvl) << 4) + FP_OFF(_brklvl) + incr) > 0xfffffL)
                return((void huge *)-1L);
        cp = _brklvl + incr;
        if ((cp < _heapbase) || (cp > _heaptop))
                return((void huge *)-1L);
        old = _brklvl;
        if (!normalize((char far *)cp))
                return((void huge *)-1L);
        return(old);
}

