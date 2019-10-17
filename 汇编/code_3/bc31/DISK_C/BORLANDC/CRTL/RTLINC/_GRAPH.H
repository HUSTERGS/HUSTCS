/*------------------------------------------------------------------------
 * filename - _graph.h
 *
 *      Internal version of "graphics.h" (the only difference being
 *      that all functions here are declared "huge").
 *-----------------------------------------------------------------------*/

/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     C/C++ Run Time Library - Version 4.0                     |*/
/*|                                                              |*/
/*|                                                              |*/
/*|     Copyright (c) 1987, 1991 by Borland International        |*/
/*|     All Rights Reserved.                                     |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

#if __STDC__
#define _Cdecl
#else
#define _Cdecl  cdecl
#endif

enum graphics_errors {          /* graphresult error return codes */
        grOk              =   0,
        grNoInitGraph     =  -1,
        grNotDetected     =  -2,
        grFileNotFound    =  -3,
        grInvalidDriver   =  -4,
        grNoLoadMem       =  -5,
        grNoScanMem       =  -6,
        grNoFloodMem      =  -7,
        grFontNotFound    =  -8,
        grNoFontMem       =  -9,
        grInvalidMode     = -10,
        grError           = -11,   /* generic error */
        grIOerror         = -12,
        grInvalidFont     = -13,
        grInvalidFontNum  = -14,
        grInvalidDeviceNum = -15
};

enum graphics_drivers {         /* define graphics drivers */
        DETECT,                 /* requests autodetection */
        CGA, MCGA, EGA, EGA64, EGAMONO, IBM8514,        /* 1 - 6 */
        HERCMONO, ATT400, VGA, PC3270                   /* 7 - 10 */
};

enum graphics_modes {           /* graphics modes for each driver */
    CGAC0      = 0,  /* 320x200 color palette 0: LightGreen, LightRed, Yellow; 1 page */
    CGAC1      = 1,  /* 320x200 color palette 1: LightCyan, LightMagenta, White; 1 page */
    CGAC2      = 2,  /* 320x200 color palette 2: Green, Red, Brown; 1 page */
    CGAC3      = 3,  /* 320x200 color palette 3: Cyan, Magenta, LightGray; 1 page */
    CGAHI      = 4,  /* 640x200 1 page                                      */
    MCGAC0     = 0,  /* 320x200 color palette 0: LightGreen, LightRed, Yellow; 1 page */
    MCGAC1     = 1,  /* 320x200 color palette 1: LightCyan, LightMagenta, White; 1 page */
    MCGAC2     = 2,  /* 320x200 color palette 2: Green, Red, Brown; 1 page */
    MCGAC3     = 3,  /* 320x200 color palette 3: Cyan, Magenta, LightGray; 1 page */
    MCGAMED    = 4,  /* 640x200 1 page                                      */
    MCGAHI     = 5,  /* 640x480 1 page                                      */
    EGALO      = 0,  /* 640x200 16 color 4 pages                            */
    EGAHI      = 1,  /* 640x350 16 color 2 pages                            */
    EGA64LO    = 0,  /* 640x200 16 color 1 page                             */
    EGA64HI    = 1,  /* 640x350 4 color  1 page                             */
    EGAMONOHI  = 3,  /* 640x350 64K on card, 1 page - 256K on card, 4 pages */
    HERCMONOHI = 0,  /* 720x348 2 pages                                     */
    ATT400C0   = 0,  /* 320x200 color palette 0: LightGreen, LightRed, Yellow; 1 page */
    ATT400C1   = 1,  /* 320x200 color palette 1: LightCyan, LightMagenta, White; 1 page */
    ATT400C2   = 2,  /* 320x200 color palette 2: Green, Red, Brown; 1 page */
    ATT400C3   = 3,  /* 320x200 color palette 3: Cyan, Magenta, LightGray; 1 page */
    ATT400MED  = 4,  /* 640x200 1 page                                      */
    ATT400HI   = 5,  /* 640x400 1 page                                      */
    VGALO      = 0,  /* 640x200 16 color 4 pages                            */
    VGAMED     = 1,  /* 640x350 16 color 2 pages                            */
    VGAHI      = 2,  /* 640x480 16 color 1 page                             */
    PC3270HI   = 0,  /* 720x350 1 page                                      */
    IBM8514LO  = 0,  /* 640x480 256 colors                                  */
    IBM8514HI  = 1   /*1024x768 256 colors                                  */
};

/* Colors for setpalette and setallpalette */

