/*
   GRAPHICS DEMO FOR Borland C++ 

   Copyright (c) 1987,88,91 Borland International. All rights reserved.

   From the command line, use:

		bcc bgidemo graphics.lib

*/

#ifdef __TINY__
#error BGIDEMO will not run in the tiny model.
#endif

#include <dos.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <graphics.h>

#define ESC	0x1b			/* Define the escape key	*/
#define TRUE	1			/* Define some handy constants	*/
#define FALSE	0			/* Define some handy constants	*/
#define PI	3.14159 		/* Define a value for PI	*/
#define ON	1			/* Define some handy constants	*/
#define OFF	0			/* Define some handy constants	*/

#define NFONTS 11

char *Fonts[NFONTS] = {
  "DefaultFont",   "TriplexFont",   "SmallFont",
  "SansSerifFont", "GothicFont", "ScriptFont", "SimplexFont", "TriplexScriptFont",
  "ComplexFont", "EuropeanFont", "BoldFont"
};

char *LineStyles[] = {
  "SolidLn",  "DottedLn",  "CenterLn",  "DashedLn",  "UserBitLn"
};

char *FillStyles[] = {
  "EmptyFill",  "SolidFill",      "LineFill",      "LtSlashFill",
  "SlashFill",  "BkSlashFill",    "LtBkSlashFill", "HatchFill",
  "XHatchFill", "InterleaveFill", "WideDotFill",   "CloseDotFill"
};

char *TextDirect[] = {
  "HorizDir",  "VertDir"
};

char *HorizJust[] = {
  "LeftText",   "CenterText",   "RightText"
};

char *VertJust[] = {
  "BottomText",  "CenterText",  "TopText"
};

struct PTS {
  int x, y;
};	/* Structure to hold vertex points	*/

int    GraphDriver;		/* The Graphics device driver		*/
int    GraphMode;		/* The Graphics mode value		*/
double AspectRatio;		/* Aspect ratio of a pixel on the screen*/
int    MaxX, MaxY;		/* The maximum resolution of the screen */
int    MaxColors;		/* The maximum # of colors available	*/
int    ErrorCode;		/* Reports any graphics errors		*/
struct palettetype palette;		/* Used to read palette info	*/

/*									*/
/*	Function prototypes						*/
/*									*/

void Initialize(void);
void ReportStatus(void);
void TextDump(void);
void Bar3DDemo(void);
void RandomBars(void);
void TextDemo(void);
void ColorDemo(void);
void ArcDemo(void);
void CircleDemo(void);
void PieDemo(void);
void BarDemo(void);
void LineRelDemo(void);
void PutPixelDemo(void);
void PutImageDemo(void);
void LineToDemo(void);
void LineStyleDemo(void);
void CRTModeDemo(void);
void UserLineStyleDemo(void);
void FillStyleDemo(void);
void FillPatternDemo(void);
void PaletteDemo(void);
void PolyDemo(void);
void SayGoodbye(void);
void Pause(void);
void MainWindow(char *header);
void StatusLine(char *msg);
void DrawBorder(void);
void changetextstyle(int font, int direction, int charsize);
int  gprintf(int *xloc, int *yloc, char *fmt, ... );

/*									*/
/*	Begin main function						*/
/*									*/

int main()
{

  Initialize(); 		/* Set system into Graphics mode	*/
  ReportStatus();		/* Report results of the initialization */

  ColorDemo();			/* Begin actual demonstration		*/
  if( GraphDriver==EGA || GraphDriver==EGALO || GraphDriver==VGA )
    PaletteDemo();
  PutPixelDemo();
  PutImageDemo();
  Bar3DDemo();
  BarDemo();
  RandomBars();
  ArcDemo();
  CircleDemo();
  PieDemo();
  LineRelDemo();
  LineToDemo();
  LineStyleDemo();
  UserLineStyleDemo();
  TextDump();
  TextDemo();
  CRTModeDemo();
  FillStyleDemo();
  FillPatternDemo();
  PolyDemo();
  SayGoodbye(); 		/* Give user the closing screen 	*/

  closegraph(); 		/* Return the system to text mode	*/
  return(0);
}

/*									*/
/*	INITIALIZE: Initializes the graphics system and reports 	*/
/*	any errors which occured.					*/
/*									*/

void Initialize(void)
{
  int xasp, yasp;			/* Used to read the aspect ratio*/

  GraphDriver = DETECT; 		/* Request auto-detection	*/
  initgraph( &GraphDriver, &GraphMode, "" );
  ErrorCode = graphresult();		/* Read result of initialization*/
  if( ErrorCode != grOk ){		/* Error occured during init	*/
    printf(" Graphics System Error: %s\n", grapherrormsg( ErrorCode ) );
    exit( 1 );
  }

  getpalette( &palette );		/* Read the palette from board	*/
  MaxColors = getmaxcolor() + 1;	/* Read maximum number of colors*/

  MaxX = getmaxx();
  MaxY = getmaxy();			/* Read size of screen		*/

  getaspectratio( &xasp, &yasp );	/* read the hardware aspect	*/
  AspectRatio = (double)xasp / (double)yasp; /* Get correction factor	*/

}

/*									*/
/*	REPORTSTATUS: Report the current configuration of the system	*/
/*	after the auto-detect initialization.				*/
/*									*/

