/*------------------------------------------------------------------------
 * filename - insline.c
 *
 * function(s)
 *        insline  -  inserts a line of text
 *        delline  -  deletes a line of text
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

Name            insline  - inserts a line of text

Usage           void insline(void);

Prototype in    conio.h

Description     inserts a line of text at the current row position.

*---------------------------------------------------------------------*/
void insline(void)
/* Inserts a line at the current line */
{
        __scroll(DOWN, _video.windowx1, _wherey(),
        _video.windowx2, _video.windowy2, 1);
} /* insline */


/*---------------------------------------------------------------------*

Name            delline  - deletes a line of text

Usage           void delline(void);

Prototype in    conio.h

Description     deletes the current line of text.

*---------------------------------------------------------------------*/
void delline(void)
/* Deletes the current line on the screen */
{
        __scroll(UP, _video.windowx1, _wherey(),
        _video.windowx2, _video.windowy2, 1);
} /* delline */
