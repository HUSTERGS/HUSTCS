/*------------------------------------------------------------------------
 * filename - ctime.c
 *
 * function(s)
 *    comtime   - converts long timedate to a structure
 *    atime     - converts date and time to ASCII without trailing '\n'
 *    asctime   - converts date and time to ASCII
 *    ctime     - converts date and time to a string
 *    gmtime    - converts date and time to Greenwich Mean Time
 *    localtime - converts date and time to a structure
 *    mktime    - normalizes the date and time structure
 *    strftime  - converts date and time structure to a string
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <_io.h>
#include <_printf.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <RtlData.h>

static const char Days[12] = {
  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
  };

static int YDays[12] = {
  0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
  };

static char *SWeekday[7] = {
  "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
  };

static char *LWeekday[7] = {
  "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
  };

static char *SMonth[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };

static char *LMonth[12] = {
  "January", "February", "March",     "April",   "May",      "June",
  "July",    "August",   "September", "October", "November", "December"
  };

static char *AmPm[2] = {
  "AM", "PM"
  };

#if !defined( _RTLDLL )
static  struct  tm tmX;
#endif

/*---------------------------------------------------------------------*

Name            comtime

Usage           static struct tm *comtime(unsigned long time, int dst);

Prototype in    local to this module

Description     fills the time structure tm by translating the long
                time.

Return value    the broken down time structure. This structure is
                a static which is overwritten with each call.

*---------------------------------------------------------------------*/
static  struct  tm *comtime(time_t time, int dst)
{
    int      hpery;
    unsigned i;
    unsigned cumdays;
    _QRTLDataBlock;

    if (time < 0)
        time = 0;

    _QRTLInstanceData(tmX).tm_sec = (int)(time % 60);
    time /= 60;                             /* Time in minutes */
    _QRTLInstanceData(tmX).tm_min = (int)(time % 60);
    time /= 60;                             /* Time in hours */
    i = (unsigned)(time / (1461L * 24L));   /* Number of 4 year blocks */
    _QRTLInstanceData(tmX).tm_year = (i << 2);
    _QRTLInstanceData(tmX).tm_year+= 70;
    cumdays = 1461 * i;
    time %= 1461L * 24L;        /* Hours since end of last 4 year block */

    for (;;)
        {
        hpery = 365 * 24;
        if ((_QRTLInstanceData(tmX).tm_year & 3) == 0)
            hpery += 24;
        if (time < hpery)
            break;
        cumdays += hpery / 24;
        _QRTLInstanceData(tmX).tm_year++;
        time -= hpery;
        }   /* at end, time is number of hours into current year */

    if  (dst && daylight &&
             __isDST( (int)(time % 24), (int)(time / 24), 0, _QRTLInstanceData(tmX).tm_year-70))
        {
        time++;
        _QRTLInstanceData(tmX).tm_isdst = 1;
        }
    else
        _QRTLInstanceData(tmX).tm_isdst = 0;

    _QRTLInstanceData(tmX).tm_hour = (int)(time % 24);
    time /= 24;             /* Time in days */
    _QRTLInstanceData(tmX).tm_yday = (int)time;
    cumdays += (int)time + 4;
    _QRTLInstanceData(tmX).tm_wday = cumdays % 7;
    time++;

    if ((_QRTLInstanceData(tmX).tm_year & 3) == 0)
        {
        if (time > 60)
            time--;
        else
            if (time == 60)
                {
                _QRTLInstanceData(tmX).tm_mon = 1;
                _QRTLInstanceData(tmX).tm_mday = 29;
                return(&_QRTLInstanceData(tmX));
                }
        }

    for (_QRTLInstanceData(tmX).tm_mon = 0; Days[_QRTLInstanceData(tmX).tm_mon] < time; _QRTLInstanceData(tmX).tm_mon++)
        time -= Days[_QRTLInstanceData(tmX).tm_mon];

    _QRTLInstanceData(tmX).tm_mday = (int)(time);
    return(&_QRTLInstanceData(tmX));
}


