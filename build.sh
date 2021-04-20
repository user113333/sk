#!/bin/bash

if [ "$1" != "-no-cmake" ]
then
    cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja -B ./bin .
fi

ninja -C bin
