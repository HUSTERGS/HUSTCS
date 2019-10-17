# CLIB.MAK
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
# To make a library for Windows, use -DWINDOWS on the command line.
# To make a DLL for Windows, use -DWINDLL.
# To make an import library for Windows, use -DIMPORT.

!if $d(WINDLL)
MODEL = l
!endif

!if !$d(MODEL)
!error MODEL not defined. Use -DMODEL=x on command line, or SET MODEL=x.
!endif

!if '$(MODEL)'=='h' && $d(WINDOWS)

all :
        echo Can't make a huge model WINDOWS library

clean :
        echo Can't clean up a huge model WINDOWS library

!else

# ALL - compile changed sources and add all objects (old and new) to library

all :   compile archive

!if $d(WINDOWS)

LIBNAME = cw$(MODEL)
OBJDIR  = w$(MODEL)
TC      = $(TC) +..\winlib\turboc.cfg
TASM    = tasm -D_Windows -D_WINDOWS -o
OBJECTS = lib1 lib2 lib3 lib5

!elif $d(WINDLL)

LIBNAME = crtldll
OBJDIR  = ..\winlib\d
TC      = $(TC) +..\winlib\tcdll.cfg
TASM    = tasm -D_Windows -D_WINDOWS -D_BUILDRTLDLL -o
OBJECTS = lib1 lib2 lib3 lib5

!else

LIBNAME = c$(MODEL)
OBJECTS = lib1 lib2 lib3 lib4 lib5

!endif

!include "..\rules.mak"

!include "clibobj.mak"

lib1 : $(OBJS1)
lib2 : $(OBJS2)
lib3 : $(OBJS3)
lib4 : $(OBJS4)
lib5 : $(OBJS5)

# gregistr.obj cannot be built in tiny model.

!if '$(MODEL)'=='s' && !$d(WINDOWS) && !$d(WINDLL)
gregistr.obj: gregistr.c
        $(TC) -ms -n$(OBJDIR) $?
!endif

# ARCHIVE - add all objects to a new library.

!if $d(WINDLL)

archive :
        makersp "%s\n" &&|
        $(OBJS5)
|       >> ..\winlib\dllmak.rsp
        makersp "+%s &\n" &&|
        $(OBJS1)
        $(OBJS2)
        $(OBJS3)
|       > clibmak.rsp
        if exist $(LIBDIR)\$(LIBNAME).lib del $(LIBDIR)\$(LIBNAME).lib
        cd ..\winlib\d
        $(TLIB) ..\$(LIBDIR)\$(LIBNAME) /C @..\..\clib\clibmak.rsp,nul
        if exist ..\$(LIBDIR)\*.bak del ..\$(LIBDIR)\*.bak
        cd ..\..\clib
        del *.rsp

!elif $d(WINDOWS)

archive :
        if exist $(LIBDIR)\$(LIBNAME).lib del $(LIBDIR)\$(LIBNAME).lib
        makersp "+$(OBJDIR)\\\\%s &\n" &&|
        $(OBJS1)
        $(OBJS2)
        $(OBJS3)
        $(OBJS5)
|       > clibmak.rsp
        $(TLIB) $(LIBDIR)\$(LIBNAME) /C @clibmak.rsp,nul
        if exist $(LIBDIR)\*.bak del $(LIBDIR)\*.bak
        del *.rsp

!else

archive :
        if exist $(LIBDIR)\$(LIBNAME).lib del $(LIBDIR)\$(LIBNAME).lib
        makersp "+$(OBJDIR)\\\\%s &\n" &&|
        $(OBJS1)
        $(OBJS2)
        $(OBJS3)
        $(OBJS4)
        $(OBJS5)
|       > clibmak.rsp
        $(TLIB) $(LIBDIR)\$(LIBNAME) /C @clibmak.rsp,nul
        if exist $(LIBDIR)\*.bak del $(LIBDIR)\*.bak
        del *.rsp

!endif          # if $d(WINDLL)

!endif          # if huge model WINDOWS
