# WINLIB.MAK
#
# To compile all changed modules and replace (or add) both old and new objects
# in an existing (or new) library, type
#
#       MAKE all
#
# To clean up (i.e., delete) all object files and temporary files, type
#
#       MAKE -DTARGET clean
#
# The memory model must be specified in one of two ways.  You can
# set the environment variable MODEL before running MAKE:
#
#       SET MODEL=x
#
# or you can use the -D command line switch:
#
#       MAKE -DMODEL=x
#
# where x is the letter s, c, m, l, or h.  Using -D overrides the
# environment variable.
#
# To make a DLL for Windows, use -DWINDLL on the command line.

!if $d(WINDLL)
MODEL = l
!endif

!if !$d(MODEL)
!error MODEL not defined. Use -DMODEL=x on command line, or SET MODEL=x.
!endif

!if '$(MODEL)'=='h'

all :
        echo Can't make a huge model WINDOWS library

clean :
        echo Can't clean up a huge model WINDOWS library

!else

# ALL - compiled changes sources and add all objects (old and new) to library

all :	compile archive

!include "winobj.mak"

!if $d(WINDLL)

LIBNAME = crtldll.lib
OBJDIR  = d
TC      = $(TC) +tcdll.cfg
TASM    = $(TASM) -D_Windows -D_WINDOWS -o
OBJECTS = $(OBJS1) $(OBJS2) $(OBJS3)

!else

LIBNAME = cw$(MODEL)
OBJECTS = $(OBJS1) $(OBJS2)

!endif

WINDOWS = 1     # prevent rules.mak from using tiny model

!include "..\rules.mak"

# ARCHIVE - add all objects to a new library.

!if $d(WINDLL)

archive :
        makersp "..\\\\..\\\\winlib\\\\d\\\\%s\n" &&|
        $(OBJS2)
        $(OBJS3)
|       >> dllmak.rsp
        makersp "+$(OBJDIR)\\\\%s &\n" &&|
        $(OBJS1)
|       > winmak.rsp
        $(TLIB) $(LIBDIR)\$(LIBNAME) /C @winmak.rsp,nul
        if exist $(LIBDIR)\*.bak del $(LIBDIR)\*.bak

!else

archive :
        makersp "+$(OBJDIR)\\\\%s &\n" &&|
        $(OBJS1)
        $(OBJS2)
|       > winmak.rsp
        $(TLIB) $(LIBDIR)\$(LIBNAME) /C @winmak.rsp,nul
        if exist $(LIBDIR)\*.bak del $(LIBDIR)\*.bak
        del *.rsp

!endif          # if $d(WINDLL)

!endif          # if huge model
