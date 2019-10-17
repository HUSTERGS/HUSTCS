/*-----------------------------------------------------------------------*
 * filename - vapp.cpp
 * C++ VECTOR APPLY
 * This is called internally by the compiler to copy arrays of classes
 * having assignment operators or reference constructors
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
void  _vector_apply_(void far* dest,    // address of destination array
                     void far* src,     // address of source array
                     size_t size,       // size of each object
                     unsigned count,    // number of objects
                     unsigned mode,
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
    appNNC np;          /* Near pointer version */
    appFNC fp;          /* Far pointer version */

    va_start(ap, mode);

    if (mode & VFARCALL)
        fp = va_arg(ap, appFNC);
    else
        np = va_arg(ap, appNNC);

    if (mode & VFASTTHIS)   // this-last has no effect with fast-this
        mode &= ~(VTHISLAST);

    do
        {
        switch (mode)
            {
            case 0:
                (*(appNNC) np)((void near *)dest, (void near *)src); break;
            case (VFARCALL):
                (*(appFNC) fp)((void near *)dest, (void near *)src); break;
            case (VPASCAL):
                (*(appNNP) np)((void near *)dest, (void near *)src); break;
            case (VPASCAL | VTHISLAST):
                (*(appNNPL) np)((void near *)src, (void near *)dest); break;
            case (VFARCALL | VPASCAL):
                (*(appFNP) fp)((void near *)dest, (void near *)src); break;
            case (VFARCALL | VPASCAL | VTHISLAST):
                (*(appFNPL) fp)((void near *)src, (void near *)dest); break;
            case (VFASTCALL):
                (*(appNNF) np)((void near *)dest, (void near *)src); break;
            case (VFASTCALL | VTHISLAST):
                (*(appNNFL) np)((void near *)src, (void near *)dest); break;
            case (VFARCALL | VFASTCALL):
                (*(appFNF) fp)((void near *)dest, (void near *)src); break;
            case (VFARCALL | VFASTCALL | VTHISLAST):
                (*(appFNFL) fp)((void near *)src, (void near *)dest); break;
            case (VFARPTR):
                (*(appNFC) np)((void far  *)dest, (void far  *)src); break;
            case (VFARCALL | VFARPTR):
                (*(appFFC) fp)((void far  *)dest, (void far  *)src); break;
            case (VFARPTR | VPASCAL):
                (*(appNFP) np)((void far  *)dest, (void far  *)src); break;
            case (VFARPTR | VPASCAL | VTHISLAST):
                (*(appNFPL) np)((void far  *)src, (void far  *)dest); break;
            case (VFARCALL | VFARPTR | VPASCAL):
                (*(appFFP) fp)((void far  *)dest, (void far  *)src); break;
            case (VFARCALL | VFARPTR | VPASCAL | VTHISLAST):
                (*(appFFPL) fp)((void far  *)src, (void far  *)dest); break;
            case (VFARPTR | VFASTCALL):
                (*(appNFF) np)((void far  *)dest, (void far  *)src); break;
            case (VFARPTR | VFASTCALL | VTHISLAST):
                (*(appNFFL) np)((void far  *)src, (void far  *)dest); break;
            case (VFARCALL | VFARPTR | VFASTCALL):
                (*(appFFF) fp)((void far  *)dest, (void far  *)src); break;
            case (VFARCALL | VFARPTR | VFASTCALL | VTHISLAST):
                (*(appFFFL) fp)((void far  *)src, (void far  *)dest); break;
            case (0 | VFASTTHIS):
                LOAD_NEAR_THIS(dest);
                (*(appNNCT) np)((void near *)src);
                END_NEAR_THIS();
                break;
            case (VFARCALL | VFASTTHIS):
                LOAD_NEAR_THIS(dest);
                (*(appFNCT) fp)((void near *)src);
                END_NEAR_THIS();
                break;
            case (VPASCAL | VFASTTHIS):
                LOAD_NEAR_THIS(dest);
                (*(appNNPT) np)((void near *)src);
                END_NEAR_THIS();
                break;
            case (VFARCALL | VPASCAL | VFASTTHIS):
                LOAD_NEAR_THIS(dest);
                (*(appFNPT) fp)((void near *)src);
                END_NEAR_THIS();
                break;
            case (VFASTCALL | VFASTTHIS):
                LOAD_NEAR_THIS(dest);
                (*(appNNFT) np)((void near *)src);
                END_NEAR_THIS();
                break;
            case (VFARCALL | VFASTCALL | VFASTTHIS):
                LOAD_NEAR_THIS(dest);
                (*(appFNFT) fp)((void near *)src);
                END_NEAR_THIS();
                break;
            case (VFARPTR | VFASTTHIS):
                LOAD_FAR_THIS(dest);
                (*(appNFCT) np)((void far  *)src);
                END_FAR_THIS();
                break;
            case (VFARCALL | VFARPTR | VFASTTHIS):
                LOAD_FAR_THIS(dest);
                (*(appFFCT) fp)((void far  *)src);
                END_FAR_THIS();
                break;
            case (VFARPTR | VPASCAL | VFASTTHIS):
                LOAD_FAR_THIS(dest);
                (*(appNFPT) np)((void far  *)src);
                END_FAR_THIS();
                break;
            case (VFARCALL | VFARPTR | VPASCAL | VFASTTHIS):
                LOAD_FAR_THIS(dest);
                (*(appFFPT) fp)((void far  *)src);
                END_FAR_THIS();
                break;
            case (VFARPTR | VFASTCALL | VFASTTHIS):
                LOAD_FAR_THIS(dest);
                (*(appNFFT) np)((void far  *)src);
                END_FAR_THIS();
                break;
            case (VFARCALL | VFARPTR | VFASTCALL | VFASTTHIS):
                LOAD_FAR_THIS(dest);
                (*(appFFFT) fp)((void far  *)src);
                END_FAR_THIS();
                break;
            default:
                abort(); break;
            }
        (char far *) dest += size;
        (char far *) src += size;
        } while (--count > 0);
}
