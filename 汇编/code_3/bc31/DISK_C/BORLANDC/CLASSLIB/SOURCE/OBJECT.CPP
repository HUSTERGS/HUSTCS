/*------------------------------------------------------------------------*/
/*                                                                        */
/*  OBJECT.CPP                                                            */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( TEMPLATES )
#define TEMPLATES
#endif

#if !defined( __CLSDEFS_H )
#include <ClsDefs.h>
#endif  // __CLSDEFS_H

#if !defined( __OBJECT_H )
#include <Object.h>
#endif  // __OBJECT_H

#if !defined( __STDLIB_H )
#include <StdLib.h>
#endif  // __STDLIB_H

#if !defined( __STRSTREA_H )
#include <StrStrea.h>
#endif  // __STRSTREA_H

#if !defined( __MALLOC_H )
#include <Malloc.h>
#endif  // __MALLOC_H

Error theErrorObject;

Object *Object::ZERO = &theErrorObject;

// Error reporting

static char *errstring[__ElastError] =
{
    "firstError: [[ Error in error reporting???? ]]",
    "EDELERROR: Attemping to delete the ERROR object",
    "EXPANDFS: Attempting to expand a fixed size array.",
    "EXPANDLB: Attempt to expand lower bound of array.",
    "NOMEM: Out of Memory",
    "NOTSORT: Object must be sortable.",
    "NOTASSOC: Object must be association type.",
    "ORDER3: B-trees must be at least of order 3.",
    "NOMEMIA: No room for the item array for an InnerNode",
    "NOMEMLN: No room for item array for a LeafNode.",
    "PRBADCLASS: PersistRegister called with bad class id.",
    "PRINCONS: PersistRegister called with inconsistent values.",
    "BNZERODIV: Attempt to divide by zero.",
    "BNILLLOG: Attempt to take log of zero or negative number.",
    "BNNOMEM: No memory for a bignum.",
    "RANDOM2SMALL: Bignum RNG must be bigger than 32 bits (> 2 words).",
    "BNTEMPSTKOVFL: Too many markTempRing invocations,",
    "BNTEMPSTKUNFL: Too many releaseTempRing invocations,",
    "BN2MANYTEMPS: Ran out of temporaries on the Temp ring.",
    "BN2BIG2PRINT: Bignum has too many digits in current output base.",
    "BNNOMEM4PRINT: No memory for temporaries for printing.",
    "BNRESULT2BIG: An operation would have resulted in too large of a number.",
    "RNG2BIG: Sorry.  RNGs are limited to 32767 `digits' in size.",
    "BNSQRTILLEGAL: Trying to take sqrt of negative bignum.",
};

extern "C" void __ErrorMessage( const char _FAR * );

void _FARFUNC ClassLib_error( ClassLib_errors errnum, char _FAR *addstr )
{
    ostrstream os;
    os << endl << "Fatal error from class library:" << endl;
    os << "__E" << errstring[errnum] << endl;
    if( addstr != 0 )
        os << addstr << endl;
    os << ends;

    char *buf = os.str();
    __ErrorMessage( buf );
    delete [] buf;

    exit( errnum );
}
