/*------------------------------------------------------------------------
 * filename - _dir.h
 *
 *      Defines structures, macros, and functions for dealing with
 *      directories and pathnames.
 *-----------------------------------------------------------------------*/

/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     C/C++ Run Time Library - Version 4.0                     |*/
/*|                                                              |*/
/*|                                                              |*/
/*|     Copyright (c) 1987, 1991 by Borland International        |*/
/*|     All Rights Reserved.                                     |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

#ifdef __cplusplus
extern "C" {
#endif
char    *pascal near __searchpath(const char *__pathP, int __mode);
#ifdef __cplusplus
}
#endif

#define _USEPATH        1
#define _PROGRAM        2
#define _STRING         4
