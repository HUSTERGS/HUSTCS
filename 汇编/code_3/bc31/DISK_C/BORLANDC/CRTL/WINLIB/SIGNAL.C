/*----------------------------------------------------------------------*
 * filename - signal.c                                                  *
 *                                                                      *
 * function(s) signal(), raise()                                        *
 * usage                                                                *
 *              Function prototypes are in SIGNAL.H                     *
 *                                                                      *
 *      oldcatcher = signal(sig, newcatcher);                           *
 *              void (*oldcatcher)(int) Ptr to previous signal catcher  *
 *              int  sig                Signal # to install catcher for *
 *      void (*newcatcher)(int) Address of new signal catcher           *
 *                                                                      *
 *      rc = raise(sig);                                                *
 *      int  rc                 Return code, success=0, error=!0        *
 *      int  sig                Signal number to raise                  *
 *----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */

#include <process.h>    /* Get definition for _exit() */
#include <errno.h>
#include <dos.h>
#include <float.h>      /* Get definition for FPE_nn SEGV_nn ILL_nn types */
#include <string.h>
#include <signal.h>

#if defined( _Windows )
#include <_win.h>
#endif

#pragma warn -pro

#undef ANSI_CONFORMING
#undef BOUNDS_TRAP
#undef ILLEGALOP_TRAP

#define ANSI_CONFORMING
#define BOUNDS_TRAP
#define ILLEGALOP_TRAP

/*----------------------------- NOTE ! ---------------------------------

Normal ANSI operation resets ALL signals,  Microsoft(R) doesn't reset SIGFPE.
Remove ANSI_CONFORMING define for MS style SIGFPE operation.
Remove BOUNDS_TRAP define disables SIGSEGV bound violations.
Remove ILLEGALOP_TRAP define disables SIGILL illegal op violations.
Default configuration is ANSI conforming SIGFPE operation.
Default configuration enables SIGSEGV to detect BOUND violations.
Default configuration enables SIGSILL to detect illegal operations.

  ----------------------------- NOTE ! -------------------------------*/

typedef unsigned char UCHAR;

#if defined( _Windows )

#include <windows.h>

extern void (far *_FPVector)();

#else   // not _Windows

static void interrupt Int0Catcher(unsigned);
static void interrupt Int4Catcher(unsigned);

#ifdef BOUNDS_TRAP
typedef unsigned U;

static void interrupt (*BiosPrtScr)();  /* Old BIOS Int 5 vector */

static char GotInt5 = 0;
static void interrupt Int5Catcher(U, U, U, U, U, U, U, U, U, U, U, U);
#endif

#ifdef ILLEGALOP_TRAP
static void interrupt Int6Catcher(unsigned);
#endif

static void interrupt Int23Catcher(void);
static int GetIndex(int);

#endif  // _Windows

_CatcherPTR _FARFUNC signal(int, _CatcherPTR);
int _FARFUNC raise(int);

#if !defined( _Windows )
extern  _CatcherPTR      (*__SignalPtr)();
static  char            SignalPtrSet=0;
#endif

#define BogusSignal     -1      /* Flags a bogus signal type    */

/*+----------------------------------------------------------------------+
  |       Signal Dispatch, Index Generator & Signal Default Tables       |
  | *** Note : Ordering of constants in these tables MUST match          |
  +----------------------------------------------------------------------+*/
#define SIGINT_INDEX    0
#define SIGILL_INDEX    1
#define SIGFPE_INDEX    2
#define SIGSEGV_INDEX   3
#define SIGTERM_INDEX   4
#define SIGABRT_INDEX   5

static _CatcherPTR Dispatch[] =
{
        (_CatcherPTR)SIG_DFL,    /* SIGINT   (2) */
        (_CatcherPTR)SIG_DFL,    /* SIGILL   (4) */
        (_CatcherPTR)SIG_DFL,    /* SIGFPE   (8) */
        (_CatcherPTR)SIG_DFL,    /* SIGSEGV  (11)*/
        (_CatcherPTR)SIG_DFL,    /* SIGTERM  (15)*/
        (_CatcherPTR)SIG_DFL     /* SIGABRT  (22)*/
};

#ifdef _BUILDRTLDLL
static unsigned SavedDS[6] =
{
        0,                      /* SIGINT  */
        0,                      /* SIGILL  */
        0,                      /* SIGFPE  */
        0,                      /* SIGSEGV */
        0,                      /* SIGTERM */
        0                       /* SIGABRT */
};
#endif

