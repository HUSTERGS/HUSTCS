/*-----------------------------------------------------------------------*
 * filename - vdel.cpp
 * C++ vector_delete
 * Called internally by the compiler to deallocate arrays of classes
 * having destructors
 *
 * NOTE: This is the old version used in TC++ 1.0 and BC++ 2.0
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdlib.h>
#include <stdarg.h>

typedef void (near * destNNC)(void near*, int);
typedef void (near * destNFC)(void far*, int);
typedef void pascal (near * destNNP)(void near*, int);
typedef void pascal (near * destNFP)(void far*, int);
typedef void (far * destFNC)(void near*, int);
typedef void (far * destFFC)(void far*, int);
typedef void pascal (far * destFNP)(void near*, int);
typedef void pascal (far * destFFP)(void far*, int);

extern "C"
void _vector_delete_(void far *ptr,     // address of array (always needed)
             size_t size,               // size of each object
             unsigned count,            // how many objects
             unsigned mode,             // How to call
             ...
            )
/* This routine is used to destroy an array of class type.  If mode is
   set, it deallocates the space for the array afterwards. Since the
   destructor for the class may be of either memory model, and take
   an argument of any memory model, we are forced to pass a mode parameter
   to tell us how to cast it.  Since we must pass a near pointer for near
   functions and a far pointer for far functions, we can't even know the
   argument type until runtime, so we have to use varargs to get at it.

   The interpretation of the mode parameter is:
    far function    0x01
    pascal call     0x02
    far pointer     0x04
    deallocate      0x08
    stored count    0x10
*/
{
    va_list ap;     /* for access to parameters */
    destNNC np;     /* Near pointer version */
    destFNC fp;     /* Far pointer version */
    int dealloc = mode & 8;
    int stored_count = mode & 0x10;

    if ( ptr == 0 )
        return;

    va_start(ap, mode);

    if (mode & 1)
        fp = va_arg(ap, destFNC);
    else
        np = va_arg(ap, destNNC);

    if (stored_count)   // If count is stored then use it
        count = *((unsigned far *)ptr - 1);

    mode &= 0x07;   // strip out all flags except call type

    for( char far *p = (char far *) ptr + size * (count - 1);
            count-- > 0; p -= size )
        switch (mode)
            {
            case 0: np((void near *) p, 2); break;
            case 1: fp((void near *) p, 2); break;
            case 2: (*(destNNP) np)((void near *) p, 2); break;
            case 3: (*(destFNP) fp)((void near *) p, 2); break;
            case 4: (*(destNFC) np)((void far  *) p, 2); break;
            case 5: (*(destFFC) fp)((void far  *) p, 2); break;
            case 6: (*(destNFP) np)((void far  *) p, 2); break;
            default:(*(destFFP) fp)((void far  *) p, 2); break;
            }

    if( dealloc )
        {
        if (stored_count)
            ptr = (char far *)ptr - sizeof(count);
        operator delete((void *)ptr);
        }
}
