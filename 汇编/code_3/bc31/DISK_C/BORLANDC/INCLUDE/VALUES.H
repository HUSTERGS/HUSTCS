/*  values.h

    Symbolic names for important constants, including machine
    dependencies. A System V compatible header.

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#if !defined(__VALUES_H)
#define __VALUES_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#ifndef _VALUES_H
#define _VALUES_H

#define BITSPERBYTE 8
#define MAXSHORT    0x7FFF
#define MAXINT      0x7FFF
#define MAXLONG     0x7FFFFFFFL
#define HIBITS      0x8000
#define HIBITI      0x8000
#define HIBITL      0x80000000

#define DMAXEXP     308
#define FMAXEXP     38
#define DMINEXP     -307
#define FMINEXP     -37

#define MAXDOUBLE   1.797693E+308
#define MAXFLOAT    3.37E+38
#define MINDOUBLE   2.225074E-308
#define MINFLOAT    8.43E-37

#define DSIGNIF     53
#define FSIGNIF     24

#define DMAXPOWTWO  0x3FF
#define FMAXPOWTWO  0x7F
#define _DEXPLEN    11
#define _FEXPLEN    8
#define _EXPBASE    2
#define _IEEE       1
#define _LENBASE    1
#define HIDDENBIT   1
#define LN_MAXDOUBLE    7.0978E+2
#define LN_MINDOUBLE    -7.0840E+2

#endif

#endif  /* __VALUES_H */

