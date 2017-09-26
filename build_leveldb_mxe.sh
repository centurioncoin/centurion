#!/bin/bash

cd src/leveldb

export PATH=/usr/lib/mxe/usr/bin:$PATH
make clean
make -j8 libleveldb.a libmemenv.a TARGET_OS=OS_WINDOWS_CROSSCOMPILE CC=i686-w64-mingw32.static-gcc CXX=i686-w64-mingw32.static-g++

# install
# sudo cp libleveldb.a libmemenv.a /usr/lib/mxe/usr/i686-w64-mingw32.static/lib/
