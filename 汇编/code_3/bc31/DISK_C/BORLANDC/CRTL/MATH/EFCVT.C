/*------------------------------------------------------------------------
 * filename - efcvt.c
 *
 * function(s)
 *        ecvt - converts a floating-point number to a string
 *        fcvt - converts a floating-point number to a string
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


#include <stdlib.h>
#include <_printf.h>
#include <RtlData.h>

#if !defined( _RTLDLL )
static  char    _cvtBuf [__XCVTDIG__ + 2];
#endif


/*--------------------------------------------------------------------------*

Name            ecvt - converts a floating-point number to a string

Usage           char *ecvt(double value, int ndigit, int *decpt, int *sign);
                char *fcvt(double value, int ndigit, int *decpt, int *sign);

Prototype in    stdlib.h

Description     ecvt converts  value to a null-terminated  string of ndigit
                digits and returns a pointer to the string. The position of
                the decimal point  relative to the beginning of  the string
                is stored  indirectly through decpt  (a negative value  for
                decpt means  to the left   of the returned  digits). If the
                sign of the result is negative, the word pointed to by sign
                is  non-zero; otherwise,  it is  0. The  low-order digit is
                rounded.

                fcvt is identical to ecvt except that the correct digit has
                been rounded for  FORTRAN F-format output of the  number of
                digits specified by ndigit.

Return value    The return  values of ecvt   and fcvt point  to static data
                whose content is overwritten by each call to ecvt or fcvt.

*---------------------------------------------------------------------------*/
char  _FAR * ecvt  (double value, int nDig, int _FAR *decP, int _FAR *signP )

/*
The double (value) is converted to a decimal string (_cvtBuf) of up to 18
digits, a sign (*signP, false == positive) and a decimal exponent (*decP).

"nDig" specifies the number of significant digits.
  If nDig < 1  then nDig = 1.
  If nDig > 18 then nDig = 18.

The string is in ASCIIZ form.  The string is padded with zeros to the
right to fill in the requested number of digits or decimal places.

The exponent *decP is calculated as if the decimal point were at the left
(most significant) end of the string (there is no "." character in the
string).

If the value was zero then the exponent is 0 and the string is all "0".  If
the value was infinite or NAN then the exponent is 999 and the string is
all "9".

The conversion to a numeral string is done in __xcvt, with only some
parameter checking and result storage needs to be done here.

The return value is a pointer to _cvtBuf.
*/

{
    *decP = __xcvt (& value,
                   (nDig > 1) ? nDig : 1,
                   signP,
                   _RTLInstanceData(_cvtBuf),
                   F_8byteFloat
                   );
    return _RTLInstanceData(_cvtBuf);
}

/*---------------------------------------------------------------------*

Name            fcvt - converts a floating-point number to a string

Usage           char *fcvt(double value, int ndigit, int *decpt, int *sign);

Prototype in    stdlib.h

Description     see ecvt

*---------------------------------------------------------------------*/
char  _FAR * fcvt (double value, int nDig, int _FAR *decP, int _FAR *signP )

/*
Identical to ecvt except for the interpretation of nDig.

"nDig" specifies the number of significant digits following the
  decimal point.
  If nDig < 1  then nDig = 1.
  If nDig > 18 then nDig = 18.

Also, the total of digits both left and right of the decimal point shall
not exceed 18.
*/

{
    *decP = __xcvt ( &value,
                     (nDig > 0) ? -nDig : 0,
                     signP,
                     _RTLInstanceData(_cvtBuf),
                     F_8byteFloat);
    return _RTLInstanceData(_cvtBuf);
}
