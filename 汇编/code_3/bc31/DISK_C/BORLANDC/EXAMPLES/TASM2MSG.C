/*
   EXAMPLE SOURCE CODE FOR TASM FILTER

   Tasm2Msg.C
   Copyright (c) 1990, 1991 Borland International, Inc.
   All rights reserved.

   Tasm2Msg - assembler output filter to the IDE message window.

   This filter accepts input through the standard input stream, converts
   it and outputs it to the standard output stream.  The streams are linked
   through pipes, such that the input stream is the output from the assembler
   being invoked, and the output stream is connected to the message window
   of the IDE, ie.

	      tasm fname | tasm2msg | IDE message window

   Input can come from TASM, MASM 5.1 or OPTASM.  The type of assembler is
   determined from analysing the lines of output from the assembler.

   Compile using the LARGE memory model.
*/

#include <dir.h>
#include <dos.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <alloc.h>
#include <io.h>
#include <ctype.h>
#include "filter.h"

#define TRUE (1 == 1)
#define FALSE !(TRUE)

/* Turbo Assembler text for conversion */
char TasmWarningTxt[] = "*Warning* ";
char TasmErrorTxt[]   = "**Error** ";
char TasmFatalTxt[]   = "**Fatal** ";

/* Microsoft Assembler and OPTASM text for conversion */
char MasmWarningText[] = "warning";
char MasmErrorText[]   = "error";

char     CurFile[MAXPATH];       /* Current file in message window */
unsigned BufSize,                /* Size of internal working buffer */
         CurBufLen;              /* Buffer space in use */
char     *InBuffer,              /* Input buffer */
         *OutBuffer,             /* Output buffer */
         *CurInPtr,              /* current character in input buffer */
         *CurOutPtr,             /* current character in output */
         *LinePtr;               /* pointer to the current character in
                                    the input buffer */
int      (*processor)(char *);   /* function pointer used to call the
                                    appropriate conversion routine */
char     Line[133];              /* static buffer to store line most recently
                                    input */
long int InOff;                  /* position in actual input stream */
char     EndMark;                /* Used to output end of data to message
                                    window */

/*************************************************************************
Function  : NextChar
Parameters: none
Returns   : next character in input buffer or 0 on end of file

Input from the standard input stream is buffered in a global buffer InBuffer
which is allocated in function main.  The function will return
the next character in the buffer, reading from the input stream when the
buffer becomes empty.
**************************************************************************/
char NextChar(void)
{
  if (CurInPtr < InBuffer+CurBufLen)  /* if buffer is not empty */
  {
    return *(CurInPtr++);             /* return next character */
  }
  else
  {
    CurInPtr = InBuffer;              /* reset pointer to front of buffer */
    lseek(0,InOff,0);                 /* seek to the next section for read */
    InOff += BufSize;                 /* increment pointer to next block */
    if ((CurBufLen = read(0,InBuffer,BufSize)) !=0)
      return NextChar();              /* recursive call merely returns
                                         first character in buffer after read */
    return 0;                         /* return 0 on end of file */
  }
}

/*************************************************************************
Function  : flushOut
Parameter : Size   The number of characters to be written out
Returns   : nothing

Strings to be sent to the message window are buffered in a buffer called
OutBuffer.  A call to this function will write out Size bytes from OutBuffer
to the standard output stream and resets the output buffer pointer to the
beginning of the buffer.  The output buffer is considered empty after a call
to this function.
*************************************************************************/
void flushOut(unsigned Size)
{
   if (Size != 0)                /* don't flush an empty buffer */
   {
      CurOutPtr = OutBuffer;     /* reset pointer to beginning of buffer */
      lseek(1,0,2);              /* seek output stream to end */
      write(1,OutBuffer,Size);   /* write out Size bytes */
   }
}

/************************************************************************
Function  : Put
Parameters: S    pointer to bytes being put into output buffer
            Len  number of bytes to be put in output buffer
Returns   : nothing

Put places bytes into OutBuffer so they may be later flushed out into
the standard output stream.
************************************************************************/
void Put(char *S,int Len)
{
   int i;

   for (i = 0; i < Len; i++)
   {
      *CurOutPtr++ = S[i];                   /* place byte in buffer */
      if (CurOutPtr >= OutBuffer+BufSize)    /* if buffer overflows */
         flushOut(BufSize);                  /* flush the buffer */
   }
}


