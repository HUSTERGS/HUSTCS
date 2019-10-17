/*  malloc.h

    memory management functions and variables.

    Copyright (c) 1991, 1992 by Borland International
    All Rights Reserved.
*/

#include <alloc.h>

#if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)

/* Near heap functions currently allowed only in small data models */

#define _nmalloc(size)          malloc(size)
#define _nfree(block)           free(block)
#define _nrealloc(block,size)   realloc(block,size)
#define _ncalloc(num,size)      calloc(num,size)
#define _nheapmin()             0
#define _memavl()               coreleft()

#endif  /* small data models */

/* Model-independent functions */

#define _fmalloc(size)          farmalloc((unsigned long)(size))
#define _ffree(block)           farfree(block)
#define _frealloc(block,size)   farrealloc(block,(unsigned long)(size))
#define _fcalloc(num,size)      farcalloc((unsigned long)(num),(unsigned long)(size))
#define halloc(num,size)        (void huge *)farmalloc((unsigned long)(num)*(size))
#define hfree(block)            farfree((void far *)(block))
#define _heapmin()              0
#define _fheapmin()             0

/* Prototypes */

#ifdef __cplusplus
extern "C" {
#endif
void *      _Cdecl alloca     (size_t __size);
void *      _Cdecl __alloca__ (size_t __size);
#if defined(__BCOPT__ ) && !defined(_Windows)
#define     alloca  __alloca__
#endif
size_t      _Cdecl stackavail (void);
#ifdef __cplusplus
}
#endif
