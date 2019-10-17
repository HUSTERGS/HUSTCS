/*------------------------------------------------------------------------
 * filename - _vector.h
 *
 *      Typedefs and constants for use by compiler helper functions
 *      for working on arrays of classes
 *-----------------------------------------------------------------------*/

/*[]------------------------------------------------------------[]*/
/*|                                                              |*/
/*|     C/C++ Run Time Library - Version 4.0                     |*/
/*|                                                              |*/
/*|                                                              |*/
/*|     Copyright (c) 1991 by Borland International              |*/
/*|     All Rights Reserved.                                     |*/
/*|                                                              |*/
/*[]------------------------------------------------------------[]*/

// VDEL
typedef void _cdecl     (near * destNNC)(void near*, int);
typedef void _cdecl     (near * destNFC)(void far*, int);
typedef void _pascal    (near * destNNP)(void near*, int);
typedef void _pascal    (near * destNFP)(void far*, int);
typedef void _pascal    (near * destNNPL)(int, void near*);
typedef void _pascal    (near * destNFPL)(int, void far*);
typedef void _fastcall  (near * destNNF)(void near*, int);
typedef void _fastcall  (near * destNFF)(void far*, int);
typedef void _fastcall  (near * destNNFL)(int, void near*);
typedef void _fastcall  (near * destNFFL)(int, void far*);
typedef void _cdecl     (far  * destFNC)(void near*, int);
typedef void _cdecl     (far  * destFFC)(void far*, int);
typedef void _pascal    (far  * destFNP)(void near*, int);
typedef void _pascal    (far  * destFFP)(void far*, int);
typedef void _pascal    (far  * destFNPL)(int, void near*);
typedef void _pascal    (far  * destFFPL)(int, void far*);
typedef void _fastcall  (far  * destFNF)(void near*, int);
typedef void _fastcall  (far  * destFFF)(void far*, int);
typedef void _fastcall  (far  * destFNFL)(int, void near*);
typedef void _fastcall  (far  * destFFFL)(int, void far*);
typedef void _cdecl     (near * destNNCT)(int);
typedef void _cdecl     (near * destNFCT)(int);
typedef void _pascal    (near * destNNPT)(int);
typedef void _pascal    (near * destNFPT)(int);
typedef void _fastcall  (near * destNNFT)(int);
typedef void _fastcall  (near * destNFFT)(int);
typedef void _cdecl     (far  * destFNCT)(int);
typedef void _cdecl     (far  * destFFCT)(int);
typedef void _pascal    (far  * destFNPT)(int);
typedef void _pascal    (far  * destFFPT)(int);
typedef void _fastcall  (far  * destFNFT)(int);
typedef void _fastcall  (far  * destFFFT)(int);

// VNEW
typedef void _cdecl     (near * constNNC)(void near*);
typedef void _cdecl     (near * constNFC)(void far*);
typedef void _pascal    (near * constNNP)(void near*);
typedef void _pascal    (near * constNFP)(void far*);
typedef void _fastcall  (near * constNNF)(void near*);
typedef void _fastcall  (near * constNFF)(void far*);
typedef void _cdecl     (far  * constFNC)(void near*);
typedef void _cdecl     (far  * constFFC)(void far*);
typedef void _pascal    (far  * constFNP)(void near*);
typedef void _pascal    (far  * constFFP)(void far*);
typedef void _fastcall  (far  * constFNF)(void near*);
typedef void _fastcall  (far  * constFFF)(void far*);
typedef void _cdecl     (near * constNNCT)();
typedef void _cdecl     (near * constNFCT)();
typedef void _pascal    (near * constNNPT)();
typedef void _pascal    (near * constNFPT)();
typedef void _fastcall  (near * constNNFT)();
typedef void _fastcall  (near * constNFFT)();
typedef void _cdecl     (far  * constFNCT)();
typedef void _cdecl     (far  * constFFCT)();
typedef void _pascal    (far  * constFNPT)();
typedef void _pascal    (far  * constFFPT)();
typedef void _fastcall  (far  * constFNFT)();
typedef void _fastcall  (far  * constFFFT)();

