# MAKEFILE - makes a library (or libraries) for a single memory model.
#
# Invoke as follows:
#
# MAKE -DMODEL=x [clib | winlib | windll | math | startup | all]
#

!include "rules.mak"

.swap

!if !$d(MODEL)
!error MODEL not defined.
!endif

!if !$d(LOGFILE)
LOGFILE = con
!endif

MAKEFLAGS = -DMODEL=$(MODEL) -DLOGFILE=$(LOGFILE)

bad :
        echo No target specified (clib, winlib, windll, math, startup, or all).

# CLIB - the DOS libraries

clib :
        cd clib
        time < ..\return.txt >> $(LOGFILE)
        make -DMODEL=$(MODEL) -fclib all >> $(LOGFILE)
        make -DMODEL=$(MODEL) -ffarfuncs all >> $(LOGFILE)
!if '$(MODEL)'=='c'
        make -DMODEL=$(MODEL) -fclib -DTARGET wildargs.obj >> $(LOGFILE)
!endif
        cd ..\iostream
        make -DMODEL=$(MODEL) -fiostream all >> $(LOGFILE)
        time < ..\return.txt >> $(LOGFILE)
        cd ..

# WINLIB - the Windows libraries

winlib :
        cd clib
        time < ..\return.txt >> $(LOGFILE)
        make -DMODEL=$(MODEL) -DWINDOWS -fclib all >> $(LOGFILE)
        make -DMODEL=$(MODEL) -DWINDOWS -ffarfuncs all >> $(LOGFILE)
        cd ..\winlib
        make -DMODEL=$(MODEL) -fwinlib all >> $(LOGFILE)
        make -DMODEL=$(MODEL) -findep >> $(LOGFILE)
        make -fimport >> $(LOGFILE)
        cd ..\iostream
        make -DMODEL=$(MODEL) -DWINDOWS -fiostream all >> $(LOGFILE)
        time < ..\return.txt >> $(LOGFILE)
        cd ..

# WINDLL - the Windows dll and static link library

windll :
        cd clib
        time < ..\return.txt >> $(LOGFILE)
        if exist ..\winlib\dllmak.rsp del ..\winlib\dllmak.rsp
        make -DMODEL=$(MODEL) -DWINDLL -fclib all >> $(LOGFILE)
        make -DMODEL=$(MODEL) -DWINDLL -ffarfuncs all >> $(LOGFILE)
        cd ..\iostream
        make -DMODEL=$(MODEL) -DWINDLL -fiostream all >> $(LOGFILE)
        cd ..\math
        make -DMODEL=$(MODEL) -DWINDLL -fmath all >> $(LOGFILE)
        cd ..\winlib
        make -DMODEL=$(MODEL) -DWINDLL -fwinlib all >> $(LOGFILE)
        make -DMODEL=$(MODEL) -DWINDLL -findep >> $(LOGFILE)
        make -fwindll >> $(LOGFILE)
        time < ..\return.txt >> $(LOGFILE)
        cd ..

# MATH - the math libraries

math :
        cd math
        time < ..\return.txt >> $(LOGFILE)
        make -DMODEL=$(MODEL) -fmath all >> $(LOGFILE)
        make -DMODEL=$(MODEL) -DWINDOWS -fmath all >> $(LOGFILE)
        time < ..\return.txt >> $(LOGFILE)
        cd ..

# STARTUP - the startup code

startup :
        cd startup
        time < ..\return.txt >> $(LOGFILE)
        make -fstartup >> $(LOGFILE)
        time < ..\return.txt >> $(LOGFILE)
        cd ..

# ALL - build all of the above libraries

all : clib winlib windll checkmath checkstartup

checkmath :
        if exist math\math.mak make $(MAKEFLAGS) math

checkstartup :
        if exist startup\startup.mak make $(MAKEFLAGS) startup

# CLEANUP - close off the log file and return to home directory

cleanup :
