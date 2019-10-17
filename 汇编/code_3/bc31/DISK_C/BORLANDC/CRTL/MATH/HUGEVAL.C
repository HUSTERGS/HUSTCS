/*------------------------------------------------------------------------
 * filename - hugeval.c
 *
 * function(s)
 *        none
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


/*--------------------------------------------------------------------------*

Constants for HUGE_VAL and related constants.

Some numbers are stored as global data items either because
it is difficult to represent them in ASCII form, or because
the program may wish to change them.

The rationale for the maximum numbers is that these are the
largest "representable" numbers in the format.  INF and NAN
are not considered representable.  It is perfectly valid to
consider these representable, just not traditional.  For some
applications it is indeed preferable, and it may be the default
for some future release of Turbo C.

Approximate decimal values are:

        _huge_flt                       3.40282347E+38F
        _huge_dble              1.7976931348623158E+308
        _huge_ldble             1.189731495357232E+4932L
        _tiny_ldble             3.362103143112094E-4932L

Declarations are in <math.h> and in <float.h>.

_indefinite is not used, and provided only for the convenience
of those using INFs and NANs.  Declare it with

        extern float cdecl _indefinite;

Its value is the NAN preferred by the 8087 chip.

*---------------------------------------------------------------------------*/

#define UsingINF        0

#if     UsingINF

/* +INF in various formats */
unsigned short _huge_flt[] = { 0, 0x7F80 };
unsigned short _huge_dble[] = { 0, 0, 0, 0x7FF0 };
unsigned short _huge_ldble[] = { 0, 0, 0, 0x8000, 0x7FFF };

#else

unsigned short _huge_flt[] = { -1, 0x7F7F };
unsigned short _huge_dble[] = { -1, -1, -1, 0x7FEF };
unsigned short _huge_ldble[] = { -1, -1, -1, -1, 0x7FFE };

#endif

unsigned short _indefinite[] = { 0, 0x7FC0 };
unsigned short _tiny_ldble[] = { 0, 0, 0, 0x8000, 1 };