void ReportStatus(void)
{
  struct viewporttype	  viewinfo;	/* Params for inquiry procedures*/
  struct linesettingstype lineinfo;
  struct fillsettingstype fillinfo;
  struct textsettingstype textinfo;
  struct palettetype	  palette;

  char *driver, *mode;			/* Strings for driver and mode	*/
  int x, y;

  getviewsettings( &viewinfo );
  getlinesettings( &lineinfo );
  getfillsettings( &fillinfo );
  gettextsettings( &textinfo );
  getpalette( &palette );

  x = 10;
  y = 4;

  MainWindow( "Status report after InitGraph" );
  settextjustify( LEFT_TEXT, TOP_TEXT );

  driver = getdrivername();
  mode = getmodename(GraphMode);	/* get current setting		*/

  gprintf( &x, &y, "Graphics device    : %-20s (%d)", driver, GraphDriver );
  gprintf( &x, &y, "Graphics mode      : %-20s (%d)", mode, GraphMode );
  gprintf( &x, &y, "Screen resolution  : ( 0, 0, %d, %d )", getmaxx(), getmaxy() );

  gprintf( &x, &y, "Current view port  : ( %d, %d, %d, %d )",
  viewinfo.left, viewinfo.top, viewinfo.right, viewinfo.bottom );
  gprintf( &x, &y, "Clipping           : %s", viewinfo.clip ? "ON" : "OFF" );

  gprintf( &x, &y, "Current position   : ( %d, %d )", getx(), gety() );
  gprintf( &x, &y, "Colors available   : %d", MaxColors );
  gprintf( &x, &y, "Current color      : %d", getcolor() );

  gprintf( &x, &y, "Line style         : %s", LineStyles[ lineinfo.linestyle ] );
  gprintf( &x, &y, "Line thickness     : %d", lineinfo.thickness );

  gprintf( &x, &y, "Current fill style : %s", FillStyles[ fillinfo.pattern ] );
  gprintf( &x, &y, "Current fill color : %d", fillinfo.color );

  gprintf( &x, &y, "Current font       : %s", Fonts[ textinfo.font ] );
  gprintf( &x, &y, "Text direction     : %s", TextDirect[ textinfo.direction ] );
  gprintf( &x, &y, "Character size     : %d", textinfo.charsize );
  gprintf( &x, &y, "Horizontal justify : %s", HorizJust[ textinfo.horiz ] );
  gprintf( &x, &y, "Vertical justify   : %s", VertJust[ textinfo.vert ] );

  Pause();				/* Pause for user to read screen*/

}

/*									*/
/*	TEXTDUMP: Display the all the characters in each of the 	*/
/*	available fonts.						*/
/*									*/

void TextDump()
{
  static int CGASizes[]  = {
    1, 3, 7, 3, 3, 2, 2, 2, 2, 2, 2  };
  static int NormSizes[] = {
    1, 4, 7, 4, 4, 2, 2, 2, 2, 2, 2  };

  char buffer[80];
  int font, ch, wwidth, lwidth, size;
  struct viewporttype vp;

  for( font=0 ; font<NFONTS ; ++font ){	/* For each available font	*/
    sprintf( buffer, "%s Character Set", Fonts[font] );
    MainWindow( buffer );		/* Display fontname as banner	*/
    getviewsettings( &vp );		/* read current viewport	*/

    settextjustify( LEFT_TEXT, TOP_TEXT );
    moveto( 2, 3 );

    buffer[1] = '\0';                   /* Terminate string             */
    wwidth = vp.right - vp.left;	/* Determine the window width	*/
    lwidth = textwidth( "H" );          /* Get average letter width     */

    if( font == DEFAULT_FONT ){
      changetextstyle( font, HORIZ_DIR, 1 );
      ch = 0;
      while( ch < 256 ){		/* For each possible character	*/
	buffer[0] = ch; 		/* Put character into a string	*/
	outtext( buffer );		/* send string to screen	*/
	if( (getx() + lwidth) > wwidth )
	  moveto( 2, gety() + textheight("H") + 3 );
	++ch;				/* Goto the next character	*/
      }
    }
    else{

      size = (MaxY < 200) ? CGASizes[font] : NormSizes[font];
      changetextstyle( font, HORIZ_DIR, size );

      ch = '!';                         /* Begin at 1st printable       */
      while( ch < 256 ){		/* For each printable character */
	buffer[0] = ch; 		/* Put character into a string	*/
	outtext( buffer );		/* send string to screen	*/
	if( (lwidth+getx()) > wwidth )	/* Are we still in window?	*/
	  moveto( 2, gety()+textheight("H")+3 );
	++ch;				/* Goto the next character	*/
      }

    }

    Pause();				/* Pause until user acks	*/

  }					/* End of FONT loop		*/

}

/*									*/
/*	BAR3DDEMO: Display a 3-D bar chart on the screen.		*/
/*									*/

void Bar3DDemo(void)
{
  static int barheight[] = {
    1, 3, 5, 4, 3, 2, 1, 5, 4, 2, 3   };
  struct viewporttype vp;
  int xstep, ystep;
  int i, j, h, color, bheight;
  char buffer[10];

  MainWindow( "Bar 3-D / Rectangle Demonstration" );

  h = 3 * textheight( "H" );
  getviewsettings( &vp );
  settextjustify( CENTER_TEXT, TOP_TEXT );
  changetextstyle( TRIPLEX_FONT, HORIZ_DIR, 4 );
  outtextxy( MaxX/2, 6, "These are 3-D Bars" );
  changetextstyle( DEFAULT_FONT, HORIZ_DIR, 1 );
  setviewport( vp.left+50, vp.top+40, vp.right-50, vp.bottom-10, 1 );
  getviewsettings( &vp );

  line( h, h, h, vp.bottom-vp.top-h );
  line( h, (vp.bottom-vp.top)-h, (vp.right-vp.left)-h, (vp.bottom-vp.top)-h );
  xstep = ((vp.right-vp.left) - (2*h)) / 10;
  ystep = ((vp.bottom-vp.top) - (2*h)) / 5;
  j = (vp.bottom-vp.top) - h;
  settextjustify( CENTER_TEXT, CENTER_TEXT );

  for( i=0 ; i<6 ; ++i ){
    line( h/2, j, h, j );
    itoa( i, buffer, 10 );
    outtextxy( 0, j, buffer );
    j -= ystep;
  }

  j = h;
  settextjustify( CENTER_TEXT, TOP_TEXT );

  for( i=0 ; i<11 ; ++i ){
    color = random( MaxColors );
    setfillstyle( i+1, color );
    line( j, (vp.bottom-vp.top)-h, j, (vp.bottom-vp.top-3)-(h/2) );
    itoa( i, buffer, 10 );
    outtextxy( j, (vp.bottom-vp.top)-(h/2), buffer );
    if( i != 10 ){
      bheight = (vp.bottom-vp.top) - h - 1;
      bar3d( j, (vp.bottom-vp.top-h)-(barheight[i]*ystep), j+xstep, bheight, 15, 1 );
    }
    j += xstep;
  }

  Pause();				/* Pause for user's response    */

}

