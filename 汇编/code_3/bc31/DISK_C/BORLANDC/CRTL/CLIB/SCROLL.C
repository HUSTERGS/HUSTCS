/*-----------------------------------------------------------------------*
 * filename - scroll.c
 *
 * function(s)
 *        zapline  - deletes a line
 *        __scroll - scrolls the current window in text mode
 *
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <conio.h>
#include <_video.h>

/*---------------------------------------------------------------------*

Name            zapline - deletes a line

Usage           static void near pascal zapline(unsigned int *linebuffer,
                                                int x1, int x2);

Return value    None

*---------------------------------------------------------------------*/
static void near pascal zapline(unsigned int *linebuffer, int x1, int x2)
{
        _CH = _video.attribute;
        _CL = 0x20;
        for (; x1 <= x2; x1++)
                *linebuffer++ = _CX;
}


/*---------------------------------------------------------------------*

Name            __scroll - scrolls the current window in text mode

Usage           static pascal __scroll(uchar dir, uchar x1, uchar y1,
                                       uchar x2, uchar y2, uchar lines);

Return value    None

*---------------------------------------------------------------------*/
void pascal near __scroll(uchar dir, uchar x1, uchar y1, uchar x2, uchar y2, uchar lines)
{
        unsigned linebuffer[80];

        if (!_video.graphicsmode && directvideo && lines == 1)
        {
                x1++;
                y1++;
                x2++;
                y2++;
                if (dir == UP)
                {
                        movetext(x1,y1+1,x2,y2,x1,y1);
                        gettext(x1,y2,x1,y2,linebuffer);
                        zapline(linebuffer,x1,x2);
                        puttext(x1,y2,x2,y2,linebuffer);
                }
                else
                {
                        movetext(x1,y1,x2,y2-1,x1,y1+1);
                        gettext(x1,y1,x1,y1,linebuffer);
                        zapline(linebuffer,x1,x2);
                        puttext(x1,y1,x2,y1,linebuffer);
                }
        }
        else
        {
                _BH = _video.attribute;
                _AH = dir;
                _AL = lines;
                _CH = y1;
                _CL = x1;
                _DH = y2;
                _DL = x2;
                _VideoInt();
        }
}
