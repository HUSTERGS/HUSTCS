/*------------------------------------------------------------------------
 * filename - rtldata.h
 *
 *      definitions for DLL instance data
 *-----------------------------------------------------------------------*/

/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     C/C++ Run Time Library - Version 4.0                     |*/
/*|                                                              |*/
/*|                                                              |*/
/*|     Copyright (c) 1991 by Borland International              |*/
/*|     All Rights Reserved.                                     |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

#if !defined( __RTLDATA_H )
#define __RTLDATA_H

#include <_defs.h>
#include <time.h>
#include <_printf.h>
#include <suballoc.h>
#include <stdio.h>
#include <_nfile.h>

#define _F_STDIN    (_F_READ | _F_TERM | _F_LBUF)
#define _F_STDOUT   (_F_WRIT | _F_TERM | _F_LBUF)
#define _F_STDERR   (_F_WRIT | _F_TERM)
#define _F_STDAUX   (_F_RDWR | _F_TERM | _F_BIN)
#define _F_STDPRN   (_F_WRIT | _F_TERM | _F_BIN)

typedef void (_FAR * _FARFUNC pvf)();

#define TZstrlen        3        /* Len of tz string(- null terminator) */
#define DefaultTimeZone 5L
#define YES 1
#define DefaultDaylight YES

struct _RTLData
{
    FILE _streams[_NFILE_];
    unsigned int _openfd[_NFILE_];
    unsigned int _nfile;
    int _fmode;
    int _notUmask;
    int _doserrno_;
    pvf _new_handler;
    char strbuf[94 + 2 + 64 + 1];
    char *Ss;
    char _template[L_tmpnam];
    unsigned int _tmpnum;
    char a[26];
    char _DfltZone[ TZstrlen+1 ], _DfltLight[ TZstrlen+1 ];
    long  timezone_;
    int   daylight_;
    char  *tzname_[2];
    struct tm tmX;
    int errno_;
    unsigned long _StartTime;
    char _cvtBuf[__XCVTDIG__ + 2];
    struct TSubAllocClientData subAllocData;
};

#if !defined( _RTLDLL )
#   define _QRTLDataBlock
#   define _RTLInstanceData(x) (x)
#   define _QRTLInstanceData(x) (x)
#else
#   if defined( __cplusplus )
        extern "C" struct _RTLData far * _export pascal __getRTLInstanceData();
        extern "C" struct TSubAllocClientData far * __GetSubAllocClientData();
#   else
        struct _RTLData far * _export pascal __getRTLInstanceData(void);
        struct TSubAllocClientData far * __GetSubAllocClientData(void);
#   endif
#   define _QRTLDataBlock struct _RTLData far *__rtlInstanceData = __getRTLInstanceData()
#   define _RTLInstanceData(x) (__getRTLInstanceData()->x)
#   define _QRTLInstanceData(x) (__rtlInstanceData->x)
#endif

#endif  // __RTLDATA_H
