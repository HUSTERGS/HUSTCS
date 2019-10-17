/*  assert.h

    assert macro

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

void _Cdecl _FARFUNC __assertfail( char _FAR *__msg,
                                   char _FAR *__cond,
                                   char _FAR *__file,
                                   int __line);

#ifdef  __cplusplus
}
#endif

#undef assert

#ifdef NDEBUG
#  define assert(p)   ((void)0)
#else
#  ifdef _Windows
#    define _ENDL
#  else
#    define _ENDL "\n"
#  endif
#  define assert(p) ((p) ? (void)0 : (void) __assertfail( \
                    "Assertion failed: %s, file %s, line %d" _ENDL, \
                    #p, __FILE__, __LINE__ ) )
#endif
