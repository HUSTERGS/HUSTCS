/*  stdlib.h

    Definitions for common types, variables, and functions.

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __STDLIB_H
#define __STDLIB_H

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

#ifndef _DIV_T
#define _DIV_T
typedef struct {
        int     quot;
        int     rem;
} div_t;
#endif

#ifndef _LDIV_T
#define _LDIV_T
typedef struct {
        long    quot;
        long    rem;
} ldiv_t;
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
typedef char wchar_t;
#endif

/* Old typedef
*/
typedef void _Cdecl (* atexit_t)(void);

/* Maximum value returned by "rand" function
*/
#define RAND_MAX 0x7FFFU

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define MB_CUR_MAX 1

#ifdef __cplusplus
extern "C" {
#endif

void        _Cdecl abort(void);
int         _Cdecl __abs__(int);
#ifdef __cplusplus
inline int _Cdecl  abs(int __x) { return __abs__(__x); }
#else
int         _CType abs(int __x);
#  define abs(x)   __abs__(x)
#endif
int         _Cdecl atexit(void (_Cdecl *__func)(void));
double      _Cdecl atof(const char _FAR *__s);
int         _CType atoi(const char _FAR *__s);
long        _CType atol(const char _FAR *__s);
void _FAR * _CType bsearch(const void _FAR *__key, const void _FAR *__base,
               size_t __nelem, size_t __width,
               int (_CType *fcmp)(const void _FAR *,
               const void _FAR *));
void _FAR * _Cdecl calloc(size_t __nitems, size_t __size);
div_t       _Cdecl div(int __numer, int __denom);
void        _Cdecl exit(int __status);
void        _Cdecl free(void _FAR *__block);
char _FAR * _CType getenv(const char _FAR *__name);
long        _Cdecl labs(long __x);
ldiv_t      _Cdecl ldiv(long __numer, long __denom);
void _FAR * _Cdecl malloc(size_t __size);
int         _Cdecl mblen(const char _FAR *__s, size_t __n);
size_t      _Cdecl mbstowcs(wchar_t _FAR *__pwcs, const char _FAR *__s,
            size_t __n);
int     _Cdecl _FARFUNC mbtowc(wchar_t _FAR *__pwc, const char _FAR *__s, size_t __n);
void    _CType _FARFUNC qsort(void _FAR *__base, size_t __nelem, size_t __width,
        int _CType (*_FARFUNC __fcmp)(const void _FAR *, const void _FAR *));
int     _Cdecl rand(void);
void _FAR *_Cdecl realloc(void _FAR *__block, size_t __size);
void    _Cdecl srand(unsigned __seed);
double  _Cdecl strtod(const char _FAR *__s, char _FAR *_FAR *__endptr);
long    _Cdecl _FARFUNC strtol(const char _FAR *__s, char _FAR *_FAR *__endptr,
              int __radix);
long double _Cdecl _strtold(const char _FAR *__s, char _FAR *_FAR *__endptr);
unsigned long _Cdecl _FARFUNC strtoul(const char _FAR *__s, char _FAR *_FAR *__endptr,
                 int __radix);
int     _Cdecl _FARFUNC system(const char _FAR *__command);
size_t  _Cdecl _FARFUNC wcstombs(char _FAR *__s, const wchar_t _FAR *__pwcs,
            size_t __n);
int     _Cdecl _FARFUNC wctomb(char _FAR *__s, wchar_t __wc);

#ifdef __cplusplus
}
#endif

#if !__STDC__

/* Variables */

#if defined( _RTLDLL )

#ifdef __cplusplus
extern "C" {
#endif

int far * far _Cdecl __getErrno(void);
int far * far _Cdecl __getDOSErrno(void);

#ifdef __cplusplus
}
#endif

#define errno (*__getErrno())
#define _doserrno (*__getDOSErrno())

#else

extern  int   _Cdecl _doserrno;
extern  int   _Cdecl errno;

#endif

/*
  These 2 constants are defined in MS's stdlib.h.  Rather than defining them
  all the time and invading the ANSI programmers name space we'll only make
  them visible when __STDC__ is *off*.  Anybody using these constants ain't
  writing standard C anyway!
*/
#define DOS_MODE  0
#define OS2_MODE  1

extern  unsigned        _Cdecl _psp;

extern  char          **_Cdecl environ;
extern  int             _Cdecl _fmode;
extern  unsigned char   _Cdecl _osmajor;
extern  unsigned char   _Cdecl _osminor;
extern  unsigned int    _Cdecl _version;

