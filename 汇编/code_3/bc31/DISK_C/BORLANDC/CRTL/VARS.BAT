@echo off
rem     VARS.BAT
rem
rem     sets environment variables for library build process
rem
rem     any variable that has already been assigned a value will
rem     not be reassigned
rem
rem     settings:
rem
rem     TC      bcc
rem     TASM    tasm
rem     MODEL   s c m l h
rem     TLIB    tlib /0
rem     LOGFILE ..\log\crtl.log

if not "%TC%"=="" goto skip1
set TC=bcc
:skip1
if not "%TASM%"=="" goto skip2
set TASM=tasm
:skip2
if not "%MODEL%"=="" goto skip3
set MODEL=s c m l h
:skip3
if not "%TLIB%"=="" goto skip4
set TLIB=tlib /0
:skip4
if not "%LOGFILE%"=="" goto checkenv
echo LOGFILE environment variable not set.  Setting it to ..\log\crtl.log
set LOGFILE=..\log\crtl.log
:checkenv
set TESTENV=test
if not "%TESTENV%"=="test" goto error
goto exit
:error
echo Environment full.  Try adding /E:2048 to SHELL line of CONFIG.SYS, then reboot.
:exit
set TESTENV=