// VNEWV
typedef void _cdecl     (near * consvNNC)(void near*, int);
typedef void _cdecl     (near * consvNFC)(void far*, int);
typedef void _pascal    (near * consvNNP)(void near*, int);
typedef void _pascal    (near * consvNFP)(void far*, int);
typedef void _pascal    (near * consvNNPL)(int, void near*);
typedef void _pascal    (near * consvNFPL)(int, void far*);
typedef void _fastcall  (near * consvNNF)(void near*, int);
typedef void _fastcall  (near * consvNFF)(void far*, int);
typedef void _fastcall  (near * consvNNFL)(int, void near*);
typedef void _fastcall  (near * consvNFFL)(int, void far*);
typedef void _cdecl     (far  * consvFNC)(void near*, int);
typedef void _cdecl     (far  * consvFFC)(void far*, int);
typedef void _pascal    (far  * consvFNP)(void near*, int);
typedef void _pascal    (far  * consvFFP)(void far*, int);
typedef void _pascal    (far  * consvFNPL)(int, void near*);
typedef void _pascal    (far  * consvFFPL)(int, void far*);
typedef void _fastcall  (far  * consvFNF)(void near*, int);
typedef void _fastcall  (far  * consvFFF)(void far*, int);
typedef void _fastcall  (far  * consvFNFL)(int, void near*);
typedef void _fastcall  (far  * consvFFFL)(int, void far*);
typedef void _cdecl     (near * consvNNCT)(int);
typedef void _cdecl     (near * consvNFCT)(int);
typedef void _pascal    (near * consvNNPT)(int);
typedef void _pascal    (near * consvNFPT)(int);
typedef void _fastcall  (near * consvNNFT)(int);
typedef void _fastcall  (near * consvNFFT)(int);
typedef void _cdecl     (far  * consvFNCT)(int);
typedef void _cdecl     (far  * consvFFCT)(int);
typedef void _pascal    (far  * consvFNPT)(int);
typedef void _pascal    (far  * consvFFPT)(int);
typedef void _fastcall  (far  * consvFNFT)(int);
typedef void _fastcall  (far  * consvFFFT)(int);

// VAPP
typedef void _cdecl     (near * appNNC)(void near*, void near*);
typedef void _cdecl     (near * appNFC)(void far*, void far*);
typedef void _pascal    (near * appNNP)(void near*, void near*);
typedef void _pascal    (near * appNFP)(void far*, void far*);
typedef void _pascal    (near * appNNPL)(void near*, void near*);
typedef void _pascal    (near * appNFPL)(void far*, void far*);
typedef void _fastcall  (near * appNNF)(void near*, void near*);
typedef void _fastcall  (near * appNFF)(void far*, void far*);
typedef void _fastcall  (near * appNNFL)(void near*, void near*);
typedef void _fastcall  (near * appNFFL)(void far*, void far*);
typedef void _cdecl     (far  * appFNC)(void near*, void near*);
typedef void _cdecl     (far  * appFFC)(void far*, void far*);
typedef void _pascal    (far  * appFNP)(void near*, void near*);
typedef void _pascal    (far  * appFFP)(void far*, void far*);
typedef void _pascal    (far  * appFNPL)(void near*, void near*);
typedef void _pascal    (far  * appFFPL)(void far*, void far*);
typedef void _fastcall  (far  * appFNF)(void near*, void near*);
typedef void _fastcall  (far  * appFFF)(void far*, void far*);
typedef void _fastcall  (far  * appFNFL)(void near*, void near*);
typedef void _fastcall  (far  * appFFFL)(void far*, void far*);
typedef void _cdecl     (near * appNNCT)(void near*);
typedef void _cdecl     (near * appNFCT)(void far*);
typedef void _pascal    (near * appNNPT)(void near*);
typedef void _pascal    (near * appNFPT)(void far*);
typedef void _fastcall  (near * appNNFT)(void near*);
typedef void _fastcall  (near * appNFFT)(void far*);
typedef void _cdecl     (far  * appFNCT)(void near*);
typedef void _cdecl     (far  * appFFCT)(void far*);
typedef void _pascal    (far  * appFNPT)(void near*);
typedef void _pascal    (far  * appFFPT)(void far*);
typedef void _fastcall  (far  * appFNFT)(void near*);
typedef void _fastcall  (far  * appFFFT)(void far*);

