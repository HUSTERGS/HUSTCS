/*------------------------------------------------------------------------*/
/*                                                                        */
/*  LTIME.H                                                               */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __LTIME_H )
#define __LTIME_H

#if !defined( __CHECKS_H )
#include <Checks.h>
#endif	// __CHECKS_H

#if !defined( __DOS_H )
#include <Dos.h>
#endif  // __DOS_H

#if !defined( __SORTABLE_H )
#include <Sortable.h>
#endif  // __SORTABLE_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

_CLASSDEF(ostream)
_CLASSDEF(BaseTime)
_CLASSDEF(Time)

class _CLASSTYPE BaseTime : public Sortable
{

public:

    unsigned hour() const;
    unsigned minute() const;
    unsigned second() const;
    unsigned hundredths() const;
    void setHour( unsigned char );
    void setMinute( unsigned char );
    void setSecond( unsigned char );
    void setHundredths( unsigned char );

    virtual classType isA() const = 0;
    virtual char _FAR *nameOf() const = 0;
    virtual hashValueType hashValue() const;
    virtual int isEqual( const Object _FAR & ) const;
    virtual int isLessThan( const Object _FAR & ) const;
    virtual void printOn( ostream _FAR & ) const = 0;

protected:

    BaseTime();
    BaseTime( const BaseTime _FAR & );
    BaseTime( unsigned char,
              unsigned char = 0,
              unsigned char = 0,
              unsigned char = 0
            );

private:

    unsigned char HH;
    unsigned char MM;
    unsigned char SS;
    unsigned char HD;
};

inline BaseTime::BaseTime()
{
    struct time t;
    gettime( &t );
    HH = t.ti_hour;
    MM = t.ti_min;
    SS = t.ti_sec;
    HD = t.ti_hund;
}

inline BaseTime::BaseTime( const BaseTime _FAR & B ) :
    HH(B.HH), MM(B.MM), SS(B.SS), HD(B.HD)
{
}

inline BaseTime::BaseTime( unsigned char H, unsigned char M, unsigned char S, unsigned char D )
{
    setHour( H );
    setMinute( M );
    setSecond( S );
    setHundredths( D );
}

inline unsigned BaseTime::hour() const
{
    return HH;
}

inline unsigned BaseTime::minute() const
{
    return MM;
}

inline unsigned BaseTime::second() const
{
    return SS;
}

inline unsigned BaseTime::hundredths() const
{
    return HD;
}

inline void BaseTime::setHour( unsigned char anHour )
{
    PRECONDITION( anHour < 24 );
    HH = anHour;
}

inline void BaseTime::setMinute( unsigned char M )
{
    PRECONDITION( M < 60 );
    MM = M;
}

inline void BaseTime::setSecond( unsigned char S )
{
    PRECONDITION( S < 60 );
    SS = S;
}

inline void BaseTime::setHundredths( unsigned char D )
{
    PRECONDITION( D < 100 );
    HD = D;
}

class _CLASSTYPE Time : public BaseTime
{

public:

    Time();
    Time( const Time _FAR & );
    Time( unsigned char,
          unsigned char = 0,
          unsigned char = 0,
          unsigned char = 0
        );

    virtual classType isA() const
        {
        return timeClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "Time";
        }

    virtual void printOn( ostream _FAR & ) const;
};

inline Time::Time() : BaseTime()
{
}

inline Time::Time( const Time& T ) : BaseTime( T )
{
}

inline Time::Time( unsigned char H, unsigned char M, unsigned char S,
                   unsigned char D ) :  BaseTime( H, M, S, D )
{
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __LTIME_H

