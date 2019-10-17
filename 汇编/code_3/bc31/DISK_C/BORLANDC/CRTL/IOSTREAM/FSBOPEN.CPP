/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     fsbopen.cpp                                              |*/
/*|                                                              |*/
/*|     Class filebuf                                            |*/
/*|          filebuf* filebuf::open( const char *, int, int )    |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <ioconfig.h>
#include "filesys.h"
#include <fstream.h>

/*
 * Open named file with mode and protection, attach to this filebuf.
 * We make no assumptions about the mode bits and what ::open() wants to
 * see, except we assume that some mapping is possible.
 * "prot" is supplied by user, assumed consistent with operating system.
 * Note checks against OS_err, assumed to be operating system error return.
 */

filebuf* filebuf::open(const char* name, int m, int prot)
{
    if( opened  || ! m )
        return 0;

    // set up "how" parameter to system ::open()
    // we let the OS decide whether the combination is legal
    int how;
    if( m & ios::out )
        {
        if( m & ios::in )
            how = O_rdwr;
        else
            how = O_wronly;
        if( ! (m & ios::nocreate) )
            {
            how |= O_create;
            if( m & ios::noreplace )
                how |= O_excl;
            }
        if( m & ios::trunc )
            how |= O_trunc;
        }
    else if( m & ios::in )
        how = O_rdonly;
    else
        return 0;   // must specfify in, out, or in/out
    if( m & ios::binary )
        how |= O_BINARY;
    else
        how |= O_TEXT;
    if( m & ios::app )
        how |= O_append;

    // now try to open
    int f = ::open(name, how, prot);
    if( f == OS_err )
        return 0;

    // finish up
    xfd = f;
    opened = 1;
    mode = m;
    last_seek = ::lseek(f, 0L, (m & ios::ate) ? L_end : L_set);
    if( last_seek == long(OS_err) )
        return 0;

    char *b = base();       // buffer address
    int pb = b ? ((blen() > 8) ? 4 : 1) : 0;    // putback area size
    setp(b+pb, b+pb);
    setg(b, b+pb, b+pb);

    return this;
}


