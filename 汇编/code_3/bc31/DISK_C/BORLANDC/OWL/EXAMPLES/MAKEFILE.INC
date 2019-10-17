#
# ObjectWindows - (C) Copyright 1992 by Borland International
#

.autodepend
.swap

!if !$d(USESTATIC)
USEDLL=1
!endif

!if $d(DEBUG)
CDBG = -v
LDBG = /v /Vt
!endif

!if $d(USEDLL)
MODEL=l
!elif !$d(MODEL)
MODEL=l
!endif

DMODEL=l

#
# By default, build all OWL applications as STRICT Windows 3.1 apps
#

WINMODE = -DWIN31 -DSTRICT

!if $d(STRICT)

WINMODE = -DSTRICT
!if $d(WIN31)
WINMODE = -DWIN31 $(WINMODE)
!endif
!if $d(WIN30)
WINMODE = -DWIN30 $(WINMODE)
!endif

!else # !STRICT

!if $d(WIN31)
WINMODE = -DWIN31
!if $d(WIN30)
WINMODE = -DWIN30 $(WINMODE)
!endif

!else # !WIN31 && !STRICT

!if $d(WIN30)
WINMODE = -DWIN30
!endif

!endif # !WIN31
!endif # !STRICT

!if !$d(BCROOT)
!include "bcroot.inc"
!endif

!if !$d(OWLROOT)
OWLROOT=$(BCROOT)\owl
!endif

!if !$d(CLASSDIR)
CLASSDIR=$(BCROOT)\classlib
!endif

INCLUDE       =   $(OWLROOT)\include;$(CLASSDIR)\include;$(BCROOT)\include
RCINCLUDEDIRS = -i$(OWLROOT)\include -i$(BCROOT)\include

CC       = bcc
TLINK    = tlink
RC       = rc

!if $d(USEDLL)
CFLAGS 	 = -WS -D_CLASSDLL $(WINMODE) $(CDBG) -c -m$(MODEL) -w
!else
CFLAGS 	 = -WE $(WINMODE) $(CDBG) -c -m$(MODEL) -w
!endif

CFLAGSD	 = -WDE -D_CLASSDLL $(WINMODE) $(CDBG) -c -m$(DMODEL) -w
CFLAGSUD = -WS  -D_CLASSDLL $(WINMODE) $(CDBG) -c -m$(DMODEL) -w

LFLAGS   = $(LDBG) /Tw /n /x /c /C
LFLAGSD  = $(LDBG) /Twd /n /x /c /C

BCLIBDIR = $(BCROOT)\lib

!if $d(USEDLL)
OWLLIBS  = $(OWLROOT)\lib\owl $(CLASSDIR)\lib\tclasdll
!else
OWLLIBS  = $(OWLROOT)\lib\owlw$(MODEL) /v- $(CLASSDIR)\lib\tclass$(MODEL)
!endif

OWLDLIBS = $(OWLROOT)\lib\owl $(CLASSDIR)\lib\tclasdll

!if $d(USEDLL)
STDLIBS  = $(BCLIBDIR)\import $(BCLIBDIR)\crtldll
!else
STDLIBS  = $(BCLIBDIR)\import $(BCLIBDIR)\mathw$(MODEL) $(BCLIBDIR)\cw$(MODEL)
!endif

STDDLIBS = $(BCLIBDIR)\import $(BCLIBDIR)\crtldll

.rc.res:
	$(RC) -r $(RCINCLUDEDIRS) $.

.cpp.obj:
	$(CC) $(CFLAGS) $.

