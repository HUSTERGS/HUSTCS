/*------------------------------------------------------------------------*/
/*                                                                        */
/*  TIMER.H                                                               */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __TIMER_H )
#define __TIMER_H

#if defined( _Windows ) && !defined( _BUILDRTLDLL )
#error Timer not available for Windows
#endif

#if !defined( __DEFS_H )
#include <_defs.h>
#endif

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

class Timer
{

public:

    Timer();

    void start();
    void stop();
    void reset();

    int status();
    double time();

    static double resolution();

private:

    static unsigned adjust;
    static unsigned calibrate();
    int running;

    struct TIME
        {
        unsigned long dosCount;
        unsigned timerCount;
        };

    TIME startTime;

    double time_;

};

inline int Timer::status()
{
    return running;
}

inline double Timer::time()
{
    return time_/1.E6;
}

inline double Timer::resolution()
{
    return 839/1.E9;
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __TIMER_H

