#!/bin/bash

git submodule update --init --recursive

mkdir build
cd build
cmake ..
make HexaGo -j8
