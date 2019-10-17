/*------------------------------------------------------------------------
 * filename - _math.h
 *
 *      Access to the Floating Point Support Library.
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

#if !defined(__MATH_H)
#include <math.h>
#endif

/*
 * Parameters must be supplied on the iNDP stack and are consumed.
 * Result will be in the iNDP TOS.
*/

/*
 *  An iNDP_image is put into memory by the FSTENV instruction.
*/

typedef struct
{
    unsigned  control;
    unsigned  status_;
    unsigned  tags;
    unsigned  ip;
    unsigned  ip_opcode;
    unsigned  dp;
    unsigned  dptop;
}
    iNDP_env;

#if defined(__OS2__) || defined(_Windows)

#ifdef __cplusplus
extern "C" {
#endif
void near _f87_Sine(void);
void near _f87_Cosine(void);
void near _f87_Tangent(void);
void near _f87_ArcTan(void);

void near _f87_Log(void);
void near _f87_Log2(void);
void near _f87_Log10(void);

void near _f87_Exp(void);
void near _f87_Exp2(void);
void near _f87_Exp10(void);

#ifdef __cplusplus
}
#endif

#else   /* not __OS2__ or _Windows */

/*
These shortcut codes are like emulated 8087 instructions, but they enter
the emulator at a level which bypasses simulation of that chip's status
registers.  Therefore the emulation is not strict.  Also the addressing
modes are fixed, none of the '87 flexibility is available (nor do you pay
the time penalty of emulating the instruction decode).  They are designed
to match the sequences the compiler frequently generates.

These shortcuts MUST be called in a fixed pattern.  For most operations
the sequence is:
*/

#define _FAST_(shortCode)  int  3Eh;  asm db    shortCode, 90h

/*
A few operations require a 4-byte sequence with two trailing bytes.
The second trailing byte supplies a register count or some other parameter.
*/

#define _FAST4_(shortCode,rNum)   int   3Eh; asm db  shortCode, rNum

#define shortcutInt     0x3E

