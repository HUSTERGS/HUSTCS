/*------------------------------------------------------------------------*/
/*                                                                        */
/*  CLSDEFS.H                                                             */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __CLSDEFS_H )
#define __CLSDEFS_H

#if !defined( __CLSTYPES_H )
#include <ClsTypes.h>
#endif  // __CLSTYPES_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

const hashValueType ERROR_CLASS_HASH_VALUE = 0;

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif
