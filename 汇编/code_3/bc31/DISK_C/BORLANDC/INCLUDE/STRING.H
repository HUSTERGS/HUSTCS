/*  string.h

    Definitions for memory and string functions.

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __STRING_H
#define __STRING_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#ifndef NULL
#include <_null.h>
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif
void _FAR * _Cdecl _FARFUNC memchr  (const void _FAR *__s, int __c, size_t __n);
int         _Cdecl _FARFUNC memcmp(const void _FAR *__s1,
                          const void _FAR *__s2, size_t __n);
void _FAR * _Cdecl _FARFUNC memcpy(void _FAR *__dest, const void _FAR *__src,
                          size_t __n);
void _FAR * _CType _FARFUNC memmove(void _FAR *__dest, const void _FAR *__src,
                           size_t __n);
void _FAR * _CType _FARFUNC memset(void _FAR *__s, int __c, size_t __n);
char _FAR * _CType _FARFUNC strcat(char _FAR *__dest, const char _FAR *__src);
char _FAR * _CType _FARFUNC strchr(const char _FAR *__s, int __c);
int         _CType _FARFUNC strcmp(const char _FAR *__s1, const char _FAR *__s2);
int         _Cdecl strcoll(const char _FAR *__s1, const char _FAR *__s2);
char _FAR * _CType _FARFUNC strcpy(char _FAR *__dest, const char _FAR *__src);
size_t      _Cdecl _FARFUNC strcspn(const char _FAR *__s1, const char _FAR *__s2);
char _FAR * _Cdecl _FARFUNC strerror(int __errnum);
size_t      _CType _FARFUNC strlen(const char _FAR *__s);
char _FAR * _CType _FARFUNC strncat(char _FAR *__dest, const char _FAR *__src,
               size_t __maxlen);
int         _CType _FARFUNC strncmp(const char _FAR *__s1, const char _FAR *__s2,
               size_t __maxlen);
char _FAR * _CType _FARFUNC strncpy(char _FAR *__dest, const char _FAR *__src,
                           size_t __maxlen);
char _FAR * _CType _FARFUNC strpbrk(const char _FAR *__s1, const char _FAR *__s2);
char _FAR * _CType _FARFUNC strrchr(const char _FAR *__s, int __c);
size_t      _Cdecl _FARFUNC strspn(const char _FAR *__s1, const char _FAR *__s2);
char _FAR * _Cdecl _FARFUNC strstr(const char _FAR *__s1, const char _FAR *__s2);
char _FAR * _CType _FARFUNC strtok(char _FAR *__s1, const char _FAR *__s2);
size_t      _Cdecl strxfrm(char _FAR *__s1, const char _FAR *__s2,
               size_t __n );
char _FAR * _Cdecl _FARFUNC _strerror(const char _FAR *__s);


#if !__STDC__
/* compatibility with other compilers */
#define strcmpi(s1,s2)      stricmp(s1,s2)
#define strncmpi(s1,s2,n)   strnicmp(s1,s2,n)

void _FAR * _Cdecl _FARFUNC memccpy(void _FAR *__dest, const void _FAR *__src,
               int __c, size_t __n);
int         _Cdecl _FARFUNC memicmp(const void _FAR *__s1, const void _FAR *__s2,
                           size_t __n);
void        _Cdecl _FARFUNC movedata(unsigned __srcseg,unsigned __srcoff,
                            unsigned __dstseg,unsigned __dstoff, size_t __n);
char _FAR * _CType stpcpy(char _FAR *__dest, const char _FAR *__src);
char _FAR * _Cdecl _stpcpy(char _FAR *__dest, const char _FAR *__src);
char _FAR * _Cdecl _FARFUNC strdup(const char _FAR *__s);
int         _CType _FARFUNC stricmp(const char _FAR *__s1, const char _FAR *__s2);
char _FAR * _CType _FARFUNC strlwr(char _FAR *__s);
int         _CType _FARFUNC strnicmp(const char _FAR *__s1, const char _FAR *__s2,
                size_t __maxlen);
char _FAR * _Cdecl _FARFUNC strnset(char _FAR *__s, int __ch, size_t __n);
char _FAR * _Cdecl _FARFUNC strrev(char _FAR *__s);
char _FAR * _Cdecl _FARFUNC strset(char _FAR *__s, int __ch);
char _FAR * _CType _FARFUNC strupr(char _FAR *__s);

void    far * _FARCALL cdecl _fmemccpy(void far *__dest, const void far *__src,
                int c, size_t __n);
void    far * _FARCALL cdecl _fmemchr(const void far *__s, int c, size_t __n);
int           _FARCALL cdecl _fmemcmp(const void far *__s1, const void far *__s2,
                size_t __n);
void    far * _FARCALL cdecl _fmemcpy(void far *__dest, const void far *__src,
                size_t __n);
