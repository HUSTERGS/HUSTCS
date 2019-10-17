# MATH.MAK
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

!if '$(MODEL)'=='h' && ( $d(WINDOWS) || $d(WINDLL) )

all :
        echo Can't make a huge model WINDOWS library

clean :
        echo Can't clean up a huge model WINDOWS library

!else

# ALL - compiled changes sources and add all objects (old and new) to library

all :	special compile archive

!if '$(MODEL)'=='s' || '$(MODEL)'=='m'
LDATA = 0
!else
LDATA = 1
!endif

!include "mathobj.mak"

!if $d(WINDOWS)

OBJDIR  = w$(MODEL)
LIBNAME = mathw$(MODEL)
TC      = $(TC) +turbocw.cfg
TASM    = $(TASM) -D_Windows -D_WINDOWS -o
OBJECTS = $(OBJS1) $(OBJS2) $(OBJS4)

!elif $d(WINDLL)

OBJDIR  = d
LIBNAME = crtldll
TC      = $(TC) +turbocw.cfg -WDE -D_RTLDLL -D_BUILDRTLDLL -c
TASM    = $(TASM) -D_Windows -D_WINDOWS -o
OBJECTS = $(OBJS1) $(OBJS2) $(OBJS4)

!else

OBJDIR  = $(MODEL)
LIBNAME = math$(MODEL)
OBJECTS = $(OBJS1) $(OBJS3) $(OBJS4)

!endif

!include "..\rules.mak"

# Rules for the objects that can't be built the normal way in rules.mak.

OBJSPEC1 = \
emuvars.obj \
flags87.obj

OBJSPEC2 = \
fftol.obj \
nftol.obj

special : turboc.cfg tasm.cfg turbocw.cfg $(OBJSPEC1) $(OBJSPEC2) 

flags87.obj : flags87.asm
        $(TASM) -D__COMPACT__ -D__BSS__ flags87.asm, $*

fftol.obj : ftol.asm
        $(TASM) -D__COMPACT__ -D__BSS__ -DFCall ftol.asm, $*

nftol.obj : ftol.asm
        $(TASM) -D__COMPACT__ -D__BSS__ -DNCall ftol.asm, $*

emuvars.obj : emuvars.asm
        $(TASM) -D__COMPACT__ -D__BSS__ -DLDATA=$(LDATA) -I..\emu emuvars, $*

turboc.cfg : math.mak
        copy &&|
-c
-D__NO_INTRINSICS__
-I..\rtlinc;..\..\include;.
-O
-w
-X
-Z
-zC_TEXT
|       turboc.cfg

turbocw.cfg : math.mak
        copy &&|
-c
-D__NO_INTRINSICS__
-D_WINDOWS
-D_Windows
-I..\rtlinc;..\..\include;.
-O
-w
-w-asm
-WE
-X
-Z
-zC_TEXT 
|       turbocw.cfg

tasm.cfg : math.mak
        copy &&|
/m /mx /q /t /z /i..\rtlinc
|       tasm.cfg

# ARCHIVE - add all objects to a new library.

!if $d(WINDLL)

archive :
        makersp "..\\\\..\\\\math\\\\d\\\\%s\n" &&|
        $(OBJS4)
|       >> ..\winlib\dllmak.rsp
        makersp "+$(OBJDIR)\\\\%s &\n" &&|
        $(OBJS1)
        $(OBJS2)
        $(OBJSPEC2)
|       > mathmak.rsp
        $(TLIB) $(LIBDIR)\$(LIBNAME) /C @mathmak.rsp,nul
        if exist $(LIBDIR)\*.bak del $(LIBDIR)\*.bak
	del *.rsp

!elif $d(WINDOWS)

archive :
        makersp "+$(OBJDIR)\\\\%s &\n" &&|
        $(OBJS1)
        $(OBJS2)
        $(OBJS4)
        $(OBJSPEC1)
        $(OBJSPEC2)
|       > mathmak.rsp
        if exist $(LIBDIR)\$(LIBNAME).lib del $(LIBDIR)\$(LIBNAME).lib
        $(TLIB) $(LIBDIR)\$(LIBNAME) /C @mathmak.rsp,nul
        if exist $(LIBDIR)\*.bak del $(LIBDIR)\*.bak
        del *.rsp

!else

archive :
        makersp "+$(OBJDIR)\\\\%s &\n" &&|
        $(OBJS1)
        $(OBJS3)
        $(OBJS4)
        $(OBJSPEC1)
        $(OBJSPEC2)
|       > mathmak.rsp
        if exist $(LIBDIR)\$(LIBNAME).lib del $(LIBDIR)\$(LIBNAME).lib
        $(TLIB) $(LIBDIR)\$(LIBNAME) /C @mathmak.rsp,nul
        if exist $(LIBDIR)\*.bak del $(LIBDIR)\*.bak
        del *.rsp

!endif          # if $d(WINDLL)

!endif          # if huge model WINDOWS