static const UCHAR IxGen[] =
{
/* NEVER! change the ordering of these */

        SIGINT,                 /* Index 0 */
        SIGILL,                 /* Index 1 */
        SIGFPE,                 /* Index 2 */
        SIGSEGV,                /* Index 3 */
        SIGTERM,                /* Index 4 */
        SIGABRT                 /* Index 5 */
};

/*+----------------------------------------------------------------------+
  |            Table of values for EXPLICITLY raised signals             |
  |  For SIGILL, SIGFPE & SIGSEGV explicit generation may have special   |
  |  meaning to applications.  For the others use dummy 0's.             |
  +----------------------------------------------------------------------+*/
static const UCHAR ExplicitVal[] =
{
        0,                      /* SIGINT  */
        ILL_EXPLICITGEN,        /* SIGILL  */
        FPE_EXPLICITGEN,        /* SIGFPE  */
        SEGV_EXPLICITGEN,       /* SIGSEGV */
        0,                      /* SIGTERM */
        0                       /* SIGABRT */
};


#if !defined( _Windows )

#ifdef BOUNDS_TRAP
/*+----------------------------------------------------------------------+
  |  Int5Catcher() - Int 5 catcher for detecting BOUND violations on     |
  |                  80188/80186/80286/80386 & NEC V Series processors.  |
  |                                                                      |
  |  This routine is installed when any call to signal with SIGSEGV is   |
  |  specified.  THIS ROUTINE REMAINS INSTALLED AS THE INT 5 HANDLER FOR |
  |  THE REST OF THE PROGRAM DURATION.                                   |
  |  When activated this routine checks where the interrupt came from.   |
  |  If the return CS:IP points to a BOUND instruction it is assumed the |
  |  bounds check done by that instruction failed.  If the return CS:IP  |
  |  points to something other than a BOUND instruction then we assume   |
  |  that the user wanted to do a BIOS Prt-screen.  We call the old BIOS |
  |  handler in this case.                                               |
  |                                                                      |
  +----------------------------------------------------------------------+
  |                                                                      |
  |  There are some EXTREMELY rare cases where this scheme fails.        |
  |  One is when somebody does the following instruction sequence in     |
  |  their code (which I doubt has EVER been done ANYWHERE by anybody):  |
  |                                                                      |
  |               INT 5           ; Do a prt-screen                      |
  |               BOUND  ...      ; Check bounds                         |
  |                                                                      |
  |  Here the return CS:IP on the interrupt handlers stack DOES point to |
  |  a BOUND instruction, but one that hasn't been executed yet!  We     |
  |  might think the heuristic "if it's a BOUND instruction proceeded by |
  |  an INT 5 then it's not a REAL violation." would serve us well here, |
  |  but alas it doesn't because the following situation can exist.      |
  |  A program jumps to a BOUND instruction that is preceded by some     |
  |  DATA that happens to LOOK like an INT 5 instruction by accident ex: |
  |                                                                      |
  |              JMP   DOBOUND                                           |
  |  SOMEDATA    DB    0CDH, 5   ; Data that looks like an INT 5         |
  |  DOBOUND :   BOUND  ...      ; Check bounds                          |
  |                                                                      |
  |  In the above example the heuristic fails us completely.             |
  |                                                                      |
  |  Thus, we're left solidly impaled on the horns of a dilemma.  Do we  |
  |  recognize a BOUND violation where none exists, or do we ignore a    |
  |  possibly genuine BOUND violation?  Hmm... if only Prt-Scr wasn't on |
  |  INT 5.                                                              |
  |                                                                      |
  |  So... what do we do here, eh?                                       |
  |  For the sake of expedience we'll punt.  A quick look at the         |
  |  instruction pointed to by the return CS:IP will be done. If we      |
  |  see a BOUND instruction we call the handler.                        |
  |                                                                      |
  |  Avoiding these situations amounts to putting a NOP before           |
  |  any BOUND instruction that is in one of these rare situations.      |
  |  Not exactly a tough a work around!                                  |
  +----------------------------------------------------------------------+*/

