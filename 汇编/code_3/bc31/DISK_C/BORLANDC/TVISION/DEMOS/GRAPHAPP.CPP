/*-------------------------------------------------------------------*/
/*                                                                   */
/*   Turbo Vision 1.0                                                */
/*   Turbo Vision Demo                                               */
/*   Copyright (c) 1991 by Borland International                     */
/*                                                                   */
/*   BGI support file for use with Turbo Vision BGI (TVBGI) program. */
/*-------------------------------------------------------------------*/

#define Uses_TProgram
#include <tv.h>

#if !defined( __GRAPHAPP_H )
#include "Graphapp.h"
#endif  // __GRAPHAPP_H

#if !defined( __STRING_H )
#include <string.h>
#endif  // __STRING_H

#if !defined( __FSTREAM_H )
#include <fstream.h>
#endif  // __FSTREAM_H

#if !defined( __STRSTREA_H )
#include <strstrea.h>
#endif  // __STRSTREA_H

#if !defined( __IO_H )
#include <io.h>
#endif  // __IO_H


//Utility functions


void freeDriverMem()
{
    if (driverPtr != 0)
    delete (char *)driverPtr;
    driverPtr = NULL;
    driverSize = 0;
}

typedef void(*function)();


Boolean graphAppLoadDriver( int driverNum )
{
    char fileName[MAXSIZE];
    int handle, ccode;
    ostrstream ss(fileName, MAXSIZE);

    if (driverNum <= lastDriver)
        {
        if (bgiPath[strlen(bgiPath)-1] != '\\')
            strcat(bgiPath,"\\");
        ss << bgiPath << driverName[driver-1] << ".BGI" << ends;

        ifstream f(ss.str(), ios::in|ios::binary);
        if (f)
            {
            handle = f.rdbuf()->fd();
            driverSize = (unsigned int)filelength(handle);
            f.seekg( 0L, ios::beg);
	    if (driverSize < (64 * 1024L - 0xF))
                {
                driverPtr = NULL;
                driverPtr = (DriverPtrFunction) new char[driverSize];
                f.read((char *)driverPtr, ushort(driverSize));
                if (f)
                    {
                    ccode = registerfarbgidriver(driverPtr);
                    if (ccode >= 0)
                        return True;
                    else
                        freeDriverMem();
                    }
                    f.close();
                }
            }
        }
    return False;
}

//------------------------------------------------------------------//
// Init BGI. If loadAtInit is true, try to locate and load driver.  //
// Returns true if LoadAtInit succeeds or is set to False. Does     //
// not "own" bgiPath, but instead is passed a pointer to a string   //
// that is allocated elsewhere. Does not de-allocate bgiPath when   //
// done.                                                            //
//------------------------------------------------------------------//

Boolean graphAppInit( int aDriver, int aMode,
            char *aBGIPath, Boolean loadAtInit )
{
    if (aBGIPath != 0)
        bgiPath = aBGIPath;
    driver = aDriver;
    mode = aMode;
    freeDriverMem();
    if ( loadAtInit == True )
        {
        if ( driver == 0 )
            detectgraph(&driver, &mode);
        if ( driver > 0 )
            return graphAppLoadDriver(driver);
        else
            return False;
        }
    return(True);
}

void graphAppDone()
{
    if ( graphActive == True )
        closegraph();
    freeDriverMem();
    graphActive = False;
    bgiPath = emptyString;
    driver = DETECT;
    mode = 0;
}

void graphicsStop(void);

Boolean graphicsStart(void)
{
    if ( graphActive == True )
        return(True);

    initgraph( &driver, &mode, bgiPath );

    if ( driver < 0 )
        {
        graphicsStop();
        return False;
        }
    else
        graphActive = True;
    return True;
}

Boolean graphicsActive(void)
{
    if ( graphActive == True )
        return True;
    else
        return False;
}

void graphicsStop(void)
{
    if ( graphActive == True )
        closegraph();

    graphActive = False;
    TProgram::application->redraw();
}

