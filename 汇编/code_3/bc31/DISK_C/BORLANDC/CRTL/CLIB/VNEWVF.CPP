/*-----------------------------------------------------------------------*
 * filename - vnewvf.cpp
 * C++ VECTOR_NEW for virtual base classes.
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

void far * _vector_vnew_(void far* ptr, // address of array, 0 means allocate it
                 size_t size,           // size of each object
                 unsigned long count,   // how many objects
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
    consvNNC np;        // near call version
    consvFNC fp;        // far call version
    int construct = 1;  // flag whether to call constructors

    va_start(ap, mode);

    if (mode & VFARCALL)
        {
        fp = va_arg(ap, consvFNC);
        if (!fp)
            construct = 0;
        }
    else
        {
        np = va_arg(ap, consvNNC);
        if (!np)
            construct = 0;
        }

    if (ptr == 0)               // should we allocate it?
        {
        unsigned Header;
        unsigned Overhead = 0;
        unsigned PadFromZero;

        if (mode & VSTORECNT)   // stored count
            Overhead = sizeof(count);

        if (mode & VHUGEVECT)   // huge vector
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
            unsigned long Length = size * count + Overhead;
            if (Length > 0xFFFF)
                return 0;

            ptr = operator new((unsigned long)Length);
            if (!ptr)
                return 0;
            }

        // have ptr at either final location or count before

        if (mode & VSTORECNT)   // store count
            {
            *(unsigned long far *)ptr = count;
            ((unsigned long far *)ptr)++;
            }
        }

    mode &= VCALLTYPE;   // strip out all flags except call type

    if (mode & VFASTTHIS)   // this-last has no effect with fast-this
        mode &= ~(VTHISLAST);

    if (construct)
        {
        for( char huge *p = (char huge *) ptr;  count-- > 0;  p += size )
            switch (mode)
                {
                case (VFARPTR):
                    (*(consvNFC) np)((void far *) p, 0); break;
                case (VFARCALL | VFARPTR):
                    (*(consvFFC) fp)((void far *) p, 0); break;
                case (VFARPTR | VPASCAL):
                    (*(consvNFP) np)((void far *) p, 0); break;
                case (VFARPTR | VPASCAL | VTHISLAST):
                    (*(consvNFPL) np)(0, (void far *) p); break;
                case (VFARCALL | VFARPTR | VPASCAL):
                    (*(consvFFP) fp)((void far *) p, 0); break;
                case (VFARCALL | VFARPTR | VPASCAL | VTHISLAST):
                    (*(consvFFPL) fp)(0, (void far *) p); break;
                case (VFARPTR | VFASTCALL):
                    (*(consvNFF) np)((void far *) p, 0); break;
                case (VFARPTR | VFASTCALL | VTHISLAST):
                    (*(consvNFFL) np)(0, (void far *) p); break;
                case (VFARCALL | VFARPTR | VFASTCALL):
                    (*(consvFFF) fp)((void far *) p, 0); break;
                case (VFARCALL | VFARPTR | VFASTCALL | VTHISLAST):
                    (*(consvFFFL) fp)(0, (void far *) p); break;
                case (VFARPTR | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(consvNFCT) np)(0);
                    END_FAR_THIS();
                    break;
                case (VFARCALL | VFARPTR | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(consvFFCT) fp)(0);
                    END_FAR_THIS();
                    break;
                case (VFARPTR | VPASCAL | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(consvNFPT) np)(0);
                    END_FAR_THIS();
                    break;
                case (VFARCALL | VFARPTR | VPASCAL | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(consvFFPT) fp)(0);
                    END_FAR_THIS();
                    break;
                case (VFARPTR | VFASTCALL | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(consvNFFT) np)(0);
                    END_FAR_THIS();
                    break;
                case (VFARCALL | VFARPTR | VFASTCALL | VFASTTHIS):
                    LOAD_FAR_THIS(p);
                    (*(consvFFFT) fp)(0);
                    END_FAR_THIS();
                    break;
                default:
                    abort(); break;
                }
        }
    return ptr;
}
