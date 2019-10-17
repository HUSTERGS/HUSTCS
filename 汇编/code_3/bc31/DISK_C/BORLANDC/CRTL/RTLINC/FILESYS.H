/*------------------------------------------------------------------------
 * filename - filesys.h
 *
 *      interface to file system
 *-----------------------------------------------------------------------*/

/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     C/C++ Run Time Library - Version 4.0                     |*/
/*|                                                              |*/
/*|                                                              |*/
/*|     Copyright (c) 1987, 1991 by Borland International        |*/
/*|     All Rights Reserved.                                     |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

/*
 * The following declarations will need to be adjusted for the
 * operating system in use.
 *
 * We assume a Unix-like model.  If yours is very different, additional
 * interface functions will be needed, or some rewriting of the
 * implementation which uses these functions and data.
 */

#include <fcntl.h>
#include <sys/stat.h>
#include <io.h>

// Assume the following OS routines return this value on error,
// and that this value is NOT ZERO.
// Assume they also set errno when needed.
const int OS_err = -1;  

// open file, return fd, open mode 'how', protection 'prot'
//extern "C" int open(const char *name, int how, int prot);
// 'how' bits, these values for SUN OS (like BSD Unix)
const int O_rdonly = O_RDONLY;  // read only
const int O_wronly = O_WRONLY;  // write only
const int O_rdwr   = O_RDWR;    // read and write
const int O_append = O_APPEND;  // append at each write
const int O_create = O_CREAT;   // create file if it does not exist
const int O_trunc  = O_TRUNC;   // truncate file length to 0 if exists
const int O_excl   = O_EXCL;    // error if create and file exists

// close file, return 0 on success
//extern "C" int close(int fd);

// read 'count' chars into 'buf', return number read
//extern "C" int read(int fd, void* buf, unsigned count);

// write 'count' chars from 'buf', return number written
//extern "C" int write(int fd, void* buf, unsigned count);

// seek to 'offset' relative to 'whence',
// return new file position, long(OS_err) on error (set errno)
//extern "C" long lseek(int fd, long offset, int whence);
// values for 'whence':
const int L_set = SEEK_SET;     // from beginning
const int L_cur = SEEK_CUR;     // from current pos
const int L_end = SEEK_END;     // from end


// natural size for a file buffer, plus 4 for putback
const int B_size = 516;

// default protection bits
const int P_default = S_IREAD | S_IWRITE;


// fd numbers for standard in, out, error
const int F_stdin = 0;
const int F_stdout = 1;
const int F_stderr = 2;