int           _FARCALL cdecl _fmemicmp(const void far *__s1, const void far *__s2,
                size_t __n);
void    far * _FARCALL cdecl _fmemmove(void far *__dest, const void far *__src,
                size_t __n);
void    far * _FARCALL cdecl _fmemset(void far *__s, int c, size_t __n);
void          _FARCALL cdecl _fmovmem(const void far *__src, void far *__dest,
                unsigned __length);
void          _FARCALL cdecl _fsetmem(void far *__dest,unsigned __length,
                char __value);

char    far * _FARCALL cdecl _fstrcat(char far *__dest, const char far *__src);
char    far * _FARCALL cdecl _fstrchr(const char far *__s, int c);
int           _FARCALL cdecl _fstrcmp(const char far *__s1, const char far *__s2);
char    far * _FARCALL cdecl _fstrcpy(char far *__dest, const char far *__src);
size_t        _FARCALL cdecl _fstrcspn(const char far *__s1, const char far *__s2);
char    far * _FARCALL cdecl _fstrdup(const char far *__s);
int           _FARCALL cdecl _fstricmp(const char far *__s1, const char far *__s2);
size_t        _FARCALL cdecl _fstrlen(const char far *__s);
char    far * _FARCALL cdecl _fstrlwr(char far *__s);
char    far * _FARCALL cdecl _fstrncat(char far *__dest, const char far *__src,
             size_t maxlen);
int           _FARCALL cdecl _fstrncmp(const char far *__s1, const char far *__s2,
             size_t maxlen);
char    far * _FARCALL cdecl _fstrncpy(char far *__dest, const char far *__src,
             size_t maxlen);
int           _FARCALL cdecl _fstrnicmp(const char far *__s1, const char far *__s2,
              size_t maxlen);
char    far * _FARCALL cdecl _fstrnset(char far *__s, int ch, size_t __n);
char    far * _FARCALL cdecl _fstrpbrk(const char far *__s1, const char far *__s2);
char    far * _FARCALL cdecl _fstrrchr(const char far *__s, int c);
char    far * _FARCALL cdecl _fstrrev(char far *__s);
char    far * _FARCALL cdecl _fstrset(char far *__s, int ch);
size_t        _FARCALL cdecl _fstrspn(const char far *__s1, const char far *__s2);
char    far * _FARCALL cdecl _fstrstr(const char far *__s1, const char far *__s2);
char    far * _FARCALL cdecl _fstrtok(char far *__s1, const char far *__s2);
char    far * _FARCALL cdecl _fstrupr(char far *__s);

#ifdef __MSC
#define _stricmp(s1,s2) stricmp(s1,s2)
#define _strdup(s1)     strdup(s1)
#define _strupr(s1)     strupr(s1)
#define _strlwr(s1)     strlwr(s1)
#define _strrev(s1)     strrev(s1)
#endif

#endif  /* ! __STDC__ */

/* Intrinsic functions */

#if !defined(__MEM_H)
void _FAR * _Cdecl _FARFUNC __memchr__  (const void _FAR *__s, int __c, size_t __n);
int         _Cdecl _FARFUNC __memcmp__(const void _FAR *__s1,
                          const void _FAR *__s2, size_t __n);
void _FAR * _Cdecl _FARFUNC __memcpy__(void _FAR *__dest, const void _FAR *__src,
                          size_t __n);
void _FAR * _CType _FARFUNC __memset__(void _FAR *__s, int __c, size_t __n);
#endif
char _FAR * _Cdecl __stpcpy__(char _FAR *__dest, const char _FAR *__src);
char _FAR * _CType _FARFUNC __strcat__(char _FAR *__dest, const char _FAR *__src);
char _FAR * _Cdecl _FARFUNC __strchr__(const char _FAR *__s, int __c);
int         _CType _FARFUNC __strcmp__(const char _FAR *__s1, const char _FAR *__s2);
char _FAR * _CType _FARFUNC __strcpy__(char _FAR *__dest, const char _FAR *__src);
size_t      _CType _FARFUNC __strlen__(const char _FAR *__s);
char _FAR * _Cdecl _FARFUNC __strncat__(char _FAR *__dest, const char _FAR *__src,
               size_t __maxlen);
int         _Cdecl _FARFUNC __strncmp__(const char _FAR *__s1, const char _FAR *__s2,
               size_t __maxlen);
char _FAR * _CType _FARFUNC __strncpy__(char _FAR *__dest, const char _FAR *__src,
                           size_t __maxlen);
char _FAR * _Cdecl _FARFUNC __strnset__(char _FAR *__s, int __ch, size_t __n);
char _FAR * _CType _FARFUNC __strrchr__(const char _FAR *__s, int __c);
char _FAR * _Cdecl _FARFUNC __strset__(char _FAR *__s, int __ch);

#ifdef __cplusplus
}
#endif

#endif
