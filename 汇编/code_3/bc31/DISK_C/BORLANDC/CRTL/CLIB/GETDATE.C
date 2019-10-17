/*-----------------------------------------------------------------------*
 * filename - getdate.c
 *
 * function(s)
 *        getdate - gets MS-DOS date
 *        gettime - gets MS-DOS time
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

Name            getdate - gets MS-DOS date

Usage           #include <dos.h>
                void getdate(struct date *dateblk);

Prototype in    dos.h

Description     getdate fills in the date structure (pointed to by
                dateblk) with the system's current date.

                The date structure is defined as follows:

                struct date {
                        int da_year;    (* Current year *)
                        char da_day;    (* Day of the month *)
                        char da_mon;    (* Month (1 = Jan) *)
                };

Return value    nothing

*---------------------------------------------------------------------*/
void _CType getdate(struct date *datep)
{
        _AH = 0x2a;
        geninterrupt(0x21);
        ((int *)datep)[0] = _CX;
        ((int *)datep)[1] = _DX;
}

/*---------------------------------------------------------------------*

Name            gettime - gets MS-DOS time

Usage           #include <dos.h>
                void gettime(struct time *timep);

Prototype in    dos.h

Description     gettime fills in the time structure pointed to by timep
                with the system's current time.

                The time structure is defined as follows:

                struct time {
                        unsigned char ti_min;   (* Minutes *)
                        unsigned char ti_hour;  (* Hours *)
                        unsigned char ti_hund;  (* Hundredths of seconds *)
                        unsigned char ti_sec;   (* Seconds *)
                };

Return value    nothing

*---------------------------------------------------------------------*/
void _CType gettime(struct time *timep)
{
        _AH = 0x2c;
        geninterrupt(0x21);
        ((int *)timep)[0] = _CX;
        ((int *)timep)[1] = _DX;
}