typedef enum  _shortCodes_
{
        _FSCALEAX_      = 0xA2,
        _FCOM_          = 0xA4,
        _FSTCWAX_       = 0xA6,
        _FLDSTN_        = 0xA8,         /* FAST4        */

        _FASC2BIN_      = 0xAA,
        _FBIN2ASC_      = 0xAC,

        _FNINIT_        = 0xAE,
        _FLDCW_         = 0xB0,
        _FSTSWAX_       = 0xB2,
        _FERROR_        = 0xB4,

        _FFRAC_         = 0xB6,

        _FSTPRI_        = 0xB8,
        _FSTPRUI_       = 0xBA,
        _FSTPRL_        = 0xBC,
        _FSTPRUL_       = 0xBE,

        _FSTPTI_        = 0xC0,
        _FSTPTUI_       = 0xC2,
        _FSTPTL_        = 0xC4,
        _FSTPTUL_       = 0xC6,

        _FLDI_          = 0xC8,
        _FLDUI_         = 0xCA,
        _FLDL_          = 0xCC,
        _FLDUL_         = 0xCE,

        _FLDLEC_        = 0xD0,
        _FLDULEC_       = 0xD2,

        _FLDSDA_        = 0xD4,
        _FLDSEC_        = 0xD6,
        _FSTPSDA_       = 0xD8,

        _FXCHN_         = 0xDA,         /* FAST4        */

/*  The following 8 compiler-support short-cuts are supported by the
    emulator even when true emulation is used and the other short-cuts
    are suppressed.
*/
        _FSPILLN_       = 0xDC,         /* FAST4        */
        _FRELOADN_      = 0xDE,         /* FAST4        */

        _FCMPPS_        = 0xE0,
        _FCMPPD_        = 0xE2,
        _FCMPP_         = 0xE4,
        _FCMP_          = 0xE6,
        _FTST_          = 0xE8,
        _FXAM_          = 0xEA,

/*  The following 10 transcendental short-cuts are supported by the
    emulator even when true emulation is used and the other short-cuts
    are suppressed.
*/
        _FSIN_          = 0xEC,
        _FCOS_          = 0xEE,
        _FTAN_          = 0xF0,
        _FATAN_         = 0xF2,
        _FLOG_          = 0xF4,
        _FLOG2_         = 0xF6,
        _FLOG10_        = 0xF8,
        _FEXP_          = 0xFA,
        _FEXP2_         = 0xFC,
        _FEXP10_        = 0xFE,

/* negatives have no simple in-line equivalents, though some (like FXCHN)
   will be patched in-line.  Positives can be inline patched by a uniform
   look-up table.
*/
        _FSADD_         = 0x00,
        _FSSUB_         = 0x02,
        _FSSUBR_        = 0x04,
        _FSMUL_         = 0x06,
        _FSDIV_         = 0x08,
        _FSDIVR_        = 0x0A,
        _FSSQRT_        = 0x0C,

        _FLDSES_        = 0x0E,
        _FLDSCS_        = 0x10,
        _FLDSSS_        = 0x12,
        _FLDSDS_        = 0x14,

        _FLDDES_        = 0x16,
        _FLDDCS_        = 0x18,
        _FLDDSS_        = 0x1A,
        _FLDDDS_        = 0x1C,

        _FLDXES_        = 0x1E,
        _FLDXCS_        = 0x20,
        _FLDXSS_        = 0x22,
        _FLDXDS_        = 0x24,

        _FLDCES_        = 0x26,
        _FLDCCS_        = 0x28,
        _FLDCSS_        = 0x2A,
        _FLDCDS_        = 0x2C,

        _FLDBXES_       = 0x2E,
        _FLDBXCS_       = 0x30,
        _FLDBXSS_       = 0x32,
        _FLDBXDS_       = 0x34,

        _FSTPSES_       = 0x36,
        _FSTPSCS_       = 0x38,
        _FSTPSSS_       = 0x3A,
        _FSTPSDS_       = 0x3C,

        _FSTPDES_       = 0x3E,
        _FSTPDCS_       = 0x40,
        _FSTPDSS_       = 0x42,
        _FSTPDDS_       = 0x44,

        _FSTPXES_       = 0x46,
        _FSTPXCS_       = 0x48,
        _FSTPXSS_       = 0x4A,
        _FSTPXDS_       = 0x4C,

        _FSTPCES_       = 0x4E,
        _FSTPCCS_       = 0x50,
        _FSTPCSS_       = 0x52,
        _FSTPCDS_       = 0x54,

        _FADD_          = 0x56,
        _FSUB_          = 0x58,
        _FSUBR_         = 0x5A,
        _FMUL_          = 0x5C,
        _FDIV_          = 0x5E,
        _FDIVR_         = 0x60,
        _FSQRT_         = 0x62,

        _FCHS_          = 0x64,
        _FABS_          = 0x66,

        _FLDST0_        = 0x68,
        _FSTPST0_       = 0x6A,
        _FXCH_          = 0x6C,
        _FRNDINT_       = 0x6E,

        _FLDZ_          = 0x70,
        _FLD1_          = 0x72,
        _FPREM_         = 0x74,
        _FXTRACT_       = 0x76,
        _FLDPI_         = 0x78,
};
#endif  /* not __OS2__ */

/* The flag _8087 says whether coprocessor is in use.
   It is only valid floating point is used in the program.
   The values are:
     0 - nocoprocessor, or ignored because of SET 87=N.
     1 - 8087 or 80187, or using coprocessor because of SET 87=Y.
     2 - 80287
     3 - 80387
*/

extern int cdecl _8087;

/* some 80387 opcodes */

#define OPCODE_FSIN             0D9h, 0FEh
#define OPCODE_FCOS             0D9h, 0FFh
#define OPCODE_FSINCOS          0D9h, 0FBh
#define OPCODE_FSTSWAX          0DFh, 0E0h

#ifdef __cplusplus
extern "C" {
#endif

/* helper functions and variables for math library */

void pascal near        __expld(void);
void pascal near        __round(void);
long double pascal near __pow10(int __p);

extern char *_mathwhy[];

#ifdef __cplusplus
}
#endif

#if     MSC
#include "msc.h"
#endif

/*  The customary matherr() exception handler for math functions is
    not compatible with the x3j11 draft standard for C.  _matherr() is
    provided as a compromise.
*/

double _Cdecl _FARFUNC _matherr(_mexcep __why, char _FAR *__fun, double _FAR *__arg1p,
                       double  _FAR *__arg2p, double  __retval);
long double _Cdecl _FARFUNC __matherrl(_mexcep __why, char _FAR *__fun,
                        long double _FAR *__arg1p, long double  _FAR *__arg2p,
                        long double  __retval);
