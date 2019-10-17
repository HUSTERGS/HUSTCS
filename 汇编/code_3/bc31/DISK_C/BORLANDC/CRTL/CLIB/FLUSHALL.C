/*-----------------------------------------------------------------------*
 * filename - flushall.c
 *
 * function(s)
 *        flushall - clears all buffers
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdio.h>
#include <RtlData.h>

/*---------------------------------------------------------------------*

Name            flushall - clears all buffers

Usage           int flushall(void);

Prototype in    stdio.h

Description     clears all buffers associated with open input streams,
                and writes all buffers associated with open output streams
                to their respective files.  Any read operation following
                flushall reads new data into the buffers from the input
                files.

Return value    the number of open input and output streams

*---------------------------------------------------------------------*/
int _FARFUNC flushall(void)
{
    register FILE   *fp;
    register int    Nb;
    int     Cpt;
    _QRTLDataBlock;

    for (Cpt = 0, Nb = _QRTLInstanceData(_nfile), fp = _QRTLInstanceData(_streams);
         Nb--;
         fp++)

    if (fp->flags & _F_RDWR)
        {
        fflush(fp);
        Cpt++;
        }

    return(Cpt);
}
