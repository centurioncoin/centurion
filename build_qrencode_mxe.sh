#!/bin/bash

mkdir /tmp/build_qrencode_mxe
cd /tmp/build_qrencode_mxe

wget -c https://fukuchi.org/works/qrencode/qrencode-4.0.0.tar.gz
tar zxf qrencode-4.0.0.tar.gz

cd qrencode-4.0.0
mkdir build_mxe
cd build_mxe

export PATH=/usr/lib/mxe/usr/bin:$PATH
i686-w64-mingw32.static-cmake ..

make -j8
sudo make install