# IOSTREAM.MAK
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
# To make a DLL for Windows, use -DWINDLL on the command line.

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

# ALL - compiled changes sources and add all objects (old and new) to library

all :	compile archive

!if $d(WINDOWS)

LIBNAME = cw$(MODEL)
OBJDIR  = w$(MODEL)
TC      = $(TC) +..\winlib\turboc.cfg
TASM    = $(TASM) -D_Windows -D_WINDOWS -o

!elif $d(WINDLL)

LIBNAME = crtldll.lib
OBJDIR  = d
TC      = $(TC) +tcdll.cfg
TASM    = $(TASM) -D_Windows -D_WINDOWS -o

!else

LIBNAME = c$(MODEL)
TC      = $(TC) +..\clib\turboc.cfg

!endif

OBJECTS = lib1 lib2 lib3

!include "..\rules.mak"

!include "iostobj.mak"

lib1 :  $(OBJS1)
lib2 :  $(OBJS2)
lib3 :  $(OBJS3)

# ARCHIVE - add all objects to a new library.

!if $d(WINDLL)

archive :
        makersp "..\\\\..\\\\iostream\\\\d\\\\%s\n" &&|
        $(OBJS2)
        $(OBJS3)
|       >> ..\winlib\dllmak.rsp
        makersp "+$(OBJDIR)\\\\%s &\n" &&|
        $(OBJS1)
|       > iostrmak.rsp
        $(TLIB) $(LIBDIR)\$(LIBNAME) /C @iostrmak.rsp,nul
        if exist $(LIBDIR)\*.bak del $(LIBDIR)\*.bak
        del *.rsp

!else

archive :
        makersp "+$(OBJDIR)\\\\%s &\n" &&|
        $(OBJS1)
        $(OBJS2)
        $(OBJS3)
|       > iostrmak.rsp
        $(TLIB) $(LIBDIR)\$(LIBNAME) /C @iostrmak.rsp,nul
        if exist $(LIBDIR)\*.bak del $(LIBDIR)\*.bak
        del *.rsp

!endif          # if $d(WINDLL)

!endif          # if huge model WINDOWS
