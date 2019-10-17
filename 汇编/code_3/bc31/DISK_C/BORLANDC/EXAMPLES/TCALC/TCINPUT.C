/* Turbo C++ - (C) Copyright 1987-1991 by Borland International */

#include <string.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <bios.h>
#include <conio.h>
#include <string.h>
#include "tcalc.h"

int getkey(void)
/* Uses the BIOS to read the next keyboard character */
{
 int key, lo, hi;

 key = bioskey(0);
 lo = key & 0X00FF;
 hi = (key & 0XFF00) >> 8;
 return((lo == 0) ? hi + 256 : lo);
} /* getkey */

int editstring(char *s, char *legal, int maxlength)
/* Allows the user to edit a string with only certain characters allowed -
   Returns TRUE if ESC was not pressed, FALSE is ESC was pressed.
*/
{
 int c, len = strlen(s), pos = len, insert = TRUE;

 changecursor(insert);
 do
 {
  writef(1, 25, WHITE, 79, "%s", s);
  gotoxy(pos + 1, 25);
  switch(c = getkey())
  {
   case HOMEKEY :
    pos = 0;
    break;
   case ENDKEY :
    pos = len;
    break;
   case INSKEY :
    insert = !insert;
    changecursor(insert);
    break;
   case LEFTKEY :
    if (pos > 0)
     pos--;
    break;
   case RIGHTKEY :
    if (pos < len)
     pos++;
    break;
   case BS :
    if (pos > 0)
    {
     movmem(&s[pos], &s[pos - 1], len - pos + 1);
     pos--;
     len--;
    }
    break;
   case DELKEY :
    if (pos < len)
    {
     movmem(&s[pos + 1], &s[pos], len - pos);
     len--;
    }
    break;
   case CR :
    break;
   case UPKEY :
    c = CR;
    break;
   case DOWNKEY :
    c = CR;
    break;
   case ESC :
    len = 0;
    break;
   default :
    if (((legal[0] == 0) || (strchr(legal, c) != NULL)) &&
        ((c >= ' ') && (c <= '~')) &&
        (len < maxlength))
    {
     if (insert)
     {
      memmove(&s[pos + 1], &s[pos], len - pos + 1);
      len++;
     }
     else if (pos >= len)
      len++;
     s[pos++] = c;
    }
    break;
  } /* switch */
  s[len] = 0;
 }
 while ((c != CR) && (c != ESC));
 clearinput();
 changecursor(FALSE);
 setcursor(nocursor);
 return(c != ESC);
} /* editstring */

void getinput(int c)
/* Reads and acts on an input string from the keyboard that started with c. */
{
 char s[MAXINPUT + 1];

 s[0] = c;
 s[1] = 0;
 if (!editstring(s, "", MAXINPUT) || (s[0] == 0))
  return;
 act(s);
 changed = TRUE;
} /* getinput */

int getint(int *number, int low, int high)
/* Reads in a positive integer from low to high */
{
 int i, good = FALSE;
 char s[5], message[81];

 s[0] = 0;
 sprintf(message, MSGBADNUMBER, low, high);
 do
 {
  if (!editstring(s, "1234567890", 4))
   return(FALSE);
  i = atoi(s);
  if ((good = ((i >= low) && (i <= high))) == 0)
   errormsg(message);
 }
 while (!good);
 *number = i;
 return(TRUE);
} /* getint */

int getcell(int *col, int *row)
/* Reads in a cell name that was typed in - Returns FALSE if ESC was pressed */
{
 int first = TRUE, good = FALSE, len, numlen = rowwidth(MAXROWS),
     oldcol = *col, oldrow = *row;
 char data[10], *input, *start, numstring[6];

 data[0] = 0;
 do
 {
  if (!first)
   errormsg(MSGBADCELL);
  first = FALSE;
  input = data;
  if (!editstring(data, "", numlen + 2))
  {
   *col = oldcol;
   *row = oldrow;
   return(FALSE);
  }
  *col = toupper(*(input++)) - 'A';
  if (isalpha(*input))
  {
   *col *= 26;
   *col += toupper(*(input++)) - 'A' + 26;
  }
  if (*col >= MAXCOLS)
   continue;
  start = input;
  for (len = 0; len < numlen; len++)
  {
   if (!isdigit(*(input++)))
   {
    input--;
    break;
   }
  }
  if (len == 0)
   continue;
  strncpy(numstring, start, len);
  numstring[len] = 0;
  *row = atoi(numstring) - 1;
  if ((*row >= MAXROWS) || (*row == -1) || (*input != 0))
   continue;
  good = TRUE;
 }
 while (!good);
 return(TRUE);
} /* getcell */
int getyesno(int *yesno, char *prompt)
/* Prints a prompt and gets a yes or no answer - returns TRUE if ESC was
   pressed, FALSE if not.
*/
{
 writeprompt(prompt);
 setcursor(shortcursor);
 do
 {
  *yesno = toupper(getkey());
  if (*yesno == ESC)
  {
   setcursor(nocursor);
   return(FALSE);
  }
 }
 while (strchr("YN", *yesno) == NULL);
 setcursor(nocursor);
 return(TRUE);
} /* getyesno */


