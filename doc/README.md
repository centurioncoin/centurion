centurion
Copyright (c) 2013 NovaCoin Developers
Copyright (c) 2011-2012 PPCoin Developers
Distributed under the MIT/X11 software license, see the accompanying
file license.txt or http://www.opensource.org/licenses/mit-license.php.
This product includes software developed by the OpenSSL Project for use in
the OpenSSL Toolkit (http://www.openssl.org/).  This product includes
cryptographic software written by Eric Young (eay@cryptsoft.com).


## Intro

centurion is a free open source project derived from Bitcoin, with
the goal of providing a long-term energy-efficient scrypt-based crypto-currency.
Built on the foundation of Bitcoin, PPCoin and NovaCoin, innovations such as proof-of-stake
help further advance the field of crypto-currency.

## To Build

Build local LevelDB:
```
cd src/leveldb
make libleveldb.a libmemenv.a
cd ../..
```

Build Centurion:
```
mkdir build
cd build
cmake ..
make
```
Binaries are placed in same dir (build), tests are in src/tests.

Optional GUI and tests:
```
rm -f CMakeCache.txt ; # clear cached values
cmake .. -DBUILD_GUI=OFF -DBUILD_TESTS=OFF
```

Debug and release build types:
```
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake .. -DCMAKE_BUILD_TYPE=Release
```

### Dependencies

Ubuntu/Debian

apt install build-essential cmake libboost-all-dev libssl-dev libsodium-dev libminiupnpc-dev libdb-dev libdb++-dev

| Library | Decription |
| --- | --- |
| Boost | Library for threading, data structures, etc |
| libssl, libcrypto | Random Number Generation, Elliptic Curve Cryptography |
| libsodium | Used for equihash calculation
| miniupnpc | UPnP Support |
| leveldb | Can be compiled from `src/leveldb` |
| libdb4.8 | Wallet storage |

Optional GUI dependencies:

| Library | Decription |
| --- | --- |
| Qt5 | GUI toolkit |
| libqrencode | Generate QR codes |
| librt ||

## Windows cross-compilation
MXE (M cross environment) setup instructions and packages can be found at http://pkg.mxe.cc.

Existing MXE binary packages:
- boost
- openssl
- miniupnpc
- libsodium
- qt qtbase qttools

Other deps are built with scripts:
- `build_db4.8_mxe.sh`
- `build_qrencode_mxe.sh`
- `build_leveldb_mxe.sh`

```
cd build
/usr/lib/mxe/usr/bin/i686-w64-mingw32.static-cmake ..
make
```

SUMMARY STEP BY STEP

****
**** Packet to install
****

sudo add-apt-repository ppa:bitcoin/bitcoin
sudo apt-get update
sudo apt-get install libdb4.8-dev libdb4.8++-dev build-essential libtool
autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils
git libboost-all-dev libminiupnpc-dev

****
**** Optionally crate  swap file  for compile
****

sudo fallocate -l 2G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile


git clone https://github.com/centurioncoin/centurion.git

cd centurion/src/
make -f makefile.unix

****
**** Build local LevelDB
****

cd src/leveldb
cd leveldb/
make libleveldb.a libmemenv.a
cd ../..

****
**** Build Centurion
****
**** from the centurion folder downloaded from github


mkdir build
cd build
cmake .. -DBUILD_GUI=OFF -DBUILD_TESTS=OFF
make

****
**** Binaries are placed in same dir (build)
****
