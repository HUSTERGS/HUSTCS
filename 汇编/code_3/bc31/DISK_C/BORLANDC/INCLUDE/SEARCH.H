/*  search.h

    Definitions for search functions.

    Copyright (c) 1991, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __SEARCH_H
#define __SEARCH_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif
void   _FAR *_CType _FARFUNC bsearch(const void _FAR *__key, const void _FAR *__base,
                size_t __nelem, size_t __width,
                int _Cdecl(* _FARFUNC __fcmp)(const void _FAR *, const void _FAR *));
void   _FAR *_Cdecl _FARFUNC lfind(const void _FAR *__key, const void _FAR *__base,
                 size_t _FAR *__num, size_t __width,
                 int _Cdecl(* _FARFUNC __fcmp)(const void _FAR *, const void _FAR *));
void   _FAR *_Cdecl _FARFUNC lsearch(const void _FAR *__key, void _FAR *__base,
                 size_t _FAR *__num, size_t __width,
                 int _Cdecl(* _FARFUNC __fcmp)(const void _FAR *, const void _FAR *));
void    _CType _FARFUNC qsort(void _FAR *__base, size_t __nelem, size_t __width,
                int _CType (* _FARFUNC __fcmp)(const void _FAR *, const void _FAR *));
#ifdef __cplusplus
}
#endif

#endif  /* __SEARCH_H */