// VAPPV
typedef void _cdecl     (near * appvNNC)(void near*, int, void near*);
typedef void _cdecl     (near * appvNFC)(void far*, int, void far*);
typedef void _pascal    (near * appvNNP)(void near*, int, void near*);
typedef void _pascal    (near * appvNFP)(void far*, int, void far*);
typedef void _pascal    (near * appvNNPL)(int, void near*, void near*);
typedef void _pascal    (near * appvNFPL)(int, void far*, void far*);
typedef void _fastcall  (near * appvNNF)(void near*, int, void near*);
typedef void _fastcall  (near * appvNFF)(void far*, int, void far*);
typedef void _fastcall  (near * appvNNFL)(int, void near*, void near*);
typedef void _fastcall  (near * appvNFFL)(int, void far*, void far*);
typedef void _cdecl     (far  * appvFNC)(void near*, int, void near*);
typedef void _cdecl     (far  * appvFFC)(void far*, int, void far*);
typedef void _pascal    (far  * appvFNP)(void near*, int, void near*);
typedef void _pascal    (far  * appvFFP)(void far*, int, void far*);
typedef void _pascal    (far  * appvFNPL)(int, void near*, void near*);
typedef void _pascal    (far  * appvFFPL)(int, void far*, void far*);
typedef void _fastcall  (far  * appvFNF)(void near*, int, void near*);
typedef void _fastcall  (far  * appvFFF)(void far*, int, void far*);
typedef void _fastcall  (far  * appvFNFL)(int, void near*, void near*);
typedef void _fastcall  (far  * appvFFFL)(int, void far*, void far*);
typedef void _cdecl     (near * appvNNCT)(int, void near*);
typedef void _cdecl     (near * appvNFCT)(int, void far*);
typedef void _pascal    (near * appvNNPT)(int, void near*);
typedef void _pascal    (near * appvNFPT)(int, void far*);
typedef void _fastcall  (near * appvNNFT)(int, void near*);
typedef void _fastcall  (near * appvNFFT)(int, void far*);
typedef void _cdecl     (far  * appvFNCT)(int, void near*);
typedef void _cdecl     (far  * appvFFCT)(int, void far*);
typedef void _pascal    (far  * appvFNPT)(int, void near*);
typedef void _pascal    (far  * appvFFPT)(int, void far*);
typedef void _fastcall  (far  * appvFNFT)(int, void near*);
typedef void _fastcall  (far  * appvFFFT)(int, void far*);


#define  VFARCALL   0x01
#define  VPASCAL    0x02
#define  VFARPTR    0x04
#define  VDEALLOC   0x08
#define  VSTORECNT  0x10
#define  VFASTCALL  0x20
#define  VHUGEVECT  0x40
#define  VFASTTHIS  0x80
#define  VTHISLAST  0x100

#define VCALLTYPE   (VFARCALL | VPASCAL | VFARPTR | VFASTCALL | VFASTTHIS | VTHISLAST)

#define LOAD_FAR_THIS(p)    asm push ds; asm push si; asm lds si, p
#define END_FAR_THIS()      asm pop si; asm pop ds

#define LOAD_NEAR_THIS(p)   asm push si; asm mov si, word ptr p
#define END_NEAR_THIS()     asm pop si

// Need fast huge pointers.  Classes will be aligned correctly.
#pragma option -h+
