/*  new.h

    Access to operator new() and newhandler()

    Copyright (c) 1990, 1992 by Borland International
    All Rights Reserved.
*/

#if !defined(__NEW_H)
#define __NEW_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#ifndef __cplusplus
#error Must use C++ with new.h
#endif

typedef void (_FAR * _FARFUNC pvf)();

extern void (_FAR * _Cdecl _FARFUNC _new_handler)();

void (_FAR * _FARFUNC set_new_handler( void (_FAR * _FARFUNC )() ))();

#ifdef __MSC
#define _set_new_handler(f) set_new_handler(f)
#endif

void _FAR * _FARFUNC operator new( unsigned );

#endif  /* __NEW_H */

