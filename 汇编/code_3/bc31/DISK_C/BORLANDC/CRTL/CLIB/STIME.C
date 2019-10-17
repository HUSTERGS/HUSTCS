/*-----------------------------------------------------------------------*
 * filename - stime.c
 *
 * function(s)
 *        stime - sets time of day
 *        time  - gets time of day
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <time.h>
#include <dos.h>

/*---------------------------------------------------------------------*

Name            stime - sets time

Usage           int stime(long *tp);

Related
functions usage long time(long *tloc);

Prototype in    time.h

Description     see time

*---------------------------------------------------------------------*/
int stime(time_t *tp)
{
        struct  date    d;
        struct  time    t;

        unixtodos(*tp, &d, &t);
        setdate(&d);
        settime(&t);
        return (0);
}


/*---------------------------------------------------------------------*

Name            time - gets time of day

Usage           long time(long *tloc);

Related
functions usage int stime(long *tp);

Prototype in    time.h

Description     time retrieves the current time (in seconds, elapsed
                since 00:00:00 GMT, January 1, 1970) and stores that
                value in the location pointed to by tloc.

                stime sets the system time and date.

Return value    time returns the elapsed time, stime returns 0.

*---------------------------------------------------------------------*/
time_t time(time_t *tloc)
{
        struct  date    d;
        struct  time    t;
        time_t          x;

        getdate(&d);
        gettime(&t);
        x = dostounix(&d, &t);
        if (tloc)
                *tloc = x;
        return (x);
}
