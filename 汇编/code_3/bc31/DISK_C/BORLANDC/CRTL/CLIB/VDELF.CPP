/*-----------------------------------------------------------------------*
 * filename - vdel.cpp
 * C++ vector_delete
 * Called internally by the compiler to deallocate arrays of classes
 * having destructors
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
#include <dos.h>
#include <_vector.h>

void _vector_delete_(void far *ptr,     // address of array (always needed)
             size_t size,               // size of each object
             unsigned long count,       // how many objects
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

    if (mode & VSTORECNT)       // if stored count
        count = *((unsigned long far *) ((char far *)ptr - sizeof(count)));

    if (destruct)
        {
        // get call type
        unsigned CallType = mode & VCALLTYPE;

        if (CallType & VFASTTHIS)
            CallType &= ~(VTHISLAST);

        for( char huge *p = (char huge *) ptr + size * (count - 1);
             count-- > 0; p -= size )
            {
            switch (CallType)
                {
                case (VFARPTR):
                    (*(destNFC) np)((void far  *) p, 2); break;
                case (VFARCALL | VFARPTR):
                    (*(destFFC) fp)((void far  *) p, 2); break;
                case (VFARPTR | VPASCAL):
                    (*(destNFP) np)((void far  *) p, 2); break;
                case (VFARPTR | VPASCAL | VTHISLAST):
                    (*(destNFPL) np)(2, (void far  *) p); break;
                case (VFARCALL | VFARPTR | VPASCAL):
                    (*(destFFP) fp)((void far  *) p, 2); break;
                case (VFARCALL | VFARPTR | VPASCAL | VTHISLAST):
                    (*(destFFPL) fp)(2, (void far  *) p); break;
                case (VFARPTR | VFASTCALL):
                    (*(destNFF) np)((void far  *) p, 2); break;
                case (VFARPTR | VFASTCALL | VTHISLAST):
                    (*(destNFFL) np)(2, (void far  *) p); break;
                case (VFARCALL | VFARPTR | VFASTCALL):
                    (*(destFFF) fp)((void far  *) p, 2); break;
                case (VFARCALL | VFARPTR | VFASTCALL | VTHISLAST):
                    (*(destFFFL) fp)(2, (void far  *) p); break;
                case (VFARPTR | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(destNFCT) np)(2);
                    END_FAR_THIS();
                    break;
                case (VFARCALL | VFARPTR | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(destFFCT) fp)(2);
                    END_FAR_THIS();
                    break;
                 case (VFARPTR | VPASCAL | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(destNFPT) np)(2);
                    END_FAR_THIS();
                    break;
                case (VFARCALL | VFARPTR | VPASCAL | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(destFFPT) fp)(2);
                    END_FAR_THIS();
                    break;
                 case (VFARPTR | VFASTCALL | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(destNFFT) np)(2);
                    END_FAR_THIS();
                    break;
                case (VFARCALL | VFARPTR | VFASTCALL | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(destFFFT) fp)(2);
                    END_FAR_THIS();
                    break;
                default:
                    abort(); break;
                }
            }
        }

    if (mode & VDEALLOC)
        {
        unsigned Header;
        unsigned Overhead = 0;

        if (mode & 0x10)        // stored count
            Overhead = sizeof(count);

        if (mode & VHUGEVECT)   // huge vector
            {
            Overhead += sizeof(Header);
            Header = *((char far *)ptr - Overhead);
            ptr = MK_FP(FP_SEG(ptr), Header);
            }
        else
            ptr = (char far *)ptr - Overhead;

        operator delete((void far *)ptr);
        }
}
