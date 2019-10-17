/*  stat.h

    Definitions used for file status functions

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __STAT_H
#define __STAT_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#define S_IFMT  0xF000  /* file type mask */
#define S_IFDIR 0x4000  /* directory */
#define S_IFIFO 0x1000  /* FIFO special */
#define S_IFCHR 0x2000  /* character special */
#define S_IFBLK 0x3000  /* block special */
#define S_IFREG 0x8000  /* or just 0x0000, regular */
#define S_IREAD 0x0100  /* owner may read */
#define S_IWRITE 0x0080 /* owner may write */
#define S_IEXEC 0x0040  /* owner may execute <directory search> */

struct  stat
{
    short st_dev;
    short st_ino;
    short st_mode;
    short st_nlink;
    int   st_uid;
    int   st_gid;
    short st_rdev;
    long  st_size;
    long  st_atime;
    long  st_mtime;
    long  st_ctime;
};

#ifdef __cplusplus
extern "C" {
#endif
int  _Cdecl _FARFUNC fstat(int __handle, struct stat _FAR *__statbuf);
int  _Cdecl _FARFUNC stat(const char _FAR *__path, struct stat _FAR *__statbuf);

#ifdef __MSC
#define _fstat(h,b) fstat(h,b)
#define _stat(p,b)  stat(p,b)
struct  _stat
{
    short st_dev;
    short st_ino;
    short st_mode;
    short st_nlink;
    int   st_uid;
    int   st_gid;
    short st_rdev;
    long  st_size;
    long  st_atime;
    long  st_mtime;
    long  st_ctime;
};
#endif

#ifdef __cplusplus
}
#endif

#endif  /* __STAT_H */
