@echo off
if not "%TASM%"=="" goto skip
set tasm=tasm
:skip

if not %3.==. goto noobjdir
set objdir=.
goto objdirset
:noobjdir
set objdir=%3
:objdirset

if not %2.==. goto noc0dir
set c0dir=.
goto c0dirset
:noc0dir
set c0dir=%2
:c0dirset

if %1.==clib. goto clib
if %1.==winlib. goto winlib
goto error
:clib
echo Building DOS startups
cd %c0dir%
%TASM% /M /MX /Q /T /D__TINY__    c0, %objdir%\c0t
%TASM% /M /MX /Q /T /D__SMALL__   c0, %objdir%\c0s
%TASM% /M /MX /Q /T /D__COMPACT__ c0, %objdir%\c0c
%TASM% /M /MX /Q /T /D__MEDIUM__  c0, %objdir%\c0m
%TASM% /M /MX /Q /T /D__LARGE__   c0, %objdir%\c0l
%TASM% /M /MX /Q /T /D__HUGE__    c0, %objdir%\c0h

%TASM% /M /MX /Q /T /D__TINY__    /D_DSSTACK_ c0, %objdir%\c0ft
%TASM% /M /MX /Q /T /D__SMALL__   /D_DSSTACK_ c0, %objdir%\c0fs
%TASM% /M /MX /Q /T /D__COMPACT__ /D_DSSTACK_ c0, %objdir%\c0fc
%TASM% /M /MX /Q /T /D__MEDIUM__  /D_DSSTACK_ c0, %objdir%\c0fm
%TASM% /M /MX /Q /T /D__LARGE__   /D_DSSTACK_ c0, %objdir%\c0fl
%TASM% /M /MX /Q /T /D__HUGE__                c0, %objdir%\c0fh
if not %c0dir%==. cd ..
goto exit
:winlib
echo Building Windows startups
cd %c0dir%
%TASM% /M /MX /Q /T /D__SMALL__   /D__WINDOWS__ c0w, %objdir%\c0ws
%TASM% /M /MX /Q /T /D__COMPACT__ /D__WINDOWS__ c0w, %objdir%\c0wc
%TASM% /M /MX /Q /T /D__MEDIUM__  /D__WINDOWS__ c0w, %objdir%\c0wm
%TASM% /M /MX /Q /T /D__LARGE__   /D__WINDOWS__ c0w, %objdir%\c0wl

%TASM% /M /MX /Q /T /D__SMALL__   /D__WINDOWS__ c0d, %objdir%\c0ds
%TASM% /M /MX /Q /T /D__COMPACT__ /D__WINDOWS__ c0d, %objdir%\c0dc
%TASM% /M /MX /Q /T /D__MEDIUM__  /D__WINDOWS__ c0d, %objdir%\c0dm
%TASM% /M /MX /Q /T /D__LARGE__   /D__WINDOWS__ c0d, %objdir%\c0dl
if not %c0dir%==. cd ..
goto exit
:error
echo BUILD-C0.BAT
echo Usage: build-c0 libtype [srcdir [objdir]]
echo  libtype   clib (DOS) or winlib (Windows)
echo  srcdir    source subdirectory (default is ".")
echo  objdir    object subdirectory relative to srcdir (default is ".")
echo Example: build-c0 clib startup ..\lib
echo This batch file builds the C startup module (or modules) for
echo DOS or Windows.  All memory models are built.
:exit