#define BLACK           0       /* dark colors */
#define BLUE            1
#define GREEN           2
#define CYAN            3
#define RED             4
#define MAGENTA         5
#define BROWN           6
#define LIGHTGRAY       7
#define DARKGRAY        8       /* light colors */
#define LIGHTBLUE       9
#define LIGHTGREEN      10
#define LIGHTCYAN       11
#define LIGHTRED        12
#define LIGHTMAGENTA    13
#define YELLOW          14
#define WHITE           15

#define EGA_BLACK               0       /* dark colors */
#define EGA_BLUE                1
#define EGA_GREEN               2
#define EGA_CYAN                3
#define EGA_RED                 4
#define EGA_MAGENTA             5
#define EGA_BROWN               20
#define EGA_LIGHTGRAY           7
#define EGA_DARKGRAY            56      /* light colors */
#define EGA_LIGHTBLUE           57
#define EGA_LIGHTGREEN          58
#define EGA_LIGHTCYAN           59
#define EGA_LIGHTRED            60
#define EGA_LIGHTMAGENTA        61
#define EGA_YELLOW              62
#define EGA_WHITE               63

enum line_styles {              /* Line styles for get/setlinestyle */
        SOLID_LINE   = 0,
        DOTTED_LINE  = 1,
        CENTER_LINE  = 2,
        DASHED_LINE  = 3,
        USERBIT_LINE = 4,       /* User defined line style */
};

enum line_widths {              /* Line widths for get/setlinestyle */
        NORM_WIDTH  = 1,
        THICK_WIDTH = 3,
};

enum font_names {
        DEFAULT_FONT    = 0,    /* 8x8 bit mapped font */
        TRIPLEX_FONT    = 1,    /* "Stroked" fonts */
        SMALL_FONT      = 2,
        SANS_SERIF_FONT = 3,
        GOTHIC_FONT     = 4
};

#define HORIZ_DIR       0       /* left to right */
#define VERT_DIR        1       /* bottom to top */

#define USER_CHAR_SIZE  0       /* user-defined char size */

enum fill_patterns {            /* Fill patterns for get/setfillstyle */
        EMPTY_FILL,             /* fills area in background color */
        SOLID_FILL,             /* fills area in solid fill color */
        LINE_FILL,              /* --- fill */
        LTSLASH_FILL,           /* /// fill */
        SLASH_FILL,             /* /// fill with thick lines */
        BKSLASH_FILL,           /* \\\ fill with thick lines */
        LTBKSLASH_FILL,         /* \\\ fill */
        HATCH_FILL,             /* light hatch fill */
        XHATCH_FILL,            /* heavy cross hatch fill */
        INTERLEAVE_FILL,        /* interleaving line fill */
        WIDE_DOT_FILL,          /* Widely spaced dot fill */
        CLOSE_DOT_FILL,         /* Closely spaced dot fill */
        USER_FILL               /* user defined fill */
};

enum putimage_ops {             /* BitBlt operators for putimage */
        COPY_PUT,               /* MOV */
        XOR_PUT,                /* XOR */
        OR_PUT,                 /* OR  */
        AND_PUT,                /* AND */
        NOT_PUT                 /* NOT */
};

enum text_just {                /* Horizontal and vertical justification
                                   for settextjustify */
        LEFT_TEXT       = 0,
        CENTER_TEXT     = 1,
        RIGHT_TEXT      = 2,

        BOTTOM_TEXT     = 0,
     /* CENTER_TEXT     = 1,  already defined above */
        TOP_TEXT        = 2
};


#define MAXCOLORS 15

struct palettetype {
        unsigned char size;
          signed char colors[MAXCOLORS+1];
};

struct linesettingstype {
        int linestyle;
        unsigned upattern;
        int thickness;
};

struct textsettingstype {
        int font;
        int direction;
        int charsize;
        int horiz;
        int vert;
};

struct fillsettingstype {
        int pattern;
        int color;
};

struct pointtype {
        int x, y;
};

struct viewporttype {
        int left, top, right, bottom;
        int clip;
};

struct arccoordstype {
        int x, y;
        int xstart, ystart, xend, yend;
};

typedef unsigned char fillpatterntype[8];

