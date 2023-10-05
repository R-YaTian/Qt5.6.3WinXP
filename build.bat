REM this script assumes that the Microsoft.VisualStudio.Component.WinXP
REM component is available in the local Visual Studio installation.

call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat" x86
call "C:\Program Files (x86)\MicrosoftDirectXSDK\Utilities\bin\dx_setenv.cmd" x86

REM https://devblogs.microsoft.com/cppblog/windows-xp-targeting-with-c-in-visual-studio-2012/
set INCLUDE=%ProgramFiles(x86)%\Microsoft SDKs\Windows\v7.1A\Include;C:\OpenSSL\include;%INCLUDE%
set PATH=%ProgramFiles(x86)%\Microsoft SDKs\Windows\v7.1A\Bin;.\gnuwin32\bin;.\Python27;%PATH%
set LIB=%ProgramFiles(x86)%\Microsoft SDKs\Windows\v7.1A\Lib;C:\OpenSSL\lib;%LIB%

REM the additional linker parameters are taken care of by qmake, since the
REM -target xp switch causes the configure script to set the QMAKE_TARGET_OS
REM variable to "xp", which is then used to define QMAKE_SUBSYSTEM_SUFFIX to
REM ",5.01", which is then passed as the extra suffix to the linker's subsystem
REM parameter.

REM harfbuzz is disabled because of QTBUG-38913
call configure.bat -prefix C:\Qt\5.6.3\ -opensource -confirm-license^
 -release -nomake examples -nomake tests -target xp -mp -no-pch^
 -no-harfbuzz -no-sse3 -no-ssse3 -no-sse4.1 -no-sse4.2 -no-avx -no-avx2^
 -platform win32-msvc2013 -opengl dynamic -openssl-linked

7z x Python27.7z
7z x gnuwin32.7z

mkdir C:\Qt
nmake
nmake install
copy /Y C:\OpenSSL\bin\libeay32.dll C:\Qt\5.6.3\bin\libeay32.dll
copy /Y C:\OpenSSL\bin\ssleay32.dll C:\Qt\5.6.3\bin\ssleay32.dll
xcopy /Y /S /Q C:\OpenSSL\lib C:\Qt\5.6.3\lib

cd /d C:\Qt
7z a -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on -sse Qt-5.6.3-XP.7z 5.6.3
pause
