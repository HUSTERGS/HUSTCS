/*------------------------------------------------------------------------
 * filename - _video.h
 *
 *      Private definitions for Turbo Pascal style video functions.
 *      External interfaces in VIDEO.H
 *-----------------------------------------------------------------------*/

/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     C/C++ Run Time Library - Version 4.0                     |*/
/*|                                                              |*/
/*|                                                              |*/
/*|     Copyright (c) 1987, 1990 by Borland International        |*/
/*|     All Rights Reserved.                                     |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

#if __STDC__
#define _Cdecl
#else
#define _Cdecl  cdecl
#endif

#ifndef __PASCAL__
#define _CType _Cdecl
#else
#define _CType pascal
#endif

typedef unsigned char uchar;

typedef struct
{
        uchar windowx1;
        uchar windowy1;
        uchar windowx2;
        uchar windowy2;
        uchar attribute;
        uchar normattr;
        uchar currmode;
        uchar screenheight;
        uchar screenwidth;
        uchar graphicsmode;
        uchar snow;
        union {
                char far * p;
                struct { unsigned off,seg; } u;
        } displayptr;
} VIDEOREC;

#ifndef __IN_CRTINIT
extern VIDEOREC _video;
#endif

#ifdef __cplusplus
extern "C" {
#endif
unsigned pascal near __cputn(const void *__s, unsigned __n, void *__dontCare);

void near _crtinit(uchar __newmode);
void near _VideoInt(void);
void pascal near __scroll(uchar __dir, uchar __x1, uchar __y1, uchar __x2, uchar __y2, uchar __lines);
unsigned near _wherexy(void);
void far * pascal near __vptr(int __x, int __y);
void pascal near __vram(void far *__dst, void far *__src, int __len);
int pascal near __validatexy(int __x1, int __y1, int __x2, int __y2);
void pascal near __screenio(void far *__dst, void far *__src, int __len);
#ifdef __cplusplus
}
#endif

#define _wherex()       ((uchar) _wherexy())
#define _wherey()       ((uchar) (_wherexy() >> 8))

#define V_SET_MODE              0x00
#define V_SET_CURSOR_POS        0x02
#define V_GET_CURSOR_POS        0x03
#define V_SCROLL_UP             0x06
#define V_SCROLL_DOWN           0x07
#define V_RD_CHAR_ATTR          0x08
#define V_WR_CHAR_ATTR          0x09
#define V_WR_CHAR               0x0a
#define V_WR_TTY                0x0e
#define V_GET_MODE              0x0f

#define UP      V_SCROLL_UP
#define DOWN    V_SCROLL_DOWN