/*									*/
/*	RANDOMBARS: Display random bars 				*/
/*									*/

void RandomBars(void)
{
  int color;

  MainWindow( "Random Bars" );
  StatusLine( "Esc aborts or press a key..." ); /* Put msg at bottom of screen   */
  while( !kbhit() ){			/* Until user enters a key...	*/
    color = random( MaxColors-1 )+1;
    setcolor( color );
    setfillstyle( random(11)+1, color );
    bar3d( random( getmaxx() ), random( getmaxy() ),
	   random( getmaxx() ), random( getmaxy() ), 0, OFF);
  }

  Pause();				/* Pause for user's response    */

}


/*									*/
/*	TEXTDEMO: Show each font in several sizes to the user.		*/
/*									*/

void TextDemo(void)
{
  int charsize[] = {
    1, 3, 7, 3, 4, 2, 2, 2, 2, 2, 2   };
  int font, size;
  int h, x, y, i;
  struct viewporttype vp;
  char buffer[80];

  for( font=0 ; font<NFONTS ; ++font ){	/* For each of the avail. fonts	*/

    sprintf( buffer, "%s Demonstration", Fonts[font] );
    MainWindow( buffer );
    getviewsettings( &vp );

    changetextstyle( font, VERT_DIR, charsize[font] );
    settextjustify( CENTER_TEXT, BOTTOM_TEXT );
    outtextxy( 2*textwidth("M"), vp.bottom - 2*textheight("M"), "Vertical" );

    changetextstyle( font, HORIZ_DIR, charsize[font] );
    settextjustify( LEFT_TEXT, TOP_TEXT );
    outtextxy( 2*textwidth("M"), 2, "Horizontal" );

    settextjustify( CENTER_TEXT, CENTER_TEXT );
    x = (vp.right - vp.left) / 2;
    y = textheight( "H" );

    for( i=1 ; i<5 ; ++i ){		/* For each of the sizes */
      size = (font == SMALL_FONT) ? i+3 : i;
      changetextstyle( font, HORIZ_DIR, size );
      h = textheight( "H" );
      y += h;
      sprintf( buffer, "Size %d", size );
      outtextxy( x, y, buffer );

    }

    if( font != DEFAULT_FONT ){ 	/* Show user declared font size */
      y += h / 2;			/* Move down the screen 	*/
      settextjustify( CENTER_TEXT, TOP_TEXT );
      setusercharsize( 5, 6, 3, 2 );
      changetextstyle( font, HORIZ_DIR, USER_CHAR_SIZE );
      outtextxy( (vp.right-vp.left)/2, y, "User Defined Size" );
    }

    Pause();				/* Pause to let user look	*/

  }					/* End of FONT loop		*/

}

/*									*/
/*	COLORDEMO: Display the current color palette on the screen.	*/
/*									*/

void ColorDemo(void)
{
  struct viewporttype vp;
  int color, height, width;
  int x, y, i, j;
  char cnum[5];

  MainWindow( "Color Demonstration" );  /* Show demonstration name      */

  color = 1;
  getviewsettings( &vp );		/* Get the current window size	*/
  width  = 2 * ( (vp.right+1) / 16 );	   /* Get box dimensions	   */
  height = 2 * ( (vp.bottom-10) / 10 );

  x = width / 2;
  y = height / 2;	/* Leave 1/2 box border 	*/

  for( j=0 ; j<3 ; ++j ){		/* Row loop			*/

    for( i=0 ; i<5 ; ++i ){		/* Column loop			*/

      setfillstyle(SOLID_FILL, color);	/* Set to solid fill in color	*/
      setcolor( color );		/* Set the same border color	*/

      bar( x, y, x+width, y+height );	/* Draw the rectangle		*/
      rectangle( x, y, x+width, y+height );  /* outline the rectangle	*/

      if( color == BLACK ){		/* If box was black...		*/
	setcolor( WHITE );		/* Set drawing color to white	*/
	rectangle( x, y, x+width, y+height );  /* Outline black in white*/
      }

      itoa( color, cnum, 10 );		/* Convert # to ASCII		*/
      outtextxy( x+(width/2), y+height+4, cnum );  /* Show color #	*/

      color = ++color % MaxColors;	/* Advance to the next color	*/
      x += (width / 2) * 3;		/* move the column base 	*/
    }				/* End of Column loop		*/

    y += (height / 2) * 3;		/* move the row base		*/
    x = width / 2;			/* reset column base		*/
  }					/* End of Row loop		*/

  Pause();				/* Pause for user's response    */

}

/*									*/
/*	ARCDEMO: Display a random pattern of arcs on the screen */
/*	until the user says enough.					*/
/*									*/

void ArcDemo(void)
{
  int mradius;				/* Maximum radius allowed	*/
  int eangle;				/* Random end angle of Arc	*/
  struct arccoordstype ai;		/* Used to read Arc Cord info	*/

  MainWindow( "Arc Demonstration" );
  StatusLine( "ESC Aborts - Press a Key to stop" );

  mradius = MaxY / 10;			/* Determine the maximum radius */

  while( !kbhit() ){			/* Repeat until a key is hit	*/
    setcolor( random( MaxColors - 1 ) + 1 );	/* Randomly select a color	*/
    eangle = random( 358 ) + 1; 	/* Select an end angle		*/
    arc( random(MaxX), random(MaxY), random(eangle), eangle, mradius );
    getarccoords( &ai );		/* Read Cord data		*/
    line( ai.x, ai.y, ai.xstart, ai.ystart ); /* line from start to center */
    line( ai.x, ai.y,	ai.xend,   ai.yend ); /* line from end to center   */
  }					/* End of WHILE not KBHIT	*/

  Pause();				/* Wait for user's response     */

}

/*									*/
/*	CIRCLEDEMO: Display a random pattern of circles on the screen	*/
/*	until the user says enough.					*/
/*									*/

void CircleDemo(void)
{
  int mradius;				/* Maximum radius allowed	*/

  MainWindow( "Circle Demonstration" );
  StatusLine( "ESC Aborts - Press a Key to stop" );

  mradius = MaxY / 10;			/* Determine the maximum radius */

  while( !kbhit() ){			/* Repeat until a key is hit	*/
    setcolor( random( MaxColors - 1 ) + 1 );	/* Randomly select a color	*/
    circle( random(MaxX), random(MaxY), random(mradius) );
  }					/* End of WHILE not KBHIT	*/

  Pause();				/* Wait for user's response     */

}

