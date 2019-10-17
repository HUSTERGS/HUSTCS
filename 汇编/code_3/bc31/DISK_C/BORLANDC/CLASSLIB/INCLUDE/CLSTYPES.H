/*------------------------------------------------------------------------*/
/*                                                                        */
/*  CLSTYPES.H                                                            */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __CLSTYPES_H )
#define __CLSTYPES_H

#if !defined( __DEFS_H )
#include <_defs.h>
#endif  // __DEFS_H

#if !defined( __LIMITS_H )
#include <limits.h>
#endif

#pragma option -Vo-
#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po-
#endif

typedef unsigned int classType;
typedef unsigned int hashValueType;
typedef unsigned int sizeType;

_CLASSDEF(Object)

typedef void ( _FAR *iterFuncType )( class Object _FAR &, void _FAR * );
typedef int ( _FAR *condFuncType )( const class Object _FAR &, void _FAR * );
typedef int    countType;

enum
{
    objectClass,
    errorClass,
    sortableClass,
    stringClass,
    listElementClass,
    doubleListElementClass,
    containerClass,
    stackClass,
    queueClass,
    dequeClass,
    collectionClass,
    hashTableClass,
    bagClass,
    setClass,
    dictionaryClass,
    associationClass,
    arrayClass,
    sortedArrayClass,
    listClass,
    doubleListClass,
    timeClass,
    dateClass,
    btreeClass,
    priorityQueueClass,
    __firstOWLClass = 100,
    __lastLibClass = 255,
    __firstUserClass,
    __lastClass = UINT_MAX
};

enum ClassLib_errors
{
    __EfirstError, // don't remove
    __EDELERROR,
    __EEXPANDFS,
    __EEXPANDLB,
    __ENOMEM,
    __ENOTSORT,
    __ENOTASSOC,
    __EORDER3,
    __ENOMEMIA,
    __ENOMEMLN,
    __EPRBADCLASS,
    __EPRINCONS,
    __EBNZERODIV,
    __EBNILLLOG,
    __EBNNOMEM,
    __ERANDOM2SMALL,
    __EBNTEMPSTKOVFL,
    __EBNTEMPSTKUNFL,
    __EBN2MANYTEMPS,
    __EBN2BIG2PRINT,
    __EBNNOMEM4PRINT,
    __EBNRESULT2BIG,
    __ERNG2BIG,
    __EBNSQRTILLEGAL,
    __ElastError   // don't remove
};

void ClassLib_error( ClassLib_errors, char _FAR *addstr = 0 );

#if defined( __BCOPT__ ) && !defined( _ALLOW_po )
#pragma option -po.
#endif
#pragma option -Vo.

#endif
