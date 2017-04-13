@echo off

set _gnt=tools/gnt
set _msbuild=tools/hMSBuild


call %_gnt% /p:wpath="%cd%" /p:ngconfig="packages.config;snet\\packages.config" /nologo /v:m /m:4 || goto err

call %_msbuild% -notamd64 "regXwild.sln" /v:normal /l:"packages\vsSBE.CI.MSBuild\bin\CI.MSBuild.dll" /m:4 /t:Build /p:Configuration=Release /p:Platform=Win32 || goto err


goto exit

:err

echo. Build failed. 1>&2
exit /B 1

:exit
exit /B 0