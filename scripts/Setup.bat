@echo off

pushd ..
vendor\Premake\premake5.exe --file=Build-SmellsLikeRubber.lua vs2026
popd
pause