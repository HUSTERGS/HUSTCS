/*-----------------------------------------------------------------------*
 * filename - vdel.cpp
 * C++ vector_delete
 * Called internally by the compiler to deallocate arrays of classes
 *  having destructors
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

void _vector_delete_(void near *ptr,    // address of array (always needed)
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

   If the destructor pointer is NULL no destructors are called.

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
#else
    va_list ap;         // for access to parameters
    destNNC np;         // near call version
    destFNC fp;         // far call version
    int destruct = 1;   // flag whether to call destructors

    if (!ptr)
        return;

    va_start(ap, mode);

    if (mode & VFARCALL)
        {
        fp = va_arg(ap, destFNC);
        if (!fp)
            destruct = 0;
        }
    else
        {
        np = va_arg(ap, destNNC);
        if (!np)
            destruct = 0;
        }

    if (mode & VSTORECNT)   // if stored count
        count = *((unsigned *) ((char *)ptr - sizeof(count)));

    if (destruct)
        {
        // get call type
        unsigned CallType = mode & VCALLTYPE;

        // this-last has no effect with fast-this
        if (CallType & VFASTTHIS)
            CallType &= ~(VTHISLAST);

        for(char near *p = (char near *) ptr + size * (count - 1);
            count-- > 0; p -= size)
            {
            switch (CallType)
                {
                case 0:
                    (*(destNNC) np)((void near *) p, 2); break;
                case (VFARCALL):
                    (*(destFNC) fp)((void near *) p, 2); break;
                case (VPASCAL):
                    (*(destNNP) np)((void near *) p, 2); break;
                case (VPASCAL | VTHISLAST):
                    (*(destNNPL) np)(2, (void near *) p); break;
                case (VFARCALL | VPASCAL):
                    (*(destFNP) fp)((void near *) p, 2); break;
                case (VFARCALL | VPASCAL | VTHISLAST):
                    (*(destFNPL) fp)(2, (void near *) p); break;
                case (VFASTCALL):
                    (*(destNNF) np)((void near *) p, 2); break;
                case (VFASTCALL | VTHISLAST):
                    (*(destNNFL) np)(2, (void near *) p); break;
                case (VFARCALL | VFASTCALL):
                    (*(destFNF) fp)((void near *) p, 2); break;
                case (VFARCALL | VFASTCALL | VTHISLAST):
                    (*(destFNFL) fp)(2, (void near *) p); break;
                case (0 | VFASTTHIS):
                    LOAD_NEAR_THIS(p);
                    (*(destNNCT) np)(2);
                    END_NEAR_THIS();
                    break;
                case (VFARCALL | VFASTTHIS):
                    LOAD_NEAR_THIS(p);
                    (*(destFNCT) fp)(2);
                    END_NEAR_THIS();
                    break;
                case (VPASCAL | VFASTTHIS):
                    LOAD_NEAR_THIS(p);
                    (*(destNNPT) np)(2);
                    END_NEAR_THIS();
                    break;
                case (VFARCALL | VPASCAL | VFASTTHIS):
                    LOAD_NEAR_THIS(p);
                    (*(destFNPT) fp)(2);
                    END_NEAR_THIS();
                    break;
                case (VFASTCALL | VFASTTHIS):
                    LOAD_NEAR_THIS(p);
                    (*(destNNFT) np)(2);
                    END_NEAR_THIS();
                    break;
                case (VFARCALL | VFASTCALL | VFASTTHIS):
                    LOAD_NEAR_THIS(p);
                    (*(destFNFT) fp)(2);
                    END_NEAR_THIS();
                    break;
                default:
                    abort(); break;
                }
            }
        }

    if (mode & VDEALLOC)
        {
        if (mode & VSTORECNT)   // stored count
            ptr = (char *)ptr - sizeof(count);

        operator delete((void near *)ptr);
        }
#endif
}
