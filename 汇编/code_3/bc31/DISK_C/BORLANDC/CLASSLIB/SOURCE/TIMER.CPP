/*------------------------------------------------------------------------*/
/*                                                                        */
/*  TIMER.CPP                                                             */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __TIMER_H )
#include <Timer.h>
#endif  // __TIMER_H

#if !defined( __DOS_H )
#include <Dos.h>
#endif  // __DOS_H

const unsigned long far * const dosTime =
    (const unsigned long far * const)MK_FP( 0x40, 0x6C );

unsigned Timer::adjust = calibrate();

Timer::Timer() : time_(0), running(0)
{
}

void Timer::start()
{
    if( !running )
        {
        outportb( 0x43, 0x34 );
        asm jmp __1;
    __1:
        outportb( 0x40, 0 );
        asm jmp __2;
    __2:
        outportb( 0x40, 0 );
        startTime.dosCount = *dosTime;
        startTime.timerCount = 0;
        running = 1;
        }
}

void Timer::stop()
{
    outportb( 0x43, 0 );
    unsigned char temp = inportb( 0x40 );

    TIME stopTime;
    stopTime.timerCount = (inportb( 0x40 ) << 8) + temp;
    stopTime.dosCount = *dosTime;

    TIME elapsedTime;
    elapsedTime.dosCount = stopTime.dosCount - startTime.dosCount;
    elapsedTime.timerCount = -( stopTime.timerCount - adjust );

    const double fudge = 83810.0/100000.0;
    time_ += ((elapsedTime.dosCount << 16) + elapsedTime.timerCount)*fudge;

    running = 0;

}

void Timer::reset()
{
    time_ = 0;
    if( running )
        start();
}

unsigned Timer::calibrate()
{
    adjust = 0;
    unsigned long sum = 0;
    Timer w;
    for( int i = 0; i < 100; i++ )
        {
        w.start();
        w.stop();
        sum += w.time();
        w.reset();
        }
    return (unsigned)((sum+5)/100);
}

#if defined( TEST_TIMER )
#include <iostream.h>
#include <stdio.h>

int main( void )
{
    delay( 0 );
    cout << "Resolution: " << Timer::resolution() << endl;
    Timer w;
    for( unsigned del = 0; del < 10; del++ )
        {
        unsigned d1 = del*100;
        w.start();
        delay( d1 );
        w.stop();
        printf( "%4u ms., actual time = %6f seconds.\n", d1, w.time() );
        w.reset();
        }
    return 0;
}
#endif /* TEST_TIMER */


