#!/bin/bash
cd "$(dirname "$0")/build"
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)
./FTSClient
exit