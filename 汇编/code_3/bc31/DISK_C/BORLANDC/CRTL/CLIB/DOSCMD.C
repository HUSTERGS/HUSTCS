/*------------------------------------------------------------------------
 * filename - doscmd.c
 *
 * function(s)
 *        __DOScmd - Prepare Spawn/Exec command line
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <_process.h>
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------------*

Name            __DOScmd -- Build a DOS command line from argv array

Usage           char * pascal __DOScmd(char **argV);

Prototype in    _process.h

Description     This function allocates  a buffer and fill it  with all the
                argument  strings one  after the  others. The  command line
                starts  with  the  command  length  and  terminates  with a
                carriage return which is not included in the count.


Return value    __DOScmd  returns  a pointer  to  command  string buffer if
                successful, and NULL on error.

*------------------------------------------------------------------------*/
char    * pascal near __DOScmd(char **argV)
{
        register char   **argW;
        register unsigned       cmdS, Wrk;
        char    *bufP;

/*      Compute the command line size including the NULL string at the
        end of the command line.
*/

        cmdS = 1;               /* Command size byte */
        if ((argW = argV) != NULL && *argW++)
                while (*argW && **argW) {
                        Wrk = strlen(*argW++) + 1;
                        if ((cmdS + Wrk) > 127)
                                return NULL;
                        cmdS += Wrk;
                }
        cmdS++;                 /* Ending Carriage Return */

/*      Allocate a buffer, and concatenate all argument strings
*/
        if ((bufP = malloc(cmdS)) != NULL) {
                if ((*bufP++ = cmdS - 2) != 0) {
                        argW = argV + 1;
                        while (*argW && **argW) {
                                *bufP++ = ' ';
                                bufP = _stpcpy(bufP, *argW++);
                        }
                }
                *bufP++ = '\r';
                return bufP - cmdS;
        }
        else
                return NULL;
}
