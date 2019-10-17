/*-----------------------------------------------------------------------*
 * filename - dosgdate.c
 *
 * function(s)
 *        _dos_getdate - gets MS-DOS date (MSC compatible)
 *        _dos_gettime - gets MS-DOS time (MSC compatible)
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1991, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#define _MSC
#include <dos.h>

/*---------------------------------------------------------------------*

Name            _dos_getdate - gets MS-DOS date

Usage           #include <dos.h>
                void _dos_getdate(struct dosdate_t *dateblk);

Prototype in    dos.h

Description     _dos_getdate fills in the dosdate_t structure (pointed to by
                dateblk) with the system's current date.

                The dosdate_t structure is defined as follows:

                struct dosdate_t {
                        unsigned char day;      (* 1-31 *)
                        unsigned char month;    (* 1-12 *)
                        unsigned int  year;     (* 1980 - 2099 *)
                        unsigned char dayofweek;(* 0 - 6 (0=Sunday) *)
                };

Return value    nothing

Note            Compatible with Microsoft C.  Not the same as getdate().

*---------------------------------------------------------------------*/
void _dos_getdate(struct dosdate_t *datep)
{
        _AH = 0x2a;
        geninterrupt(0x21);
        datep->dayofweek = _AL;
        datep->day = _DL;
        datep->month = _DH;
        datep->year = _CX;
}


/*---------------------------------------------------------------------*

Name            _dos_gettime - gets MS-DOS time

Usage           #include <dos.h>
                void _dos_gettime(struct dostime_t *timep);

Prototype in    dos.h

Description     _dos_gettime fills in the dostime_t structure pointed to
                by timep with the system's current time.

                The dostime_t structure is defined as follows:

                struct dostime_t {
                        unsigned char hour;     (* Hours *)
                        unsigned char minute;   (* Minutes *)
                        unsigned char second;   (* Seconds *)
                        unsigned char hsecond;  (* Hundredths of seconds *)
                };

Return value    nothing

Note            Compatible with Microsoft C.  Not the same as gettime().

*---------------------------------------------------------------------*/
void _dos_gettime(struct dostime_t *timep)
{
        _AH = 0x2c;
        geninterrupt(0x21);
        timep->hour = _CH;
        timep->minute = _CL;
        timep->second = _DH;
        timep->hsecond = _DL;
}
