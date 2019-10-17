/*-----------------------------------------------------------------------*
 * filename - vnewn.cpp
 * C++ VECTOR_NEW
 * Called internally by the compiler to allocate arrays of classes
 *  having constructors
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
#include <_vector.h>

#pragma argsused

void near * _vector_new_(void near *ptr, // address of array, 0 means allocate
        size_t size,                     // size of each object
        unsigned count,                  // how many objects
        unsigned mode,                   // actual type of constructor
        ...
        )
/* This routine is used to initialize an array of class type.  If ptr is
   NULL, it allocates the space for the array first.  Since the constructor
   for the class may be of either memory model, and take an argument of any
   memory model, we are forced to pass a mode parameter to tell us how to
   cast it.  Since we must pass a near pointer for near functions and a
   far call for far functions, we can't even know the argument type until
   runtime, so we have to use varargs to get at it.

   If the constructor pointer is NULL no constructors are called.

   The interpretation of the mode parameter is:
       far function    0x01     VFARCALL
       pascal call     0x02     VPASCAL
       far pointer     0x04     VFARPTR
       deallocate      0x08     VDEALLOC
       stored count    0x10     VSTORECNT
       fastcall        0x20     VFASTCALL
       huge vector     0x40     VHUGEVECT
       fastthis        0x80     VFASTTHIS
       this last       0x100    VTHISLAST
*/
{
#if defined(__LARGE__) || defined(__HUGE__) || defined(__COMPACT__)
    abort();
    return 0;
#else
    va_list ap;         // for access to parameters
    constNNC np;        // near call version
    constFNC fp;        // far call version
    int construct = 1;  // flag whether to call constructors

    va_start(ap, mode);

    if (mode & VFARCALL)
        {
        fp = va_arg(ap, constFNC);
        if (!fp)
            construct = 0;
        }
    else
        {
        np = va_arg(ap, constNNC);
        if (!np)
            construct = 0;
        }

    if( ptr == 0 )
        {
        unsigned long Length = size * count;

        if (mode & VSTORECNT)       // stored count
            Length += sizeof(count);

        // check that additional bytes don't make it go over 64K
        if (Length > 0xFFFF)
            return 0;

        ptr = operator new((unsigned)Length);

        if (!ptr)
            return 0;

        // have ptr at either final location or count before
        if (mode & VSTORECNT)       // store count
            {
            *(unsigned *)ptr = count;
            ((unsigned *)ptr)++;
            }
        }

    mode &= VCALLTYPE;      // strip out all flags except call type

    if (mode & VFASTTHIS)   // this-last has no effect with fast-this
        mode &= ~(VTHISLAST);

    if (construct)
        {
        for( char *p = (char *) ptr;  count-- > 0;  p += size )
            switch (mode)
                {
                case 0:
                    (*(constNNC) np)((void near *) p); break;
                case (VFARCALL):
                    (*(constFNC) fp)((void near *) p); break;
                case (VPASCAL):
                case (VPASCAL | VTHISLAST):
                    (*(constNNP) np)((void near *) p); break;
                case (VFARCALL | VPASCAL):
                case (VFARCALL | VPASCAL | VTHISLAST):
                    (*(constFNP) fp)((void near *) p); break;
                case (VFASTCALL):
                case (VFASTCALL | VTHISLAST):
                    (*(constNNF) np)((void near *) p); break;
                case (VFARCALL | VFASTCALL):
                case (VFARCALL | VFASTCALL | VTHISLAST):
                    (*(constFNF) fp)((void near *) p); break;
                case (0 | VFASTTHIS):
                    LOAD_NEAR_THIS(p);
                    (*(constNNCT) np)();
                    END_NEAR_THIS();
                    break;
                case (VFARCALL | VFASTTHIS):
                    LOAD_NEAR_THIS(p);
                    (*(constFNCT) fp)();
                    END_NEAR_THIS();
                    break;
                case (VPASCAL | VFASTTHIS):
                    LOAD_NEAR_THIS(p);
                    (*(constNNPT) np)();
                    END_NEAR_THIS();
                    break;
                case (VFARCALL | VPASCAL | VFASTTHIS):
                    LOAD_NEAR_THIS(p);
                    (*(constFNPT) fp)();
                    END_NEAR_THIS();
                    break;
                case (VFASTCALL | VFASTTHIS):
                    LOAD_NEAR_THIS(p);
                    (*(constNNFT) np)();
                    END_NEAR_THIS();
                    break;
                case (VFARCALL | VFASTCALL | VFASTTHIS):
                    LOAD_NEAR_THIS(p);
                    (*(constFNFT) fp)();
                    END_NEAR_THIS();
                    break;
                default:
                    abort(); break;
                }
        }
    return ptr;
#endif
}