/************************************************************************
Function  : ProcessNonTasmLine
Parameters: Line  a pointer to the current line of characters to process
Returns   : 1 if line is Microsoft Assembler line
            0 if line is not

Analyze line to determine if it is output from a MASM or OPTASM compatible
assembler. In the case of a recognizable line, output relevant information
to the message window indicating message and line number.
-*----------------------------------------------------------------------*-
Microsoft assembler lines which are in need of conversion are of the form:

   source-file(LINE #): message-kind message-num : message text

where message-kind is one of:  warning, error
-*----------------------------------------------------------------------*-
OPTASM assembler lines which are in need of conversion are of the form:

   source-file(LINE #) : message-kind message-num : message text

where message-kind is one of: Warning, Error
-*----------------------------------------------------------------------*-
Masm and Optasm lines differ from Tasm lines in that half the line must be
scanned in order to determine if the line is valid.  For this reason all
output information is stored and sent at the end when the determination of
a valid line is made.
************************************************************************/
int ProcessNonTasmLine(char *Line)
{
   char     Type;
   unsigned i;
   char     *s;
   char     fn[MAXPATH];
   int      NewFile;

   if (Line[0] == 0)                         /* Empty line, no action */
      return 0;

   s = strchr(Line,'(');                     /* find ( */
   if (s != NULL)                            /* if no (, invalid line */
   {
      memmove(fn,Line,(unsigned)(s-Line));    /* store filename */
      fn[(unsigned)(s-Line)] = 0;             /* null terminate name */
      memmove(Line,++s,strlen(Line));         /* shift line left */
      if (strcmp(fn,CurFile) != 0)            /* if new filename */
      {
         NewFile = TRUE;                      /* indicate by setting flag */
         strcpy(CurFile,fn);                  /* store new name */
      }
      else NewFile = FALSE;
      s = strchr(Line,')');                   /* find the close paren */
      if (s != NULL)                          /* if no ) invalid line */
      {
         *s = 0;                               /* isolate the line number */
         i = atoi(Line);                       /* if number is found convert
                                                  string to integer */
         if (i != 0)
         {
            s++;
            while (*s == ' ')                  /* optasm has space here */
               s++;
            if (*s != ':')                     /* strip : from line */
               return 0;                       /* no :, not MASM line */
            s++;
            memmove(Line,s,strlen(s)+1);        /* shift line */
            while (Line[0] == ' ' && Line[0] != 0)  /* strip spaces from line */
               memmove(Line,&Line[1],strlen(Line));
            Line[0] = tolower(Line[0]);        /* optasm uses upper case */
            /* check for warning or error text from MASM, shift line if
               needed. */
            if ((strncmp(Line, MasmWarningText, strlen(MasmWarningText)) != 0) &&
                (strncmp(Line, MasmErrorText, strlen(MasmErrorText)) != 0))
               return 0; /* not error or warning, not MASM line */

            /* strip spaces from beginning of line */
            while (Line[0] == ' ' && Line[0] != 0)  /* strip spaces from line */
               memmove(Line,&Line[1],strlen(Line));
         }
         else return 0;                   /* no line number, not MASM line */
      }
      else return 0;                      /* no ), not MASM line */
      if (NewFile)
      {
         Type = MsgNewFile;               /* send new file indicated */
         Put(&Type,1);                    /* Put info to output stream */
         Put(CurFile,strlen(CurFile)+1);  /* along with the new name */
      }
      Type = MsgNewLine;                  /* set type to new line */
      Put(&Type,1);                       /* indicate need for new line */
      Put((char *)&i,2);                  /* put the number out */
      i = 1;                              /* set column in message box */
      Put((char *)&i,2);                  /* tab over to put message */
      Put(Line,strlen(Line)+1);           /* output the message */
   }
   else return 0;                         /* no ( on line, not MASM line */

   return 1;                              /* MASM line */
}

