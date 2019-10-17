/*-----------------------------------------------------------------------*
 * filename - vappv.cpp
 * C++ VECTOR APPLY for virtual base classes
 * This is called internally by the compiler to copy
 * arrays of classes having assignment operators or ref constructors
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <_vector.h>

extern "C"
void  _vector_applyv_(void far * dest,  // address of destination array
                      void far * src,   // address of source array
                      size_t size,      // size of each object
                      unsigned count,   // number of objects
                      unsigned mode,    // type of function to call
                      ...
                     )

/* This routine is used to copy an array of class type.

   Since the routine used for the class may be of either memory model, and
   take arguments of any memory model, we are forced to pass a mode
   parameter to tell us how to cast it.  Since we must pass a near pointer
   for near functions and a far call for far functions, we can't even know
   the argument type until runtime, so we have to use varargs to get at it.
   We do assume that both source and destination have the same distance
   modifier, and the compiler enforces that.

   The interpretation of the mode parameter is:
       far function    0x01     VFARCALL
       pascal call     0x02     VPASCAL
       far pointer     0x04     VFARPTR
       fastcall        0x20     VFASTCALL
       fastthis        0x80     VFASTTHIS
       this last       0x100    VTHISLAST
*/
{
    va_list ap;         /* for access to parameters */
    appvNNC np;         /* Near pointer version */
    appvFNC fp;         /* Far pointer version */

    va_start(ap, mode);

    if (mode & 1)
        fp = va_arg(ap, appvFNC);
    else
        np = va_arg(ap, appvNNC);

    if (mode & VFASTTHIS)   // this-last has no effect with fast-this
        mode &= ~(VTHISLAST);

    do
        {
        switch (mode)
            {
            case 0:
                (*(appvNNC) np)((void near *)dest, 0, (void near *)src); break;
            case (VFARCALL):
                (*(appvFNC) fp)((void near *)dest, 0, (void near *)src); break;
            case (VPASCAL):
                (*(appvNNP) np)((void near *)dest, 0, (void near *)src); break;
            case (VPASCAL | VTHISLAST):
                (*(appvNNPL) np)(0, (void near *)src, (void near *)dest); break;
            case (VFARCALL | VPASCAL):
                (*(appvFNP) fp)((void near *)dest, 0, (void near *)src); break;
            case (VFARCALL | VPASCAL | VTHISLAST):
                (*(appvFNPL) fp)(0, (void near *)src, (void near *)dest); break;
            case (VFASTCALL):
                (*(appvNNF) np)((void near *)dest, 0, (void near *)src); break;
            case (VFASTCALL | VTHISLAST):
                (*(appvNNFL) np)(0, (void near *)src, (void near *)dest); break;
            case (VFARCALL | VFASTCALL):
                (*(appvFNF) fp)((void near *)dest, 0, (void near *)src); break;
            case (VFARCALL | VFASTCALL | VTHISLAST):
                (*(appvFNFL) fp)(0, (void near *)src, (void near *)dest); break;
            case (VFARPTR):
                (*(appvNFC) np)((void far  *)dest, 0, (void far  *)src); break;
            case (VFARCALL | VFARPTR):
                (*(appvFFC) fp)((void far  *)dest, 0, (void far  *)src); break;
            case (VFARPTR | VPASCAL):
                (*(appvNFP) np)((void far  *)dest, 0, (void far  *)src); break;
            case (VFARPTR | VPASCAL | VTHISLAST):
                (*(appvNFPL) np)(0, (void far  *)src, (void far  *)dest); break;
            case (VFARCALL | VFARPTR | VPASCAL):
                (*(appvFFP) fp)((void far  *)dest, 0, (void far  *)src); break;
            case (VFARCALL | VFARPTR | VPASCAL | VTHISLAST):
                (*(appvFFPL) fp)(0, (void far  *)src, (void far  *)dest); break;
            case (VFARPTR | VFASTCALL):
                (*(appvNFF) np)((void far  *)dest, 0, (void far  *)src); break;
            case (VFARPTR | VFASTCALL | VTHISLAST):
                (*(appvNFFL) np)(0, (void far  *)src, (void far  *)dest); break;
            case (VFARCALL | VFARPTR | VFASTCALL):
                (*(appvFFF) fp)((void far  *)dest, 0, (void far  *)src); break;
            case (VFARCALL | VFARPTR | VFASTCALL | VTHISLAST):
                (*(appvFFFL) fp)(0, (void far  *)src, (void far *)dest); break;
            case (0 | VFASTTHIS):
                LOAD_NEAR_THIS(dest);
                (*(appvNNCT) np)(0, (void near *)src);
                END_NEAR_THIS();
                break;
            case (VFARCALL | VFASTTHIS):
                LOAD_NEAR_THIS(dest);
                (*(appvFNCT) fp)(0, (void near *)src);
                END_NEAR_THIS();
                break;
            case (VPASCAL | VFASTTHIS):
                LOAD_NEAR_THIS(dest);
                (*(appvNNPT) np)(0, (void near *)src);
                END_NEAR_THIS();
                break;
            case (VFARCALL | VPASCAL | VFASTTHIS):
                LOAD_NEAR_THIS(dest);
                (*(appvFNPT) fp)(0, (void near *)src);
                END_NEAR_THIS();
                break;
            case (VFASTCALL | VFASTTHIS):
                LOAD_NEAR_THIS(dest);
                (*(appvNNFT) np)(0, (void near *)src);
                END_NEAR_THIS();
                break;
            case (VFARCALL | VFASTCALL | VFASTTHIS):
                LOAD_NEAR_THIS(dest);
                (*(appvFNFT) fp)(0, (void near *)src);
                END_NEAR_THIS();
                break;
            case (VFARPTR | VFASTTHIS):
                LOAD_FAR_THIS(dest);
                (*(appvNFCT) np)(0, (void far  *)src);
                END_FAR_THIS();
                break;
            case (VFARCALL | VFARPTR | VFASTTHIS):
                LOAD_FAR_THIS(dest);
                (*(appvFFCT) fp)(0, (void far  *)src);
                END_FAR_THIS();
                break;
            case (VFARPTR | VPASCAL | VFASTTHIS):
                LOAD_FAR_THIS(dest);
                (*(appvNFPT) np)(0, (void far  *)src);
                END_FAR_THIS();
                break;
            case (VFARCALL | VFARPTR | VPASCAL | VFASTTHIS):
                LOAD_FAR_THIS(dest);
                (*(appvFFPT) fp)(0, (void far  *)src);
                END_FAR_THIS();
                break;
            case (VFARPTR | VFASTCALL | VFASTTHIS):
                LOAD_FAR_THIS(dest);
                (*(appvNFFT) np)(0, (void far  *)src);
                END_FAR_THIS();
                break;
            case (VFARCALL | VFARPTR | VFASTCALL | VFASTTHIS):
                LOAD_FAR_THIS(dest);
                (*(appvFFFT) fp)(0, (void far  *)src);
                END_FAR_THIS();
                break;
            default:
                abort(); break;
            }
        (char far *) dest += size;
        (char far *) src += size;
        } while (--count > 0);
}
