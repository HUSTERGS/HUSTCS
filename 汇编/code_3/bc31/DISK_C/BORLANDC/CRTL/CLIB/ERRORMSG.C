/*-----------------------------------------------------------------------*
 * filename - errormsg.c
 *
 * function(s)
 *        __ErrorMessage - display an error message
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#ifdef _Windows
#include <_win.h>
#else
#include <io.h>
#include <string.h>
#endif

void __ErrorMessage(const char *msg)
{
#ifdef _Windows
    _errorBox((char *) msg);
#else
    _write(2, msg, strlen(msg));
#endif
}
