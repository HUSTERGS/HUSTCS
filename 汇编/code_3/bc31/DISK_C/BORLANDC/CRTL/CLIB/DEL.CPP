/*-----------------------------------------------------------------------*
 * filename - del.cpp
 * C++ DELETE
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stddef.h>
#include <stdlib.h>

void operator delete( void _FAR *ptr )
{
    free(ptr);
}