/*									*/
/*	PIEDEMO: Display a pie chart on the screen.			*/
/*									*/

#define adjasp( y )	((int)(AspectRatio * (double)(y)))
#define torad( d )	(( (double)(d) * PI ) / 180.0 )

void PieDemo(void)
{
  struct viewporttype vp;
  int xcenter, ycenter, radius, lradius;
  int x, y;
  double radians, piesize;

  MainWindow( "Pie Chart Demonstration" );

  getviewsettings( &vp );		/* Get the current viewport	*/
  xcenter = (vp.right - vp.left) / 2;	/* Center the Pie horizontally	*/
  ycenter = (vp.bottom - vp.top) / 2+20;/* Center the Pie vertically	*/
  radius  = (vp.bottom - vp.top) / 3;	/* It will cover 2/3rds screen	*/
  piesize = (vp.bottom - vp.top) / 4.0; /* Optimum height ratio of pie	*/

  while( (AspectRatio*radius) < piesize ) ++radius;

  lradius = radius + ( radius / 5 );	/* Labels placed 20% farther	*/

  changetextstyle( TRIPLEX_FONT, HORIZ_DIR, 4 );
  settextjustify( CENTER_TEXT, TOP_TEXT );
  outtextxy( MaxX/2, 6, "This is a Pie Chart" );
  changetextstyle( TRIPLEX_FONT, HORIZ_DIR, 1 );
  settextjustify( CENTER_TEXT, TOP_TEXT );

  setfillstyle( SOLID_FILL, RED );
  pieslice( xcenter+10, ycenter-adjasp(10), 0, 90, radius );
  radians = torad( 45 );
  x = xcenter + (int)( cos( radians ) * (double)lradius );
  y = ycenter - (int)( sin( radians ) * (double)lradius * AspectRatio );
  settextjustify( LEFT_TEXT, BOTTOM_TEXT );
  outtextxy( x, y, "25 %" );

  setfillstyle( WIDE_DOT_FILL, GREEN );
  pieslice( xcenter, ycenter, 90, 135, radius );
  radians = torad( 113 );
  x = xcenter + (int)( cos( radians ) * (double)lradius );
  y = ycenter - (int)( sin( radians ) * (double)lradius * AspectRatio );
  settextjustify( RIGHT_TEXT, BOTTOM_TEXT );
  outtextxy( x, y, "12.5 %" );

  setfillstyle( INTERLEAVE_FILL, YELLOW );
  settextjustify( RIGHT_TEXT, CENTER_TEXT );
  pieslice( xcenter-10, ycenter, 135, 225, radius );
  radians = torad( 180 );
  x = xcenter + (int)( cos( radians ) * (double)lradius );
  y = ycenter - (int)( sin( radians ) * (double)lradius * AspectRatio );
  settextjustify( RIGHT_TEXT, CENTER_TEXT );
  outtextxy( x, y, "25 %" );

  setfillstyle( HATCH_FILL, BLUE );
  pieslice( xcenter, ycenter, 225, 360, radius );
  radians = torad( 293 );
  x = xcenter + (int)( cos( radians ) * (double)lradius );
  y = ycenter - (int)( sin( radians ) * (double)lradius * AspectRatio );
  settextjustify( LEFT_TEXT, TOP_TEXT );
  outtextxy( x, y, "37.5 %" );

  Pause();				/* Pause for user's response    */

}

/*									*/
/*	BARDEMO: Draw a 2-D bar chart using Bar and Rectangle.		*/
/*									*/

void BarDemo(void)
{
  int barheight[] = {
    1, 3, 5, 2, 4   };
  int styles[]	  = {
    1, 3, 10, 5, 9, 1	};
  int xstep, ystep;
  int sheight, swidth;
  int i, j, h;
  struct viewporttype vp;
  char buffer[40];

  MainWindow( "Bar / Rectangle demonstration" );
  h = 3 * textheight( "H" );
  getviewsettings( &vp );
  settextjustify( CENTER_TEXT, TOP_TEXT );
  changetextstyle( TRIPLEX_FONT, HORIZ_DIR, 4 );
  outtextxy( MaxX /2, 6, "These are 2-D Bars" );
  changetextstyle( DEFAULT_FONT, HORIZ_DIR, 1 );
  setviewport( vp.left+50, vp.top+30, vp.right-50, vp.bottom-10, 1 );

  getviewsettings( &vp );
  sheight = vp.bottom - vp.top;
  swidth  = vp.right  - vp.left;

  line( h, h, h, sheight-h );
  line( h, sheight-h, sheight-h, sheight-h );
  ystep = (sheight - (2*h) ) / 5;
  xstep = (swidth  - (2*h) ) / 5;
  j = sheight - h;
  settextjustify( CENTER_TEXT, CENTER_TEXT );

  for( i=0 ; i<6 ; ++i ){
    line( h/2, j, h, j );
    itoa( i, buffer, 10 );
    outtextxy( 0, j, buffer );
    j -= ystep;
  }

  j = h;
  settextjustify( CENTER_TEXT, TOP_TEXT );
  for( i=0 ; i<6 ; ++i ){
    setfillstyle( styles[i], random(MaxColors) );
    line( j, sheight - h, j, sheight- 3 - (h/2) );
    itoa( i, buffer, 10 );
    outtextxy( j, sheight - (h/2), buffer );
    if( i != 5 ){
      bar( j, (sheight-h)-(barheight[i] * ystep), j+xstep, sheight-h-1 );
      rectangle( j, (sheight-h)-(barheight[i] * ystep), j+xstep, sheight-h);
    }
    j += xstep;
  }

  Pause();

}

/*									*/
/*	LINERELDEMO: Display pattern using moverel and linerel cmds.	*/
/*									*/

