#
# ObjectWindows - (C) Copyright 1992 by Borland International
#

MODEL = l

!if !$d(BCROOT)
!include "..\bcroot.inc"
!endif

!include "..\makefile.inc"

OBJS = wchess.obj talk.obj board.obj display.obj info.obj small.obj \
timelib.obj movgen.obj search.obj evalu.obj saverest.obj edit.obj \
colors.obj drag.obj pvalue.obj

wchess.exe: turboc.cfg wchess.rsp $(OBJS) wchess.res
     $(TLINK) $(LFLAGS) @wchess.rsp
     $(RC) -30 -K wchess.res wchess.exe

wchess.res: wchess.rc bpawn.bmp brook.bmp bkngt.bmp bbishop.bmp bqueen.bmp bking.bmp wpawn.bmp wrook.bmp wkngt.bmp wbishop.bmp wqueen.bmp wking.bmp pmask.bmp rmask.bmp ktmask.bmp bmask.bmp qmask.bmp kmask.bmp bkbrush.bmp

wchess.rsp: makefile ..\makefile.inc turboc.cfg
       copy &&!
/c $(BCLIBDIR)\c0w$(MODEL)+
.\wchess.obj+
.\talk.obj+
.\board.obj+
.\display.obj+
.\info.obj+
.\small.obj+
.\timelib.obj+
.\movgen.obj+
.\search.obj+
.\evalu.obj+
.\saverest.obj+
.\edit.obj+
.\colors.obj+
.\drag.obj+
.\pvalue.obj
wchess
wchess
$(BCROOT)\lib\bwcc.lib+
$(OWLLIBS)+
$(STDLIBS)
.\wchess.def
! wchess.rsp

turboc.cfg: makefile ..\makefile.inc
	echo -I$(INCLUDE) >turboc.cfg

clean:
	del *.obj
	del *.exe
	del *.res
	del *.dll
	del *.map
	del *.sym
        del turboc.cfg

