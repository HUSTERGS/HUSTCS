/*------------------------------------------------------------------------*/
/*                                                                        */
/*  LDATE.H                                                               */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __LDATE_H )
#define __LDATE_H

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
_CLASSDEF(BaseDate)
_CLASSDEF(Date)

class _CLASSTYPE BaseDate : public Sortable
{

public:

    unsigned Month() const;
    unsigned Day() const;
    unsigned Year() const;
    void SetMonth( unsigned char );
    void SetDay( unsigned char );
    void SetYear( unsigned );

    virtual hashValueType hashValue() const;
    virtual int isEqual( const Object _FAR & ) const;
    virtual int isLessThan( const Object _FAR & ) const;
    virtual void printOn( ostream _FAR & ) const = 0;

protected:

    BaseDate();
    BaseDate( unsigned char, unsigned char, unsigned );
    BaseDate( const BaseDate _FAR & );

private:

    unsigned char MM;
    unsigned char DD;
    unsigned int YY;

};

inline BaseDate::BaseDate()
{
    struct date d;
    getdate( &d );
    MM = d.da_mon;
    DD = d.da_day;
    YY = d.da_year;
}

inline BaseDate::BaseDate( unsigned char M, unsigned char D, unsigned Y )
{
    SetMonth( M );
    SetDay( D );
    SetYear( Y );
}

inline BaseDate::BaseDate( const BaseDate _FAR & B ) :
    MM(B.MM), DD(B.DD), YY(B.YY)
{
}

inline unsigned BaseDate::Month() const
{
    return MM;
}

inline unsigned BaseDate::Day() const
{
    return DD;
}

inline unsigned BaseDate::Year() const
{
    return YY;
}

inline void BaseDate::SetMonth( unsigned char M )
{
    PRECONDITION( M > 0 && M < 13 );
    MM = M;
}

inline void BaseDate::SetDay( unsigned char D )
{
    PRECONDITION( D < 32 );
    DD = D;
}

inline void BaseDate::SetYear( unsigned Y )
{
    YY = Y;
}

class _CLASSTYPE Date : public BaseDate
{

public:

    Date();
    Date( unsigned char, unsigned char, unsigned );
    Date( const Date _FAR & );

    virtual classType isA() const
        {
        return dateClass;
        }

    virtual char _FAR *nameOf() const
        {
        return "Date";
        }

    virtual void printOn( ostream _FAR & ) const;

};

inline Date::Date()
{
}

inline Date::Date( unsigned char M, unsigned char D, unsigned Y ) :
    BaseDate( M, D, Y )
{
}

inline Date::Date( const Date& D ) : BaseDate( D )
{
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __LDATE_H
