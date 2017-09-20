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

```
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