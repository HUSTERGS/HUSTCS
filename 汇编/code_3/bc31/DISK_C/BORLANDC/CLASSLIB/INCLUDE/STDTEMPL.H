/*------------------------------------------------------------------------*/
/*                                                                        */
/*  STDTEMPL.H                                                            */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*                                                                        */
/*  Implements commonly used template functions min(), max(), range()     */
/*                                                                        */
/*      T min( T, T ) returns the lesser of its arguments                 */
/*                                                                        */
/*      T min( T, T, T ) returns the least of its arguments               */
/*                                                                        */
/*      T max( T, T ) returns the greater of its arguments                */
/*                                                                        */
/*      T max( T, T, T ) returns the greatest of its arguments            */
/*                                                                        */
/*      T range( T minVal, T maxVal, T val ) returns val if val is        */
/*          between minVal and maxVal.  If val is greater than maxVal,    */
/*          returns maxVal.  If val is less than minVal, returns minVal.  */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __STDTEMPL_H )
#define __STDTEMPL_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

template <class T> inline T min( T t1, T t2 )
{
    return t1>t2 ? t2 : t1;
}

template <class T> inline T min( T t1, T t2, T t3 )
{
    return t1>t2 ? (t2>t3 ? t3 : t2) : (t1>t3 ? t3 : t1 );
}

template <class T> inline T max( T t1, T t2 )
{
    return t1>t2 ? t1 : t2;
}

template <class T> inline T max( T t1, T t2, T t3 )
{
    return t1>t2 ? (t1>t3 ? t1 : t3) : (t2>t3 ? t2 : t3);
}

template <class T> inline T range( T minVal, T maxVal, T val )
{
    return min( maxVal, max( minVal, val ) );
}

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __STDTEMPL_H

