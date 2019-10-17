/*------------------------------------------------------------------------
 * filename - clreol.c
 *
 * function(s)
 *        clreol - Clears to the end of the line in the text window
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



/*------------------------------------------------------------------------*

Name            clreol - Clears to the end of the line in text window

Usage           void clreol(void)

Prototype in    conio.h

Description     clreol clears all characters from the cursor position to
                the end of the line within the current text window without
                moving the cursor.

Return value    None

*--------------------------------------------------------------------------*/
void clreol(void)
{
  register int line;

  line = _wherey();
  __scroll(UP, _wherex(), line, _video.windowx2, line, 0);
}