#ifdef __cplusplus
extern "C" {
#endif
void       huge _Cdecl arc(int __x, int __y, int __stangle, int __endangle,
                           int __radius);
void       huge _Cdecl bar(int __left, int __top, int __right, int __bottom);
void       huge _Cdecl bar3d(int __left, int __top, int __right, int __bottom,
                             int __depth, int __topflag);
void       huge _Cdecl circle(int __x, int __y, int __radius);
void       huge _Cdecl cleardevice(void);
void       huge _Cdecl clearviewport(void);
void       huge _Cdecl closegraph(void);
void       huge _Cdecl detectgraph(int far *__graphdriver,int far *__graphmode);
void       huge _Cdecl drawpoly(int __numpoints, int far *__polypoints);
void       huge _Cdecl ellipse(int __x, int __y, int __stangle, int __endangle,
                               int __xradius, int __yradius);
void       huge _Cdecl fillpoly(int __numpoints, int far *__polypoints);
void       huge _Cdecl floodfill(int __x, int __y, int __border);
void       huge _Cdecl getarccoords(struct arccoordstype far *__arccoords);
void       huge _Cdecl getaspectratio(int far *__xasp, int far *__yasp);
int        huge _Cdecl getbkcolor(void);
int        huge _Cdecl getcolor(void);
void       huge _Cdecl getfillpattern(char far *__pattern);
void       huge _Cdecl getfillsettings(struct fillsettingstype far *__fillinfo);
int        huge _Cdecl getgraphmode(void);
void       huge _Cdecl getimage(int __left, int __top, int __right, int __bottom,
                                void far *__bitmap);
void       huge _Cdecl getlinesettings(struct linesettingstype far *__lineinfo);
int        huge _Cdecl getmaxcolor(void);
int        huge _Cdecl getmaxx(void);
int        huge _Cdecl getmaxy(void);
void       huge _Cdecl getmoderange(int __graphdriver, int far *__lomode,
                                    int far *__himode);
unsigned   huge _Cdecl getpixel(int __x, int __y);
void       huge _Cdecl getpalette(struct palettetype far *__palette);
void       huge _Cdecl gettextsettings(struct textsettingstype far *__textinfo);
void       huge _Cdecl getviewsettings(struct viewporttype far *__viewport);
int        huge _Cdecl getx(void);
int        huge _Cdecl gety(void);
void       huge _Cdecl graphdefaults(void);
char far * huge _Cdecl grapherrormsg(int __errorcode);
void       far  _Cdecl _graphexit(int __status);
void       far  _Cdecl _graphfreemem(void far *__ptr, unsigned __size);
void far * far  _Cdecl _graphgetmem(unsigned __size);
int        huge _Cdecl graphresult(void);
unsigned   huge _Cdecl imagesize(int __left, int __top, int __right, int __bottom);
void       huge _Cdecl initgraph(int  far *__graphdriver,
                                 int  far *__graphmode,
                                 char far *__pathtodriver);
void       huge _Cdecl line(int __x1, int __y1, int __x2, int __y2);
void       huge _Cdecl linerel(int __dx, int __dy);
void       huge _Cdecl lineto(int __x, int __y);
void       huge _Cdecl moverel(int __dx, int __dy);
void       huge _Cdecl moveto(int __x, int __y);
void       huge _Cdecl outtext(char far *__textstring);
void       huge _Cdecl outtextxy(int __x, int __y, char far *__textstring);
void       huge _Cdecl pieslice(int __x, int __y, int __stangle, int __endangle,
                                int __radius);
void       huge _Cdecl putimage(int __left, int __top, void far *__bitmap, int __op);
void       huge _Cdecl putpixel(int __x, int __y, int __color);
void       huge _Cdecl rectangle(int __left, int __top, int __right, int __bottom);
void       huge _Cdecl restorecrtmode(void);
void       huge _Cdecl setactivepage(int __page);
void       huge _Cdecl setallpalette(struct palettetype far *__palette);
void       huge _Cdecl setbkcolor(int __color);
void       huge _Cdecl setcolor(int __color);
void       huge _Cdecl setfillpattern(char far *__upattern, int __color);
void       huge _Cdecl setfillstyle(int __pattern, int __color);
unsigned   huge _Cdecl setgraphbufsize(unsigned __bufsize);
void       huge _Cdecl setgraphmode(int __mode);
void       huge _Cdecl setlinestyle(int __linestyle,
                                    unsigned __upattern,
                                    int __thickness);
void       huge _Cdecl setpalette(int __colornum, int __color);
void       huge _Cdecl setrgbpalette(int __colornum,
                                     int __red, int __green, int __blue);
void       huge _Cdecl settextjustify(int __horiz, int __vert);
void       huge _Cdecl settextstyle(int __font, int __direction, int __charsize);
void       huge _Cdecl setusercharsize(int __multx, int __divx,
                                       int __multy, int __divy);
void       huge _Cdecl setviewport(int __left, int __top, int __right, int __bottom,
                                   int __clip);
void       huge _Cdecl setvisualpage(int __page);
int        huge _Cdecl textheight(char far *__textstring);
int        huge _Cdecl textwidth(char far *__textstring);

void            _Cdecl registerbgidriver(void (*driver)(void));
int        huge _Cdecl registerfarbgidriver(void far *__driver);
void            _Cdecl registerbgifont(void (*font)(void));
int        huge _Cdecl registerfarbgifont(void far *__font);
#ifdef __cplusplus
}
#endif
