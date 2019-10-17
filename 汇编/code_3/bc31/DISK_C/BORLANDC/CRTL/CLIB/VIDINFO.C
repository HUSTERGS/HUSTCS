/*-----------------------------------------------------------------------*
 * filename - vidinfo.c
 *
 * function(s)
 *        gettextinfo  - give the user information on video mode,
 *                       window coordinates and video attributes
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

Name            gettextinfo - give the user information on video mode,
                              window coordinates and video attributes

Usage           #include <conio.h>
                void gettextinfo(struct text_info *r);

Prototype in    conio.h

Description     fills the text_info structure with the current video
                information.

Return value    None

NOTE: text_info structure is partial prefix of _video structure

*---------------------------------------------------------------------*/
void gettextinfo(struct text_info *r)
{
        *r = *(struct text_info *)& _video;     /* move data all at once */
        r->winleft      += 1;                   /* 1,1 origin */
        r->wintop       += 1;
        r->winright     += 1;
        r->winbottom    += 1;
        r->curx = wherex();
        r->cury = wherey();
}
