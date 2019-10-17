/*-----------------------------------------------------------------------*
 * filename - sleep.c
 *
 * function(s)
 *        sleep - suspends execution for interval
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>

/*---------------------------------------------------------------------*

Name            sleep - suspends execution for interval

Usage           unsigned sleep(unsigned seconds);

Prototype in    dos.h

Description     With a call to sleep, the current program is
                suspended from execution for the number of seconds specified
                by the argument seconds. The interval is only accurate to
                the nearest hundredth of a second, or the accuracy of the
                MS-DOS clock, whichever is less accurate.

Return value    None

*---------------------------------------------------------------------*/
void sleep(unsigned seconds)
{
        struct   time   t;
        register int    secs;
        register int    hunds;

        gettime(&t);
        hunds = (t.ti_hund > 90) ? 90 : t.ti_hund;
        while (seconds--)
        {
                secs = t.ti_sec;
                do
                        gettime(&t);
                while (secs == t.ti_sec);
        }
        do
                gettime(&t);
        while (hunds > t.ti_hund);
}

