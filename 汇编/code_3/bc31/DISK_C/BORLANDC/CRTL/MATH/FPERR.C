/*-----------------------------------------------------------------------*
 * filename - fperr.c
 *
 * Floating point exception handler code.
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <stdio.h>
#include <math.h>       /* for _mexcep */
#include <stdlib.h>
#include <signal.h>
#include <float.h>      /* for FPE types */

/* No denormal signal are caught here, but treat it for completeness. */
#define FPE_DENORMAL            130     /* 80x87 denormalized operand   */

typedef void cdecl (* CatcherPTR)(); /* Cleaner signal catcher declaration */

extern  CatcherPTR (* cdecl __SignalPtr)();

/*
        The only exceptions routed through this code are GENUINE floating
        point ones.  The explicitly raised SIGFPE and the integer related
        SIGFPE types DO NOT come this way.
*/
static const
        struct f_errors
        {
                int     FPEtype;
                char    *string;
        }
        fp_errors[] =
        {
                { FPE_INVALID,          "Domain" },
                { FPE_DENORMAL,         "Denormal" },
                { FPE_ZERODIVIDE,       "Divide by 0" },
                { FPE_OVERFLOW,         "Overflow" },
                { FPE_UNDERFLOW,        "Underflow" },
                { FPE_INEXACT,          "Partial loss of precision" },
                { FPE_STACKFAULT,       "Stack fault" },
        };

/*
This is an fp exception structure.  It describes the info passed
to _fperror, the purpose of which is to give a C interface to
trapping fp exceptions in a style similar to matherr().

_fperror() is called directly from the NMI handler.  Portable fp
exception handlers should call signal() instead, as that is an
ANSI function.  _fperror() is for lower level control over the
exception.

The default _fperror() only uses the type and subtype fields of
struct fpexcep.  The other fields are correctly filled in if the
coprocessor is present, but not otherwise.  They can be used to
help track down the source of the error, and the circumstances
causing the error.

_fperror() is not called for denormal exceptions, as these are
handled by the NMI handler.  The NMI handler also attempts to
correct some invalid operation exceptions, and only calls
_fperror() if it is unsuccessful in curing the problem.

_fperror() is also not called for certain Invalid Operation
exceptions.  Some of these are recoverable stack faults.

The subtype is always 1.  Future implementations may use this
field to pass more info, such as whether an INVALID exception
came from a FSQRT instruction.

Here are the reasonable alternatives for an fp exception handler.

1. Print a suitable message and exit.  This is what the default
handler does.  A program that wants to do the same may still wish
to replace the handler as it may have some additional cleaning up
to do, or may want to print a more informative message.

2. Do a long jump to safe place in the program.  If so, the
program must pay attention to all of the usual hazards of long
jumps, and in addition,
        It should call _fpreset() to reset the coprocessor or emulator.
        Since interrupts occur asynchronously, there is more danger than
        usual that the code will be left in an inconsistent state.

3. Ignore the exception.  In most cases the coprocessor will
generate infinities and NANs which are likely to cause additional
exceptions. These exceptions can be ignored more efficiently by
using _control87() to mask them.  This option does not work if
the coprocessor is being emulated, as the emulator does not support
all of the exception handling that the 8087 does.

4. Set a flag and continue.  As with case 3 above, most programs
may prefer the simpler strategy of masking the exceptions.  The
occurrence of the exception can still be detected by examining
the status word with _status87() and can be cleared with
_clear87().  This option does not work if the coprocessor is being
emulated.

5. Attempt to analyze the damage and repair it. This is nearly
impossible as the 8087 is a very complex chip with many
instructions, data types, registers, and special cases.  Some
info is provided at the _fperror() level for programs to try.

Caution: _fperror() is a huge function in all memory models.

Bugs:
Currently, only the 'type' field of the struct fpexcep is supported.
Do NOT use any of the others.
*/

struct fpexcep
{
        _mexcep type;
        int subtype;
        unsigned int opcode;    /* offending instruction */
        void huge *datap;       /* ptr to bad mem operand, if any */
        void (huge *codep)();   /* ptr to bad instruction */
};

/*
void huge cdecl _fperror(void)
*/
void near cdecl _fperror(void)
{
        struct fpexcep far *a = (struct fpexcep _ss *) _BX;

        /*
        If signal() functions are installed, use them. signal() makes
        it's presence known by filling the '__SignalPtr' function pointer
        the first time it's called.
        */

        if (__SignalPtr != NULL)                /* signals installed    */
        {
                CatcherPTR      func;

#pragma warn -pro
                func = (*__SignalPtr)(SIGFPE, SIG_DFL); /* get current  */
                (*__SignalPtr)(SIGFPE, func);           /* restore it   */

                if (func != SIG_IGN)
                {
                        if (func == SIG_DFL)
                                goto default_actions;

                        /*
                                Set a default handler and call the users
                                handler.  The user handler is responsible for
                                reenabling itself if it needs to.
                        */
                        (*__SignalPtr)(SIGFPE, SIG_DFL);
                        (* func)(SIGFPE, fp_errors[a->type-1].FPEtype);
                }
        }
#pragma warn .pro
        else    /* Default actions if signals aren't present    */
        {       /* or are defaulted.                            */
default_actions :
                /*
                        default handler treats all exceptions as fatal.
                        some won't occur unless the user enables them.
                */
                fprintf(stderr, "Floating point error: %s.\n",
                                fp_errors[a->type-1].string);

                /*
                        Now abort the program.  The exit sequence will
                        clean off the chip and restore interrupts.
                */
                abort();
                /* not reached */
        }
}