#if defined( _RTLDLL )

#ifdef __cplusplus
extern "C" {
#endif
extern  char far * far * far _Cdecl __get_sys_errlist(void);
extern  int  far _Cdecl __get_sys_nerr(void);
#ifdef __cplusplus
}
#endif

#define sys_errlist __get_sys_errlist()
#define sys_nerr __get_sys_nerr()

#else

extern  char           _FAR *_Cdecl sys_errlist[];
extern  int             _Cdecl sys_nerr;

#endif

/* Constants for MSC pathname functions */

#define _MAX_PATH       80
#define _MAX_DRIVE      3
#define _MAX_DIR        66
#define _MAX_FNAME      9
#define _MAX_EXT        5

#ifdef __cplusplus
inline int _Cdecl random(int __num)
                 { return(int)(((long)rand()*__num)/(RAND_MAX+1)); }
/* need prototype of time() for C++ randomize() */
extern "C" long _Cdecl _FARFUNC time(long _FAR *);
inline void _Cdecl randomize(void) { srand((unsigned) time(NULL)); }
inline int  _Cdecl atoi(const char _FAR *__s) { return (int) atol(__s); }
#else
#define random(num)(int)(((long)rand()*(num))/(RAND_MAX+1))
#define randomize()     srand((unsigned)time(NULL))
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#define atoi(s)     ((int) atol(s))
#endif

#ifdef __cplusplus
extern "C" {
#endif

long double _Cdecl _atold(const char _FAR *__s);
char   _FAR *_Cdecl ecvt(double __value, int __ndig, int _FAR *__dec,
             int _FAR *__sign);
void    _Cdecl _exit(int __status);
char   _FAR *_Cdecl fcvt(double __value, int __ndig, int _FAR *__dec,
            int _FAR *__sign);
char _FAR * _CType _FARFUNC _fullpath( char _FAR *__buf,
                  const char _FAR *__path,
                  size_t __maxlen );
char   _FAR *_Cdecl gcvt(double __value, int __ndec, char _FAR *__buf);
char   _FAR *_CType _FARFUNC itoa(int __value, char _FAR *__string, int __radix);
void   _FAR *_Cdecl _FARFUNC lfind(const void _FAR *__key, const void _FAR *__base,
         size_t _FAR *__num, size_t __width,
         int _Cdecl(*_FARFUNC __fcmp)(const void _FAR *, const void _FAR *));

unsigned long _Cdecl _lrotl(unsigned long __val, int __count);
unsigned long _Cdecl _lrotr(unsigned long __val, int __count);

void   _FAR *_Cdecl _FARFUNC lsearch(const void _FAR *__key, void _FAR *__base,
         size_t _FAR *__num, size_t __width,
         int _Cdecl(*_FARFUNC __fcmp)(const void _FAR *, const void _FAR *));
char _FAR * _CType _FARFUNC ltoa(long __value, char _FAR *__string, int __radix);
void _Cdecl _FARFUNC _makepath( char _FAR *__path,
                  const char _FAR *__drive,
                  const char _FAR *__dir,
                  const char _FAR *__name,
                  const char _FAR *__ext );
int     _Cdecl _FARFUNC putenv(const char _FAR *__name);

unsigned    _Cdecl _rotl(unsigned __value, int __count);
unsigned    _Cdecl _rotr(unsigned __value, int __count);

unsigned    _Cdecl __rotl__(unsigned __value, int __count);     /* intrinsic */
unsigned    _Cdecl __rotr__(unsigned __value, int __count);     /* intrinsic */

void        _Cdecl _searchenv(const char _FAR *__file,
                  const char _FAR *__varname,
                  char _FAR *__pathname);
void        _Cdecl _searchstr(const char _FAR *__file,
                  const char _FAR *__ipath,
                  char _FAR *__pathname);
void _Cdecl _FARFUNC _splitpath( const char _FAR *__path,
                   char _FAR *__drive,
                   char _FAR *__dir,
                   char _FAR *__name,
                   char _FAR *__ext );
void    _Cdecl _FARFUNC swab(char _FAR *__from, char _FAR *__to, int __nbytes);
char _FAR *_CType _FARFUNC ultoa(unsigned long __value, char _FAR *__string,
              int __radix);


#ifdef __cplusplus
}
#endif

#ifdef __BCOPT__
#define _rotl(__value, __count)  __rotl__(__value, __count)
#define _rotr(__value, __count)  __rotr__(__value, __count)
#endif

#endif  /* !__STDC__ */

#endif  /* __STDLIB_H */