#pragma argsused
static void interrupt Int5Catcher(bp,di,si,ds,es,dx,cx,bx,ax,ip,cs,flags)
unsigned bp,di,si,ds,es,dx,cx,bx,ax,ip,cs,flags;
{
        register _CatcherPTR     action;

#define BND_OPCODE      0x62

        if (*(*((UCHAR far * far *)((unsigned far *)&ip))) != BND_OPCODE)
                (*BiosPrtScr)();                     // Hand off Prt-Sc request
        else                                         // Process BOUND violation
                if ((action = Dispatch[3]) != SIG_IGN)
                {
                        if ((action == SIG_DFL) || (action == SIG_ERR))
                                _exit(1);
                        Dispatch[3] = SIG_DFL;        // Reset signal
                        (*action)(SIGSEGV, SEGV_BOUND, &bp); // Call handler
                }
}
#endif  /*** BOUNDS_TRAP ***/

#ifdef ILLEGALOP_TRAP
/*+----------------------------------------------------------------------+
  |  Int6Catcher() - Int 6 catcher for detecting illegal operations on   |
  |                  80188/80186/80286/80386 & NEC V Series processors.  |
  |                                                                      |
  |  This routine is installed when any call to signal with SIGILL is    |
  |  specified.  THIS ROUTINE REMAINS INSTALLED AS THE INT 6 HANDLER FOR |
  |  THE REST OF THE PROGRAM DURATION.                                   |
  +----------------------------------------------------------------------+*/
static void interrupt Int6Catcher(bp)
unsigned bp;
{
        register _CatcherPTR     action;

        if ((action = Dispatch[1]) != SIG_IGN)
        {
                if ((action == SIG_DFL) || (action == SIG_ERR))
                        _exit(1);
                Dispatch[1] = SIG_DFL;          /* Reset signal */
                (*action)(SIGILL, ILL_EXECUTION, &bp);  /* Call handler */
        }
}
#endif  /*** ILLEGALOP_TRAP ***/

/*+----------------------------------------------------------------------+
  |  Int0Catcher() - Integer divide by zero exception handler.           |
  |                  This routine is part of the extensions to SIGFPE    |
  |                  handling to include integer arithmetic exceptions.  |
  |                  ANSI doesn't restrict SIGFPE to just floats!        |
  |                                                                      |
  |  This routine is installed when any call to signal with SIGFPE is    |
  |  specified.  When activated this routine does the equivalent of      |
  |  raise(SIGFPE, ...).  THIS ROUTINE REMAINS INSTALLED AS THE DIVIDE   |
  |  BY ZERO HANDLER FOR THE REST OF THE PROGRAM DURATION.  If the       |
  |  application never installs a SIGFPE handler then the default action |
  |  setup by the 'C' startup code will be used.  If the app steals      |
  |  INT 0 back from us the only way the INT 0 SIGFPE code can be        |
  |  reactivated is signal(SIGFPE, ....) again!                          |
  +----------------------------------------------------------------------+*/
static void interrupt Int0Catcher(bp)
unsigned bp;
{
        register _CatcherPTR     action;

        if ((action = Dispatch[2]) != SIG_IGN)
        {
                if ((action == SIG_DFL) || (action == SIG_ERR))
                        _exit(1);
#ifdef ANSI_CONFORMING
                Dispatch[2] = SIG_DFL;          /* Reset signal */
#endif
                (*action)(SIGFPE, FPE_INTDIV0, &bp);    /* Call handler */
        }
}

/*+----------------------------------------------------------------------+
  |  Int4Catcher() - Interrupt on overflow handler.                      |
  |                  This routine is part of the extensions to SIGFPE    |
  |                  handling to include integer arithmetic exceptions.  |
  |                  ANSI doesn't restrict SIGFPE to just floats!        |
  |                                                                      |
  |  This routine is installed when any call to signal with SIGFPE is    |
  |  specified.  When activated this routine does the equivalent of      |
  |  raise(SIGFPE, ...).  THIS ROUTINE REMAINS INSTALLED AS THE Int 4    |
  |  HANDLER FOR THE REST OF THE PROGRAM DURATION.  If the               |
  |  application never installs a SIGFPE handler then the default actions|
  |  apply. If the app steals INT 4 back from us the only way the INT 4  |
  |  SIGFPE code can be reactivated is call signal(SIGFPE, ....) again!  |
  +----------------------------------------------------------------------+*/
