/*-------------------------------------------------------------------------*
 * filename - peek.c
 *
 * function(s)
 *        peek  - examines memory location
 *        peekb - examines memory location
 *--------------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>
#undef  peek
#undef  peekb

/*---------------------------------------------------------------------*

Name            peek - examines memory location

Usage           int peek(unsigned segment, unsigned offset);

Related
functions usage char peekb(unsigned segment, unsigned offset);

Prototype in    dos.h

Description     peek and peekb examine the memory location addressed
                by segment:offset.

                If these routines are called when dos.h has been included,
                they will be treated as macros that  expand to in-line code.
                If you don't include dos.h (or if you do include it and
                #undef the routines) you will get the functions rather
                than the macros.

Return value    peek and peekb return the value stored at the
                memory location segment:offset. peek returns a word, and
                peekb returns a byte.

*---------------------------------------------------------------------*/
int peek(unsigned segment, unsigned offset)
{
        _ES = segment;
        return(* (int _es *) offset);
}


/*---------------------------------------------------------------------*

Name            peekb - examines memory location

Usage           #include <dos.h>
                char peekb(unsigned segment, unsigned offset);

Prototype in    dos.h

Description     see peek above

*---------------------------------------------------------------------*/
char peekb(unsigned segment, unsigned offset)
{
        _ES = segment;
        return(* (unsigned char _es *) offset);
}
