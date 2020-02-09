@echo off

set cim=packages\vsSolutionBuildEvent\cim.cmd -vsw-priority "Microsoft.VisualStudio.Component.VC.Redist.14.Latest Microsoft.NetCore.Component.SDK"
set _gnt=tools/gnt

set reltype=%~1
if not defined reltype (
    set reltype=Release
)

call %_gnt% /p:wpath="%cd%" /p:ngconfig="packages.config;snet\\packages.config" /nologo /v:m /m:4 || goto err

    setlocal
        set "__InitBuild=1" & call :build Win32 Unicode
    endlocal

    call :build x64 Unicode
    call :build Win32 MultiByte

    setlocal
        set "__FinalBuild=1" & call :build x64 MultiByte
    endlocal


goto exit


:build
setlocal
    set "platform=%~1" & set "CharacterSet=%~2"
    call %cim% "regXwild.sln" /v:m /m:4 /p:Configuration="%reltype%" /p:Platform=%platform% || goto err
endlocal
exit /B 0

:err

echo. Build failed. 1>&2
exit /B 1

:exit
exit /B 0