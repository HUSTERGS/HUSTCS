#--------------------------------------------------------------------------#
#                                                                          #
#   MAKEFILE for Class Libraries                                           #
#                                                                          #
#   Copyright (c) Borland International 1991, 1992                         #
#   All Rights Reserved                                                    #
#                                                                          #
#   Usage:                                                                 #
#                                                                          #
#       make                                                               #
#           builds all libraries for all memory models and for DLLs        #
#                                                                          #
#       make -DDLL                                                         #
#           builds DLLs                                                    #
#                                                                          #
#       make -DMDL=x                                                       #
#           builds all libraries for memory model x, where x               #
#           should be replaced by s, c, m, l, or h.                        #
#                                                                          #
#       options:                                                           #
#                                                                          #
#           -DDBG specifies the debugging version, which enables           #
#                 PRECONDITION and CHECK testing.  See CHECKS.H.           #
#                                                                          #
#           -DTEMPLATES specifies the template version of the library.     #
#                                                                          #
#           -DINCLUDE=... specifies the directories for include files.     #
#                 Only needed if the class library was not installed in    #
#                 in the default location, beneath the compiler root       #
#                 directory.                                               #
#                                                                          #
#           -DLIB=... specifies the directory where the compiler libraries #
#                 are located.  Only needed if the class library was not   #
#                 installed in the default location, beneath the compiler  #
#                 root directory.                                          #
#                                                                          #
#       compiling with Object Data Calling Convention                      #
#           This makefile builds generic libraries that can be used with   #
#           both Windows and DOS.  This doesn't work if you want to use    #
#           the Object Data Calling Convention, so you'll have to build    #
#           separate libraries for DOS and Windows.                        #
#                                                                          #
#--------------------------------------------------------------------------#

# USE_po = 1    # uncomment this line to use -po

# WINDOWS = 1   # uncomment this line when using -po and building a
                # Windows library

.autodepend
.swap

!if $d(DLL)
MDL=l
!endif

all:
!if $d(DLL)
    make -DDLL lib
    make -DDLL -DTEMPLATES lib
!elif $d(MDL)
    make -DMDL=$(MDL) lib
    make -DMDL=$(MDL) -DDBG lib
    make -DMDL=$(MDL) -DTEMPLATES lib
    make -DMDL=$(MDL) -DDBG -DTEMPLATES lib
!else
    for %m in (s c m l h) do make -DMDL=%m
    make -DDLL
!endif

!if $d(TEMPLATES)
TFLAG = -DTEMPLATES
!endif

!if $(MDL) == h
WFLAG =
!elif $d(DLL)
WFLAG = -WDE
!elif $(MDL) == s || $(MDL) == c
!if !$d(USE_po) || $d(WINDOWS)
WFLAG = -WE
!endif
!else
!if !$d(USE_po)
WFLAG = -Y      # for generic libraries
!elif $d(WINDOWS)
WFLAG = -WE
!endif
!endif

!if $d(DLL)

DEBUG = -D__DEBUG=0
.PATH.obj = objs\dll
LIBR = tlib /0
FLAGS = -v- -D_CLASSDLL
BFLAG = -D_BUILDRTLDLL

!if $d( TEMPLATES )
LIBNAME = bidsdll.lib
DLLNAME = bids31.dll
!else
LIBNAME = tclasdll.lib
DLLNAME = tclass31.dll
!endif

!elif $d(DBG)

DEBUG = -D__DEBUG=2
.PATH.obj = objs\d$(MDL)
LIBR = tlib /0
FLAGS = -v-

!if $d( TEMPLATES )
LIBNAME = bidsdb$(MDL)
!else
LIBNAME = tclasdb$(MDL)
!endif

!else

DEBUG = -D__DEBUG=0
.PATH.obj = objs\$(MDL)
LIBR = tlib /0
FLAGS = -v-

!if $d( TEMPLATES )
LIBNAME = bids$(MDL)
!else
LIBNAME = tclass$(MDL)
!endif

!endif

.PATH.cpp = source
.PATH.lib = lib

!if $d(INCLUDE)
IFLAG = -I$(INCLUDE)
!else
IFLAG = -I..\include;include
!endif

!if !$d(LIB)
LIB=..\..\..\lib
!endif

MFLAG = -m$(MDL)

!if !$d(USE_po)
FLAGS = $(FLAGS) $(DEBUG) $(MFLAG) $(TFLAG)
!else
FLAGS = $(FLAGS) $(DEBUG) $(MFLAG) $(TFLAG) -D_ALLOW_po -po
!endif

AFLAGS = -c -n$(.PATH.obj) $(IFLAG) $(BFLAG)
CFLAGS = $(AFLAGS) $(FLAGS)

CC = bcc

lib: config dirs $(LIBNAME)

config:
    echo $(FLAGS) > turboc.cfg
    echo $(AFLAGS) >> turboc.cfg

dirs: makedummy objs\dummy.txt
    if exist objs\dummy.txt del objs\dummy.txt

makedummy:
    echo dummy >objs\dummy.txt

objs\dummy.txt:
    -md objs
    -md objs\s
    -md objs\c
    -md objs\m
    -md objs\l
    -md objs\h
    -md objs\ds
    -md objs\dc
    -md objs\dm
    -md objs\dl
    -md objs\dh
    -md objs\dll

