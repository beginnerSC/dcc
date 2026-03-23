#!/bin/bash

cmake --preset=vcpkg-linux
# cmake --build build --config Release
# ./build/tests/cpp/Release/dcc_core_test
cmake --build build --config Debug
./build/tests/cpp/Debug/dcc_core_test