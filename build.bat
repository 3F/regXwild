@echo off

set cim=packages\vsSolutionBuildEvent\cim.cmd -vsw-priority "Microsoft.VisualStudio.Component.VC.Redist.14.Latest Microsoft.NetCore.Component.SDK"
set _gnt=tools/gnt

set reltype=%~1
if not defined reltype (
    set reltype=Release
)

call %_gnt% /p:wpath="%cd%" /p:ngconfig="packages.config;snet\\packages.config" /nologo /v:m /m:4 || goto err

setlocal
    call %cim% "regXwild.sln" /v:m /m:4 /p:Configuration="%reltype%" /p:Platform=Win32 || goto err
endlocal

setlocal
    set regXwildx32x64=1
    call %cim% "regXwild.sln" /v:m /m:4 /p:Configuration="%reltype%" /p:Platform=x64 || goto err
endlocal


goto exit

:err

echo. Build failed. 1>&2
exit /B 1

:exit
exit /B 0