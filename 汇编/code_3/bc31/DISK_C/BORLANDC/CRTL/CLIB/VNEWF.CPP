/*-----------------------------------------------------------------------*
 * filename - vnewf.cpp
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
#include <dos.h>
#include <_vector.h>

void far * _vector_new_(void far *ptr,  // address of array, 0 means allocate
        size_t size,                    // size of each object
        unsigned long count,            // how many objects
        unsigned mode,                  // actual type of constructor
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

    if (ptr == 0)               // should we allocate it?
        {
        unsigned Header;
        unsigned Overhead = 0;
        unsigned PadFromZero;

        if (mode & VSTORECNT)        // stored count
            Overhead = sizeof(count);

        if (mode & VHUGEVECT)        // huge vector
            {
            Overhead += sizeof(Header);
            ptr = operator new((unsigned long)count * size + Overhead + size);
            if (!ptr)
                return 0;
            PadFromZero = (unsigned) (65536L % size);
            Header = FP_OFF(ptr);
            while (PadFromZero < Overhead + Header)
                PadFromZero += size;

            (char far *)ptr += PadFromZero - Header - Overhead;
            *(unsigned far *)ptr = Header;
            ((unsigned far *)ptr)++;
            }
        else
            {
            // check that additional bytes don't make it go over 64K
            unsigned long Length = size * count + Overhead;
            if (Length > 0xFFFF)
                return 0;

            ptr = operator new((unsigned long)Length);
            if (!ptr)
                return 0;
            }

        // have ptr at either final location or count before

        if (mode & VSTORECNT)    // store count
            {
            *(unsigned long far *)ptr = count;
            ((unsigned long far *)ptr)++;
            }
        }

    mode &= VCALLTYPE;      // strip out all flags except call type

    if (mode & VFASTTHIS)   // this-last has no effect with fast-this
        mode &= ~(VTHISLAST);

    if (construct)
        {
        for (char huge *p = (char huge *) ptr; count-- > 0; p += size)
            switch (mode)
                {
                case (VFARPTR):
                    (*(constNFC) np)((void far *) p); break;
                case (VFARCALL | VFARPTR):
                    (*(constFFC) fp)((void far *) p); break;
                case (VFARPTR | VPASCAL):
                case (VFARPTR | VPASCAL | VTHISLAST):
                    (*(constNFP) np)((void far *) p); break;
                case (VFARCALL | VFARPTR | VPASCAL):
                case (VFARCALL | VFARPTR | VPASCAL | VTHISLAST):
                    (*(constFFP) fp)((void far *) p); break;
                case (VFARPTR | VFASTCALL):
                case (VFARPTR | VFASTCALL | VTHISLAST):
                    (*(constNFF) np)((void far *) p); break;
                case (VFARCALL | VFARPTR | VFASTCALL):
                case (VFARCALL | VFARPTR | VFASTCALL | VTHISLAST):
                    (*(constFFF) fp)((void far *) p); break;
                case (VFARPTR | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(constNFCT) np)();
                    END_FAR_THIS();
                    break;
                case (VFARCALL | VFARPTR | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(constFFCT) fp)();
                    END_FAR_THIS();
                    break;
                case (VFARPTR | VPASCAL | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(constNFPT) np)();
                    END_FAR_THIS();
                    break;
                case (VFARCALL | VFARPTR | VPASCAL | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(constFFPT) fp)();
                    END_FAR_THIS();
                    break;
                case (VFARPTR | VFASTCALL | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(constNFFT) np)();
                    END_FAR_THIS();
                    break;
                case (VFARCALL | VFARPTR | VFASTCALL | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(constFFFT) fp)();
                    END_FAR_THIS();
                    break;
                default:
                    abort(); break;
                }
        }
    return ptr;
}
