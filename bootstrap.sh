#!/bin/sh

rm -rf build
mkdir build
cd build
cmake -GNinja -DCMAKE_BUILD_TYPE=DEBUG ..
