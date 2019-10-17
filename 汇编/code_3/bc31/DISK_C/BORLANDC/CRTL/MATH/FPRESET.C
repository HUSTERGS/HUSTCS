/*------------------------------------------------------------------------
 * filename - fpreset.c
 *
 * function(s)
 *        _fpreset - reinitializes floating point math package
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <float.h>

/* The function __fpreset() is in the emulator library and is   */
/* used during the initialization of the FPU (emu1st).          */
/* As all the emulator functions which are model-independent,   */
/* __fpreset() is a NEAR function, and must be called from the  */
/* _TEXT segment.                                               */

void near cdecl __fpreset(void);

/*--------------------------------------------------------------------------*

Name            _fpreset - reinitializes floating point math package

Usage           void _fpreset(void);

Prototype in    float.h

Description     _fpreset  reinitializes the   floating point  math package.
                This function  is usually used in  conjunction with signal,
                system, or the exec... or spawn... functions.

Return value    No return value

*---------------------------------------------------------------------------*/
void _fpreset(void)
{
        __fpreset();
}
