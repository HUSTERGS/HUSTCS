/*------------------------------------------------------------------------
 * filename - _farfunc.h
 *
 *      macros for far memory and string functions
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

#define memccpy  _fmemccpy
#define memchr   _fmemchr 
#define memcmp   _fmemcmp 
#define memcpy   _fmemcpy 
#define memicmp  _fmemicmp
#define memset   _fmemset 
#define setmem   _fsetmem
#define strcat   _fstrcat 
#define strchr   _fstrchr 
#define strcmp   _fstrcmp 
#define strcpy   _fstrcpy 
#define strcspn  _fstrcspn
#define strdup   _fstrdup 
#define stricmp  _fstricmp
#define strlen   _fstrlen 
#define strlwr   _fstrlwr 
#define strncat  _fstrncat
#define strncmp  _fstrncmp
#define strncpy  _fstrncpy
#define strnicmp _fstrnicmp
#define strnset  _fstrnset
#define strpbrk  _fstrpbrk
#define strrchr  _fstrrchr
#define strrev   _fstrrev 
#define strset   _fstrset 
#define strspn   _fstrspn 
#define strstr   _fstrstr 
#define strtok   _fstrtok 
#define strupr   _fstrupr 

#define movmem   _fmovmem
#define memmove  _fmemmove
#define qsort    _hqsort

#if !defined(_RTLDLL)
void far * far _ffarmalloc(unsigned long __nbytes);
#define malloc   _ffarmalloc
#else
#define malloc farmalloc
#endif

#define toupper  _ftoupper
#define tolower  _ftolower
