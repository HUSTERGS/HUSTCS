/*------------------------------------------------------------------------
 * filename - ftime.c
 *
 * function(s)
 *        ftime - Get current time and store it in 'timeb' structure
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <sys\timeb.h>
#include <time.h>
#include <dos.h>
#include <mem.h>
#include <_io.h>

/*---------------------------------------------------------------------*

Name            ftime - Get current time and store it in 'timeb' structure

Usage           void ftime(struct timeb *TimeStructPtr);

Prototype in    sys\timeb.h

Description     ftime determines the current time and fills in the fields
                in the timeb structure pointed to by TimeStructPtr.

*---------------------------------------------------------------------*/

void _FARFUNC ftime(struct timeb _FAR *TimeStructPtr)
{
    struct date DosDate, Vdate;
    struct time DosTime;

    tzset(); /* Get timezone info. */

    /*
       Because there is a window of vulnerability at exactly midnight when
       calling getdate(INT 21 fn 2A) and gettime(INT 21 fn 2C) in succession,
       we do 2 calls to getdate() to ensure we aren't in this window.
    */
    do
    {
        getdate(&DosDate);
        gettime(&DosTime);
        getdate(&Vdate);
    }
    while ( (DosDate.da_year != Vdate.da_year) ||
                (DosDate.da_day  != Vdate.da_day)  ||
                (DosDate.da_mon  != Vdate.da_mon) );

    /*
       Convert extern 'timezone's seconds to structure 'timezone's minutes.
       Set daylight savings indicator.
       Convert DOS date and time to UNIX style time and store in structure.
       Set milliseconds structure field. DOS is only accurate to 100ths of a
          second so (100ths * 10) makes 1000ths.
    */
#if defined(_RTLDLL)
        TimeStructPtr->_timezone = (short)(timezone / 60L);
#else
        TimeStructPtr->timezone = (short)(timezone / 60L);
#endif
    if (daylight && __isDST( DosTime.ti_hour, DosDate.da_day,
                                 DosDate.da_mon,  DosDate.da_year-1970) )
        TimeStructPtr->dstflag  = 1;
    else
        TimeStructPtr->dstflag  = 0;
    TimeStructPtr->time     = dostounix(&DosDate, &DosTime);
    TimeStructPtr->millitm  = DosTime.ti_hund * 10;
}
