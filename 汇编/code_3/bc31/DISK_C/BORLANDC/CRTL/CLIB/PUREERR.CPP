/*-----------------------------------------------------------------------*
 * filename - pureerr.cpp
 * Error routine linked in when pure function called
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


/*
   A pointer to this routine is linked into virtual vectors whenever
   a virtual function has been declared pure.
*/

#include <stdlib.h>
#include <_io.h>

#ifdef _Windows
#define _LOADDS
extern "C" unsigned far _GetDGROUP(void);
#else
#define _LOADDS _loadds
#endif


extern "C" void near _LOADDS _npure_error_()
{
#ifdef _Windows
        _DS = _GetDGROUP();
#endif
        __ErrorMessage("Pure virtual function called");
        exit(EXIT_FAILURE);
}

extern "C" void far _LOADDS _fpure_error_()
{
#ifdef _Windows
        _DS = _GetDGROUP();
#endif
        __ErrorMessage("Pure virtual function called");
        exit(EXIT_FAILURE);
}
