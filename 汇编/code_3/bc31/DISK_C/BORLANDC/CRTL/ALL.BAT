SET TC=bcc
SET TASM=tasm
SET TLIB=tlib /0
SET LOGFILE=..\log\crtl.log
SET MODEL=s c m l h

rem  Model independent builds
call build startup

rem  Model dependent builds
call build clib
call build winlib
call build math

SET MODEL=l
call build windll
