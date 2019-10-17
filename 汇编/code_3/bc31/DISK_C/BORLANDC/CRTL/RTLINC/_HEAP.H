/*------------------------------------------------------------------------
 * filename - _HEAP.H
 *      near heap variables and functions
 *-----------------------------------------------------------------------*/

/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     C/C++ Run Time Library - Version 4.0                     |*/
/*|                                                              |*/
/*|                                                              |*/
/*|     Copyright (c) 1987, 1991 by Borland International        |*/
/*|     All Rights Reserved.                                     |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

#define MARGIN  512

        /* Near Heap Variables */

extern  unsigned         __brklvl;

        /* Near Heap Functions */

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif
void    *cdecl  malloc(size_t __nbytes);
void    cdecl free(void _FAR *__ap);
void *cdecl realloc(void _FAR *__ptr, size_t __size);
#if defined(__LARGE__) || defined(__HUGE__) || defined(__COMPACT__)
unsigned long cdecl     coreleft(void);
#else
unsigned cdecl          coreleft(void);
#endif
int     cdecl near      __brk(void *__addr);
void    *cdecl near     __sbrk(long __incr);
#ifdef __cplusplus
}
#endif