void LineRelDemo(void)
{
  struct viewporttype vp;
  int h, w, dx, dy, cx, cy;
  struct PTS outs[7];


  MainWindow( "MoveRel / LineRel Demonstration" );
  StatusLine( "Press any key to continue, ESC to Abort" );

  getviewsettings( &vp );
  cx = (vp.right  - vp.left) / 2;	/* Center of the screen coords	*/
  cy = (vp.bottom - vp.top ) / 2;

  h  = (vp.bottom - vp.top ) / 8;
  w  = (vp.right  - vp.left) / 9;

  dx = 2 * w;
  dy = 2 * h;

  setcolor( BLACK );

  setfillstyle( SOLID_FILL, BLUE );
  bar( 0, 0, vp.right-vp.left, vp.bottom-vp.top );	/* Draw backgnd */

  outs[0].x = cx -  dx;
  outs[0].y = cy -  dy;
  outs[1].x = cx - (dx-w);
  outs[1].y = cy - (dy+h);
  outs[2].x = cx +  dx;
  outs[2].y = cy - (dy+h);
  outs[3].x = cx +  dx;
  outs[3].y = cy +  dy;
  outs[4].x = cx + (dx-w);
  outs[4].y = cy + (dy+h);
  outs[5].x = cx -  dx;
  outs[5].y = cy + (dy+h);
  outs[6].x = cx -  dx;
  outs[6].y = cy -  dy;

  setfillstyle( SOLID_FILL, WHITE );
  fillpoly( 7, (int far *)outs );

  outs[0].x = cx - (w/2);
  outs[0].y = cy + h;
  outs[1].x = cx + (w/2);
  outs[1].y = cy + h;
  outs[2].x = cx + (w/2);
  outs[2].y = cy - h;
  outs[3].x = cx - (w/2);
  outs[3].y = cy - h;
  outs[4].x = cx - (w/2);
  outs[4].y = cy + h;

  setfillstyle( SOLID_FILL, BLUE );
  fillpoly( 5, (int far *)outs );

  /*	Draw a Tesseract object on the screen using the LineRel and	*/
  /*	MoveRel drawing commands.					*/

  moveto( cx-dx, cy-dy );
  linerel(  w, -h );
  linerel(  3*w,	0 );
  linerel(   0,  5*h );
  linerel( -w,	h );
  linerel( -3*w,	0 );
  linerel(   0, -5*h );

  moverel( w, -h );
  linerel(   0,  5*h );
  linerel( w+(w/2), 0 );
  linerel(   0, -3*h );
  linerel( w/2,   -h );
  linerel( 0, 5*h );

  moverel(  0, -5*h );
  linerel( -(w+(w/2)), 0 );
  linerel( 0, 3*h );
  linerel( -w/2, h );

  moverel( w/2, -h );
  linerel( w, 0 );

  moverel( 0, -2*h );
  linerel( -w, 0 );

  Pause();				/* Wait for user's response     */

}

/*									*/
/*	PUTPIXELDEMO: Display a pattern of random dots on the screen	*/
/*	and pick them back up again.					*/
/*									*/

void PutPixelDemo(void)
{
  int seed = 1958;
  int i, x, y, h, w, color;
  struct viewporttype vp;

  MainWindow( "PutPixel / GetPixel Demonstration" );

  getviewsettings( &vp );
  h = vp.bottom - vp.top;
  w = vp.right	- vp.left;

  srand( seed );			/* Restart random # function	*/

  for( i=0 ; i<5000 ; ++i ){		/* Put 5000 pixels on screen	*/
    x = 1 + random( w - 1 );		/* Generate a random location	*/
    y = 1 + random( h - 1 );
    color = random( MaxColors );
    putpixel( x, y, color );
  }

  srand( seed );			/* Restart Random # at same #	*/

  for( i=0 ; i<5000 ; ++i ){		/* Take the 5000 pixels off	*/
    x = 1 + random( w - 1 );		/* Generate a random location	*/
    y = 1 + random( h - 1 );
    color = getpixel( x, y );		/* Read the color pixel 	*/
    if( color == random( MaxColors ) )	/* Used to keep RANDOM in sync	*/
      putpixel( x, y, 0 );		/* Write pixel to BLACK 	*/
  }

  Pause();				/* Wait for user's response     */

}

/*									*/
/*   PUTIMAGEDEMO							*/
/*									*/
void PutImageDemo(void)
{
  static int r	    = 20;
  static int StartX = 100;
  static int StartY = 50;

  struct viewporttype vp;
  int PauseTime, x, y, ulx, uly, lrx, lry, size, i, width, height, step;
  void *Saucer;

  MainWindow("GetImage / PutImage Demonstration");
  getviewsettings( &vp );

  /* Draw Saucer */
  setfillstyle( SOLID_FILL, getmaxcolor() );
  fillellipse(StartX, StartY, r, (r/3)+2);
  ellipse(StartX, StartY-4, 190, 357, r, r/3);

  line(StartX+7, StartY-6, StartX+10, StartY-12);
  circle(StartX+10, StartY-12, 2);
  line(StartX-7, StartY-6, StartX-10, StartY-12);
  circle(StartX-10, StartY-12, 2);


  /* Read saucer image */
  ulx = StartX-(r+1);
  uly = StartY-14;
  lrx = StartX+(r+1);
  lry = StartY+(r/3)+3;
  width = lrx - ulx + 1;
  height = lry - uly + 1;
  size = imagesize(ulx, uly, lrx, lry);

  Saucer = malloc( size );
  getimage(ulx, uly, lrx, lry, Saucer);
  putimage(ulx, uly, Saucer, XOR_PUT);

/* Plot some "stars"  */
  for ( i=0 ; i<1000; ++i )
    putpixel(random(MaxX), random(MaxY), random( MaxColors-1 )+1);
  x = MaxX / 2;
  y = MaxY / 2;
  PauseTime = 70;

  /* until a key is hit */
  while ( !kbhit() ) {

    /* Draw the Saucer */
    putimage(x, y, Saucer, XOR_PUT);		     /*  draw image  */
    delay(PauseTime);
    putimage(x, y, Saucer, XOR_PUT);		     /* erase image  */

    /* Move Saucer */

    step = random( 2*r );
    if ((step/2) % 2 != 0 )
      step = -1 * step;
    x = x + step;
    step = random( r );
    if ((step/2) % 2 != 0 )
      step = -1 * step;
    y = y + step;

    if (vp.left + x + width - 1 > vp.right)
      x = vp.right-vp.left-width + 1;
    else
      if (x < 0)
	x = 0;
    if (vp.top + y + height - 1 > vp.bottom)
      y = vp.bottom-vp.top-height + 1;
    else
      if (y < 0)
	y = 0;
  }
  free( Saucer );
  Pause();
}


