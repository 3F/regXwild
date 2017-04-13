@echo off

if not exist "Conari\\Conari.sln" goto restore
REM ...

goto build

:restore

echo. Getting of Conari engine ...

git submodule update --init --recursive || goto gitNotFound

goto build

:gitNotFound

echo.  
echo. `git` was not found or something went wrong. Check your connection and env. variable `PATH`. 1>&2
exit /B 2

:build

setlocal

cd Conari
echo.  

set _cfgConari=Release

if exist "bin\\%_cfgConari%\\raw" goto exit

call build.bat %_cfgConari% >nul

endlocal


:exit
exit /B 0