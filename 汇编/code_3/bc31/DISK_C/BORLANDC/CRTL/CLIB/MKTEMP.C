/*-----------------------------------------------------------------------*
 * filename - mktemp.c
 *
 * function(s)
 *        mktemp - makes a unique file name
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dir.h>
#include <string.h>
#include <io.h>

/*---------------------------------------------------------------------*

Name            mktemp - makes a unique file name

Usage           char *mktemp(char *template);

Prototype in    dir.h

Description     mktemp replaces template by a unique file name
                and returns the address of template.

                The template should be a null-terminated string
                with six trailing X's. These X's are replaced with a unique
                collection of letters plus a dot, so that there are two letters,
                a dot, and three suffix letters in the new file name.

                Starting with AA.AAA, the new file name is assigned by looking
                up the names on the disk and avoiding pre-existing names of the
                same format.

Return value    If template is well-formed, mktemp returns the
                address of the template string. Otherwise, it does not create
                or open the file.

*---------------------------------------------------------------------*/
char * _FARFUNC mktemp(char *temp)
{
        register char   *cp;
        int             len;
        int             i, j, k, l, m;

        len = strlen(temp);
        if (len < 6)
                return(0);
        cp = temp + len - 6;
        if (strcmp(cp, "XXXXXX") != 0)
                return(0);
        cp[2] = '.';
        for (i = 'A'; i <= 'Z'; i++)
        {
                cp[0] = i;
                for (j = 'A'; j <= 'Z'; j++)
                {
                        cp[1] = j;
                        for (k = 'A'; k <= 'Z'; k++)
                        {
                                cp[3] = k;
                                for (l = 'A'; l <= 'Z'; l++)
                                {
                                        cp[4] = l;
                                        for (m = 'A'; m <= 'Z'; m++)
                                        {
                                                cp[5] = m;
                                                if (access(temp, 0) == -1)
                                                        return(temp);
                                        }
                                }
                        }
                }
        }
        return(0);
}
