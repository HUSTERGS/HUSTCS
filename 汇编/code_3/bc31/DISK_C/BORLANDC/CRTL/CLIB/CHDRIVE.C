/*---------------------------------------------------------------------------
 * filename - _chdrive.cas
 *
 * function(s)
 *        _chdrive   - change the current working drive
 *        _getrive   - get the current working drive
 *--------------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>

/*--------------------------------------------------------------------------*

Name            _chdrive - sets current drive

Usage           int _chdrive(int drive);

Prototype in    dir.h

Description     sets the current drive.
                1 = A:, 2 = B:, 3 = C:; etc.

Return value    0 if drive changed successfully, -1 if error.

Note            Compatible with MSC. Not the same as setdisk().
*---------------------------------------------------------------------------*/

int _chdrive(int drive)
{
    int newdrive;

    _dos_setdrive((unsigned)drive,(unsigned *)&newdrive); /* set the drive */
    _dos_getdrive((unsigned *)&newdrive);       /* get current drive */
    if (newdrive == drive)                      /* success? */
        return 0;
    else
        return -1;              /* error, disk didn't change for some reason */
}

/*--------------------------------------------------------------------------*

Name            _getdrive - sets current drive

Usage           int _getdrive(int drive);

Prototype in    dir.h

Description     sets the current drive.
                1 = A:, 2 = B:, 3 = C:; etc.

Return value    0 if drive changed successfully, -1 if error.

Note            Compatible with MSC. Not the same as setdisk().
*---------------------------------------------------------------------------*/

int _getdrive()
{
    int newdrive;

    _dos_getdrive((unsigned *)&newdrive);       /* get current drive */
    return (newdrive);
}
