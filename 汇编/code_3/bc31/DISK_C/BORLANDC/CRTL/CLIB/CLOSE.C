/*------------------------------------------------------------------------
 * filename - close.c
 *
 * function(s)
 *        close - close a file handle
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <io.h>
#include <_io.h>
#include <RtlData.h>

#if CPM_ctlZ  /* see commentary in file "zapctlz.cas" */
#include <fcntl.h>
#endif

/*-------------------------------------------------------------------------*

Name            close - close a file handle

Usage           int close(int handle);

Prototype in    io.h

Description     close closes the  file handle indicated by handle  which is
                obtained  from a  _creat, creat,  creatnew, creattemp, dup,
                dup2, _open or open call.

Return value    Upon  successful completion,  close returns  0 otherwise,  a
                value of  -1 is returned  and, errno is  set to
                EBADF Bad file number

*---------------------------------------------------------------------------*/
int _CType _FARFUNC close (register int handle)
{
  if ((unsigned)handle >= _nfile)
    return __IOerror (e_badHandle);

#if CPM_ctlZ  /* see commentary in file "zapctlz.cas" */
  if ( !(_openfd[handle] & (O_BINARY | O_DEVICE)) && _openfd[handle] & O_CHANGED)
    __AppendCtlZ (handle);
#endif
  _RTLInstanceData(_openfd) [handle] = 0;
  return _close(handle);
}
