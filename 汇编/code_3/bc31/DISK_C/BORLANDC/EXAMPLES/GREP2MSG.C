/*
   EXAMPLE SOURCE CODE FOR GREP FILTER

   Grep2Msg.C
   Copyright (c) 1990, 1991 Borland International, Inc.
   All rights reserved.

   Grep2Msg - Message filter from Turbo Grep to the IDE message window.

   This filter accepts input through the standard input stream, converts
   it and outputs it to the standard output stream.  The streams are linked
   through pipes, such that the input stream is the output from GREP, and
   the output stream is connected to the message window of the IDE.
   This filter is invoked through the IDE transfer mechanism as

            grep <commands> | grep2msg | IDE message window

    Compile using the LARGE memory model.
*/

#include <dir.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <alloc.h>
#include <io.h>
#include <dos.h>
#include "filter.h"

#define TRUE  1
#define FALSE 0

char     NewFileText[] = "File ";
unsigned BufSize,CurBufLen;
char     *InBuffer,
         *OutBuffer,
         *CurInPtr,
         *CurOutPtr,
         *LinePtr;
char     Line[133];
long int InOff;
char     EndMark;
int      NoLines;

/************************************************************************
Function  : NextChar
Parameters: None
Returns   : next character in input buffer or 0 for end of file

Input from the standard input stream is buffered in a global buffer InBuffer
which is allocated in function main.  NextChar function will return
the next character in the buffer, reading from the input stream when the
buffer becomes empty.
************************************************************************/
char NextChar(void)
{
   if (CurInPtr < InBuffer+CurBufLen)   /* if buffer is not empty */
   {
      return *(CurInPtr++);             /* return next information */
   }
   else
   {
      CurInPtr = InBuffer;              /* reset pointer to front of buffer */
      lseek(0,InOff,0);                 /* seek to the next section for read */
      InOff += BufSize;                 /* increment pointer to next block */
      if ((CurBufLen = read(0,InBuffer,BufSize)) !=0)
         return NextChar();             /* recursive call returns first
                                           character in buffer after read */
      return 0;                         /* return 0 on end of file */
   }
}

/*************************************************************************
Function  : flushOut
Parameters: Size   The number of characters to be written out
Returns   : nothing

Strings to be sent to the message window are placed in a buffer called
OutBuffer.  A call to this function will write Size bytes to the
standard output stream and reset the output buffer pointer to the
beginning of the buffer.  Any additional information in the buffer is
thus lost.
**************************************************************************/
void flushOut(unsigned Size)
{
  if (Size != 0)                 /* don't flush an empty buffer */
  {
    CurOutPtr = OutBuffer;       /* reset pointer to beginning of buffer */
    lseek(1,0,2);                /* seek output stream to end */
    write(1,OutBuffer,Size);     /* write out Size bytes */
  }
}

/**************************************************************************
Function  : Put
Parameters: S     pointer to a string of characters
            Len   length of the string of characters
Returns   : Nothing.

Put places bytes into OutBuffer so they may be later flushed out into the
standard output stream using flushOut.
*************************************************************************/
void Put(char *S,int Len)
{
  int i;

  for (i = 0; i < Len; i++)
  {
    *CurOutPtr++ = S[i];                     /* place byte in buffer */
    if (CurOutPtr >= OutBuffer+BufSize)      /* if buffer overflows */
      flushOut(BufSize);                     /* flush to the stream */
  }
}

