/* Emuvars.h

    Floating point records used by emulator and FPU exception handler.
    For Borland internal use.


    Copyright (c) Borland International 1987, 1992
    All Rights Reserved.
*/


/* from _math.h:
        An iNDP_image is put into memory by the FSTENV instruction.
*/
typedef struct
{
        unsigned        control_;
        unsigned        status_;
        unsigned        tags;
        unsigned        ip;
        unsigned        ip_opcode;
        unsigned        dp;
        unsigned        dptop;
}
        iNDP_env;

/* This must be consistent with the STRUC in emuvars.asi */

union { unsigned int control1; struct { unsigned char mask, status;} shadow;};

struct emu {
        unsigned int status;
        unsigned int control;   /* shadow mask, status */
        unsigned int adjust;
        unsigned int _8087;
        unsigned int type;
        unsigned int TOS;
        unsigned int lastSP;
        unsigned int initSP;
        iNDP_env FPExcep;
        unsigned int count1;            /* for debugging */
        unsigned int count2;            /* for debugging */
        unsigned int status2;           /* shadow status */
};

/* Caution: this is in the STACK segment, possible not the DGROUP! */
extern struct emu cdecl _emu;

