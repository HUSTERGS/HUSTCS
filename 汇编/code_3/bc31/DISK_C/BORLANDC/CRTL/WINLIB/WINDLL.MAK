windll: bc30rtl.dll

.PATH.exe = ..\lib
.PATH.obj = d

OBJECTS =        \
    instdata.obj \
    rtldata.obj  \
    rtlmain.obj

OPTIONS = -WDE -ml -1 -D_RTLDLL -lC -c-

bc30rtl.dll : $(OBJECTS)
    copy bcrtl.def $(.PATH.exe)\bc30rtl.def
    cd $(.PATH.obj)
    $(TC) @&&!
    $(OPTIONS) -e..\$(.PATH.exe)\bc30rtl.dll -L..\..\..\lib
    $(OBJECTS)
!   @..\dllmak.rsp ..\$(.PATH.exe)\crtldll.lib
    cd ..\..\lib
    implib temp.lib bc30rtl.dll
    $(TLIB) crtldll.lib +temp.lib
    del temp.lib
    del crtldll.bak
    del bc30rtl.def
    cd ..\winlib
    del *.rsp

.cpp.obj:
    $(TC) $(OPTIONS) -n$(.PATH.obj) -c {$< }

.c.obj:
    $(TC) $(OPTIONS) -n$(.PATH.obj) -c {$< }
