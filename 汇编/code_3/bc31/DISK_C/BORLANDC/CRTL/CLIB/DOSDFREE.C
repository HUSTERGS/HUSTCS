/*---------------------------------------------------------------------------
 * filename - dosdfree.cas
 *
 * function(s)
 *        _dos_getdiskfree - gets disk free space (MSC compatible)
 *--------------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>
#include <errno.h>

/*--------------------------------------------------------------------------*

Name            _dos_getdiskfree - gets disk free space

Usage           #include <dos.h>
                unsigned _dos_getdiskfree(unsigned drive,
                                        struct diskfree_t *dfreep);

Prototype in    dos.h

Description     accepts a drive specifier in drive (0 = default, 1 = A, etc.)
                and fills in the diskfree_t structure pointed to by dfreep with
                disk characteristics.

                The diskfree_t structure is defined as follows:

                struct diskfree_t {
                        unsigned total_clusters;
                        unsigned avail_clusters;
                        unsigned sectors_per_cluster;
                        unsigned bytes_per_sector;
                };

Return value    Returns 0 on success.  Otherwise, returns non-zero
                and sets errno to:

                        EINVAL  Invalid drive specified

*---------------------------------------------------------------------------*/

unsigned _dos_getdiskfree(unsigned drive, struct diskfree_t *dtable)
{
    unsigned bx;

    _DL = drive;
    _AH = 0x36;
    geninterrupt(0x21);

    if (_AX == -1U)     /* error */
        return (errno = EINVAL);
    else                        /* success */
    {
        bx = _BX;
        dtable->total_clusters = _DX;
        dtable->sectors_per_cluster = _AX;
        dtable->bytes_per_sector = _CX;
        dtable->avail_clusters = bx;
        return (0);
    }
}
