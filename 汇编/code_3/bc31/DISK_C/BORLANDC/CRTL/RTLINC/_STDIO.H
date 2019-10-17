/*------------------------------------------------------------------------
 * filename - _stdio.h
 *
 *      Definitions for stream input/output.
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

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif
size_t  pascal near __fputn  (const void *__ptr, size_t __n, FILE *__fp);
char  * pascal near __mkname (char *__s, char *__pfx, unsigned __num);
char  * pascal near __tmpnam (char *__s, unsigned *__numP);
FILE  * pascal near __openfp (FILE *__fp, const char *__fname,
                const char *__type, int __shflag);
FILE  * pascal near __getfp  (void);

int near _Cdecl _Ngetche    (void);
int near _Cdecl _Nungetch   (int __ch);
int near _Cdecl _Nfgetc     (FILE *__stream);
int near _Cdecl _Nungetc    (int __c, FILE *__stream);

#ifdef __OS2__

void _lock_all_streams   (void);
void _unlock_all_streams (void);
void _lock_stream        (FILE *__stream);
void _unlock_stream      (FILE *__stream);

int  _flushall           (void);
int  _lgetc              (FILE  *__stream );
int  _lputc              (int __ch, FILE *__stream );

#endif

#ifdef __cplusplus
}
#endif
