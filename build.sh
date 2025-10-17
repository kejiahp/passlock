#!/bin/sh

# exit on first error
set -e

mkdir -p build
cd build

cmake ..

cmake --build .