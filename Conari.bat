@echo off

if not exist "Conari\\Conari.sln" goto restore
REM ...

goto build

:restore

echo. Getting of Conari engine ...

git submodule update --init --recursive 2>nul || goto err_gitNotFound

goto build

:err_gitNotFound

echo.  
echo. `git` was not found or something went wrong. Check your connection and env. variable `PATH`.

goto exit

:build

setlocal

cd Conari
echo.  

set _cfgConari=Release

if exist "bin\\%_cfgConari%\\raw" goto exit

call build.bat %_cfgConari% >nul

endlocal
goto exit


:exit
exit /B 0