# FARFUNCS.MAK
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
# To make a DLL for Windows, use -DDLL on the command line.

!if !$d(MODEL)
!error MODEL not defined. Use -DMODEL=x on command line, or SET MODEL=x.
!endif

!if '$(MODEL)'=='h' && ( $d(WINDOWS) || $d(DLL) )

all :
        echo Can't make a huge model WINDOWS library

new :
        echo Can't make a huge model WINDOWS library

clean :
        echo Can't clean up a huge model WINDOWS library

!else

!if $d(WINDOWS)

LIBNAME = cw$(MODEL)
OBJDIR  = w$(MODEL)
TC      = $(TC) +..\winlib\turboc.cfg
TASM    = $(TASM) -D_Windows -D_WINDOWS -o

!elif $d(WINDLL)

LIBNAME = crtldll.lib
OBJDIR  = d
TC      = $(TC) +..\winlib\tcdll.cfg -D_RTLDLL -c
TASM    = $(TASM) -D_Windows -D_WINDOWS -o

!else

LIBNAME = c$(MODEL)

!endif

OBJECTS = lib1

# The target "replace" is defined in rules.mak

all : $(OBJECTS) archive

!include "..\rules.mak"

# The list of object files.  WARNING: if you add a file to this list,
# you must also add an explicit rule for compiling it at the end of
# this makefile.

DLLOBJS = \
$(OBJDIR)\fmemccpy.obj \
$(OBJDIR)\fmemchr.obj \
$(OBJDIR)\fmemcmp.obj \
$(OBJDIR)\fmemcpy.obj \
$(OBJDIR)\fmemicmp.obj \
$(OBJDIR)\fmemset.obj \
$(OBJDIR)\fmovmem.obj \
$(OBJDIR)\fstrcat.obj \
$(OBJDIR)\fstrchr.obj \
$(OBJDIR)\fstrcmp.obj \
$(OBJDIR)\fstrcpy.obj \
$(OBJDIR)\fstrcspn.obj \
$(OBJDIR)\fstrdup.obj \
$(OBJDIR)\fstricmp.obj \
$(OBJDIR)\fstrlen.obj \
$(OBJDIR)\fstrlwr.obj \
$(OBJDIR)\fstrncat.obj \
$(OBJDIR)\fstrncmp.obj \
$(OBJDIR)\fstrncpy.obj \
$(OBJDIR)\fstrnicm.obj \
$(OBJDIR)\fstrnset.obj \
$(OBJDIR)\fstrpbrk.obj \
$(OBJDIR)\fstrrchr.obj \
$(OBJDIR)\fstrrev.obj \
$(OBJDIR)\fstrset.obj \
$(OBJDIR)\fstrspn.obj \
$(OBJDIR)\fstrstr.obj \
$(OBJDIR)\fstrtok.obj \
$(OBJDIR)\fstrupr.obj \
$(OBJDIR)\ftoupper.obj \
$(OBJDIR)\ftolower.obj \
$(OBJDIR)\hqsort.obj

lib1 : $(DLLOBJS) $(NONDLLOBJS)

# ARCHIVE - add all objects to a new library

!if $d(WINDLL)

archive :
        makersp "..\\\\..\\\\clib\\\\%s\n" &&|
        $(DLLOBJS)
|       >> ..\winlib\dllmak.rsp
        makersp "+$(OBJDIR)\\\\%s &\n" &&|
        $(NONDLLOBJS)
|       > farfuncs.rsp
        $(TLIB) $(LIBDIR)\$(LIBNAME) /C @farfuncs.rsp,nul
        if exist $(LIBDIR)\*.bak del $(LIBDIR)\*.bak
	del *.rsp

!else

archive :
        makersp "+%s &\n" &&|
        $(DLLOBJS)
        $(NONDLLOBJS)
|       > farfuncs.rsp
        $(TLIB) $(LIBDIR)\$(LIBNAME) /C @farfuncs.rsp,nul
        if exist $(LIBDIR)\*.bak del $(LIBDIR)\*.bak
        del *.rsp
