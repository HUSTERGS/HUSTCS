/*-----------------------------------------------------------------------*
 * filename - locking.c
 *
 * function(s)
 *        wait1    - wait 1 second
 *        locking  - sets or resets file sharing locks (MSC compatible)
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <io.h>
#include <_io.h>
#include <dos.h>
#include <errno.h>
#include <sys\locking.h>


/*-----------------------------------------------------------------------*

Name            wait1 - wait 1 second

Usage           void wait1(void);

Prototype in    local

Description     wait1() uses _dos_gettime() in a spin loop to wait 1 second.

Return value    No value is returned.

Portability     Unique to MS-DOS. On multi-tasking operating systems
                this should be rewritten to do a wait.

*------------------------------------------------------------------------*/

static void pascal near wait1(void)
{
    struct dostime_t start, end;
    unsigned char endsec;

    /* Get current time.
     */
    _dos_gettime(&start);
    if (start.second == 59)
        endsec = 0;
    else
        endsec = start.second + 1;

    /* Wait for second to change.
     */
    do {
        _dos_gettime(&end);
    } while (end.second == start.second);

    /* Wait for hundredths of seconds to catch up.
     */
    while (end.second == endsec && end.hsecond < start.hsecond) {
        _dos_gettime(&end);
    }
}

/*-----------------------------------------------------------------------*

Name            locking - sets file sharing locks

Usage           int locking(int handle, int mode, long length);

Prototype in    io.h

Description     locking provides an interface to the MS-DOS
                3.x file-sharing mechanism.  The region to be locked
                or unlocked starts at the current file position;
                the size of the region is given by length.

                The mode parameter specifies the action (values
                for mode are given in <sys\locking.h>):

                LK_LOCK         lock the region; if unsuccessful, try
                                once a second for 10 seconds before
                                giving up.
                LK_NBLCK        lock the region, if unsuccessful, give
                                up immediately.
                LK_NBRLCK       Same as LK_NBLCK.
                LK_RCLK         Same as LK_LOCK.
                LK_UNLCK        Unlock the region, which must have
                                been previously locked.

                Locks can be placed on arbitrary, non-overlapping regions of
                any file. A program attempting to read or write into a
                locked region will retry the operation three times. If all
                three retries fail, the call fails with an error.

                unlock removes lock; to avoid error, lock must be removed
                before a file is closed. A program must release all lock(s)
                before completing.

Return value    Locking return 0 on success.  On failure, -1 is returned,
                and errno is set to one of the following:

                EACCESS         File already locked or unlocked
                EBADF           Bad file number
                EDEADLOCK       File cannot be locked after 10 retries
                                (mode is LK_LOCK or LK_RLCK)
                EINVAL          Invalid mode


Portability     Unique to MS-DOS 3.x. Older versions of MS-DOS do
                not support these calls.

Note            Compatible with Microsoft C.  Not the same as lock().


*------------------------------------------------------------------------*/

int _FARFUNC locking(int handle, int mode, long length)
{
    int tries;
    long offset;

    /* Get current file offset, which gives the start of
     * the region to be locked or unlocked.  This also
     * verifies the file handle.
     */
    if (_dos_seek(handle,0L,SEEK_CUR,&offset) != 0)
            return (-1);

    switch (mode)
    {
    case LK_LOCK:
    case LK_RLCK:

        /* Try 10 times, once every second, to lock the file.
         */
        for (tries = 1; tries <= 10; tries++)
            {
            if (_dos_lock(handle,offset,length) == 0)
                    return (0);             /* success */
            if (errno != EACCES)        /* not a locking violation? */
                    return (-1);                /* return right away */
            wait1();                        /* failed - try again 1 sec later */
            }
        errno = EDEADLOCK;                  /* give up */
        return (-1);

    case LK_NBLCK:
    case LK_NBRLCK:

        /* Lock the region, give up immediately if not sucessful.
         */
        return (_dos_lock(handle,offset,length) == 0 ? 0 : -1);

    case LK_UNLCK:

        /* Unlock the region.
         */
        return (_dos_unlock(handle,offset,length) == 0 ? 0 : -1);

    default:
        errno = EINVAL;
        return (-1);
    }
}
