export PATH="./gnuwin32/bin:$PATH"
OPENSSL_LIBS='-lssl -lcrypto -lgdi32' ./configure -prefix /mingw32/qt563-static -opensource -confirm-license \
 -release -static -nomake examples -nomake tests -no-pch \
 -no-harfbuzz -no-sse3 -no-ssse3 -no-sse4.1 -no-sse4.2 -no-avx -no-avx2 \
 -platform win32-g++ -opengl auto -openssl-linked

7z x gnuwin32.7z

make -j$(nproc)
make install
