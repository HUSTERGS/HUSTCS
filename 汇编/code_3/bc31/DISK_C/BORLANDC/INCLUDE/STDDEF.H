/*  stddef.h

    Definitions for common types, and NULL

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __STDDEF_H
#define __STDDEF_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#ifndef NULL
#include <_null.h>
#endif

#ifndef _PTRDIFF_T
#define _PTRDIFF_T
#if     defined(__LARGE__) || defined(__HUGE__) || defined(__COMPACT__)
typedef long    ptrdiff_t;
#else
typedef int     ptrdiff_t;
#endif
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#define offsetof( s_name, m_name )  (size_t)&(((s_name _FAR *)0)->m_name)

#ifndef _WCHAR_T
#define _WCHAR_T
typedef char wchar_t;
#endif

#endif  /* __STDDEF_H */