/*------------------------------------------------------------------------*

Name            atime - converts date and time to ASCII without trailing '\n'

Usage           #include <time.h>
                static int atime( char *dest, const struct tm *tmPtr );

                Local to this module

Description     Provides the basic formatting capabilities for asctime() and
                strftime( "%c" ).  These two functions both provide an ASCII
                version of the date and time in the struct tm, but asctime()
                adds a newline to the end.

Return value    Returns the number of characters in the ASCII string

*---------------------------------------------------------------------------*/

static int _FARFUNC atime( char *dest, const struct tm *tmPtr )
{
    return sprintf( dest, "%s %s %02d %02d:%02d:%02d %4d",
        SWeekday[tmPtr->tm_wday],
        SMonth[tmPtr->tm_mon],
        tmPtr->tm_mday,
        tmPtr->tm_hour,
        tmPtr->tm_min,
        tmPtr->tm_sec,
        tmPtr->tm_year + 1900
        );
}

/*------------------------------------------------------------------------*

Name            asctime   - converts date and time to ASCII
                ctime     - converts date and time to a string
                gmtime    - converts date and time to Greenwich Mean Time
                localtime - converts date and time to a structure

Usage           #include <time.h>
                char *asctime(struct tm *_QRTLInstanceData(tmX));
                char *ctime(long *clock);
                struct tm *gmtime(long *clock);
                struct tm *localtime(long *clock);

Prototype in    time.h

Description     asctime  converts  a  time  stored  as  a  structure  to  a
                26-character string in the following form:

                Mon Nov 21 11:31:54 1983\n\0

                All the fields have a constant width.

                ctime converts a time pointed to by clock (such as returned
                by the function time) to  a 26-character string of the form
                described above.

                localtime   and  gmtime   return  pointers   to  structures
                containing the broken-down time. localtime corrects for the
                time  zone  and  possible  daylight  savings  time;  gmtime
                converts directly to GMT.

                The global  long variable timezone contains  the difference
                in  seconds between  GMT and  local standard  time (in EST,
                timezone  is  5*60*60).  The  global  variable  daylight is
                non-zero  if  and  only  if  the  standard  U.S.A. Daylight
                Savings Time conversion should be applied.

Return value    asctime and ctime return a  pointer to the character string
                containing the date and time. This string is a static which
                is overwritten with each call.

                gmtime and localtime return the broken down time structure.
                This structure is  a static which is overwritten  with each
                call.

*---------------------------------------------------------------------------*/
struct  tm      *_FARFUNC gmtime(const time_t *clock)
{
    return(comtime(*clock, 0));
}

struct  tm      *_FARFUNC localtime(const time_t *clock)
{
    unsigned long    x;

    tzset();        /* get timezone info */
    x = *clock - timezone;
    return(comtime(x, 1));
}

char    *_FARFUNC asctime(const struct tm *tmPtr)
{
#if !defined( _RTLDLL )
    static char a[26];
#endif
    int end;
    _QRTLDataBlock;

    end = atime( _QRTLInstanceData(a), tmPtr );
    _QRTLInstanceData(a)[end++] = '\n';        //  add terminating newline
    _QRTLInstanceData(a)[end] = '\0';

    return(_QRTLInstanceData(a));
}

char    * _FARFUNC ctime(const time_t *clock)
{
    return(asctime(localtime(clock)));
}


/*------------------------------------------------------------------------*
    Converts a date expressed in local time to the number of seconds
    elapsed since year 70 (1970) in calendar time.
    All arguments are zero based.
 *------------------------------------------------------------------------*/
static unsigned long near totalsec(int year, int month, int day, int hour, int min, int sec)
{
    int leaps;
    time_t days, secs;

    if (year < 70 || year > 138)
        return ((time_t) -1);

    min += sec / 60;
    sec %= 60;              /* Seconds are normalized */
    hour += min / 60;
    min %= 60;              /* Minutes are normalized */
    day += hour / 24;
    hour %= 24;             /* Hours are normalized   */

    year += month / 12;     /* Normalize month (not necessarily final) */
    month %= 12;

    while (day >= Days[month])
        {
        if (!(year & 3) && (month ==1))
            {
            if (day > 28)
                {
                day -= 29;
                month++;
                }
        else
        break;
            }
        else
            {
            day -= Days[month];
            month++;
            }
        year += month / 12; /* Normalize month */
        month %= 12;
        }

    year -= 70;
    leaps = (year + 2) / 4;

    if (!((year+70) & 3) && (month < 2))
        --leaps;

    days = year*365L + leaps + YDays[month] + day;

    secs = days*86400L + hour*3600L + min*60L + sec + timezone;

    if (daylight && __isDST(hour, day, month+1, year))
        secs -= 3600;

    return(secs > 0 ? secs : (time_t) -1);
}


