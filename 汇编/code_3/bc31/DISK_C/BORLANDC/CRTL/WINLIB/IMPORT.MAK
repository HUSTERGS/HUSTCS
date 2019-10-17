# IMPORT.MAK - build the WINDOWS 3.1 import library.

LIBDIR = ..\lib
LIBFILE = $(LIBDIR)\import.lib

MODEL = l

all : $(LIBFILE)

!include "..\rules.mak"

$(LIBFILE) : win31.def profc.obj
	if exist $(LIBFILE) del $(LIBFILE)
	implib $(LIBFILE) win31.def
	tlib $(LIBFILE) +$(OBJDIR)\profc.obj
