/*------------------------------------------------------------------------*/
/*                                                                        */
/*  TMPLINST.CPP                                                          */
/*                                                                        */
/*  Copyright Borland International 1991, 1992                            */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*  Provides instantiations of the various Object containers,             */
/*  for use in the DLL version of the class libraries.                    */
/*                                                                        */
/*------------------------------------------------------------------------*/


#if !defined( TEMPLATES )
#define TEMPLATES
#endif

#pragma option -Jgd

#include <VectImp.h>
#include <Stacks.h>
#include <Queues.h>
#include <ListImp.h>
#include <DListImp.h>
#include <Deques.h>
#include <Sets.h>

typedef BI_SDoubleListImp<void _FAR *> dummy1;
typedef BI_DoubleListIteratorImp<void _FAR *> dummy2;

typedef BI_IDequeAsVector<Object> dummy3;
typedef BI_IDequeAsVectorIterator<Object> dummy4;

typedef BI_IDequeAsDoubleList<Object> dummy5;
typedef BI_IDequeAsDoubleListIterator<Object> dummy6;

typedef BI_SListImp<void _FAR *> dummy7;
typedef BI_ListIteratorImp<void _FAR *> dummy8;

typedef BI_IQueueAsVector<Object> dummy9;
typedef BI_IQueueAsVectorIterator<Object> dummy10;

typedef BI_IQueueAsDoubleList<Object> dummy11;
typedef BI_IQueueAsDoubleListIterator<Object> dummy12;

typedef BI_IStackAsVector<Object> dummy13;
typedef BI_IStackAsVectorIterator<Object> dummy14;

typedef BI_IStackAsList<Object> dummy15;
typedef BI_IStackAsListIterator<Object> dummy16;

typedef BI_VectorImp<void _FAR *> dummy17;
typedef BI_CVectorImp<void _FAR *> dummy18;
typedef BI_SVectorImp<void _FAR *> dummy19;
typedef BI_VectorIteratorImp<void _FAR *> dummy20;

typedef BI_ISetAsVector<Object> dummy21;
typedef BI_ISetAsVectorIterator<Object> dummy22;

typedef BI_IVectorImp<Object> dummy23;
typedef BI_ICVectorImp<Object> dummy24;