/*									*/
/*	LINETODEMO: Display a pattern using moveto and lineto commands. */
/*									*/

#define MAXPTS	15

void LineToDemo(void)
{
  struct viewporttype vp;
  struct PTS points[MAXPTS];
  int i, j, h, w, xcenter, ycenter;
  int radius, angle, step;
  double  rads;

  MainWindow( "MoveTo / LineTo Demonstration" );

  getviewsettings( &vp );
  h = vp.bottom - vp.top;
  w = vp.right	- vp.left;

  xcenter = w / 2;			/* Determine the center of circle */
  ycenter = h / 2;
  radius  = (h - 30) / (AspectRatio * 2);
  step	  = 360 / MAXPTS;		/* Determine # of increments	*/

  angle = 0;				/* Begin at zero degrees	*/
  for( i=0 ; i<MAXPTS ; ++i ){		/* Determine circle intercepts	*/
    rads = (double)angle * PI / 180.0;	/* Convert angle to radians	*/
    points[i].x = xcenter + (int)( cos(rads) * radius );
    points[i].y = ycenter - (int)( sin(rads) * radius * AspectRatio );
    angle += step;			/* Move to next increment	*/
  }

  circle( xcenter, ycenter, radius );	/* Draw bounding circle 	*/

  for( i=0 ; i<MAXPTS ; ++i ){		/* Draw the cords to the circle */
    for( j=i ; j<MAXPTS ; ++j ){	/* For each remaining intersect */
      moveto(points[i].x, points[i].y); /* Move to beginning of cord	*/
      lineto(points[j].x, points[j].y); /* Draw the cord		*/
    }
  }

  Pause();				/* Wait for user's response     */

}

/*									*/
/*	LINESTYLEDEMO: Display a pattern using all of the standard	*/
/*	line styles that are available. 				*/
/*									*/

void LineStyleDemo(void)
{
  int style, step;
  int x, y, w;
  struct viewporttype vp;
  char buffer[40];

  MainWindow( "Pre-defined line styles" );

  getviewsettings( &vp );
  w = vp.right	- vp.left;

  x = 35;
  y = 10;
  step = w / 11;

  settextjustify( LEFT_TEXT, TOP_TEXT );
  outtextxy( x, y, "Normal Width" );

  settextjustify( CENTER_TEXT, TOP_TEXT );

  for( style=0 ; style<4 ; ++style ){
    setlinestyle( style, 0, NORM_WIDTH );
    line( x, y+20, x, vp.bottom-40 );
    itoa( style, buffer, 10 );
    outtextxy( x, vp.bottom-30, buffer );
    x += step;
  }

  x += 2 * step;

  settextjustify( LEFT_TEXT, TOP_TEXT );
  outtextxy( x, y, "Thick Width" );
  settextjustify( CENTER_TEXT, TOP_TEXT );

  for( style=0 ; style<4 ; ++style ){
    setlinestyle( style, 0, THICK_WIDTH );
    line( x, y+20, x, vp.bottom-40 );
    itoa( style, buffer, 10 );
    outtextxy( x, vp.bottom-30, buffer );
    x += step;
  }

  settextjustify( LEFT_TEXT, TOP_TEXT );

  Pause();				/* Wait for user's response     */

}

/*									*/
/*	CRTMODEDEMO: Demonstrate the effects of the change mode 	*/
/*	commands on the current screen. 				*/
/*									*/

void CRTModeDemo(void)
{
  struct viewporttype vp;
  int mode;

  MainWindow( "SetGraphMode / RestoreCRTMode demo" );
  getviewsettings( &vp );
  mode = getgraphmode();
  settextjustify( CENTER_TEXT, CENTER_TEXT );

  outtextxy( (vp.right-vp.left)/2, (vp.bottom-vp.top)/2,
  "Now you are in graphics mode..." );
  StatusLine( "Press any key for text mode..." );
  getch();

  restorecrtmode();
  printf( "Now you are in text mode.\n\n" );
  printf( "Press any key to go back to graphics..." );
  getch();

  setgraphmode( mode );
  MainWindow( "SetGraphMode / RestoreCRTMode demo" );
  settextjustify( CENTER_TEXT, CENTER_TEXT );
  outtextxy( (vp.right-vp.left)/2, (vp.bottom-vp.top)/2,
  "Back in Graphics Mode..." );

  Pause();				/* Wait for user's response     */

}

/*									*/
/*	USERLINESTYLEDEMO: Display line styles showing the user 	*/
/*	defined line style functions.					*/
/*									*/

void UserLineStyleDemo(void)
{
  int x, y, i, h, flag;
  unsigned int style;
  struct viewporttype vp;

  MainWindow( "User defined line styles" );

  getviewsettings( &vp );
  h = vp.bottom - vp.top;

  x = 4;
  y = 10;
  style = 0;
  i = 0;

  settextjustify( CENTER_TEXT, TOP_TEXT );
  flag = TRUE;				/* Set the bits in this pass	*/

  while( x < vp.right-2 ){		/* Draw lines across the screen */

    if( flag )				/* If flag, set bits... 	*/
      style = style | (1 << i); 	/*    Set the Ith bit in word	*/
    else				/* If no flag, clear bits	*/
    style = style & !(0x8000 >> i);	/*    Clear the Ith bit in word */

    setlinestyle( USERBIT_LINE, style, NORM_WIDTH );
    line( x, y, x, h-y );		/* Draw the new line pattern	*/

    x += 5;				/* Move the X location of line	*/
    i = ++i % 16;			/* Advance to next bit pattern	*/

    if( style == 0xffff ){		/* Are all bits set?		*/
      flag = FALSE;			/*   begin removing bits	*/
      i = 0;				/* Start with whole pattern	*/
    }
    else{				/* Bits not all set...		*/
      if( style == 0 )			/* Are all bits clear?		*/
	flag = TRUE;			/*   begin setting bits 	*/
    }
  }

  settextjustify( LEFT_TEXT, TOP_TEXT );

  Pause();				/* Wait for user's response     */

}

