/*------------------------------------------------------------------------
 * filename - chmod.c
 *
 * function(s)
 *        chmod - changes access mode of file
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <io.h>
#include <dos.h>
#include <sys\stat.h>


/*-------------------------------------------------------------------------*

Name            chmod - changes access mode of file

Usage           #include <sys\stat.h>
                int chmod(const char *filename, int permiss);

Prototype in    io.h

Description     chmod  sets   the  file access  permissions  of   the  file
                according to the mask given by permiss.

                filename points to a string naming the file

                permiss can contain  one or both of the  symbolic constants
                S_IWRITE and S_IREAD:

                Value of permiss        Access Permission
                S_IWRITE                Permission to write
                S_IREAD                 Permission to read
                S_IREAD | S_IWRITE      Permission to read and write

Return value    Upon  successfully  changing  the  file access  mode, chmod
                returns 0 otherwise, it returns a  value of -1 and errno is
                set to one of the following:

                ENOENT  Path or file name not found
                EACCES  Permission denied

*---------------------------------------------------------------------------*/
int _FARFUNC chmod(const char *filename, int permiss)
{
  register int  attrib;

  attrib = _chmod(filename, 0);
  if (attrib == -1)
    return(attrib);
  attrib &= ~FA_RDONLY;
  if ((permiss & S_IWRITE) == 0)
    attrib |= FA_RDONLY;
  attrib = _chmod(filename, 1, attrib);
  if (attrib == -1)
    return(attrib);
  return(0);
}
