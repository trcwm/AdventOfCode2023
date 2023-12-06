#!/bin/sh

rmdir build
mkdir build
cd build
cmake -GNinja ..
