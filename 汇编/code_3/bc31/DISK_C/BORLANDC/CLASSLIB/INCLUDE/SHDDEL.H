/*------------------------------------------------------------------------*/
/*                                                                        */
/*  SHDDEL.H                                                              */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __SHDDEL_H )
#define __SHDDEL_H

#if !defined( __DEFS_H )
#include <_defs.h>
#endif  // __DEFS_H

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

_CLASSDEF(TShouldDelete)

class _CLASSTYPE TShouldDelete
{

public:

    enum DeleteType { NoDelete, DefDelete, Delete };

    TShouldDelete( DeleteType dt = Delete )
        {
        ownsElements( dt );
        }

    int ownsElements()
        {
        return shouldDelete == Delete;
        }

    void ownsElements( int del )
        {
        shouldDelete = (del == 0) ? NoDelete : Delete;
        }

protected:

    int delObj( DeleteType dt )
        {
        return dt == Delete || (dt==DefDelete && shouldDelete==Delete);
        }

private:

    DeleteType shouldDelete;

};

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif  // __SHDDEL_H

