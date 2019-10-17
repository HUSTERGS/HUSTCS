/*------------------------------------------------------------------------*/
/*                                                                        */
/*  CLASMAIN.CPP                                                          */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*  Provides the LibMain() function for the DLL version                   */
/*  of the class libraries                                                */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __WINDOWS_H )
#include <Windows.h>
#endif	// __WINDOWS_H

extern "C" int FAR PASCAL LibMain( HANDLE, WORD, WORD, LPSTR )
{
    return 1;
}


