/*-----------------------------------------------------------------------*
 * filename - wherexy.c
 *
 * function(s)
 *        wherex - gives horizontal cursor position within window
 *        wherey - gives vertical cursor position within window
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

/*---------------------------------------------------------------------*

Name            _wherexy - returns the horizontal and vertical cursor
                           position

Usage           unsigned _wherexy(void);

Prototype in    _video.h

Return value    an unsigned integer holding the horizontal coordinate
                in the lower byte and the vertical coordinate in the
                upper byte

*---------------------------------------------------------------------*/
unsigned near _wherexy(void)
{
        _AH = 3;
        _BH = 0;
        _VideoInt();
        return (_DX);
}


/*---------------------------------------------------------------------*

Name            wherex - returns the horizontal position within window

Usage           int wherex(void);

Related
functions usage int wherey(void);

Prototype in    conio.h

Description     wherex returns the x-coordinate of the current cursor
                position (within the current text window). wherey
                returns the y-coordinate of the current cursor position
                (within the current text window).

Return value    integer in the range 1 to 80

*---------------------------------------------------------------------*/
int wherex(void)
{
        return (_wherex() - _video.windowx1 + 1);
}


/*---------------------------------------------------------------------*

Name            wherey - returns the vertical position within window

Usage           int wherey(void);

Related
functions usage int wherex(void);

Prototype in    conio.h

Description     wherex returns the x-coordinate of the current cursor
                position (within the current text window). wherey
                returns the y-coordinate of the current cursor position
                (within the current text window).

Return value    integer in the range 1 to 80

*---------------------------------------------------------------------*/

int wherey(void)
{
        return (_wherey() - _video.windowy1 + 1);
}
