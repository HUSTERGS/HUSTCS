/*-----------------------------------------------------------------------*
 * filename - rand.c
 *
 * function(s)
 *        srand - initializes random number generator
 *        rand  - random number generator
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdlib.h>

#define MULTIPLIER      0x015a4e35L
#define INCREMENT       1

static  long    Seed = 1;

/*---------------------------------------------------------------------*

Name            srand - initializes random number generator

Usage           void srand(unsigned seed);

Prototype in    stdlib.h

Description     see rand below

Return value    Nothing

*---------------------------------------------------------------------*/
void srand(unsigned seed)
{
        Seed = seed;
}


/*---------------------------------------------------------------------*

Name            rand - random number generator

Usage           int rand(void);

Related
functions usage void srand(unsigned seed);

Prototype in    stdlib.h

Description     rand uses a multiplicative congruential random number
                generator with period 2^32 to return successive pseudo-
                random numbers in the range from 0 to 2^15 - 1.

                The generator is reinitialized by calling srand with an
                argument value of 1. It can be set to a new starting point by
                calling srand with a given seed number.

*---------------------------------------------------------------------*/
int rand(void)
{
        Seed = MULTIPLIER * Seed + INCREMENT;
        return((int)(Seed >> 16) & 0x7fff);
}
