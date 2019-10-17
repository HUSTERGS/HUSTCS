/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     stsync.cpp                                               |*/
/*|                                                              |*/
/*|     Class ios                                                |*/
/*|          void ios::sync_with_stdio()                         |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1990, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <stdiostr.h>

extern streambuf *__stdin_streambuf;
extern streambuf *__stdout_streambuf;
extern streambuf *__stderr_streambuf;

static short already_done = 0;

void ios::sync_with_stdio()
{
    if( already_done )
        return;     // we only do this once!
    already_done = 1;

    cin.sync();
    cout.flush();
    clog.flush();

    // recover the streambuf space
    cin.rdbuf()->streambuf::~streambuf();
    cout.rdbuf()->streambuf::~streambuf();
    clog.rdbuf()->streambuf::~streambuf();

    // make stdiobufs for the stdio files
    __stdin_streambuf =  new stdiobuf(stdin);
    __stdout_streambuf = new stdiobuf(stdout);
    __stderr_streambuf = new stdiobuf(stderr);

    cin  = __stdin_streambuf;
    cout = __stdout_streambuf;
    cerr = __stderr_streambuf;
    clog = __stderr_streambuf;

    cout.setf(ios::unitbuf);
    clog.setf(ios::unitbuf);
}
