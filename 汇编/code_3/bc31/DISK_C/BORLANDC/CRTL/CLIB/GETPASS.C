/*-----------------------------------------------------------------------*
 * filename - getpass.c
 *
 * function(s)
 *        _KbdFlush - flushes the keyboard buffer
 *        getpass   - reads a password
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <conio.h>
#include <stdio.h>
#include <dos.h>

/*---------------------------------------------------------------------*

Name            _KbdFlush - flushes the keyboard buffer

Usage           static void pascal _KbdFlush(void);

Description     flushes the keyboard buffer

Return value    nothing

*---------------------------------------------------------------------*/
static void pascal _KbdFlush(void)
{
        bdos(0x0c, 0x00, 0x02);
}


/*---------------------------------------------------------------------*

Name            getpass - reads a password

Usage           char *getpass(const char *prompt);

Prototype in    conio.h

Description     getpass reads a password from the system console after
                prompting with the null-terminated string prompt and disabling
                the echo. A pointer is returned to a null-terminated string
                of up to eight characters at most (not counting the
                null-terminator).

Return value    The return value is a pointer to a static string
                which is overwritten with each call.

*---------------------------------------------------------------------*/
char * _FARFUNC getpass(const char *prompt)
{
        register char   *cp;
        register int    i;

        static  char    xc[9];

        /* Print the prompt message */
        fprintf(stderr, "%s", prompt);

        /* Flush the keyboard buffer */
        _KbdFlush();

        /* Read the password from keyboard without echo */
        for (cp = xc, i = 0; i < 8 ; i++, cp++)
                if ((*cp = bdos(7,0,0)) == '\r')
                        break;

        *cp = '\0';             /* Password is a NULL terminated string */
        bdos(0x02,'\r',0);      /* Display a new line                   */
        bdos(0x02,'\n',0);

        /* Read any remaining characters */
        _KbdFlush();
        return(xc);
}