!endif          # if $d(WINDLL)

# How to compile modules.

!if '$(MODEL)'=='h'
COMPILE   = $(TC) -mh -D__FARFUNCS__ -o$<
!else
COMPILE   = $(TC) -ml -D__FARFUNCS__ -o$<
!endif

# We have to painstakingly give an explicit rule for each
# object file in OBJECTS, because the object filename is
# different from the source filename -- it has an "f" prepended --
# and because names with 8 characters have to be shortened.

$(OBJDIR)\fmemccpy.obj : memccpy.cas
        $(COMPILE) memccpy.cas
$(OBJDIR)\fmemchr.obj : memchr.cas
        $(COMPILE) memchr.cas
$(OBJDIR)\fmemcmp.obj : memcmp.cas
        $(COMPILE) memcmp.cas
$(OBJDIR)\fmemcpy.obj : memcpy.cas
        $(COMPILE) memcpy.cas
$(OBJDIR)\fmemicmp.obj : memicmp.c
        $(COMPILE) memicmp.c
$(OBJDIR)\fmemset.obj : memset.cas
        $(COMPILE) memset.cas
$(OBJDIR)\fmovmem.obj : movmem.cas
        $(COMPILE) movmem.cas
$(OBJDIR)\fstrcat.obj : strcat.cas
        $(COMPILE) strcat.cas
$(OBJDIR)\fstrchr.obj : strchr.cas
        $(COMPILE) strchr.cas
$(OBJDIR)\fstrcmp.obj : strcmp.cas
        $(COMPILE) strcmp.cas
$(OBJDIR)\fstrcpy.obj : strcpy.cas
        $(COMPILE) strcpy.cas
$(OBJDIR)\fstrcspn.obj : strcspn.c
        $(COMPILE) strcspn.c
$(OBJDIR)\fstrdup.obj : strdup.c
        $(COMPILE) strdup.c
$(OBJDIR)\fstricmp.obj : stricmp.cas
        $(COMPILE) stricmp.cas
$(OBJDIR)\fstrlen.obj : strlen.cas
        $(COMPILE) strlen.cas
$(OBJDIR)\fstrlwr.obj : strlwr.cas
        $(COMPILE) strlwr.cas
$(OBJDIR)\fstrncat.obj : strncat.c
        $(COMPILE) strncat.c
$(OBJDIR)\fstrncmp.obj : strncmp.cas
        $(COMPILE) strncmp.cas
$(OBJDIR)\fstrncpy.obj : strncpy.cas
        $(COMPILE) strncpy.cas
$(OBJDIR)\fstrnicm.obj : strnicmp.cas
        $(COMPILE) strnicmp.cas
$(OBJDIR)\fstrnset.obj : strnset.c
        $(COMPILE) strnset.c
$(OBJDIR)\fstrpbrk.obj : strpbrk.c
        $(COMPILE) strpbrk.c
$(OBJDIR)\fstrrchr.obj : strrchr.c
        $(COMPILE) strrchr.c
$(OBJDIR)\fstrrev.obj : strrev.cas
        $(COMPILE) strrev.cas
$(OBJDIR)\fstrset.obj : strset.c
        $(COMPILE) strset.c
$(OBJDIR)\fstrspn.obj : strspn.c
        $(COMPILE) strspn.c
$(OBJDIR)\fstrstr.obj : strstr.cas
        $(COMPILE) strstr.cas
$(OBJDIR)\fstrtok.obj : strtok.c
        $(COMPILE) strtok.c
$(OBJDIR)\fstrupr.obj : strupr.cas
        $(COMPILE) strupr.cas
$(OBJDIR)\ftoupper.obj : toupper.c
        $(COMPILE) toupper.c
$(OBJDIR)\ftolower.obj : tolower.c
        $(COMPILE) tolower.c
$(OBJDIR)\hqsort.obj : qsort.cas
        $(COMPILE) qsort.cas
!endif          # if huge model WINDOWS
