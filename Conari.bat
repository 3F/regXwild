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

cd Conari
echo.  

if exist "bin\\" goto exit

set msbuild=tools/msbuild

call %msbuild% gnt.core /p:ngconfig="packages.config" /nologo /v:m /m:4
call %msbuild% "Conari.sln" /verbosity:minimal /l:"packages\vsSBE.CI.MSBuild\bin\CI.MSBuild.dll" /m:4 /t:Build /p:Configuration=Release

:exit