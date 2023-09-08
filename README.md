# Qt 5.6.3 build for Windows XP

This repository contains Qt 5.6.3 sources with a script meant to build the library
with MSVC runtime, as well as additional fixes meant to make the build runnable on
Windows XP.

Keep in mind that this does not aim to be a complete build of the library, I use
OpenGL desktop, no OpenGL ES2, Qtcanvas3d, Qt3d, Qtscript, Qtserialbus, Qtquick2,
Qtwebengine, Qtwebview and some other unneeded module support.

A [WindowsXP build of OpenSSL](https://github.com/R-YaTian/openssl102u-xp) is
included in the library. OpenSSL code will be included in the resulting executables
built with this Qt build if you use the `network` module in your application.
