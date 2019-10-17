/*-----------------------------------------------------------------------*
 * filename - screen.c
 *
 * function(s)
 *        screenpos  - returns the current CP
 *        moveto     - moves the CP to (x,y)
 *        bios       - moves a block of screen data through bios
 *        __screenio - moves a block of screen data
 *        __validatexy - checks the validity of the window coordinates
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <_video.h>
#include <dos.h>
#include <conio.h>
#include <string.h>

/*---------------------------------------------------------------------*

Name            screenpos - returns the current CP

Usage           static unsigned near pascal screenpos(void far *ptr);

Return value    current row/column in higher/lower byte

*---------------------------------------------------------------------*/
static unsigned near pascal screenpos(void far *ptr)
{
        register unsigned offset;
        unsigned char row, col;

        offset = FP_OFF(ptr) >> 1;
        row = (unsigned char)(offset / _video.screenwidth);
        col = (unsigned char)(offset - row * _video.screenwidth);

        _AH = row;
        _AL = col;
        return _AX;
}


/*---------------------------------------------------------------------*

Name            moveto - moves the CP to (x,y)

Usage           static void pascal moveto(unsigned *newpos, unsigned *oldpos);

Return value    None

*---------------------------------------------------------------------*/
static void near pascal moveto(unsigned *newpos, unsigned *oldpos)
{
        _DX = *newpos;
        if (_DX != *oldpos)
        {
                _BH = 0;
                _AH = 2;
                _VideoInt();
                *oldpos = _DX;
        }
        _DL++;
        if (_DL >= _video.screenwidth)
        {
                _DH++;
                _DL = 0;
        }
        *newpos = _DX;
}



/*---------------------------------------------------------------------*

Name            bios - moves a block of screen data through bios

Usage           static void near pascal bios(void far *dst, void far *src,
                                             int len);

Return value    None

*---------------------------------------------------------------------*/
static void near pascal bios(void far *dst, void far *src, int len)
{
        register unsigned charcell;
        unsigned dstpos, srcpos, cursorpos;
        int originalpos, dstvram, srcvram;

        cursorpos = originalpos = _wherexy();

        if ((dstvram = (FP_SEG(dst) == _video.displayptr.u.seg)) != 0)
                dstpos = screenpos(dst);

        if ((srcvram = (FP_SEG(src) == _video.displayptr.u.seg)) != 0)
                srcpos = screenpos(src);

        while (len--)
        {

                if (srcvram)
                {
                        moveto(&srcpos, &cursorpos);
                        _BH = 0;
                        _AH = 8;
                        _VideoInt();
                        charcell = _AX;
                }
                else
                        charcell = *((unsigned far *)src)++;

                if (dstvram)
                {
                        moveto(&dstpos, &cursorpos);
                        _AX = charcell;
                        _BL = _AH;
                        _CX = 1;
                        _BH = 0;
                        _AH = 9;
                        _VideoInt();
                }
                else
                        *((unsigned far *)dst)++ = charcell;
        }

        _DX = originalpos;
        _BH = 0;
        _AH = 2;
        _VideoInt();
}


/*---------------------------------------------------------------------*

Name            __screenio -  moves a block of screen data

Usage           void pascal __screenio(void far *dst, void far *src, int len);

Return value    None

*---------------------------------------------------------------------*/
void pascal near __screenio(void far *dst, void far *src, int len)
{
        if (!_video.graphicsmode && directvideo)
                __vram(dst, src, len);
        else
                bios(dst, src, len);
}


/*---------------------------------------------------------------------*

Name            __validatexy - checks the validity of the screen coordinates

Usage           int pascal __validatexy(int x1, int y1, int x2, int y2);

Return value    __validatexy returns zero if the coordinates are invalid

*---------------------------------------------------------------------*/
int pascal near __validatexy(int x1, int y1, int x2, int y2)
{
        _CX = _video.screenwidth;
        _DX = _video.screenheight;
        return !(x1 > _CX || x2 > _CX || x1 > x2 ||
                 y1 > _DX || y2 > _DX || y1 > y2 ||
                 x1 <= 0  || x2 <= 0  || y1 <= 0 || y2 <= 0);
}
