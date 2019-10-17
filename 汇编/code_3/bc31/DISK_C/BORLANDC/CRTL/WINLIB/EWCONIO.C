/*------------------------------------------------------------------------
 * filename - ewconio.c
 *
 * function(s)
 *        getch -  get keyboard character
 *        getche - get and echo keyboard character
 *        kbhit  - check for keyboard character available
 *        putch  - write character to display
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <conio.h>

int   _ReadKey(void);
void  _WriteChar(char Ch);
int   _KeyPressed(void);

int getch(void)
{
    return _ReadKey();
}

int getche(void)
{
    int c = _ReadKey();
    _WriteChar(c);
    return c;
}

int kbhit(void)
{
    return _KeyPressed();
}

int putch(int c)
{
    _WriteChar(c);
    return c;
}
