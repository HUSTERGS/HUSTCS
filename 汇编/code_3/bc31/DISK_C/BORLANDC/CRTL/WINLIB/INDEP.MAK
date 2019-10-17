# INDEP.MAK - makefile for functions not implemented under Windows
#
# To clean up (i.e., delete) all object files and temporary files, type
#       MAKE clean
# To compile all changed modules and replace their objects in the library, type
#       MAKE
# The memory model must be specified in one of two ways.  You can
# set the environment variable MODEL before running MAKE:
#       SET MODEL=x
# or you can use the -D command line switch:
#       MAKE -DMODEL=x
# where x is the letter s, c, m, l, or h.  Using -D overrides the
# environment variable.

!if !$d(MODEL)
!error MODEL not defined. Use -DMODEL=x on command line, or SET MODEL=x.
!endif

!if '$(MODEL)'=='h'

all :
        echo Can't make a huge model WINDOWS library

new :
        echo Can't make a huge model WINDOWS library

clean :
        echo Can't clean up a huge model WINDOWS library

!else

!if !$d(TASM)
TASM = tasm
!endif

!if !$d(TLIB)
TLIB = tlib /0
!endif

!if $d(WINDLL)
LIBNAME = crtldll.lib
!else
LIBNAME = cw$(MODEL)
!endif

LIBDIR = ..\..\lib

all : indep\notimp.rsp
        cd indep
        $(TLIB) $(LIBDIR)\$(LIBNAME) @notimp.rsp
        if exist $(LIBDIR)\*.bak del $(LIBDIR)\*.bak
        cd ..

indep\notimp.rsp : indep\notimp.lst
        cd indep
        notimp <notimp.lst
        cd ..
        $(TASM) /mx indep\*.asm, indep\\

clean :
        cd indep
        del notimp*.asm
        del *.obj
        del notimp.rsp
        cd ..

!endif          # if huge model
