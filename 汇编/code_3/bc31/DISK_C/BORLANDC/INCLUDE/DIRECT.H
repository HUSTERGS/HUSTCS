/*  direct.h


    Defines structures, macros, and functions for dealing with
    directories and pathnames.

    Copyright (c) 1991, 1992 by Borland International
    All Rights Reserved.
*/

#include <dir.h>

/* Prototypes for MSC functions */

#ifdef __cplusplus
extern "C" {
#endif

int    _Cdecl _chdrive(int __drive);
char _FAR * _Cdecl _FARFUNC _getdcwd(int __drive, char _FAR *__buf, int __len);
int    _Cdecl _getdrive(void);

#ifdef __cplusplus
}
#endif
