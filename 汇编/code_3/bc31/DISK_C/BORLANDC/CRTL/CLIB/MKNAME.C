/*-----------------------------------------------------------------------*
 * filename - mkname.c
 *
 * function(s)
 *        __mkname - builds a file name of the form TMPXXXXX.$$$
 *        __tmpnam - builds a unique file name
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <_printf.h>
#include <stdio.h>
#include <string.h>
#include <dos.h>
#include <RtlData.h>

#if !defined( _RTLDLL )
static char    _template[L_tmpnam];
#endif

/*---------------------------------------------------------------------*

Name            __mkname - builds a file name of the form TMPXXXXX.$$$

Usage           char * pascal __mkname(char *s, char *prefix, unsigned num);

Prototype in    _stdio.h

Description     __mkname constructs a file name of the form pfxXXXXX.$$$.
                The prefix can be a string of up to 3 characters; if NULL,
                "TMP" is used.  The XXXXX is the ASCII decimal equivalent
                of the 'num' serial number.  The filename is stored
                at s, or in an internal static buffer if s is NULL.

Return value    A pointer to the constructed filename.

*---------------------------------------------------------------------*/
char * pascal near __mkname(char *s, char *prefix, unsigned num)
{
        /* If no buffer provided, use internal template (static buffer)
         */
        if (s == NULL)
                s = _RTLInstanceData(_template);

        /* A temporary name is build as follows: pfxXXXXX.$$$
         * where pfx is the prefix (up to three characters),
         * and XXXXX is the ASCII decimal equivalent of num.
         */
        __utoa(num, _stpcpy(s, prefix == NULL ? "TMP" : prefix));
        strcat(s, ".$$$");
        return (s);
}

/*---------------------------------------------------------------------*

Name            __tmpnam - builds a unique file name

Usage           char *__tmpnam(char *s,unsigned *numP);

Prototype in    stdio.h

Description     __tmpnam generates a temporary filename that does not
                conflict with any existing files.  The name is stored
                in the buffer pointed by s.  If s is null, the name
                is stored in an internal static buffer.  If s is not
                NULL, it must point to a buffer of at least L__tmpnam
                bytes (L__tmpnam is defined in stdio.h).  Up to TMP_MAX
                unique filenames can be generated before names will
                be reused.

                The filename generated has the form TMPXXXXX.$$$,
                where XXXXX is the ASCII decimal equivalent of
                the file's "serial number".  NumP points to this
                serial number; this number can be passed to __mkname
                to reconstruct the filename.

                The function returns when it generates a filename
                that does not exist or cannot be accessed.

Return value    If successful, a pointer to the generated name.
                If a unique filename cannot be generated, NULL is
                returned.

*---------------------------------------------------------------------*/
char * pascal near __tmpnam(char *s, unsigned *numP)
{
        unsigned attr;

        do
                s = __mkname(s, (char *) NULL, *numP += (*numP == -1U) ? 2 : 1);
        while (_dos_getfileattr(s, &attr) == 0);

        return (s);
}
