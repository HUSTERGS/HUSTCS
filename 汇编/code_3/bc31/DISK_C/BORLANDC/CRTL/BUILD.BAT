@echo off

rem     BUILD.BAT
rem
rem     builds RTL for windows or DOS
rem
rem     parameters:
rem
rem     %1 name of library to be built 
rem     all  clib  winlib  windll  startup  math

:checkparm

if %1.==. goto error
if %1 == winlib goto ok
if %1 == windll goto ok
if %1 == clib goto ok
if %1 == math goto ok
if %1 == startup goto ok
if %1 == all goto ok
goto error

:ok

echo test >clib\s\test
if not exist clib\s\test goto makedirs
del clib\s\test
goto okdirs
:makedirs
echo Creating object directories...
call makedirs all

:okdirs

if not "%MODEL%"=="" goto checklog
if %1 == windll goto largemodel
echo MODEL environment variable not set.  Setting it to all models.
if %1 == winlib goto winmodel
set MODEL=s c m l h
goto checklog
:largemodel
set MODEL=l
goto checklog
:winmodel
set MODEL=s c m l

:checklog

call vars

:build

if %1 == startup goto startup

for %%x in (%MODEL%) do make -DMODEL=%%x %1
goto exit

:startup

if not exist startup\startup.mak goto exit
make -DMODEL=x startup
goto exit

:makedirs

echo You must run MAKEDIRS
:error

echo BUILD.BAT
echo Usage: build libtype
echo   where libtype is one of 
echo   all  clib  winlib  windll startup  math
echo 
echo Example: build clib
echo 
echo This batch file rebuilds one or more libraries.  It compiles or assembles
echo all source files, and rebuilds the library (or libraries).
echo 
echo The MODEL environment variable specifies the memory model (or models)
echo to rebuild. If MODEL isn't set, all appropriate models are rebuilt.
echo 
echo The LOGFILE environment variable specifies the name of the error log file.
echo If LOGFILE isn't set, it is set to ..\log\crtl.log.  Set LOGFILE to CON 
echo to send the error log to the screen.

goto exit

:exit
