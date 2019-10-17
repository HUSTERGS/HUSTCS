/*-----------------------------------------------------------------------*
 * filename - getcbrk.c
 *
 * function(s)
 *        getcbrk - gets control-break setting
 *        setcbrk - sets control-break setting
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>

/*---------------------------------------------------------------------*

Name            getcbrk - gets control-break setting

Usage           int getcbrk(void);

Related
functions usage int setcbrk(int value);

Prototype in    dos.h

Description     getcbrk uses the MS-DOS system call 0x33 to return
                the current setting of control-break checking.

Return value    getcbrk returns 0 if control-break checking is off
                and returns 1 if checking is on.

*---------------------------------------------------------------------*/
int getcbrk(void)
{
        _AX = 0x3300;
        geninterrupt(0x21);
        return(_DL);
}


/*---------------------------------------------------------------------*

Name            setcbrk - sets control-break setting

Usage           int setcbrk(int value);

Prototype in    dos.h

Description     setcbrk uses the MS-DOS system call 0x33 to set control-break
                checking on or off.

                value   = 0     Turns checking off (check only during
                                I/O to console, printer, or
                                communications devices)
                value   = 1     Turns checking on (check at every system call)

Return value    setcbrk returns value.

*---------------------------------------------------------------------*/
int setcbrk(int cval)
{
        _AX = 0x3301;
        _DL = cval;
        geninterrupt(0x21);
        return(_DL);
}
