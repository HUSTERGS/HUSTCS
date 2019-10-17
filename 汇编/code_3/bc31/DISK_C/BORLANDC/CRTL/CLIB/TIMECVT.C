/*-----------------------------------------------------------------------*
 * filename - timecvt.c
 *
 * function(s)
 *        dostounix - converts date and time to UNIX time format
 *    unixtodos - converts from UNIX-format time
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
#include <time.h>

static char Days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/*---------------------------------------------------------------------*

Name            dostounix - converts date and time to UNIX time format

Usage           long dostounix(struct date *d, struct time *t);

Prototype in    time.h

Description     Converts a date and time (as returned from getdate and
                gettime) into UNIX-format time.

Return value    UNIX version of the given date and time.

*---------------------------------------------------------------------*/
long _FARFUNC dostounix(struct date *d, struct time *t)
{
        long            x;
        register int    i;
        register int    days;
        int             hours;

        tzset();                                /* get timezone info */

        x = 24L * 60L * 60L * 3652L + timezone; /* Convert from 1980 to
                                                   1970 base date GMT */
        i = d->da_year - 1980;
        x += (i >> 2) * (1461L * 24L * 60L * 60L);
        x += (i & 3) * (24L * 60L * 60L * 365L);
        if (i & 3)
                x += 24L * 3600L;
        days = 0;
        i = d->da_mon - 1;                      /* Add in months */
        while (i > 0)
        {
                i--;
                days += Days[i];
        }
        days += d->da_day - 1;
        if (d->da_mon > 2 && (d->da_year & 3) == 0)
                days++;                         /* Currently in leap year */
        hours = days * 24 + t->ti_hour;         /* Find hours */
        if (daylight && __isDST( t->ti_hour, days, 0, d->da_year-1970))
                hours--;
        x += hours * 3600L;
        x += 60L * t->ti_min + t->ti_sec;
        return (x);
}


/*---------------------------------------------------------------------*

Name            unixtodos - converts from UNIX-format time

Usage           void unixtodos(long time, struct date *d, struct time *t);

Prototype in    time.h

Description     Converts a UNIX-format time into date and time.

Return value    There is no return value.

*---------------------------------------------------------------------*/
void _FARFUNC unixtodos(long time, struct date *d, struct time *t)
{
        tzset();                                /* get timezone info */

        time -= 24L * 60L * 60L * 3652L + timezone;
        t->ti_hund = 0;
        t->ti_sec = time % 60;
        time /= 60;                             /* Time in minutes */
        t->ti_min = time % 60;
        time /= 60;                             /* Time in hours */
        d->da_year = 1980 + (int)((time / (1461L * 24L)) << 2);
        time %= 1461L * 24L;
        if (time >= 366 * 24)
        {
                time -= 366 * 24;
                d->da_year++;
                d->da_year += (int)(time / (365 * 24));
                time %= 365 * 24;
        }
        if (daylight && __isDST( (int)(time % 24), (int)(time / 24), 0, d->da_year-1970 ))
                time++;
        t->ti_hour = time % 24;
        time /= 24;                             /* Time in days */
        time++;
        if ((d->da_year & 3) == 0)
        {
                if (time > 60)
                        time--;
                else
                if (time == 60)
                {
                        d->da_mon = 2;
                        d->da_day = 29;
                        return;
                }
        }
        for (d->da_mon = 0; Days[d->da_mon] < time; d->da_mon++)
                time -= Days[d->da_mon];
        d->da_mon++;
        d->da_day = time;
}
