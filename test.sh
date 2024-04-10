#!/bin/bash

PROJECT_ROOT_DIR="$(dirname "$0")"
BUILD_DIR="${PROJECT_ROOT_DIR}/build"

mkdir -p "$BUILD_DIR"

cd "$BUILD_DIR" || exit

cmake ..

make

if [ $? -ne 0 ]; then
    echo "Build failed."
    exit 1
fi

ctest -V

cd "$PROJECT_ROOT_DIR"
