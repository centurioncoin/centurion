#!/bin/bash

mkdir /tmp/build_db4.8_mxe
cd /tmp/build_db4.8_mxe

wget -c http://download.oracle.com/berkeley-db/db-4.8.30.tar.gz
tar zxvf db-4.8.30.tar.gz

cd db-4.8.30
cd build_unix

export PATH=/usr/lib/mxe/usr/bin:$PATH
../dist/configure --host=i686-w64-mingw32.static --enable-mingw --enable-cxx --disable-replication
make -j8

#install
sudo cp libdb_cxx.a libdb.a /usr/lib/mxe/usr/i686-w64-mingw32.static/lib/
sudo cp clib_port.h db_config.h db_cxx.h db_int.h db.h /usr/lib/mxe/usr/i686-w64-mingw32.static/include/
