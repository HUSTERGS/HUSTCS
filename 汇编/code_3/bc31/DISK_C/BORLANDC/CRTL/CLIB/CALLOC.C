/*------------------------------------------------------------------------
 * filename - calloc.c
 *
 * function(s)
 *        calloc - allocates main memory
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <alloc.h>
#include <stddef.h>
#include <mem.h>


/*------------------------------------------------------------------------*

Name            calloc - allocates main memory

Usage           void *calloc(size_t nelem, size_t elsize);

Prototype in    stdlib.h and alloc.h

Description     calloc allocates a  block like malloc, except the  block is
                of size nelem times elsize. The block is cleared to 0.

Return value    calloc returns a  pointer to the newly allocated  block, or
                NULL if not  enough space exists for the new  block or, the
                requested size is equal to 0.

*-------------------------------------------------------------------------*/
void * _FARFUNC calloc(size_t nelem, size_t elsize)
{
        unsigned long   msize;
        register char   *cp;

        msize = (unsigned long)nelem * elsize;
        cp = (msize > 0xFFFF) ? NULL : malloc((unsigned)msize);
        if (cp)
                setmem(cp, (unsigned)msize, 0);
        return(cp);
}