clean:
    -for %d in (s c m l h ds dc dm dl dh dll) do del objs\%d\*.obj

timer.obj: timer.cpp
  $(CC) $(CFLAGS) $(.PATH.cpp)\timer

.cpp.obj:
  $(CC) $(WFLAG) {$* }

!if $d(TEMPLATES)

OBJS =              \
    babstary.obj    \
    bsortary.obj    \
    assoc.obj       \
    btree.obj       \
    btreeinn.obj    \
    btreelfn.obj    \
    collect.obj     \
    contain.obj     \
    dbllist.obj     \
    hashtbl.obj     \
    ldate.obj       \
    list.obj        \
    ltime.obj       \
    memmgr.obj      \
    object.obj      \
    strng.obj       \
    bdict.obj

LINKOBJS =                      \
    -+$(.PATH.obj)\babstary.obj \
    -+$(.PATH.obj)\bsortary.obj \
    -+$(.PATH.obj)\assoc.obj    \
    -+$(.PATH.obj)\btree.obj    \
    -+$(.PATH.obj)\btreeinn.obj \
    -+$(.PATH.obj)\btreelfn.obj \
    -+$(.PATH.obj)\collect.obj  \
    -+$(.PATH.obj)\contain.obj  \
    -+$(.PATH.obj)\dbllist.obj  \
    -+$(.PATH.obj)\hashtbl.obj  \
    -+$(.PATH.obj)\ldate.obj    \
    -+$(.PATH.obj)\list.obj     \
    -+$(.PATH.obj)\ltime.obj    \
    -+$(.PATH.obj)\memmgr.obj   \
    -+$(.PATH.obj)\object.obj   \
    -+$(.PATH.obj)\strng.obj    \
    -+$(.PATH.obj)\bdict.obj

!else

OBJS =              \
    abstarry.obj    \
    array.obj       \
    deque.obj       \
    sortarry.obj    \
    stack.obj       \
    assoc.obj       \
    btree.obj       \
    btreeinn.obj    \
    btreelfn.obj    \
    collect.obj     \
    contain.obj     \
    dbllist.obj     \
    dict.obj        \
    hashtbl.obj     \
    ldate.obj       \
    list.obj        \
    ltime.obj       \
    memmgr.obj      \
    object.obj      \
    strng.obj

LINKOBJS =                      \
    -+$(.PATH.obj)\abstarry.obj \
    -+$(.PATH.obj)\array.obj    \
    -+$(.PATH.obj)\deque.obj    \
    -+$(.PATH.obj)\sortarry.obj \
    -+$(.PATH.obj)\stack.obj    \
    -+$(.PATH.obj)\assoc.obj    \
    -+$(.PATH.obj)\btree.obj    \
    -+$(.PATH.obj)\btreeinn.obj \
    -+$(.PATH.obj)\btreelfn.obj \
    -+$(.PATH.obj)\collect.obj  \
    -+$(.PATH.obj)\contain.obj  \
    -+$(.PATH.obj)\dbllist.obj  \
    -+$(.PATH.obj)\dict.obj     \
    -+$(.PATH.obj)\hashtbl.obj  \
    -+$(.PATH.obj)\ldate.obj    \
    -+$(.PATH.obj)\list.obj     \
    -+$(.PATH.obj)\ltime.obj    \
    -+$(.PATH.obj)\memmgr.obj   \
    -+$(.PATH.obj)\object.obj   \
    -+$(.PATH.obj)\strng.obj

!endif

!if $d(DLL)

!if $d(TEMPLATES)
LINKOBJS =          \
    babstary.obj +  \
    bdict        +  \
    bsortary.obj +  \
    tmplinst.obj +

DEFNAME = bids.def

!else

LINKOBJS =          \
    abstarry.obj +  \
    array.obj    +  \
    deque.obj    +  \
    dict         +  \
    sortarry.obj +  \
    stack.obj    +

DEFNAME = tclass.def

!endif

DLLMAIN = clasmain.obj

$(DLLNAME) : $(DLLMAIN) tmplinst.obj $(OBJS)
    cd $(.PATH.obj)
    tlink @&&!
$(LIB)\c0dl.obj+
$(DLLMAIN)+
$(LINKOBJS)
assoc+
btree+
btreeinn+
btreelfn+
collect+
contain+
dbllist+
hashtbl+
ldate+
list+
ltime+
memmgr+
object+
strng
$(DLLNAME)
/C/c/x/Twd
$(LIB)\crtldll.LIB+
$(LIB)\IMPORT.LIB+
$(LIB)\mathwl.lib+
$(LIB)\cwl.lib
..\..\$(.PATH.cpp)\$(DEFNAME)
!
    rc $(DLLNAME)
    cd ..\..
    copy $(.PATH.obj)\$(DLLNAME) $(.PATH.lib)
    del $(.PATH.obj)\$(DLLNAME)

$(LIBNAME) : $(DLLNAME)
    implib $(.PATH.lib)\$(LIBNAME) $(.PATH.lib)\$(DLLNAME)

!else

TIMER=timer.obj
LTIMER = -+$(.PATH.obj)\timer.obj

$(LIBNAME): $(OBJS) $(TIMER)
    $(LIBR) $(.PATH.lib)\$(LIBNAME) @&&!
    $(LTIMER) &
$(LINKOBJS)
!
!endif
