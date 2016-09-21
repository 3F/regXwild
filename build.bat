@echo off

set msbuild=tools/msbuild

call %msbuild% gnt.core /p:ngconfig="packages.config" /nologo /v:m /m:4
"packages\vsSBE.CI.MSBuild\bin\CI.MSBuild" "regXwild.sln" /verbosity:normal /m:4 /t:Build /p:Configuration=Release /p:Platform=Win32