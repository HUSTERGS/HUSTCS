@echo off
rem  This batch file will make the object file directories necessary to
rem  build the Borland C++ 3.0 Run Time Libraries.

if /%1==/ goto error

rem  ALL as the parameter will make all subdirectories.

if not /%1==/all goto %1

md lib
md log

:clib
for %%m in (s m c l h d) do md clib\%%m
for %%m in (s m c l h) do md clib\%%mp
for %%m in (s m c l)   do md clib\w%%m
for %%m in (s m c l)   do md clib\w%%mp
for %%m in (m l)       do md clib\b%%m
if not /%1==/all goto end

:winlib
for %%m in (s m c l d) do md winlib\%%m
for %%m in (s m c l) do md winlib\%%mp
if not /%1==/all goto end

:iostream
for %%m in (s m c l h d) do md iostream\%%m
for %%m in (s m c l)   do md iostream\w%%m
if not /%1==/all goto end

:math
for %%m in (s m c l h d) do md math\%%m
for %%m in (s m c l  ) do md math\w%%m
if not /%1==/all goto end

goto end

:error
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo !!                                            !!
echo !!  ERROR: Must pass option parameter         !!
echo !!                                            !!
echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
echo.
echo.
echo   syntax: makedirs  {options}
echo.
echo.   
echo   Options for the "options" argument:
echo.
echo   all - will create each object file directory, or:
echo   clib  winlib  iostream  math
echo.
:end
