/*  limits.h

    Defines implementation specific limits on type values.

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __LIMITS_H
#define __LIMITS_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

#define CHAR_BIT            8

#if ('\x80' < 0)
#define CHAR_MAX            127
#define CHAR_MIN            (-128)
#else
#define CHAR_MAX            255
#define CHAR_MIN            0
#endif

#define SCHAR_MAX           127
#define SCHAR_MIN           (-128)
#define UCHAR_MAX           255

#define SHRT_MAX            0x7FFF
#define SHRT_MIN            ((int)0x8000)
#define USHRT_MAX           0xFFFFU

#define INT_MAX             0x7FFF
#define INT_MIN             ((int)0x8000)
#define UINT_MAX            0xFFFFU

#define LONG_MAX            0x7FFFFFFFL
#define LONG_MIN            ((long)0x80000000L)
#define ULONG_MAX           0xFFFFFFFFUL

#define MB_LEN_MAX          1

#endif
