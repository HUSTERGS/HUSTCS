/*-----------------------------------------------------------------------*
 * filename - dossdate.c
 *
 * function(s)
 *        _dos_setdate - sets MS-DOS date (MSC compatible)
 *        _dos_settime - sets MS-DOS time (MSC compatible)
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
#include <errno.h>

/*---------------------------------------------------------------------*

Name            _dos_setdate - sets MS-DOS date

Usage           #include <dos.h>
                unsigned _dos_setdate(struct dosdate_t *dateblk);

Prototype in    dos.h

Description     _dos_setdate the system's current date using the values
                in the dosdate_t structure (pointed to by dateblk).

                The dosdate_t structure is defined as follows:

                struct dosdate_t {
                        unsigned char day;      (* 1-31 *)
                        unsigned char month;    (* 1-12 *)
                        unsigned int  year;     (* 1980 - 2099 *)
                        unsigned char dayofweek;(* 0 - 6 (0=Sunday) *)
                };

Return value    If sucess, returns 0.  Otherwise, returns non-zero
                and sets errrno:

                        EINVAL  Invalid date

Note            Compatible with Microsoft C.  Not the same as setdate().

*---------------------------------------------------------------------*/
unsigned _dos_setdate(struct dosdate_t *datep)
{
    _DH = datep->month;
    _DL = datep->day;
    _CX = datep->year;
    _AH = 0x2b;
    geninterrupt(0x21);
    if (_AL == 0xff)
    {
        errno = EINVAL;
        return -1U;
    }
    else
        return 0;
}


/*---------------------------------------------------------------------*

Name            _dos_settime - sets MS-DOS time

Usage           #include <dos.h>
                unsigned _dos_settime(struct dostime_t *timep);

Prototype in    dos.h

Description     _dos_settime sets the system's current time to the values
                in the dostime_t structure pointed to by timep.

                The dostime_t structure is defined as follows:

                struct dostime_t {
                        unsigned char hour;     (* Hours *)
                        unsigned char minute;   (* Minutes *)
                        unsigned char second;   (* Seconds *)
                        unsigned char hsecond;  (* Hundredths of seconds *)
                };

Return value    If sucess, returns 0.  Otherwise, returns non-zero
                and sets errrno:

                        EINVAL  Invalid time

Note            Compatible with Microsoft C.  Not the same as settime().

*---------------------------------------------------------------------*/
unsigned _dos_settime(struct dostime_t *timep)
{
    _CH = timep->hour;
    _CL = timep->minute;
    _DH = timep->second;
    _DL = timep->hsecond;
    _AH = 0x2d;
    geninterrupt(0x21);
    if (_AL == 0xff)
    {
        errno = EINVAL;
        return -1U;
    }
    else
        return 0;
}