time_t _FARFUNC mktime(struct tm *t)
{
    time_t secs;

    secs = totalsec(t->tm_year, t->tm_mon, t->tm_mday-1, t->tm_hour, t->tm_min, t->tm_sec);

    if (secs != (time_t) -1){
        localtime(&secs);
        *t = _RTLInstanceData(tmX);
    }

    return(secs);
}


size_t _FARFUNC strftime( char *s, size_t maxsize, const char *fmt, const struct tm *t )
  {
  char buf[ 25 ];

  char *p = buf;
  int i, len;

  for( len = 1; len < maxsize && *fmt; ++fmt, p = buf )
    {
    if( *fmt != '%' )
      {
      ++len;
      *s++ = *fmt;
      }
    else
      {
      strcpy( buf, "00" );

      switch( *++fmt )
        {
        case 'a':
            p = SWeekday[t->tm_wday];
            break;
        case 'A':
            p = LWeekday[t->tm_wday];
            break;
        case 'b':
            p = SMonth[t->tm_mon];
            break;
        case 'B':
            p = LMonth[t->tm_mon];
            break;
        case 'c':
            atime( p, t );
            break;
        case 'd':
            __utoa( t->tm_mday, buf + (t->tm_mday < 10) );
            break;
        case 'H':
            __utoa( t->tm_hour, buf + (t->tm_hour < 10) );
            break;
        case 'I':
            i = t->tm_hour % 12;
            if (i == 0)
                i = 12;
            __utoa( i, buf + (i < 10) );
            break;
        case 'j':
            i = t->tm_yday + 1;
            __utoa( i, buf + (i < 10) + (i < 100) );
            break;
        case 'm':
            i = t->tm_mon + 1;
            __utoa( i, buf + (i < 10) );
            break;
        case 'M':
            __utoa( t->tm_min, buf + (t->tm_min < 10) );
            break;
        case 'p':
            p = AmPm[ t->tm_hour / 12 ];
            break;
        case 'S':
            __utoa( t->tm_sec, buf + (t->tm_sec < 10) );
            break;
        case 'U':
            i = t->tm_wday - (t->tm_yday % 7);
            if( i < 0 )
                i += 7;
            i = (t->tm_yday + i) / 7;
            __utoa( i, buf + (i < 10) );
            break;
        case 'w':
            __utoa( t->tm_wday, buf );
            break;
        case 'W':
            i = t->tm_wday - (t->tm_yday % 7);
            if( i < 0 )
                i += 7;
            i = (t->tm_yday + i - 1) / 7;
            __utoa( i, buf + (i < 10) );
            break;
        case 'x':
            strcpy( buf, SWeekday[t->tm_wday] );
            strcat( buf, " " );
            strcat( buf, SMonth[t->tm_mon] );
            strcat( buf, " " );
            __utoa( t->tm_mday, buf + strlen( buf ) );
            strcat( buf, ", " );
            __utoa( t->tm_year + 1900, buf + strlen( buf ) );
            break;

        case 'X':
            __utoa( t->tm_hour, buf + (t->tm_hour < 10) );
            strcat( buf, ":0" );
            __utoa( t->tm_min, buf + strlen( buf ) - (t->tm_min > 9) );
            strcat( buf, ":0" );
            __utoa( t->tm_sec, buf + strlen( buf ) - (t->tm_sec > 9) );
            break;
        case 'y':
            i = t->tm_year % 100;
            __utoa( i, buf + (i < 10) );
            break;
        case 'Y':
            __utoa( 1900 + t->tm_year, buf );
            break;
        case 'Z':
            p = tzname[ t->tm_isdst ];
            break;
        case '%':
            p = "%";
        }

      i = min( strlen( p ), maxsize - len );
      strncpy( s, p, i );
      len += i;
      s += i;
      }
    }

  *s = '\0';

  if( *fmt )  return( 0 );
  else        return( len - 1 );
  }
