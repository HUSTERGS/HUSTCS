/*------------------------------------------------------------------------
 * filename - _fheap.h
 *
 *      far heap variables and functions
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

        /* Far Heap Variables */

extern  char            huge    *_heapbase;
extern  char            huge    *_heaptop;
extern  char            huge    *_brklvl;

        /* Far Heap Functions */

#ifdef __cplusplus
extern "C" {
#endif
void far * cdecl        farmalloc(unsigned long __nbytes);
void cdecl              farfree(void far *__ap);
void far *cdecl         farrealloc(void far *__ptr, unsigned long __size);
unsigned long cdecl     farcoreleft(void);
int  cdecl near         _brk(void huge *__addr);
void huge *cdecl near   _sbrk(long __incr);
#ifdef __cplusplus
}
#endif
