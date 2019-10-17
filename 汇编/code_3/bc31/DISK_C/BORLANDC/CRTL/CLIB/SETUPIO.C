/*-----------------------------------------------------------------------*
 * filename - setupio.c
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#pragma inline

#include <stdio.h>
#include <_stdio.h>
#include <io.h>
#include <_io.h>

void near _setupio( void )
{
#if !defined( _RTLDLL )

    int i;

    for (i=5; i<_nfile; i++)
        {
        _openfd[i] = 0;
        _streams[i].fd = -1;
        _streams[i].token = (short) (i + _streams);
        }

    if( !isatty( stdin->fd ) )
        stdin->flags &= ~_F_TERM;
    setvbuf( stdin, NULL, (stdin->flags & _F_TERM) ? _IOLBF : _IOFBF, BUFSIZ );
    if( !isatty( stdout->fd ) )
        stdout->flags &= ~_F_TERM;
    setvbuf( stdout, NULL, (stdout->flags & _F_TERM) ? _IONBF : _IOFBF, BUFSIZ );

#endif  // _RTLDLL
}

/* #pragma startup _setupio 2 */

#pragma warn -asm
asm _INIT_      SEGMENT WORD PUBLIC 'INITDATA'
asm         db      0
asm         db      2
asm         dw      offset _setupio
asm         dw      0
asm _INIT_  ENDS
#pragma warn .asm

