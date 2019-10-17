/*-------------------------------------------------------------------------*
 * filename - poke.c
 *
 * function(s)
 *        poke - stores value at a given memory location
 *        pokeb - value at memory location
 *--------------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>
#undef  poke
#undef  pokeb

/*---------------------------------------------------------------------*

Name            poke - stores value at a given memory location

Usage           void poke(unsigned segment, unsigned offset, int value);

Related
functions usage void pokeb(unsigned segment, unsigned offset, char value);

Prototype in    dos.h

Description     poke stores the integer value at the memory location
                segment:offset.

                If these routines are called when dos.h has been included, they
                will be treated as macros@INDEX[Macros] that  expand to in-line
                code. If you don't include dos.h (or if you do include it and
                #undef the routines) you will get the functions rather than the
                macros.

                pokeb is the same as poke, except that a byte value is
                deposited instead of an integer.

Return value    None

*---------------------------------------------------------------------*/
void poke(unsigned segment, unsigned offset, int value)
{
        _ES = segment;
        * (int _es *) offset = value;
}


/*---------------------------------------------------------------------*

Name            pokeb - value at memory location

Usage           #include <dos.h>
                void pokeb(unsigned segment, unsigned offset, char value);

Prototype in    dos.h

Description     see poke

*---------------------------------------------------------------------*/
void pokeb(unsigned segment, unsigned offset, char value)
{
        _ES = segment;
        * (char _es *) offset = value;
}
