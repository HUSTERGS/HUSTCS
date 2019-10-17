/*------------------------------------------------------------------------
 * filename - color.c
 *
 * function(s)
 *        textcolor      - selects new character color in text mode
 *        textbackground - selects new text background color
 *        textattr       - sets text attributes
 *        highvideo      - selects high intensity text characters
 *        lowvideo       - selects low intensity text characters
 *        normvideo      - selects normal intensity text characters
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

#define INTENSE 0x08


/*------------------------------------------------------------------------*

Name            textcolor - selects new character color in text mode

Usage           void textcolor(int newcolor);

Prototype in    conio.h

Description     selects the foreground character color.

Return value    None

*--------------------------------------------------------------------------*/
void textcolor(int newcolor)
{
  _video.attribute = (_video.attribute & 0x70) | (newcolor & 0x8F);
}



/*------------------------------------------------------------------------*

Name            textbackground - selects new text background color

Usage           void textbackground(int newcolor);

Prototype in    conio.h

Description     textbackground selects the background text color.

Return value    None

*--------------------------------------------------------------------------*/
void textbackground(int newcolor)
{
  _video.attribute = (_video.attribute & 0x8F) | ((newcolor<<4) & 0x7f);
}



/*------------------------------------------------------------------------*

Name            textattr - sets text attributes

Usage           void textattr(int newattr);

Prototype in    conio.h

Description     lets you set both the foreground and background
                colors in a single call.

Return value    None

*--------------------------------------------------------------------------*/

void textattr(int newattr)
{
  _video.attribute = newattr;
}



/*------------------------------------------------------------------------*

Name            highvideo - selects high intensity text characters

Usage           void highvideo(void);

Prototype in    conio.h

Description     selects high intensity characters by setting
                the high intensity bit of the currently selected
                foreground color.

Return value    None

*--------------------------------------------------------------------------*/
void highvideo(void)
{
  _video.attribute |= INTENSE;
}



/*------------------------------------------------------------------------*

Name            lowvideo - selects low intensity text characters

Usage           void lowvideo(void);

Prototype in    conio.h

Description     selects low intensity characters by clearing the
                high intensity bit of the currently selected
                foreground color.


Return value  None

*--------------------------------------------------------------------------*/
void lowvideo(void)
{
  _video.attribute &= ~INTENSE;
}



/*------------------------------------------------------------------------*

Name            normvideo - selects normal intensity text characters

Usage           void normvideo(void);

Prototype in    conio.h

Description     selects normal characters by returning the text attribute
                (foreground and background) to the value it had when the
                program started.

Return value    None

*--------------------------------------------------------------------------*/
void normvideo(void)
{
  _video.attribute = _video.normattr;
}
