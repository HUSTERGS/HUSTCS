/*-----------------------------------------------------------------------*
 * filename - utime.c
 *
 * function(s)
 *        utime - set file access and modification times
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <_io.h>
#include <dos.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <utime.h>

static char Days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/*---------------------------------------------------------------------*

Name            utime - set file modification time

Usage           int utime(char *path, struct utimbuf *times);

Prototype in    utime.h

Description     Sets the modification time for the file 'path'
                to the UNIX-format time in times->modtime.  The
                access time times->actime is ignored on DOS.
                If times is NULL, the current time is used.

Return value    If successful, 0 is returned.  Otherwise -1 is returned
                and errno is set as follows:

                ENOENT          File not found
                EMFILE          Too many open files
                EACCESS         Permission denied

*---------------------------------------------------------------------*/

int _FARFUNC utime(char *path, struct utimbuf *times)
{
    time_t tim;
    struct dosdate_t dd;
    struct dostime_t dt;
    unsigned fdate, ftime;
    unsigned err;
    int handle;

    /* We have to open the file for writing before we can modify
     * its time.
     */
    if (_dos_open(path,O_WRONLY,&handle) != 0)
            return (-1);

    /* If times not supplied, use current time.
     */
    if (times == NULL)
        {
            _dos_getdate(&dd);
            _dos_gettime(&dt);
        }
    else
        {
        /* Convert supplied modification time to a DOS date and time.
         * This code was stolen from unixtodos().
         */
        tim = times->modtime;

        tzset();                                /* get timezone info */

        tim -= 24L * 60L * 60L * 3652L + timezone;
        dt.second = tim % 60;
        tim /= 60;                              /* Time in minutes */
        dt.minute = tim % 60;
        tim /= 60;                              /* Time in hours */
        dd.year = 1980 + (int)((tim / (1461L * 24L)) << 2);
        tim %= 1461L * 24L;
        if (tim >= 366 * 24)
        {
                tim -= 366 * 24;
                dd.year++;
                dd.year += (int)(tim / (365 * 24));
                tim %= 365 * 24;
        }
        if (daylight && __isDST( (int)(tim % 24), (int)(tim / 24), 0, dd.year-1970 ))
                tim++;
        dt.hour = tim % 24;
        tim /= 24;                              /* Time in days */
        tim++;
        if ((dd.year & 3) == 0)
        {
                if (tim > 60)
                        tim--;
                else
                if (tim == 60)
                {
                        dd.month = 2;
                        dd.day = 29;
                        goto done;
                }
        }
        for (dd.month = 0; Days[dd.month] < tim; dd.month++)
                tim -= Days[dd.month];
        dd.month++;
        dd.day = tim;
done:   ;
    }

    /* Convert the date and time structures in the bitmapped
     * file date and time.
     */
    ftime = ((unsigned)dt.second >> 1)
          | ((unsigned)dt.minute << 5)
          | ((unsigned)dt.hour   << 11);
    fdate = ((unsigned)dd.day)
          | ((unsigned)dd.month << 5)
          | ((unsigned)(dd.year - 1980) << 9);

    /* Set the file time and date, close the file.
     */
    err = _dos_setftime(handle,fdate,ftime);
    _dos_close(handle);
    return (err == 0 ? 0 : -1);
}
