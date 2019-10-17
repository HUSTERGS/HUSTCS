/*------------------------------------------------------------------------
 * filename - setargv.c
 *
 * function(s)
 *   _setargv (init proc)
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>

#pragma warn -use

#ifndef _WINDOWS
#define _WINDOWS
#endif

#define StrCpy strcpy
#define strfncpy(dest, src, size)  movedata(FP_SEG(src), FP_OFF(src), \
                                            FP_SEG(dest), FP_OFF(dest), size);

#define AllocHeap(size)     malloc(size)
#define FreeHeap(handle)    free(handle)
#define LockHeap(handle)

#define PSPCMDLEN   0x80
#define PSPENV      0x2C
#define MAXFNAMELEN 80

#define CR          '\r'
#define EOS         '\0'
#define QUOTE       '"'
#define SPACE       ' '
#define QUESTION    '?'
#define ASTERICK    '*'
#define TRUE        1
#define FALSE       0

int  _argc = 1;
char **_argv = NULL;

extern unsigned _hInstance;
extern unsigned _pszCmdline;
extern char *_argv0;

extern unsigned _envseg;
extern unsigned _envLng;
extern unsigned _envSize;

void _setargv(void)
{
    char far *farcmdline;
    unsigned char far *farcmdlen;
    char _FAR *cmdline;
    char _FAR *savecmd;
    char _FAR *endpoint;
    char _FAR *start;
    int inquote, done, found;
    int length;

    farcmdline = MK_FP(_psp, _pszCmdline);
    length = _fstrlen(farcmdline);

    savecmd = cmdline = AllocHeap((length)+1);
    strfncpy(cmdline, farcmdline, (length)+1);

    endpoint = cmdline + length;

    while (*cmdline == SPACE)   /* strip leading white space */
        *cmdline++ = EOS;

    inquote = done = FALSE;
    start = cmdline;
    while (!done)
        {
        found = 0;
        while(*cmdline != EOS)
            {
            switch (*cmdline)
                {
                case QUOTE:
                    // If not in quotes then one of two possibilities:
                    // 1) Start of new argument
                    // 2) End of argument and start of new one
                    if (!inquote)
                        {
                        if (start == cmdline)
                            {
                            inquote = TRUE;   // in qoutes
                            *cmdline = EOS;   // overwrite quote char
                            cmdline++;
                            start = cmdline;
                            }
                        else
                            {
                            *cmdline = EOS;   // overwrite quote char
                            inquote = TRUE;   // but note that we got it
                            }
                        }
                    // Else were in quotes
                    else
                        {
                        *cmdline = EOS;       // overwrite quote char
                        inquote = FALSE;      // and out of quotes
                        }
                    break;

                case SPACE:
                    // If not in quotes then overwtite, else increment
                    // and note that we are in an argument
                    if (!inquote)
                        *cmdline = EOS;
                    else
                        {
                        found++;
                        cmdline++;
                        }
                    break;

                case CR:
                    // Overwite and set done flag
                    *cmdline = EOS;
                    done = TRUE;
                    break;

                default:
                    // Otherwise increment and note that we have an argument
                    cmdline++;
                    found++;
                    break;
                }
            }

        if (cmdline >= endpoint)
            done = TRUE;

        if (!done)
            {
            cmdline++;          // move past NULL
            if (!inquote)       // skip spaces if we didn't start quotes
                while (*cmdline == SPACE)
                    *cmdline++ = EOS;
            start = cmdline;
            }

        if (found)
            _argc++;
        }

/*========================================================================
 *  1) number of arguments
 *  2) size of arguments (slightly bloated)
 *  3) length needed for Program path name
 *
 *  So, ((#1)*sizeof(* _argv))+(#2)+(#3) should be total size
 *========================================================================
 */

// set curptr to first byte past last argument pointer
// set up argv[0]: copy commandline into beginning of buffer and update curptr
// loop: set argv[i] and copy next argument to buffer updating curptr
//
    _argv = (char **) AllocHeap((sizeof(*_argv)*(_argc+1))+(length)+strlen(_argv0)+2);
    start = (char *) &(_argv[_argc+1]);
    _argv[0] = (char *)start;
    StrCpy(start, _argv0);
    start += strlen(start)+1;
    cmdline = savecmd;

    for (done=1; done < _argc; done++)
        {
        _argv[done] = (char *)start;
        while (*cmdline == EOS)     // skip to next argument
            cmdline++;
        StrCpy(start, cmdline);
        found = strlen(start)+1;
        start += found;
        cmdline += found;
        }
    _argv[done] = NULL;
    FreeHeap(_argv0);
    _argv0 = _argv[0];
    FreeHeap(savecmd);
}

#pragma startup _setargv 10   // NOTE:  Must be executed after _setenv (8)
