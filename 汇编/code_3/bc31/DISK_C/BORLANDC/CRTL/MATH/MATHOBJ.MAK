# List of objects that make up the MATH library.

# Used in all libs
# Statically linked in RTLDLL
OBJS1 =         \
    atan.obj    \
    atanl.obj   \
    atof.obj    \
    atold.obj   \
    clear87.obj \
    ctrl87.obj  \
    difftime.obj\
    efcvt.obj   \
    expld.obj   \
    fabs.obj    \
    fabsl.obj   \
    gcvt.obj    \
    hugeval.obj \
    hypotl.obj  \
    ldtrunc.obj \
    mathwhy.obj \
    polyl.obj   \
    realcvt.obj \
    round.obj   \
    scantod.obj \
    stat87.obj  \
    strtod.obj  \
    xcvt.obj

# Used only in Windows lib
# Statically linked in RTLDLL
OBJS2 =         \
    fbstp.obj   \
    wintrans.obj

# Used only in DOS lib
OBJS3 =         \
    fperr.obj   \
    fpreset.obj

# Used in all libs
# Dynamically linked in RTLDLL
OBJS4 =         \
    matherrl.obj\
    _matherl.obj\
    _pow10.obj  \
    pow10d.obj  \
    pow10l.obj  \
    fmod.obj    \
    floorl.obj  \
    ldexp.obj   \
    matherr.obj \
    fmodl.obj   \
    atan2l.obj  \
    poly.obj    \
    sinl.obj    \
    sqrtl.obj   \
    cosl.obj    \
    sqrt.obj    \
    tanl.obj    \
    powl.obj    \
    ldexpl.obj  \
    tanh.obj    \
    tanhl.obj   \
    coshl.obj   \
    expl.obj    \
    logl.obj    \
    exp.obj     \
    floor.obj   \
    frexp.obj   \
    hypot.obj   \
    log10.obj   \
    modf.obj    \
    pow.obj     \
    sin.obj     \
    sinh.obj    \
    tan.obj     \
    log.obj     \
    _matherr.obj\
    cos.obj     \
    ceil.obj    \
    acosasin.obj\
    cosh.obj    \
    atan2.obj   \
    frexpl.obj  \
    sinhl.obj   \
    modfl.obj   \
    log10l.obj  \
    ceill.obj   \
    acossinl.obj