/*									*/
/*	FILLSTYLEDEMO: Display the standard fill patterns available.	*/
/*									*/

void FillStyleDemo(void)
{
  int h, w, style;
  int i, j, x, y;
  struct viewporttype vp;
  char buffer[40];

  MainWindow( "Pre-defined Fill Styles" );

  getviewsettings( &vp );
  w = 2 * ((vp.right  +  1) / 13);
  h = 2 * ((vp.bottom - 10) / 10);

  x = w / 2;
  y = h / 2;		/* Leave 1/2 blk margin 	*/
  style = 0;

  for( j=0 ; j<3 ; ++j ){		/* Three rows of boxes		*/
    for( i=0 ; i<4 ; ++i ){		/* Four column of boxes 	*/
      setfillstyle(style, MaxColors-1); /* Set the fill style and WHITE */
      bar( x, y, x+w, y+h );		/* Draw the actual box		*/
      rectangle( x, y, x+w, y+h );	/* Outline the box		*/
      itoa( style, buffer, 10 );	/* Convert style 3 to ASCII	*/
      outtextxy( x+(w / 2), y+h+4, buffer );
      ++style;				/* Go on to next style #	*/
      x += (w / 2) * 3; 		/* Go to next column		*/
    }				/* End of coulmn loop		*/
    x = w / 2;				/* Put base back to 1st column	*/
    y += (h / 2) * 3;			/* Advance to next row		*/
  }					/* End of Row loop		*/

  settextjustify( LEFT_TEXT, TOP_TEXT );

  Pause();				/* Wait for user's response     */

}

/*									*/
/*	FILLPATTERNDEMO: Demonstrate how to use the user definable	*/
/*	fill patterns.							*/
/*									*/

void FillPatternDemo(void)
{
  int style;
  int h, w;
  int x, y, i, j;
  char buffer[40];
  struct viewporttype vp;
  static char patterns[][8] = {
    { 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55 },
    { 0x33, 0x33, 0xCC, 0xCC, 0x33, 0x33, 0xCC, 0xCC },
    { 0xF0, 0xF0, 0xF0, 0xF0, 0x0F, 0x0F, 0x0F, 0x0F },
    { 0x00, 0x10, 0x28, 0x44, 0x28, 0x10, 0x00, 0x00 },
    { 0x00, 0x70, 0x20, 0x27, 0x24, 0x24, 0x07, 0x00 },
    { 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x3C, 0x3C, 0x3C, 0x3C, 0x00, 0x00 },
    { 0x00, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x7E, 0x00 },
    { 0x00, 0x00, 0x22, 0x08, 0x00, 0x22, 0x1C, 0x00 },
    { 0xFF, 0x7E, 0x3C, 0x18, 0x18, 0x3C, 0x7E, 0xFF },
    { 0x00, 0x10, 0x10, 0x7C, 0x10, 0x10, 0x00, 0x00 },
    { 0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00 }
  };

  MainWindow( "User Defined Fill Styles" );

  getviewsettings( &vp );
  w = 2 * ((vp.right  +  1) / 13);
  h = 2 * ((vp.bottom - 10) / 10);

  x = w / 2;
  y = h / 2;		/* Leave 1/2 blk margin 	*/
  style = 0;

  for( j=0 ; j<3 ; ++j ){		/* Three rows of boxes		*/
    for( i=0 ; i<4 ; ++i ){		/* Four column of boxes 	*/
      setfillpattern( &patterns[style][0], MaxColors-1 );
      bar( x, y, x+w, y+h );		/* Draw the actual box		*/
      rectangle( x, y, x+w, y+h );	/* Outline the box		*/
      itoa( style, buffer, 10 );	/* Convert style 3 to ASCII	*/
      outtextxy( x+(w / 2), y+h+4, buffer );
      ++style;				/* Go on to next style #	*/
      x += (w / 2) * 3; 		/* Go to next column		*/
    }				/* End of coulmn loop		*/
    x = w / 2;				/* Put base back to 1st column	*/
    y += (h / 2) * 3;			/* Advance to next row		*/
  }					/* End of Row loop		*/

  settextjustify( LEFT_TEXT, TOP_TEXT );

  Pause();				/* Wait for user's response     */

}

/*									*/
/*	POLYDEMO: Display a random pattern of polygons on the screen	*/
/*	until the user says enough.					*/
/*									*/

void PaletteDemo(void)
{
  int i, j, x, y, color;
  struct viewporttype vp;
  int height, width;

  MainWindow( "Palette Demonstration" );
  StatusLine( "Press any key to continue, ESC to Abort" );

  getviewsettings( &vp );
  width  = (vp.right - vp.left) / 15;	/* get width of the box 	*/
  height = (vp.bottom - vp.top) / 10;	/* Get the height of the box	*/

  x = y = 0;				/* Start in upper corner	*/
  color = 1;				/* Begin at 1st color		*/

  for( j=0 ; j<10 ; ++j ){		/* For 10 rows of boxes 	*/
    for( i=0 ; i<15 ; ++i ){		/* For 15 columns of boxes	*/
      setfillstyle( SOLID_FILL, color++ );	/* Set the color of box */
      bar( x, y, x+width, y+height );		/* Draw the box 	*/
      x += width + 1;				/* Advance to next col	*/
      color = 1 + (color % (MaxColors - 2));	/* Set new color	*/
    }				/* End of COLUMN loop		*/
    x = 0;				/* Goto 1st column		*/
    y += height + 1;			/* Goto next row		*/
  }					/* End of ROW loop		*/

  while( !kbhit() ){			/* Until user enters a key...	*/
    setpalette( 1+random(MaxColors - 2), random( 65 ) );
  }

  setallpalette( &palette );

  Pause();				/* Wait for user's response     */

}

/*									*/
/*	POLYDEMO: Display a random pattern of polygons on the screen	*/
/*	until the user says enough.					*/
/*									*/

#define MaxPts		6		/* Maximum # of pts in polygon	*/

