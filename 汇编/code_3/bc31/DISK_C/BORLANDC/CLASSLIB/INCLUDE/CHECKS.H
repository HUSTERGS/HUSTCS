/*------------------------------------------------------------------------*/
/*                                                                        */
/*  CHECKS.H                                                              */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __CHECKS_H )
#define __CHECKS_H

#if !defined( __DEFS_H )
#include <_defs.h>
#endif  // __DEFS_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

extern "C" void _Cdecl __assertfail( char _FAR *__msg,
                                     char _FAR *__cond,
                                     char _FAR *__file,
                                     int __line);

#if !defined( __DEBUG )
#define __DEBUG 2
#endif

#undef PRECONDITION

#if __DEBUG < 1
#define PRECONDITION(p)   ((void)0)
#else
#define PRECONDITION(p)   ((p) ? (void)0 : (void) __assertfail(      \
                    "Precondition violated: %s, file %s, line %d\n", \
                    #p, __FILE__, __LINE__ ) )
#endif

#undef CHECK

#if __DEBUG < 2
#define CHECK(p)    ((void)0)
#else
#define CHECK(p)    ((p) ? (void)0 : (void) __assertfail(   \
                    "Check failed: %s, file %s, line %d\n", \
                    #p, __FILE__, __LINE__ ) )
#endif

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __CHECKS_H
