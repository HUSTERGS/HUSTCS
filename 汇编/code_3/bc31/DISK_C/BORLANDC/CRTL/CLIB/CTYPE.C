/*------------------------------------------------------------------------
 * filename - ctype.c
 *
 * function(s)
 *        none
 *-----------------------------------------------------------------------*/

/*
 *      C/C++ Run Time Library - Version 5.0
 *
 *      Copyright (c) 1987, 1992 by Borland International
 *      All Rights Reserved.
 *
 */


/*------------------------------------------------------------------------*

Name            _ctype

Usage           char    _ctype[257];

Prototype in    ctype.h

Description     _ctype is an array of  257 characters used by the character
                classification  and character   conversion macros  (such as
                isalpha and toascii).

*------------------------------------------------------------------------*/

#include <ctype.h>

char _Cdecl _ctype[257] = {
        0,

        _IS_CTL, _IS_CTL, _IS_CTL, _IS_CTL, _IS_CTL, _IS_CTL, _IS_CTL,_IS_CTL,
        _IS_CTL, _IS_CTL|_IS_SP,
                          _IS_SP|_IS_CTL,
                                   _IS_SP|_IS_CTL,
                                            _IS_SP|_IS_CTL,
                                                     _IS_SP|_IS_CTL,
                                                              _IS_CTL,_IS_CTL,
        _IS_CTL, _IS_CTL, _IS_CTL, _IS_CTL, _IS_CTL, _IS_CTL, _IS_CTL,_IS_CTL,
        _IS_CTL, _IS_CTL, _IS_CTL, _IS_CTL, _IS_CTL, _IS_CTL, _IS_CTL,_IS_CTL,

        _IS_SP,  _IS_PUN, _IS_PUN, _IS_PUN, _IS_PUN, _IS_PUN, _IS_PUN,_IS_PUN,
        _IS_PUN, _IS_PUN, _IS_PUN, _IS_PUN, _IS_PUN, _IS_PUN, _IS_PUN,_IS_PUN,
        _IS_DIG, _IS_DIG, _IS_DIG, _IS_DIG, _IS_DIG, _IS_DIG, _IS_DIG,_IS_DIG,
        _IS_DIG, _IS_DIG, _IS_PUN, _IS_PUN, _IS_PUN, _IS_PUN, _IS_PUN,_IS_PUN,

        _IS_PUN, _IS_UPP|_IS_HEX,
                          _IS_HEX|_IS_UPP,
                                   _IS_UPP|_IS_HEX,
                                            _IS_UPP|_IS_HEX,
                                                     _IS_UPP|_IS_HEX,
                                                              _IS_UPP|_IS_HEX,
                                                                      _IS_UPP,
        _IS_UPP, _IS_UPP, _IS_UPP, _IS_UPP, _IS_UPP, _IS_UPP, _IS_UPP,_IS_UPP,
        _IS_UPP, _IS_UPP, _IS_UPP, _IS_UPP, _IS_UPP, _IS_UPP, _IS_UPP,_IS_UPP,
        _IS_UPP, _IS_UPP, _IS_UPP, _IS_PUN, _IS_PUN, _IS_PUN, _IS_PUN,_IS_PUN,

        _IS_PUN, _IS_LOW|_IS_HEX,
                          _IS_HEX|_IS_LOW,
                                   _IS_LOW|_IS_HEX,
                                            _IS_LOW|_IS_HEX,
                                                     _IS_LOW|_IS_HEX,
                                                              _IS_LOW|_IS_HEX,
                                                                      _IS_LOW,
        _IS_LOW, _IS_LOW, _IS_LOW, _IS_LOW, _IS_LOW, _IS_LOW, _IS_LOW,_IS_LOW,
        _IS_LOW, _IS_LOW, _IS_LOW, _IS_LOW, _IS_LOW, _IS_LOW, _IS_LOW,_IS_LOW,
        _IS_LOW, _IS_LOW, _IS_LOW, _IS_PUN, _IS_PUN, _IS_PUN, _IS_PUN,_IS_CTL
};
