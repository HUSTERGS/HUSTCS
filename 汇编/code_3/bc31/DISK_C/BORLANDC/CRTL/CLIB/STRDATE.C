/*-----------------------------------------------------------------------*
 * filename - strdate.c
 *
 * function(s)
 *        _strdate - gets MS-DOS date string (MSC compatible)
 *        _strtime - gets MS-DOS time string (MSC compatible)
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>
#include <time.h>

/*---------------------------------------------------------------------*

Name            makedate - make a date or time string

Usage           char *makedate(char *str,int one,int two,int three,
                               char sep);

Description     Makes a date or time string in the form xxsyysz,
                where xx, yy, and zz are two digit decimal representations
                of the parameters one, two, and three, respectively,
                and s is the separator character sep.  The string
                is terminated by a null

Return value    The value of str.

*---------------------------------------------------------------------*/

static char * pascal near
makedate(char *str,int one,int two,int three, char sep)
{
    str[2] = str[5] = sep;
    str[8] = '\0';
    str[0] = ((one / 10) % 10) + '0';
    str[1] = (one % 10) + '0';
    str[3] = ((two / 10) % 10) + '0';
    str[4] = (two % 10) + '0';
    str[6] = ((three / 10) % 10) + '0';
    str[7] = (three % 10) + '0';
    return (str);
}

/*---------------------------------------------------------------------*

Name            _strdate - copies MS-DOS date to a string buffer

Usage           #include <time.h>
                char *_strdate(char *datestr);

Prototype in    dos.h

Description     _strdate copies the current system date to a buffer
                pointed to by datestr, in the following format:

                        mm/dd/yy

                where mm is two digits representing the month, dd is two
                digits representing the day, and yy is two digits
                representing the year. The string thus formed is
                terminated by a null character.
                The buffer must be at least 9 bytes long.

Return value    The value of datestr.

Note            Compatible with Microsoft C.

*---------------------------------------------------------------------*/

char * _FARFUNC _strdate(char *datestr)
{
    struct dosdate_t d;

    _dos_getdate(&d);
    return (makedate(datestr,d.month,d.day,d.year-1900,'/'));
}

/*---------------------------------------------------------------------*

Name            _strtime - copies MS-DOS time to a string buffer

Usage           #include <time.h>
                char *_strtime(char *timestr);

Prototype in    dos.h

Description     _strtime copies the current system time to a buffer
                pointed to by timestr, in the following format:

                hh/mm/ss

                where hh is two digits representing the hour, mm is two
                digits representing the minutes, and yy is two digits
                representing the seconds. The string thus formed is
                terminated by a null character.
                The buffer must be at least 9 bytes long.

Return value    The value of timestr.

Note            Compatible with Microsoft C.

*---------------------------------------------------------------------*/

char * _FARFUNC _strtime(char *timestr)
{
    struct dostime_t t;

    _dos_gettime(&t);
    return (makedate(timestr,t.hour,t.minute,t.second,':'));
}
