/*------------------------------------------------------------------------
 * filename - _matherr.c
 *
 * function(s)
 *        _matherr - floating-point error handling routine
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <_math.h>
#include <math.h>
#include <stdio.h>
#include <errno.h>

#ifdef _Windows
#include <_win.h>
#endif

/*-------------------------------------------------------------------------*

Name            _matherr - floating-point error handling routine

Usage           #include<math.h>
                double   _matherr (_mexcep why,
                                   char    *fun,
                                   double  *arg1p,
                                   double  *arg2p,
                                   double  retval);


Prototype in    math.h

Description     _matherr serves as a focal  point for error handling in all
                math library functions; it  calls matherr and processes the
                return value from matherr.  _matherr should never be called
                directly by user programs.

                Whenever  an  error  occurs  in  one  of  the  math library
                routines _matherr is called with several arguments.

                _matherr does four things :
                        . It  uses its arguments  to fill out  an exception
                          structure.

                        . It  calls   matherr  with  e,  a  pointer  to the
                          exception  structure,  to   see  if  matherr  can
                          resolve the error.

                        . It  examines  the  return  value from  matherr as
                          follows:
                                If matherr  returns 0, (indicating  that it
                                was not able to resolve the error) _matherr
                                sets errno and prints an error message

                                If  matherr  returns  non-zero, (indicating
                                that  it  was  able  to  resolve the error)
                                _matherr is  silent; it does not  set errno
                                or print any messages.

                        . It returns e->retval to the original caller. Note
                          that  matherr might  modify e->retval  to specify
                          the  value  it  wants   propagated  back  to  the
                          original caller.

                When  _matherr  sets  errno  (based  on  a  0  return  from
                matherr), it maps the kind of error that occurred (from the
                type field in the exception  structure) onto an errno value
                of either EDOM or ERANGE.

Return value    _matherr returns the value, e->retval.

*-------------------------------------------------------------------------*/
double _Cdecl _FARFUNC _matherr(_mexcep why,
                char    *fun,
                double  *arg1p,
                double  *arg2p,
                double  retval)
{
        struct  exception       e;

        e.type = why;
        e.name = fun;
        e.arg1 = (NULL == arg1p) ? 0 : *arg1p;
        e.arg2 = (NULL == arg2p) ? 0 : *arg2p;
        e.retval = retval;

        if (matherr (& e) == 0)
                {
#ifdef _Windows
                char errMsg[ 80 ];
#endif

#ifdef UNIX_matherr
#    ifdef _Windows
                sprintf (errMsg, "%s (%8g,%8g): %s\n",
                         fun, *arg1p, *arg2p, _mathwhy [why - 1]);
#    else
                fprintf (stderr, "%s (%8g,%8g): %s\n",
                         fun, *arg1p, *arg2p, _mathwhy [why - 1]);
#    endif
#else
#    ifdef _Windows
                sprintf (errMsg, "%s: %s error\n", fun, _mathwhy [why - 1]);
#    else
                fprintf (stderr, "%s: %s error\n", fun, _mathwhy [why - 1]);
#    endif
#endif

                errno = ((OVERFLOW == why) || (UNDERFLOW == why)) ? ERANGE : EDOM;
#ifdef _Windows
                _errorBox( errMsg );
#endif
                }
        return  e.retval;
}
