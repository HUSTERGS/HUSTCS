/*  setjmp.h

    Defines typedef and functions for setjmp/longjmp.

    Copyright (c) 1987, 1992 by Borland International
    All Rights Reserved.
*/

#ifndef __SETJMP_H
#define __SETJMP_H

#if !defined(___DEFS_H)
#include <_defs.h>
#endif

typedef struct __jmp_buf {
    unsigned    j_sp;
    unsigned    j_ss;
    unsigned    j_flag;
    unsigned    j_cs;
    unsigned    j_ip;
    unsigned    j_bp;
    unsigned    j_di;
    unsigned    j_es;
    unsigned    j_si;
    unsigned    j_ds;
}   jmp_buf[1];

#ifdef __cplusplus
extern "C" {
#endif

#if !defined( _Windows )
void    _CType longjmp(jmp_buf __jmpb, int __retval);
int     _CType setjmp(jmp_buf __jmpb);
#else
void far pascal longjmp( struct __jmp_buf far *__jmpb, int __retval );
int far pascal setjmp( struct __jmp_buf far *__jmpb);
#endif

#ifdef __cplusplus
}
#endif

#endif

