/*------------------------------------------------------------------------
 * filename - _win.h
 *
 *      prototypes for Windows error message functions
 *-----------------------------------------------------------------------*/

/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     C/C++ Run Time Library - Version 4.0                     |*/
/*|                                                              |*/
/*|                                                              |*/
/*|     Copyright (c) 1991 by Borland International              |*/
/*|     All Rights Reserved.                                     |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

#if !defined( ___WIN_H )
#define ___WIN_H

#ifdef __cplusplus
extern "C" {
#endif

void _errorBox( char * );
void _errorExitBox( char *, int );

#ifdef  __cplusplus
}
#endif

#endif  // ___WIN_H

