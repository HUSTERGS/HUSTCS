/*------------------------------------------------------------------------*/
/*                                                                        */
/*  BSORTARY.CPP                                                          */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( TEMPLATES )
#define TEMPLATES
#endif

#if !defined( __SORTABLE_H )
#include <Sortable.h>
#endif  // __SORTABLE_H

#if !defined( __ARRAYS_H )
#include <Arrays.h>
#endif  // __ARRAYS_H

void BI_ISObjectVector::add( Object _FAR *o )
{
    if( count_ >= lim )
        resize( count_+1 );
    unsigned loc = count_++;
    while( loc > 0 && *(Sortable _FAR *)o < *(Sortable _FAR *)(data[loc-1]) )
        {
        data[loc] = data[loc-1];
        loc--;
        }
    data[loc] = o;
}

unsigned BI_ISObjectVector::find( void _FAR * obj ) const
{
    unsigned lower = 0;
    unsigned upper = count_-1;
    if( count_ != 0 )
        {
        while( lower < upper && upper != UINT_MAX )
            {
            unsigned middle = (lower+upper)/2;
            if( *(const Sortable _FAR *)(data[middle]) ==
                *(const Sortable _FAR *)obj
              )
                return middle;
            if( *(const Sortable _FAR *)(data[middle]) <
                *(const Sortable _FAR *)obj
              )
                lower = middle+1;
            else
                upper = middle-1;
            }
        }
    if( lower == upper &&
        *(const Sortable _FAR *)(data[lower]) == *(const Sortable _FAR *)obj
      )
        return lower;
    else
        return UINT_MAX;
}
