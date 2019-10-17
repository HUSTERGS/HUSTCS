/*  dirent.h

    Definitions for POSIX directory operations.

    Copyright (c) 1991, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __DIRENT_H
#define __DIRENT_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#ifndef NULL
#include <_null.h>
#endif

/* dirent structure returned by readdir().
 */
struct dirent
{
    char        d_name[13];
};

/* DIR type returned by opendir().  The first two members cannot
 * be separated, because they make up the DOS DTA structure used
 * by findfirst() and findnext().
 */
typedef struct
{
    char          _d_reserved[30];      /* reserved part of DTA */
    struct dirent _d_dirent;            /* filename part of DTA */
    char    _FAR *_d_dirname;           /* directory name */
    char          _d_first;             /* first file flag */
    unsigned char _d_magic;             /* magic cookie for verifying handle */
} DIR;

/* Prototypes.
 */
#ifdef __cplusplus
extern "C" {
#endif

DIR             _FAR * _Cdecl _FARFUNC opendir (char _FAR *__dirname);
struct dirent   _FAR * _Cdecl _FARFUNC readdir (DIR _FAR *__dir);
int             _Cdecl _FARFUNC closedir (DIR _FAR *__dir);
void            _Cdecl _FARFUNC rewinddir(DIR _FAR *__dir);

#ifdef __cplusplus
}
#endif

#endif /* __DIRENT_H */
