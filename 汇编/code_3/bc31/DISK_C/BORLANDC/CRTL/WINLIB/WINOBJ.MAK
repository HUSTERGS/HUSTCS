# List of object files for WINLIB.MAK.

# Used in all libs
# Statically linked in RTLDLL
OBJS1 =         \
    abort.obj   \
    easywin.obj \
    errexit.obj \
    ewconio.obj \
    ewinproc.obj\
    farheap.obj \
    fperr.obj   \
    fpinit.obj  \
    heap.obj    \
    h_chkstk.obj\
    intr.obj    \
    intdos.obj  \
    int86.obj   \
    ioctl.obj   \
    necp.obj    \
    ptable.obj  \
    wrealcvt.obj\
    wscantod.obj\
    setargv.obj \
    setargv0.obj\
    setenv.obj  \
    setenvrn.obj\
    setjmp.obj  \
    suballoc.obj\
    wcfncptr.obj\
    wep.obj     \
    winmain.obj  

# Used in all libs
# Dynamically linked in RTLDLL
OBJS2 =         \
    assert.obj  \
    signal.obj  \
    asmmem.obj  \
    winmem.obj  \
    fheap.obj   

# Used only in RTLDLL
# Dynamically linked in RTLDLL
OBJS3 =         \


