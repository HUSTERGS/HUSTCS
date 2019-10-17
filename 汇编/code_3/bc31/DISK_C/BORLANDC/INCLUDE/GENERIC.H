/*  generic.h -- for faking generic class declarations

    Copyright (c) 1990, 1992 by Borland International
    All rights reserved

    When type templates are implemented in C++, this will probably go away.
*/

#ifndef __cplusplus
#error Must use C++ for the generic types.
#endif

#ifndef __GENERIC_H
#define __GENERIC_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

// token-pasting macros; ANSI requires an extra level of indirection
#define _Paste2(z, y)       _Paste2_x(z, y)
#define _Paste2_x(z, y)     z##y
#define _Paste3(z, y, x)    _Paste3_x(z, y, x)
#define _Paste3_x(z, y, x)  z##y##x
#define _Paste4(z, y, x, w) _Paste4_x(z, y, x, w)
#define _Paste4_x(z, y, x, w)   z##y##x##w

// macros for declaring and implementing classes
#define name2 _Paste2
#define declare(z, y) _Paste2(z, declare)(y)
#define implement(z, y) _Paste2(z, implement)(y)
#define declare2(z, y, x) _Paste2(z, declare2)(y, x)
#define implement2(z, y, x) _Paste2(z, implement2)(y, x)

// macros for declaring error-handling functions
extern _Cdecl genericerror(int, char _FAR *);    // not implemented ***
typedef int _Cdecl (_FAR *GPT)(int, char _FAR *);
#define set_handler(gen, tp, z) _Paste4(set_, tp, gen, _handler)(z)
#define errorhandler(gen, tp) _Paste3(tp, gen, handler)
#define callerror(gen, tp, z, y) (*errorhandler(gen, tp))(z, y)

/*
 * function genericerror is not documented in the AT&T release, and
 * is not supplied.  If you can document any expected behavior, we
 * will try to adjust our implementation accordingly.
 */

#endif
