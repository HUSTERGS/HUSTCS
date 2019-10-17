/*------------------------------------------------------------------------
 * filename - suballoc.h
 *
 *      definitions for Windows memory suballocator
 *-----------------------------------------------------------------------*/

/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     C/C++ Run Time Library - Version 4.0                     |*/
/*|                                                              |*/
/*|                                                              |*/
/*|     Copyright (c) 1991 by Borland International              |*/
/*|     All Rights Reserved.                                     |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

#if !defined(__SUBALLOC_H)
#define __SUBALLOC_H

struct TSubAllocClientData
{
        void far *MemBlockPtr;
        int     MemBlockCount;
};

#if defined( __cplusplus )
extern "C"
{
#endif
        extern struct TSubAllocClientData far * __GetSubAllocClientData();
#if defined( __cplusplus )
}
#endif

#endif // __SUBALLOC_H
