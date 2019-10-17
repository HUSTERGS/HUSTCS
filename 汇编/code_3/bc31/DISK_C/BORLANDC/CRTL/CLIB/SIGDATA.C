/*----------------------------------------------------------------------*
 * filename - sigdata.c                                                 *
 *                                                                      *
 * external function pointers to signal()                               *
 * These are filled in with the actual address of signal()              *
 * at runtime.  This is needed to keep the signal functions from being  *
 * dragged in by the fperr() routine.                                   *
 *----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


typedef void (*CatcherPTR)(); /* Cleaner catcher declaration */

CatcherPTR (*__SignalPtr)();

