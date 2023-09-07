REM this script assumes that the Microsoft.VisualStudio.Component.WinXP
REM component is available in the local Visual Studio installation.

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64_x86 10.0.10240.0 -vcvars_ver=14.16

REM https://devblogs.microsoft.com/cppblog/windows-xp-targeting-with-c-in-visual-studio-2012/
set INCLUDE=%ProgramFiles(x86)%\Microsoft SDKs\Windows\v7.1A\Include;D:\OpenSSL\include;%INCLUDE%
set PATH=%ProgramFiles(x86)%\Microsoft SDKs\Windows\v7.1A\Bin;%PATH%
set LIB=%ProgramFiles(x86)%\Microsoft SDKs\Windows\v7.1A\Lib;D:\OpenSSL\lib;%LIB%

REM the additional linker parameters are taken care of by qmake, since the
REM -target xp switch causes the configure script to set the QMAKE_TARGET_OS
REM variable to "xp", which is then used to define QMAKE_SUBSYSTEM_SUFFIX to
REM ",5.01", which is then passed as the extra suffix to the linker's subsystem
REM parameter.

REM harfbuzz is disabled because of QTBUG-38913
call configure.bat -prefix D:\Qt\5.6.3XP\ -opensource -confirm-license^
 -release -nomake examples -nomake tests -target xp^
 -no-harfbuzz -no-sse3 -no-ssse3 -no-sse4.1 -no-sse4.2 -no-avx -no-avx2^
 -platform win32-msvc2017 -no-angle -opengl desktop -openssl-linked

7z x jom.zip

mkdir D:\Qt
jom
nmake
nmake install
xcopy /Y /S /Q D:\OpenSSL\lib D:\Qt\5.6.3XP\lib

cd /d D:\Qt
7z a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on -sse Qt-5.6.3-XP.7z 5.6.3XP
pause
