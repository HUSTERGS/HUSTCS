/*  io.h

    Definitions for low level I/O functions.

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __IO_H
#define __IO_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#if !defined(___NFILE_H)
#include <_nfile.h>
#endif

#define HANDLE_MAX  (_NFILE_)

extern  unsigned int    _Cdecl _nfile;

struct  ftime   {
    unsigned    ft_tsec  : 5;   /* Two second interval */
    unsigned    ft_min   : 6;   /* Minutes */
    unsigned    ft_hour  : 5;   /* Hours */
    unsigned    ft_day   : 5;   /* Days */
    unsigned    ft_month : 4;   /* Months */
    unsigned    ft_year  : 7;   /* Year */
};

#define SEEK_CUR    1
#define SEEK_END    2
#define SEEK_SET    0

#ifdef __cplusplus
extern "C" {
#endif
int  _Cdecl _FARFUNC access   (const char _FAR *path, int amode);
#ifdef __IN_CHMOD
int  _Cdecl _FARFUNC _chmod   ();
#else
int  _Cdecl _FARFUNC _chmod   (const char _FAR *__pathname, int __func, ... );
#endif
int  _Cdecl _FARFUNC chmod    (const char _FAR *__path, int __amode);
int  _Cdecl _FARFUNC chsize   (int __handle, long __size);
int  _CType _FARFUNC _close   (int __handle);
int  _CType _FARFUNC close    (int __handle);
int  _CType _FARFUNC _creat   (const char _FAR *__path, int __attribute);
int  _CType _FARFUNC creat    (const char _FAR *__path, int __amode);
int  _Cdecl _FARFUNC creatnew (const char _FAR *__path, int __mode); /* DOS 3.0 or later */
int  _Cdecl _FARFUNC creattemp(char _FAR *__path, int __amode); /* DOS 3.0 or later */
int  _Cdecl dup      (int __handle);
int  _Cdecl dup2     (int __oldhandle, int __newhandle);
int  _Cdecl _FARFUNC eof      (int __handle);
long _Cdecl _FARFUNC filelength   (int __handle);
int  _Cdecl getftime     (int __handle, struct ftime _FAR *__ftimep);
#ifdef __IN_IOCTL
int  _Cdecl ioctl    ();
#else
int  _Cdecl _FARFUNC ioctl    (int __handle, int __func, ...);
        /* optional 3rd and 4th args are: void _FAR * __argdx, int argcx */
#endif

int  _Cdecl isatty   (int __handle);
int  _Cdecl _FARFUNC lock     (int __handle, long __offset, long __length);
int  _Cdecl _FARFUNC locking  (int __handle, int __mode, long __length);
long _CType lseek    (int __handle, long __offset, int __fromwhere);
char _FAR * _FARFUNC _Cdecl mktemp( char _FAR *__template );
#ifdef __IN_OPEN
int  _Cdecl _FARFUNC open();
#else
int _Cdecl _FARFUNC open(const char _FAR *__path, int __access,... /*unsigned mode*/);
#endif
int  _CType _FARFUNC _open    (const char _FAR *__path, int __oflags);
int  _CType _FARFUNC read     (int __handle, void _FAR *__buf, unsigned __len);
int  _CType _read    (int __handle, void _FAR *__buf, unsigned __len);
int  _CType remove   (const char _FAR *__path);
int  _CType _FARFUNC rename   (const char _FAR *__oldname,const char _FAR *__newname);
int  _Cdecl setftime (int __handle, struct ftime _FAR *__ftimep);
int  _Cdecl _FARFUNC setmode  (int __handle, int __amode);

#ifdef __IN_SOPEN
int  _Cdecl sopen();
#else
int  _Cdecl sopen    (const char _FAR *__path, int __access, int __shflag,
                      ... /* unsigned mode */);
#endif
long _Cdecl tell     (int __handle);
unsigned _Cdecl umask    (unsigned __cmask);
int  _CType unlink   (const char _FAR *__path);
int  _Cdecl _FARFUNC unlock   (int __handle, long __offset, long __length);
int  _CType _FARFUNC _write   (int __handle, const void _FAR *__buf, unsigned __len);
int  _CType _FARFUNC write    (int __handle, const void _FAR *__buf, unsigned __len);
void _Cdecl _InitEasyWin(void);  /* Initialization call for Easy Windows */

#ifdef __MSC
#define _dup(h) dup(h)
#endif

#ifdef __cplusplus
}
#endif

#endif  /* __IO_H */
