/*------------------------------------------------------------------------
 * filename - rules.h
 *
 *      Standard rules for C
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


#ifdef __STDC__
#define _Cdecl
#else
#define _Cdecl  cdecl
#endif

#ifndef __PAS__
#define _CType _Cdecl
#else
#define _CType pascal
#endif

/*      Precise types for portability and clarity of intent.

- chars are for strings or text (16 bits for Oriental or video buffers)
- ordinals are for indexes and offsets
- cardinals count how many of something
- integers can be negative
- bitsets are for bits, unknown patterns, and binary trickery
*/

typedef enum { false, true }   booleanT;
typedef unsigned char   boolean;

typedef signed   char   int8;
typedef char            char8;
typedef unsigned char   card8;
typedef unsigned char   ord8;
typedef unsigned char   bits8;

typedef short           int16;
typedef unsigned short  char16;
typedef unsigned short  card16;
typedef unsigned short  ord16;
typedef unsigned short  bits16;

typedef long            int32;
typedef unsigned long   card32;
typedef unsigned long   ord32;
typedef unsigned long   bits32;

typedef short   status;                 /* >0 = OK, minus is error/failure  */
typedef short   handle;                 /* 0..19 are files, -1 = failure    */
typedef unsigned short  keyval;         /* key code, including special keys */


#ifndef MIN
#   define MIN(a,b)  ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#   define MAX(a,b)  ((a) > (b) ? (a) : (b))
#endif
#ifndef NULL
#   define NULL ((void *)0)
#endif

#define O_WP    "w+"
#define O_WPB   "w+b"
#define O_RPB   "r+b"
