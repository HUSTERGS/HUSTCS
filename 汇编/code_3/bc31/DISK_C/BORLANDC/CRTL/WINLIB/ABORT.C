/*------------------------------------------------------------------------
 * filename - abort.c
 *
 * function(s)
 *        abort - raise the SIGABRT signal
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#if !defined( __STDLIB_H )
#include <stdlib.h>
#endif  // __STDLIB_H

#if !defined( __SIGNAL_H )
#include <signal.h>
#endif  // __SIGNAL_H

#if !defined( ___WIN_H )
#include <_win.h>
#endif  // ___WIN_H

void abort( void )
{
    raise( SIGABRT );
}

