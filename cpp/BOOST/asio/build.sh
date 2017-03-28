#!/bin/bash

export CMAKE=/pfs/fsf/cmake/2.8.12.1_fixed/bin/cmake
export CXX=/puma/prod/gcc/4.9.2-3/bin/g++
export CXXFLAGS="-g -std=c++11"

${CMAKE} .
