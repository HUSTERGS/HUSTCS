/*-----------------------------------------------------------------------*
 * filename - movetext.c
 *
 * function(s)
 *        movetext - copies text from one rectangle to another.
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

Name            movetext - copies text from one rectangle to another.

Usage           int movetext(int sx1, int sy1, int sx2, int sy2, int dx1, int dy1)

Prototype in    conio.h

Description     movetext copies the contents of the on screen rectangle
                {sx1, sy1, sx2, sy2} to a source rectangle of the same
                dimensions which has its upper left hand corner at dx1, dy1.

Return value    on success, one is returned; zero is returned on failure.

*---------------------------------------------------------------------*/
int movetext(int sx1, int sy1, int sx2, int sy2, int dx1, int dy1)
{
        int first, last, direction, y;

        if (!__validatexy(sx1,sy1,sx2,sy2) || !__validatexy(dx1,dy1,dx1+(sx2-sx1),dy1+(sy2-sy1)))
                return 0;

        first = sy1;
        last = sy2;
        direction = 1;

        if (sy1 < dy1)
        {
                first = sy2;
                last = sy1;
                direction = -1;
        }

        for (y = first; y != last + direction; y += direction)
                __screenio(__vptr(dx1,dy1+(y-sy1)), __vptr(sx1,y), sx2-sx1+1);

        return 1;
}