static void interrupt Int4Catcher(bp)
unsigned bp;
{
        register _CatcherPTR     action;

        if ((action = Dispatch[2]) != SIG_IGN)
        {
                if ((action == SIG_DFL) || (action == SIG_ERR))
                        _exit(1);
#ifdef ANSI_CONFORMING
                Dispatch[2] = SIG_DFL;          /* Reset signal */
#endif
                (*action)(SIGFPE, FPE_INTOVFLOW, &bp);  /* Call handler */
        }
}

/*+----------------------------------------------------------------------+
  |          Routine intercepts int 23H and routes to user handler       |
  +----------------------------------------------------------------------+*/
static void interrupt Int23Catcher()
{
        register _CatcherPTR     action;

        if ((action = Dispatch[0]) != SIG_IGN)
        {
                if ((action == SIG_DFL) || (action == SIG_ERR))
                        _exit(1);
                Dispatch[0] = SIG_DFL;                  /* Reset signal */
                (*action)(SIGINT);                      /* Call handler */
        }
}

#endif  // !_Windows


/*+----------------------------------------------------------------------+
  |   GetIndex()  Get a DispatchTable index for specified signal type    |
  +----------------------------------------------------------------------+*/
static int GetIndex(int SigType)
{
        register int i;

        for (i = 0; i < sizeof(IxGen); i++)
                if (IxGen[i] == SigType)
                        return i;
        return -1;
}

#ifdef _Windows

extern void far _fperr( void );

#endif

/*+----------------------------------------------------------------------+
  |                Signal() - Install new signal catchers                |
  +----------------------------------------------------------------------+*/
_CatcherPTR _Cdecl _FARFUNC signal( int sig, _CatcherPTR New )
//void _Cdecl _FARFUNC (* _Cdecl _FARFUNC signal( int sig, _CatcherPTR New))(int)
{
        register int    Index;
        _CatcherPTR      OldVal;
#if !defined( _Windows )
        if (!SignalPtrSet)      /* let _fperr() know where signal is */
        {
                __SignalPtr = signal;
                SignalPtrSet = 1;
        }
#endif  // __SignalPtr not used under Windows
        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
             Get an index for the signal type, if its bad exit.
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
        if ((Index = GetIndex(sig)) == BogusSignal)
        {
                errno = EINVAL;         /* Bogus 'sig' parm was passed  */
                return SIG_ERR;
        }

        /*- - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        Install handler (SIGINT, SIGFPE & SIGSEGV are special)
        - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
        OldVal = Dispatch[Index];               /* Save the OLD handler */
        Dispatch[Index] = New;          /* Set the NEW handler  */
#ifdef _BUILDRTLDLL
        SavedDS[Index] = _SS;
#endif

#if !defined( _Windows )
        if (sig == SIGINT)
        {
                setvect(0x23, Int23Catcher); /* Take INT 23H */
        }
        else if (sig == SIGFPE)
        {
                setvect(0, Int0Catcher);     /* Take INT 0  */
                setvect(4, Int4Catcher);     /* Take INT 4  */
        }
#ifdef BOUNDS_TRAP
        else if (sig == SIGSEGV)
                if (!GotInt5)
                {
                        BiosPrtScr = getvect(5); /* Save old INT 5  */
                        setvect(5, Int5Catcher); /* Take INT 5      */
                        GotInt5 = 1;
                } else;
#endif
#ifdef ILLEGALOP_TRAP
        else  if (sig == SIGILL)
        {
                setvect(6, Int6Catcher); /* Take INT 6  */
        }
#endif

#endif  // !_Windows

        return OldVal;
}

/*+----------------------------------------------------------------------+
  |                raise() - generate a software 'event'                 |
  +----------------------------------------------------------------------+*/

#if !defined( _Windows )

static void default_action( int SigType )
{
        switch (SigType)
        {
        case SIGABRT    :
                _exit(3);
        case SIGINT     :
                geninterrupt( 0x23 );
                break;
        case SIGILL     :
        case SIGSEGV    :
        case SIGTERM    :
        case SIGFPE     :
        default         :
                _exit(1);
        }
}

#else

#define FPE_DENORMAL        0x82

#define FPE_UNEMULATED      0x87
#define FPE_SQRTNEG         0x88
#define FPE_STACKOVERFLOW   0x8a
#define FPE_STACKUNDERFLOW  0x8b

#undef  FPE_EXPLICITGEN
#define FPE_EXPLICITGEN     0x8c    /* raise( SIGFPE ); */