/**************************************************************************
Function  : ProcessLine
Parameters: Line   a pointer to the character line to be analyzed
Returns   : Nothing.

Filters lines output from grep into a format usable in the Turbo C++
environment message window.  Lines are simply sent straight through
with format characters for the message window.
**************************************************************************/
void ProcessLine(char *Line)
{
  char Type;
  unsigned i;
  char *s;

  if (Line[0] == 0)                            /* ignore blank line */
    return;

  /* check for new file name */
  if (strncmp(Line,NewFileText,strlen(NewFileText)) == 0)
  {
    if (NoLines)                             /* if no lines from last file */
    {
      Type = MsgNewLine;                     /* put some space in window */
      i = 1;
      Put(&Type,1);
      Put((char *)&i,2);
      Put((char *)&i,2);
      Put(" ",2);
    }
    Type = MsgNewFile;                       /* indicate new file */
    Line[strlen(Line)-1] = 0;                /* remove ":" */
    memmove(Line,&Line[strlen(NewFileText)],strlen(Line));
    Put(&Type,1);
    Put(Line,strlen(Line)+1);                /* write filename */
    NoLines = TRUE;
  }
  else
  {
    NoLines = FALSE;                         /* message lines output */
    Type = MsgNewLine;                       /* new line in message window */
    s = strchr(Line,' ');
    if (s != NULL)
    {
      s++;
      if (strncmp(s,"lines match",11) == 0)  /* special case lines matching */
      {
        i = 1;
        Put(&Type,1);                        /* output two newlines */
        Put((char *)&i,2);
        Put((char *)&i,2);                   /* to message window */
        Put(Line,strlen(Line)+1);            /* and the line */
      }
      else
      {
        s--;
        *s = 0;
        i = atoi(Line);
        *s = ' ';
        if (i != 0)
        {
          Put(&Type,1);
          Put((char *)&i,2);                 /* output line number */
          i = 1;                             /* Column */
          Put((char *)&i,2);                 /* set column over */
          s++;
          memmove(Line,s,strlen(s)+1);
          while (Line[0] == ' ' && Line[0] != 0)  /* strip leading spaces */
            memmove(Line,&Line[1],strlen(Line));  /* from remaining line */
          Put(Line,strlen(Line)+1);               /* and put out the line */
        }
      }
    }
  }
}

/************************************************************************
Function  : Main

Returns   : zero on successful execution
               3 on an error condition

The main routine allocates memory for the input and output buffers.
Characters are then read from the input buffer building the line buffer
that will be sent to the filter processor.  Lines are read and filtered
until the end of input is reached.
************************************************************************/
int main(void)
{
   char c;
   int i, Type;
   unsigned long core;

   setmode(1,O_BINARY);               /* set standard out to binary mode */
   NoLines = FALSE;                   /* No lines have been read yet */
   core = farcoreleft();              /* get available memory */
   if (core > 64000U)                 /* limit buffers to total of 64000 */
      BufSize = 64000U;               /* bytes */
   else
      BufSize = (unsigned)core;
   if ((InBuffer = malloc(BufSize)) == NULL) /* allocate buffer space */
      exit(3);                        /* abort if error occured */
   CurInPtr = InBuffer;               /* split buffer */
   BufSize = BufSize/2;               /* between input and output buffers */
   OutBuffer = InBuffer + BufSize;
   CurOutPtr = OutBuffer;
   LinePtr = Line;                    /* set line buffer pointer */
   CurBufLen = 0;                     /* and reset buffer size to zero */
   Put(PipeId,PipeIdLen);             /* Identify process to message window */
   while ((c = NextChar()) != 0)      /* read characters */
   {
      if ((c == 13) || (c == 10))     /* build line until new line is seen */
      {
         *LinePtr = 0;
         ProcessLine(Line);           /* then filter the line */
         LinePtr = Line;
      }
      /* characters are added to line only up to 132 characters */
      else if ((FP_OFF(LinePtr) - FP_OFF(&Line)) < 132)
      {
         *LinePtr = c;
         LinePtr++;
      }
   }
   *LinePtr = 0;
   ProcessLine(Line);                  /* filter last line */
   if (NoLines)                        /* if no lines */
   {
      Type = MsgNewLine;               /* send something to the */
      i = 1;                           /* message window */
      Put((char *)&Type,1);
      Put((char *)&i,2);
      Put((char *)&i,2);
      Put(" ",2);
   }
   EndMark = MsgEoFile;                /* indicate end of input to */
   Put(&EndMark,1);                    /* message window */
   flushOut((unsigned)(CurOutPtr-OutBuffer));  /* flush out remaining buffer */

   return  0;                          /* everything went ok */
}

