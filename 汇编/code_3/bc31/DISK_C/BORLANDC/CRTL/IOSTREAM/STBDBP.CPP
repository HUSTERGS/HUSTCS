/*-----------------------------------------------------------------------*
 * filename - dbp.cpp
 * Debugging output for streambuf
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include "filesys.h"
#include <iostream.h>
#include <stdio.h>      /* for sprintf */
#include <string.h>

// debugging output for streambuf
void streambuf::dbp()
{
    char s[80];
    sprintf(s, "alloc_ = %d, unbuf_ = %d\n", alloc_, unbuf_);
    write(F_stdout, s, strlen(s));
    sprintf(s, "base_ = %p, ebuf_ = %p\n", base_, ebuf_);
    write(F_stdout, s, strlen(s));
    sprintf(s, "pbase_ = %p, pptr_ = %p, epptr_ = %p\n", pbase_, pptr_, epptr_);
    write(F_stdout, s, strlen(s));
    sprintf(s, "gptr_ = %p, egptr_ = %p, eback_ = %p\n", gptr_, egptr_, eback_);
    write(F_stdout, s, strlen(s));
}
