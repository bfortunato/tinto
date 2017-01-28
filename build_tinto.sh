#!/bin/bash

rm -rf ./lib
mkdir lib
cd lib
cmake ..
make
