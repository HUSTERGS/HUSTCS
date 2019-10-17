/*------------------------------------------------------------------------
 * filename - clrscr.c
 *
 * function(s)
 *        clrscr - clears text mode window
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <_video.h>
#include <conio.h>

/*------------------------------------------------------------------------*

Name            clrscr - clears text mode window

Usage           void clrscr(void);

Prototype in    conio.h

Description     clrscr clears the current text window and places the cursor
                in the upper left-hand corner(at position 1,1).

Return value    None

*--------------------------------------------------------------------------*/
void clrscr(void)
{

        __scroll(UP, _video.windowx1, _video.windowy1,
                     _video.windowx2, _video.windowy2, 0);

        _DL = _video.windowx1;          /* position to window 1,1 */
        _DH = _video.windowy1;
        _AH = V_SET_CURSOR_POS;
        _BH = 0;
        _VideoInt();
}
