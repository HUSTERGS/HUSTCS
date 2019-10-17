/*------------------------------------------------------------------------
 * filename - dosenv.c
 *
 * function(s)
 *        __DOSenv - Prepare Spawn/Exec environment
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

Name            DOSenv -- Prepare Spawn/Exec environment

Usage           char * pascal __DOSenv(char **envV,
                                       char *pathP,
                                       void **envSave);

Prototype in    _process.h

Description     This function allocates  a buffer and fill it  with all the
                environment  strings one  after  the  others. If  the pathP
                variable is nonzero, then it is  appended to the end of the
                end of  the environment assumed it  is for a spawn  or exec
                purpose.


Return value    DOSenv  returns a  pointer  to  the environment  buffer if
                successful, and NULL on error.

-------------------------------------------------------------------------*/
char    * pascal near __DOSenv(char **envV, char *pathP, void **envSave)
{
        register char   **envW;
        register unsigned       envS;
        char    *bufP;

/*      Compute the environment size including  the NULL string at the
        end of the environment. (Environment size < 32 Kbytes)
*/
        envS = 1;
        if ((envW = envV) != NULL)
                for (envS = 0; *envW && **envW; envS += strlen(*envW++) + 1)
                        ;
        envS++;
        if (pathP)
                envS += 2 + strlen(pathP) + 1;
        if (envS >= 0x2000)
                return (NULL);

/*      Allocate a buffer
*/
        if ((bufP = malloc(envS + 15)) != NULL) {

/*              The environment MUST be paragraph aligned
*/
                *envSave = bufP;
                bufP += 15;
                (*((unsigned *)&(bufP))) &= 0xFFF0;

/*              Concatenate all environment strings
*/
                if ((envW = envV) != NULL && *envW != NULL)
                        while (*envW && **envW)
                {
                                bufP = _stpcpy(bufP, *envW++);
                                *bufP++ = '\0';
                }
        else
            *bufP++ = '\0';
                *bufP++ = '\0';

/*              Append program name to the environment
*/
                if (pathP) {
                        *((short *)bufP)++ = 1;
                        bufP = _stpcpy(bufP, pathP);
                        *bufP++ = '\0';
                }
                return bufP - envS;
        }
        else
                return NULL;
}
