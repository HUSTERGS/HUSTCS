/*-----------------------------------------------------------------------*
 * filename - umask.c
 *
 * function(s)
 *    umask - set file read/write permission mask
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <io.h>
#include <RtlData.h>

#if !defined( _RTLDLL )
extern  unsigned _notUmask;
#endif

/*---------------------------------------------------------------------*

Name            umask - set file read/write permission mask

Usage           #include <io.h>
                unsigned  umask(unsigned modeMask)

Prototype in    io.h

Description     Changes the read/write permission mask used for "open"
                and "creat" calls.

Return value    The replaced value of the umask.  There is no error return.

Note            "umask" is stored internally in inverted form, for convenience.

*---------------------------------------------------------------------*/
unsigned  umask(unsigned modeMask)
{
    register    oldMask;
    _QRTLDataBlock;

    oldMask = ~_QRTLInstanceData(_notUmask);
    _QRTLInstanceData(_notUmask) = ~modeMask;
    return (oldMask);
}
