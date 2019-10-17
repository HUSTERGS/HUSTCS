/*---------------------------------------------------------*/
/*                                                         */
/*   Turbo Vision 1.0                                      */
/*   Copyright (c) 1991 by Borland International           */
/*                                                         */
/*   Gadgets.h : Header file for gadgets.cpp               */
/*---------------------------------------------------------*/

#if !defined( __GADGETS_H )
#define __GADGETS_H

#define Uses_TEvent
#define Uses_TRect
#define Uses_TView
#include <tv.h>


class THeapView : public TView
{

public:

    THeapView( TRect& r );
    virtual void update();
    virtual void draw();
    virtual long heapSize();

private:

    long oldMem, newMem;
    char heapStr[16];

};


class TClockView : public TView
{

public:

    TClockView( TRect& r );
    virtual void draw();
    virtual void update();

private:

    char lastTime[9];
    char curTime[9];

};

#endif      // __GADGETS_H
