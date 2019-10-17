/*------------------------------------------------------------------------
 * filename - assert.c
 *
 * function(s)
 *        __assertfail - prints error message and aborts
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void _FARFUNC __assertfail(char *msg, char *cond, char *file, int line)
{
    fprintf(stderr, msg, cond, file, line);
    abort();
}