#pragma argsused

void _FpeDefault( int SubType )
{
static char fpMsg[] = "Floating Point: Square Root of Negative Number";
#define DIFF_LOC fpMsg + 16

        switch( SubType )
            {
            case FPE_INVALID:
                strcpy( DIFF_LOC, "Invalid" );
                break;
            case FPE_DENORMAL:
                strcpy( DIFF_LOC, "DeNormal" );
                break;
            case FPE_ZERODIVIDE:
                strcpy( DIFF_LOC, "Divide by Zero" );
                break;
            case FPE_OVERFLOW:
                strcpy( DIFF_LOC, "Overflow" );
                break;
            case FPE_UNDERFLOW:
                strcpy( DIFF_LOC, "Underflow" );
                break;
            case FPE_INEXACT:
                strcpy( DIFF_LOC, "Inexact" );
                break;
            case FPE_UNEMULATED:
                strcpy( DIFF_LOC, "Unemulated" );
                break;
            case FPE_SQRTNEG:   // no copy here: message is already right
                break;
            case FPE_STACKOVERFLOW:
                strcpy( DIFF_LOC, "Stack Overflow" );
                break;
            case FPE_STACKUNDERFLOW:
                strcpy( DIFF_LOC, "Stack Underflow" );
                break;
            case FPE_EXPLICITGEN:
                strcpy( DIFF_LOC, "Exception Raised" );
                break;
            }
        _errorExitBox( fpMsg, 3 );
}

static void default_action( int SigType )
{
        switch (SigType)
        {
        case SIGABRT    :
                _errorExitBox( "Program Aborted", 3 );
                break;
        case SIGINT     :
                geninterrupt( 0x23 );
                break;
        case SIGILL     :
                _errorExitBox( "Illegal Instruction", 1 );
                break;
        case SIGSEGV    :
                _errorExitBox( "Segment Violation", 1 );
                break;
        case SIGFPE     :
                _errorExitBox( "Floating Point Trap", 1 );
                break;
        case SIGTERM    :
                _errorExitBox( "Program Terminated", 1 );
                break;
        default         :
                _errorExitBox( "Abnormal Program Termination", 1 );
                break;
        }
}

#endif  // !_Windows

int _FARFUNC raise(int SigType)
{
        int             Index;
        _CatcherPTR     action;
#ifdef _BUILDRTLDLL
        unsigned        LocalDS;
#endif

        if ((Index = GetIndex(SigType)) == BogusSignal)
                return 1;

        if ((action = Dispatch[Index]) != SIG_IGN)
                if (action == SIG_DFL)
#ifdef _Windows
                        if( SigType == SIGFPE )
                            _FpeDefault( FPE_EXPLICITGEN );
                        else
#endif
                            default_action( SigType );
                else
                {       /*
                        Call user routine. Add optional parameter
                        specifing that the signal was raised explicitly
                        rather than asynchronously.
                        */
#ifdef ANSI_CONFORMING
                        Dispatch[Index] = SIG_DFL; /* Always default (ANSI) */
#else
                        if (SigType != SIGFPE)     /* Maybe default (MS) */
                                Dispatch[Index] = SIG_DFL;
#endif

#ifdef _BUILDRTLDLL
                        LocalDS = _DS;
                        _DS = SavedDS[Index];
#endif
                        (*action)(SigType, ExplicitVal[Index]);
#ifdef _BUILDRTLDLL
                        _DS = LocalDS;
#endif
                }
        return 0;
}

#ifdef _Windows

void _FARFUNC _FpeHandler(int subcode)
{
        register _CatcherPTR    action;
#ifdef _BUILDRTLDLL
        unsigned                LocalDS;
#endif

        if ((action = Dispatch[2]) != SIG_IGN)
        {
                if ((action == SIG_DFL) || (action == SIG_ERR))
                        _FpeDefault(subcode);
#ifdef ANSI_CONFORMING
                Dispatch[2] = SIG_DFL;          /* Reset signal */
#endif
#ifdef _BUILDRTLDLL
                LocalDS = _DS;
                _DS = SavedDS[2];
#endif
                (*action)(SIGFPE, subcode);    /* Call handler */
#ifdef _BUILDRTLDLL
                _DS = LocalDS;
#endif
        }
}

#endif // _Windows

#pragma warn .pro