void PolyDemo(void)
{
  struct PTS poly[ MaxPts ];		/* Space to hold datapoints	*/
  int color;				/* Current drawing color	*/
  int i;

  MainWindow( "DrawPoly / FillPoly Demonstration" );
  StatusLine( "ESC Aborts - Press a Key to stop" );

  while( !kbhit() ){			/* Repeat until a key is hit	*/

    color = 1 + random( MaxColors-1 );	/* Get a random color # (no blk)*/
    setfillstyle( random(10), color );	/* Set a random line style	*/
    setcolor( color );			/* Set the desired color	*/

    for( i=0 ; i<(MaxPts-1) ; i++ ){	/* Determine a random polygon	*/
      poly[i].x = random( MaxX );	/* Set the x coord of point	*/
      poly[i].y = random( MaxY );	/* Set the y coord of point	*/
    }

    poly[i].x = poly[0].x;		/* last point = first point	*/
    poly[i].y = poly[1].y;

    fillpoly( MaxPts, (int far *)poly );    /* Draw the actual polygon	    */
  }					/* End of WHILE not KBHIT	*/

  Pause();				/* Wait for user's response     */

}


/*									*/
/*	SAYGOODBYE: Give a closing screen to the user before leaving.	*/
/*									*/

void SayGoodbye(void)
{
  struct viewporttype viewinfo; 	/* Structure to read viewport	*/
  int h, w;

  MainWindow( "== Finale ==" );

  getviewsettings( &viewinfo ); 	/* Read viewport settings	*/
  changetextstyle( TRIPLEX_FONT, HORIZ_DIR, 4 );
  settextjustify( CENTER_TEXT, CENTER_TEXT );

  h = viewinfo.bottom - viewinfo.top;
  w = viewinfo.right  - viewinfo.left;
  outtextxy( w/2, h/2, "That's all, folks!" );

  StatusLine( "Press any key to EXIT" );
  getch();

  cleardevice();			/* Clear the graphics screen	*/

}

/*									*/
/*	PAUSE: Pause until the user enters a keystroke. If the		*/
/*	key is an ESC, then exit program, else simply return.		*/
/*									*/

void Pause(void)
{
  static char msg[] = "Esc aborts or press a key...";
  int c;

  StatusLine( msg );			/* Put msg at bottom of screen	*/

  c = getch();				/* Read a character from kbd	*/

  if( ESC == c ){			/* Does user wish to leave?	*/
    closegraph();			/* Change to text mode		*/
    exit( 1 );				/* Return to OS 		*/
  }

  if( 0 == c ){ 			/* Did use hit a non-ASCII key? */
    c = getch();			/* Read scan code for keyboard	*/
  }

  cleardevice();			/* Clear the screen		*/

}

/*									*/
/*	MAINWINDOW: Establish the main window for the demo and set	*/
/*	a viewport for the demo code.					*/
/*									*/

void MainWindow( char *header )
{
  int height;

  cleardevice();			/* Clear graphics screen	*/
  setcolor( MaxColors - 1 );		/* Set current color to white	*/
  setviewport( 0, 0, MaxX, MaxY, 1 );	/* Open port to full screen	*/

  height = textheight( "H" );           /* Get basic text height        */

  changetextstyle( DEFAULT_FONT, HORIZ_DIR, 1 );
  settextjustify( CENTER_TEXT, TOP_TEXT );
  outtextxy( MaxX/2, 2, header );
  setviewport( 0, height+4, MaxX, MaxY-(height+4), 1 );
  DrawBorder();
  setviewport( 1, height+5, MaxX-1, MaxY-(height+5), 1 );

}

/*									*/
/*	STATUSLINE: Display a status line at the bottom of the screen.	*/
/*									*/

void StatusLine( char *msg )
{
  int height;

  setviewport( 0, 0, MaxX, MaxY, 1 );	/* Open port to full screen	*/
  setcolor( MaxColors - 1 );		/* Set current color to white	*/

  changetextstyle( DEFAULT_FONT, HORIZ_DIR, 1 );
  settextjustify( CENTER_TEXT, TOP_TEXT );
  setlinestyle( SOLID_LINE, 0, NORM_WIDTH );
  setfillstyle( EMPTY_FILL, 0 );

  height = textheight( "H" );           /* Detemine current height      */
  bar( 0, MaxY-(height+4), MaxX, MaxY );
  rectangle( 0, MaxY-(height+4), MaxX, MaxY );
  outtextxy( MaxX/2, MaxY-(height+2), msg );
  setviewport( 1, height+5, MaxX-1, MaxY-(height+5), 1 );

}

/*									*/
/*	DRAWBORDER: Draw a solid single line around the current 	*/
/*	viewport.							*/
/*									*/

void DrawBorder(void)
{
  struct viewporttype vp;

  setcolor( MaxColors - 1 );		/* Set current color to white	*/

  setlinestyle( SOLID_LINE, 0, NORM_WIDTH );

  getviewsettings( &vp );
  rectangle( 0, 0, vp.right-vp.left, vp.bottom-vp.top );

}

/*									*/
/*	CHANGETEXTSTYLE: similar to settextstyle, but checks for	*/
/*	errors that might occur whil loading the font file.		*/
/*									*/

void changetextstyle(int font, int direction, int charsize)
{
  int ErrorCode;

  graphresult();			/* clear error code		*/
  settextstyle(font, direction, charsize);
  ErrorCode = graphresult();		/* check result 		*/
  if( ErrorCode != grOk ){		/* if error occured		*/
    closegraph();
    printf(" Graphics System Error: %s\n", grapherrormsg( ErrorCode ) );
    exit( 1 );
  }
}

/*									*/
/*	GPRINTF: Used like PRINTF except the output is sent to the	*/
/*	screen in graphics mode at the specified co-ordinate.		*/
/*									*/

int gprintf( int *xloc, int *yloc, char *fmt, ... )
{
  va_list  argptr;			/* Argument list pointer	*/
  char str[140];			/* Buffer to build sting into	*/
  int cnt;				/* Result of SPRINTF for return */

  va_start( argptr, fmt );		/* Initialize va_ functions	*/

  cnt = vsprintf( str, fmt, argptr );	/* prints string to buffer	*/
  outtextxy( *xloc, *yloc, str );	/* Send string in graphics mode */
  *yloc += textheight( "H" ) + 2;       /* Advance to next line         */

  va_end( argptr );			/* Close va_ functions		*/

  return( cnt );			/* Return the conversion count	*/

}
