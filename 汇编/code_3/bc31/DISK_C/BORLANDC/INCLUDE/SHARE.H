/*  share.h

    File sharing mode for use with sopen.
    See DOS function 3Dh for definition.

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#if !defined(__SHARE_H)
#define __SHARE_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#define SH_COMPAT   0x0000
#define SH_DENYRW   0x0010
#define SH_DENYWR   0x0020
#define SH_DENYRD   0x0030
#define SH_DENYNONE 0x0040

#define SH_DENYNO   SH_DENYNONE /* MS documentation uses both */

#endif  /* __SHARE_H */