/*************************************************************************
Function  : ProcessTasmLine
Parameters: Line  a pointer to the current line of characters to process
Returns   : 1 if line is a Turbo Assembler line
            0 if line is not

Process through a line of input to determine if it is a Turbo Assembler
output line and convert it to information for the Turbo C++ message window.

Turbo Assembler lines which are in need of conversion are of the form:

    message-type source-file(LINE #) message-text

where type is one of: *Warning*, **Error**, **Fatal**

TASM lines are identified by the first portion of text.  If warning,
error or fatal is determined at the outset, text is output from there
as it is scanned.  Any incorrect configuration will simply abort the
scanning of the rest of the line.
*************************************************************************/
int ProcessTasmLine(char *Line)
{
   static int HavePutFile = FALSE;
   char     Type;
   unsigned i;
   char     *s;
   char     fn[MAXPATH];

   /* don't try to process a NULL line */
   if (Line[0] == 0)
      return 0;

   /* check for tasm type tags */
   if ((strncmp(Line,TasmWarningTxt,strlen(TasmWarningTxt)) == 0) ||
      (strncmp(Line,TasmErrorTxt,  strlen(TasmErrorTxt)) == 0) ||
      (strncmp(Line,TasmFatalTxt,  strlen(TasmFatalTxt)) == 0))

   {
      /* skip over type by moving string left */
      memmove(Line,&Line[strlen(TasmFatalTxt)],strlen(Line));

      /* locate the first open paren '(' filename will be characters to
	 to the left, line number will be characters to the right up to the
	 close paren ')' */
      s = strchr(Line,'(');                      /* find ( */
      if (s != NULL)                             /* if no (, invalid line */
      {
	 memmove(fn,Line,(unsigned)(s-Line));    /* save filename */
	 fn[(unsigned)(s-Line)] = 0;             /* null terminate name */
	 memmove(Line,++s,strlen(Line));         /* shift line left */
	 if (strcmp(fn,CurFile) != 0)            /* if new filename */
	 {
            Type = MsgNewFile;                   /* indicate by sending type
						    out to message window */
	    strcpy(CurFile,fn);
	    Put(&Type,1);
            Put(CurFile,strlen(CurFile)+1);      /* along with the new name */
	    HavePutFile = TRUE;
	 }
	 Type = MsgNewLine;                      /* set type to new line */
	 s = strchr(Line,')');                   /* find the close paren */
	 if (s != NULL)
	 {
            *s = 0;                              /* isolate number in string */
            i = atoi(Line);                      /* if number is found convert
						    string to integer */
	    if (i != 0)
	    {
	       Put(&Type,1);                       /* indicate need for new line */
	       Put((char *)&i,2);                  /* put the number out */
	       i = 1;                              /* set column in message box */
	       Put((char *)&i,2);                  /* tab over to put message */
	       s++;
	       memmove(Line,s,strlen(s)+1);        /* shift line */
	       while (Line[0] == ' ' && Line[0] != 0)  /* strip spaces from line */
		  memmove(Line,&Line[1],strlen(Line));
	       Put(Line,strlen(Line)+1);           /* output the message */
               return 1;              /* TASM line */
	    }
            return 0;                 /* invalid line number, not TASM line */
	 }
         return 0;                    /* no ) in line, not TASM line */
      }
      else                            /* Fatal error, no line # or filename */
      {
        if( !HavePutFile )
        {
	   /* IDE expects the first message to
	      be preceded by a filename.  Since
	      we don't have one, fake it by
	      sending a NULL file before the
	      message.
	   */
	   Type = MsgNewFile;                  /* indicate by sending type
					          out to message window */
	   *CurFile = '\0';
	   Put(&Type,1);
	   Put(CurFile,1);                     /* along with null filename */
           HavePutFile = TRUE;
        }
                       
	Type = MsgNewLine;            /* Fake line # etc.                   */
	i    = 1;
	Put(&Type,1);
	Put((char *)&i,2);
	Put((char *)&i,2);
	while (Line[0] == ' ' && Line[0] != 0)
	  memmove(Line,&Line[1],strlen(Line));
	Put(Line,strlen(Line)+1);
	return 1;
      }
   }
   else return 0;                     /* no line start message, not TASM line */
}

/**************************************************************************
Function  : ProcessLine
Parameters: Line    character pointer to line of input data
Returns   : nothing

If line type has been determined, call correct line processor through
a function pointer.  Else try testing for both Tasm style line and Masm
style line to determine if either one is the input to the filter.
**************************************************************************/
void ProcessLine(char *Line)
{
    if (processor == NULL)
    {
       if (ProcessTasmLine(Line))            /* check for TASM line */
          processor = ProcessTasmLine;
       else
          if (ProcessNonTasmLine(Line))      /* check MASM or OPTASM style */
             processor = ProcessNonTasmLine;
    }
    else
       processor(Line);                      /* type already determined */
}


/***********************************************************************
Function  : main

Returns   : zero for successful execution
            3    if an error is encountered

The main routine allocates buffers for the input and output buffer.
Characters are then read from the input buffer building the line buffer
that will be sent to the filter processor.  Lines are read and filtered
until the end of input is reached.
***********************************************************************/
int main( void )
{
   char c;
   unsigned long core;

   setmode(1,O_BINARY);               /* set output stream to binary mode */
   core = farcoreleft();
   if (core > 64000U)
      BufSize = 64000U;
   else BufSize = (unsigned)core;     /* get available memory */
                                      /* stay under 64K */
   if ((CurInPtr = malloc(BufSize)) == NULL) /* allocate buffer space */
      exit(3);
   processor = NULL;                  /* set current processor to none */
   InBuffer = CurInPtr;               /* input buffer is first half of space */
   BufSize = BufSize/2;               /* output buffer is 2nd half */
   OutBuffer = InBuffer + BufSize;
   CurOutPtr = OutBuffer;             /* set buffer pointers */
   LinePtr = Line;
   CurBufLen = 0;
   Put(PipeId,PipeIdLen);             /* send ID string to message window */
   while ((c = NextChar()) != 0)      /* read characters */
   {
      if ((c == 13) || (c == 10))     /* build until line end */
      {
         *LinePtr = 0;
         ProcessLine(Line);           /* filter the line */
         LinePtr = Line;
      }
      /* characters are added to buffer up to 132 characters max */
      else if ((FP_OFF(LinePtr) - FP_OFF(&Line)) < 132)
      {
         *LinePtr = c;                /* add to line buffer */
         LinePtr++;
      }
   }
   *LinePtr = 0;
   ProcessLine(Line);                 /* filter last line */
   EndMark = MsgEoFile;
   Put(&EndMark,1);                   /* indicate end of input to
                                         the message window */
   flushOut((unsigned)(CurOutPtr-OutBuffer));     /* flush the buffer */
   return 0;                          /* return OK */
}

