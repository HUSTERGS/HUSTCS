/* Turbo C++ - (C) Copyright 1987-1991 by Borland International */

#define MAIN

#include <string.h>
#include <alloc.h>
#include <stdarg.h>
#include <dos.h>
#include <conio.h>
#include "tcalc.h"

CELLPTR cell[MAXCOLS][MAXROWS], curcell;
unsigned char format[MAXCOLS][MAXROWS];
unsigned char colwidth[MAXCOLS];
unsigned char colstart[SCREENCOLS];
int leftcol, rightcol, toprow, bottomrow, curcol, currow, lastcol, lastrow;
char changed = FALSE;
char formdisplay = FALSE;
char autocalc = TRUE;
char stop = FALSE;
char colortable[128];
char colorcard;
char snow;
char far *displayptr;
long memleft;
unsigned int oldcursor, shortcursor, tallcursor, nocursor = 0x2000;

void run()
/* The main program loop */
{
 int input;

 do
 {
  displaycell(curcol, currow, HIGHLIGHT, NOUPDATE);
  curcell = cell[curcol][currow];
  showcelltype();
  input = getkey();
  switch(input)
  {
   case '/' :
    mainmenu();
    break;
   case F1 :
    recalc();
    break;
   case F2 :
    editcell(curcell);
    break;
   case DELKEY :
    deletecell(curcol, currow, UPDATE);
    printfreemem();
    if (autocalc)
     recalc();
    break;
   case PGUPKEY :
    toprow -= 20;
    currow -= 20;
    if (currow < 0)
     currow = toprow = 0;
    else if (toprow < 0)
    {
     currow -= toprow;
     toprow = 0;
    }
    setbottomrow();
    displayscreen(NOUPDATE);
    break;
   case PGDNKEY :
    toprow += 20;
    currow += 20;
    if ((currow >= MAXROWS) && (toprow >= MAXROWS))
    {
     currow = MAXROWS - 1;
     toprow = MAXROWS - 20;
    }
    else if (toprow > (MAXROWS - 20))
    {
     currow -= (toprow + 20 - MAXROWS);
     toprow = MAXROWS - 20;
    }
    setbottomrow();
    displayscreen(NOUPDATE);
    break;
   case CTRLLEFTKEY :
    displaycell(curcol, currow, NOHIGHLIGHT, NOUPDATE);
    if (leftcol == 0)
     curcol = 0;
    else
    {
     curcol = rightcol = leftcol - 1;
     setleftcol();
     setrightcol();
     displayscreen(NOUPDATE);
    }
    break;
   case CTRLRIGHTKEY :
    displaycell(curcol, currow, NOHIGHLIGHT, NOUPDATE);
    if (rightcol == MAXCOLS - 1)
     curcol = rightcol;
    else
    {
     curcol = leftcol = rightcol + 1;
     setrightcol();
     setleftcol();
     displayscreen(NOUPDATE);
    }
    break;
   case HOMEKEY :
    currow = curcol = leftcol = toprow = 0;
    setrightcol();
    setbottomrow();
    displayscreen(NOUPDATE);
    break;
   case ENDKEY :
    rightcol = curcol = lastcol;
    currow = bottomrow = lastrow;
    settoprow();
    setleftcol();
    setrightcol();
    displayscreen(NOUPDATE);
    break;
   case UPKEY :
    moverowup();
    break;
   case DOWNKEY :
    moverowdown();
    break;
   case LEFTKEY :
    movecolleft();
    break;
   case RIGHTKEY :
    movecolright();
    break;
   default :
    if ((input >= ' ') && (input <= '~'))
     getinput(input);
    break;
  } /* switch */
 }
 while (!stop);
} /* run */

void main(int argc, char *argv[])
{
 window(1, 1, 80, 25);
 initcursor();
 initcolortable();
 setcursor(nocursor);
 setcolor(WHITE);
 clrscr();
 writef((80 - strlen(MSGHEADER)) >> 1, 11, MSGHEADERCOLOR, strlen(MSGHEADER),
        MSGHEADER);
 writef((80 - strlen(MSGKEYPRESS)) >> 1, 13, PROMPTCOLOR,
        strlen(MSGKEYPRESS), MSGKEYPRESS);
 gotoxy(80, 25);
 getkey();
 setcolor(WHITE);
 clrscr();
 initvars();
 memleft = memsize;
 redrawscreen();
 if (argc > 1)
  loadsheet(argv[1]);
 clearinput();
 run();
 setcolor(LIGHTGRAY);
 clrscr();
 setcursor(oldcursor);
}


