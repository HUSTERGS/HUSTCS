# RULES.MAK - rules for compiling and building libraries
#
# This file is intended to be !included in a makefile.
# If the following MAKE macros are not defined, they will be
# assigned default values as described below:
#
#       MODEL   memory model, default s
#       SRCDIR  source directory, default .
#       OBJDIR  object directory, default $(MODEL)
#       LIBDIR  library directory, default ..\lib
#       LIBNAME name of library without path or extension, default c$(MODEL)
#       OBJECTS list of objects that LIBNAME depends on, without path or
#               extension.  If this list is too large for MAKE, use a list
#               of fake targets that depend on sublists of object files.
#       TC      name of the compiler, default bcc
#       TASM    name of the assembler, default tasm
#       TLIB    name of the librarian, default tlib /0

!if $d(SWAP)
.swap
!endif

!if !$d(MODEL)
MODEL = s
!endif

!if !$d(SRCDIR)
SRCDIR = .
!endif

!if !$d(OBJDIR)
OBJDIR = $(MODEL)
!endif

!if !$d(LIBDIR)
LIBDIR = ..\lib
!endif

!if !$d(LIBNAME)
LIBNAME = c$(MODEL)
!endif

!if !$d(TC)
TC = bcc
!endif

!if !$d(TASM)
TASM = tasm
!endif

!if !$d(TLIB)
TLIB = tlib /0
!endif

# If this is small model, compile C modules in TINY model
# to avoid segment fixups in the object files.  This is necessary
# because the small model library is used for both small and tiny
# model programs.

!if '$(MODEL)'=='s' && !$d(WINDOWS)
CMODEL = t
!else
CMODEL = $(MODEL)
!endif

!if '$(SRCDIR)' != '.'
.path.c   = $(SRCDIR)
.path.cpp = $(SRCDIR)
.path.cas = $(SRCDIR)
.path.asm = $(SRCDIR)
!endif
.path.obj = $(OBJDIR)
.path.lib = $(LIBDIR)

# How to compile modules.  For C modules, we just build a response
# file that is passed to BCC later.  We also add the name to the
# TLIB response file.

.c.obj :
        $(TC) -m$(CMODEL) -n$(OBJDIR) { $<}

.cpp.obj :
        $(TC) -m$(CMODEL) -n$(OBJDIR) { $<}

.cas.obj :
        $(TC) -m$(CMODEL) -n$(OBJDIR) { $<}

.asm.obj :
        $(TASM) -D__$(MODEL)__ $< , $(OBJDIR)\\

compile : $(OBJECTS)

clean :
        echo Deleting all $(MODEL)-model libraries and objects
        del $(OBJDIR)\*.obj
        del $(LIBDIR)\$(LIBNAME).lib
        del $(LIBDIR)\*.bak
        del *.rsp
