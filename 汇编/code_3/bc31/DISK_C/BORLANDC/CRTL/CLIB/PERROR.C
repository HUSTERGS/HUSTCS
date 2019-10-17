/*-------------------------------------------------------------------------*
 * filename - perror.c
 *
 * function(s)
 *        perror - system error messages
 *--------------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#undef sys_errlist
#undef sys_nerr

char    *sys_errlist[] = {
/*  0 */    "Error 0",
/*  1 */    "Invalid function number",
/*  2 */    "No such file or directory",
/*  3 */    "Path not found",
/*  4 */    "Too many open files",
/*  5 */    "Permission denied",
/*  6 */    "Bad file number",
/*  7 */    "Memory arena trashed",
/*  8 */    "Not enough memory",
/*  9 */    "Invalid memory block address",
/* 10 */    "Invalid environment",
/* 11 */    "Invalid format",
/* 12 */    "Invalid access code",
/* 13 */    "Invalid data",
/* 14 */    "", // "Bad address",
/* 15 */    "No such device",
/* 16 */    "Attempted to remove current directory",
/* 17 */    "Not same device",
/* 18 */    "No more files",
/* 19 */    "Invalid argument",
/* 20 */    "Arg list too big",
/* 21 */    "Exec format error",
/* 22 */    "Cross-device link",
/* 23 */    "", // "Too many open files",
/* 24 */    "", // "No child processes",
/* 25 */    "", // "Inappropriate I/O control operation",
/* 26 */    "", // "Executable file in use",
/* 27 */    "", // "File too large",
/* 28 */    "", // "No space left on device",
/* 29 */    "", // "Illegal seek",
/* 30 */    "", // "Read-only file system",
/* 31 */    "", // "Too many links",
/* 32 */    "", // "Broken pipe",
/* 33 */    "Math argument",
/* 34 */    "Result too large",
/* 35 */    "File already exists",
/* 36 */    "Possible deadlock",
/* 37 */    "", // "Operation not permitted",
/* 38 */    "", // "No such process",
/* 39 */    "", // "Interrupted function call",
/* 40 */    "", // "Input/output error",
/* 41 */    "", // "No such device or address",
/* 42 */    "", // "Resource temporarily unavailable",
/* 43 */    "", // "Block device required",
/* 44 */    "", // "Resource busy",
/* 45 */    "", // "Not a directory",
/* 46 */    "", // "Is a directory",
/* 47 */    ""
};

int     sys_nerr = sizeof(sys_errlist) / sizeof(sys_errlist[0]);

/*---------------------------------------------------------------------*

Name            perror - system error messages

Usage           void perror(const char *string);

Prototype in    stdio.h

Description     perror prints an error message to stderr, describing
                the most recent error encountered in a system call from the
                current program.

                First the argument string is printed, then a colon, then the
                message corresponding to the current value of errno, and finally
                a newline. The convention is to pass the name of the program as
                the argument string.

                To provide more control over message formatting, the array of
                message strings is provided in sys_errlist. errno can be used as
                an index into the array to find the string corresponding to the
                error number. The string does not include any newline character.

                sys_nerr contains the number of entries in the array.

                Refer to errno, sys_errlist, and sys_nerr in the "Variables"
                section of this chapter for more information.

Return value    None

*---------------------------------------------------------------------*/
void _FARFUNC perror(const char _FAR *s)
{
    char    *cp;

    if (errno < sys_nerr && errno >= 0)
        cp = sys_errlist[errno];
    else
        cp = "Unknown error";

    fprintf(stderr, "%s: %s\n", s, cp);
}
