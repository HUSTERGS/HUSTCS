#
#   Borland C++ - (C) Copyright 1991, 1992 by Borland International
#   Makefile for building Turbo Vision help compiler
#

#
# Configuration:
#
#   If you have Borland C++ and not Turbo C++, you must use a define on
#   the make command line:
#
#       -DBC         indicates that you have Borland C++
#
#   Examples:
#
#       using Turbo C++:
#
#           make
#
#       using Borland C++:
#
#           make -DBC
#

.autodepend

!if !$d(INCLUDE)
INCLUDE=..\include;..\..\include
!endif

!if !$d(LIB)
LIB=..\lib;..\..\lib
!endif

!if $d(BC)
CC=bcc
!else
CC=tcc
!endif

CFLAGS = -O1 -ml

OBJS = tvhc.obj

.cpp.obj:
    $(CC) $(CFLAGS) -c -I$(INCLUDE) {$* }

tvhc.exe : $(OBJS)
    $(CC) -M $(CFLAGS) -L$(LIB) $(OBJS) tv.lib

