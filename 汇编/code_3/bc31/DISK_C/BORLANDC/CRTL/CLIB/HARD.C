/*-----------------------------------------------------------------------*
 * filename - hard.c
 *
 * function(s)
 *        harderr    - establishes a hardware error handler
 *        hardresume - hardware error handler function
 *        hardretn   - hardware error handler function
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <dos.h>

extern void    __harderr(int (*fptr)());        /* in harderr.cas */

/*-----------------------------------------------------------------------*

Name            harderr - establishes a hardware error handler

Usage           void harderr(int (*fptr)());

Related
functions usage void hardresume(int rescode);
                void hardretn(int errcode);

Prototype in    dos.h

Description     harderr establishes a hardware error handler for the
                current program. This handler is invoked whenever an interrupt
                0x24 occurs. (See the MS-DOS Programmer's Reference Manual for a
                discussion of the interrupt.)  The harderr macro in dos.h maps
                to the harderr function.

                The function pointed to by fptr will be called when such an
                interrupt occurs. The handler function will be called with the
                following arguments:

                   handler(int errval, int ax, int bp, int si);

                errval is the error code set in the DI register by MS-DOS.
                ax, bp, and si are the values MS-DOS sets for the AX,
                BP, and SI registers, respectively.

                ax indicates whether a disk error or other device error was
                encountered. If ax is non-negative, a disk error was
                encountered; otherwise, the error was a device error. For a
                disk error, ax ANDed with 0x00FF will give the failing drive
                number (1 = A, 2 = B, etc.).

                bp and si together point to the device driver header of
                the failing driver.

                The named function is not called directly. harderr establishes
                a DOS interrupt handler that calls the function.

                peek and peekb can be used to retrieve device information from
                this driver header. bp is the segment address, and si is
                the offset.

                The handler may issue bdos calls 1 through 0xC, but any other
                bdos call will corrupt MS-DOS. In particular, any of the C
                standard I/O or UNIX-emulation I/O calls may not be used.

                The driver header may not be altered via poke or pokeb.

                The error handler may return or call hardresume to return to
                MS-DOS. The return value of the handler or rescode (result code)
                of hardresume contains an abort (2), retry (1), or ignore (0)
                indicator. The abort is accomplished by invoking DOS interrupt
                0x23, the control-break interrupt.

                The error handler may return directly to the application
                program by calling hardretn.

                The Microsoft-compatible _harderr function is similar
                to harderr, except that the handler is always a far
                function, the handler is called with slightly different
                parameters, and the handler is not expected to return
                a value:

                        void far handler (unsigned deverror, unsigned errcode,
                                        unsigned far *devhdr);


Return value    The handler must return 0 for ignore, 1 for retry,
                2 for abort, and 3 for fail (DOS 3.0 or later).  harderr
                itself does not return a value.

Portability     Unique to MS-DOS.

See also        peek, poke, setjmp

*------------------------------------------------------------------------*/
void _CType harderr(int (*fptr)())
{
    __harderr(fptr);
}

/*-----------------------------------------------------------------------*

Name            hardresume - hardware error handler function

Usage           void hardresume(int rescode);

Prototype in    dos.h

Description     see harderr

*------------------------------------------------------------------------*/
void _CType hardresume(int axret)
{
    _hardresume(axret);
}

/*-----------------------------------------------------------------------*

Name            hardretn - hardware error handler function

Usage           void hardretn(int errcode);

Prototype in    dos.h

Description     see harderr

*------------------------------------------------------------------------*/
void _CType hardretn(int retn)
{
    _hardretn(retn);
}
