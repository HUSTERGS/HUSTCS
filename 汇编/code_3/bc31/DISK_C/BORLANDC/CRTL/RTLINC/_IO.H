/*------------------------------------------------------------------------
 * filename - _io.h
 *
 *      Definitions for low level I/O functions.
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


#if !defined( __DEFS_H )
#include <_defs.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
void             __ErrorMessage(const char *__message);
int  pascal near __IOerror    (int  __doserror);
int  pascal near __DOSerror   (int  __doserror);
long pascal near __DOStimeToU     (unsigned long __timeStamp);
int  pascal near __isDST      (unsigned __hour,  unsigned __yday,
                   unsigned __month, unsigned __year);

/* ANSI-safe entry points for low-level I/O functions.
 */
int  _CType __read   (int __handle, void *__buf, unsigned __len);
int  _CType __write  (int __handle, const void *__buf, unsigned __len);

/* DOS-level functions that are not documented.
 */
unsigned    _Cdecl _dos_lock( int __fd, long __off, long __len );
unsigned    _Cdecl _dos_seek( int __fd, long __offset, int __kind,
                   long _FAR *__newoffset );
unsigned    _Cdecl _dos_unlock( int __fd, long __off, long __len );

#if CPM_ctlZ
void pascal near __AppendCtlZ     (int __handle);
void pascal near __TrimCtlZ       (int __fildes);
#endif
#ifdef __cplusplus
}
#endif

/* And now the DOS error list.
*/
#define e_badFunction            1
#define e_fileNotFound           2
#define e_pathNotFound           3
#define e_tooManyOpen            4
#define e_accessDenied           5
#define e_badHandle              6
#define e_mcbDestroyed           7
#define e_outOfMemory            8
#define e_badBlock               9
#define e_badEnviron            10
#define e_badFormat             11
#define e_badAccess             12
#define e_badData               13
/* reserved                     14 */
#define e_badDrive              15
#define e_isCurrentDir          16
#define e_notSameDevice         17
#define e_noMoreFiles           18
#define e_readOnly              19
#define e_unknownUnit           20
#define e_notReady              21
#define e_unknownCommand        22
#define e_dataError             23
#define e_badRequestLength      24
#define e_seekError             25
#define e_unknownMedia          26
#define e_sectorNotFound        27
#define e_outOfPaper            28
#define e_writeFault            29
#define e_readFault             30
#define e_generalFault          31
#define e_sharing               32
#define e_lock                  33
#define e_diskChange            34
#define e_FCBunavailable        35
#define e_sharingOverflow       36
/* reserved                     37..49 */
#define e_networkUnsupported    50
#define e_notListening          51
#define e_dupNameOnNet          52
#define e_nameNotOnNet          53
#define e_netBusy               54
#define e_netDeviceGone         55
#define e_netCommandLimit       56
#define e_netHardError          57
#define e_wrongNetResponse      58
#define e_netError              59
#define e_remoteIncompatible    60
#define e_printQueueFull        61
#define e_printFileSpace        62
#define e_printFileDeleted      63
#define e_netNameDeleted        64
#define e_netAccessDenied       65              /* same as 5 */
#define e_netDeviceWrong        66
#define e_netNameNotFound       67              /* same as 53 */
#define e_netNameLimit          68
#define e_netBIOSlimit          69
#define e_paused                70
#define e_netRequestRefused     71
#define e_redirectionPaused     72
/* reserved                     73..79 */
#define e_fileExists            80
/* reserved                     81 */
#define e_cannotMake            82
#define e_failInt24             83
#define e_redirectionLimit      84
#define e_dupRedirection        85
#define e_password              86
#define e_parameter             87
#define e_netDevice             88

#define e_dosFinalError         88

/* Array of open file flags.
 */
extern  unsigned int    _Cdecl _openfd[];

#ifdef __OS2__

/* Standard "one entry, one exit" macro for serialization exits.
 */
#define RETURN(code)    {rc=(code); goto exit;}

#endif __OS2__
