/*-----------------------------------------------------------------------*
 * filename - vnewv.cpp
 * C++ VECTOR_NEW for virtual base classes.
 * Called internally by the compiler to allocate arrays of classes
 * having constructors
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

typedef void (near * consvNNC)(void near*, int);
typedef void (near * consvNFC)(void far*, int);
typedef void pascal (near * consvNNP)(void near*, int);
typedef void pascal (near * consvNFP)(void far*, int);
typedef void (far * consvFNC)(void near*, int);
typedef void (far * consvFFC)(void far*, int);
typedef void pascal (far * consvFNP)(void near*, int);
typedef void pascal (far * consvFFP)(void far*, int);


extern "C"
void far * _vector_vnew_(void far* ptr, // address of array, 0 means allocate it
                 size_t size,           // size of each object
                 unsigned count,        // how many objects
                 unsigned mode,         // actual type of constructor
                 ...
                 )
/* This routine is used to initialize an array of class type.  If ptr is
   NULL, it allocates the space for the array first.  Since the constructor
   for the class may be of either memory model, and take an argument of any
   memory model, we are forced to pass a mode parameter to tell us how to
   cast it.  Since we must pass a near pointer for near functions and a
   far call for far functions, we can't even know the argument type until
   runtime, so we have to use varargs to get at it.  This version passes the
   second argument needed for a class with virtual bases.

   The interpretation of the mode parameter is:
       far function             0x01
       pascal call              0x02
       far pointer              0x04
       stored count             0x10
*/
{
    va_list ap;         /* for access to parameters */
    consvNNC np;        /* Near pointer version */
    consvFNC fp;        /* Far pointer version */
    int stored_count;

    va_start(ap, mode);

    if (mode & 1)
        fp = va_arg(ap, consvFNC);
    else
        np = va_arg(ap, consvNNC);

    if( ptr == 0 )
        {
        stored_count = mode & 0x10;
        if(stored_count)
            ptr = operator new((size * count)+sizeof(count));
        else
            ptr = operator new(size * count);

        if (ptr == 0)
            return 0;

        if (stored_count)
            {
            *(unsigned far *)ptr = count;
            ptr = ((char far *)ptr + sizeof(count));
            }
        }

    mode &= 0x07;   // strip out all flags except call type

    for( char far* p = (char far*) ptr;  count-- > 0;  p += size )
        switch (mode)
            {
            case 0: np((void near *) p, 0); break;
            case 1: fp((void near *) p, 0); break;
            case 2: (*(consvNNP) np)((void near *) p, 0); break;
            case 3: (*(consvFNP) fp)((void near *) p, 0); break;
            case 4: (*(consvNFC) np)((void far  *) p, 0); break;
            case 5: (*(consvFFC) fp)((void far  *) p, 0); break;
            case 6: (*(consvNFP) np)((void far  *) p, 0); break;
            default:(*(consvFFP) fp)((void far  *) p, 0); break;
            }
    return ptr;
}
