/*------------------------------------------------------------------------
 * filename - fakeieee.h
 *
 *      fake IEEE floating point package interface
 *-----------------------------------------------------------------------*/

/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     C/C++ Run Time Library - Version 4.0                     |*/
/*|                                                              |*/
/*|                                                              |*/
/*|     Copyright (c) 1991 by Borland International              |*/
/*|     All Rights Reserved.                                     |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

/*
    If you do not have the IEEE-recommended functions discussed in
    file ostreamf.c, and if any of these statements is true
        (a) Your system does not use IEEE floating-point.
        (b) Your system doesn't have Infinity or Not-A-Number.
        (c) Your system won't generate runtime aborts on overflow,
            Infinity, or Not-A-Number (NaN).
        (d) You don't care about runtime aborts in stream I/O.
    then you may use these simple definitions to get ostreamf.c up and
    running quickly.

    Here we assume:
        (1) There is no special representation for Infinities.
        (2) There is no such thing as Not-A-Number (NaN).
*/

// The following define the kinds (classes) of a floating-point number
#define FPSIGNAN        0       // signaling NaN
#define FPQUIETNAN      1       // quiet NaN 
#define FPNEGINF        2       // -infinity 
#define FPNEG           3       // negative normalized nonzero 
#define FPNEGDENOR      4       // negative denormalized 
#define FPNEGZERO       5       // -0 
#define FPPOSZERO       6       // +0 
#define FPPOSDENOR      7       // positive denormalized 
#define FPPOS           8       // positive normalized nonzero 
#define FPPOSINF        9       // +infinity 


/* Returns kind (class) of parmeter.
 * We assume only positive, negative, or zero is possible.
 * This function is pretty inefficient, but we make no assumptions
 * whatever about floating-point representation.
 */
fpclass(long double d)
{
    return (d < 0.0) ? FPNEG : ((d == 0.0) ? FPPOSZERO : FPPOS);
}

/* True if parameter is a NaN.
 * We assume there is no such thing as a NaN.
 */
inline int fpisnan( long double ) { return 0; }

/* True if -inf < parameter < inf.
 * We assume there are no infinities.
 */
inline int fpfinite( long double ) { return 1; }

/* Return the first value with the sign of the second,
 * even if one is Infinity or a NaN.
 * This function is pretty inefficient, but we make no assumptions
 * whatever about floating-point representation.
 */
long double fpcopysign( long double d1, long double d2 )
{
    return ( d1 && ((d1 < 0.0) != (d2 < 0.0)) ) ? -d1 : d1;
}
