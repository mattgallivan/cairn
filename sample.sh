#!/bin/bash

PROJECT_ROOT_DIR="$(dirname "$0")"
BUILD_DIR="${PROJECT_ROOT_DIR}/build"

run_sample() {
    local sample_name="$1"

    # Check if the build directory exists
    if [ ! -d "$BUILD_DIR" ]; then
        mkdir -p "$BUILD_DIR" || { echo "Failed to create build directory."; exit 1; }
    fi

    # Change to the build directory
    cd "$BUILD_DIR" || { echo "Failed to change to build directory."; exit 1; }

    # Run cmake to configure the project
    cmake ..

    # Build the sample
    make "${sample_name}_sample"

    # Check if the build was successful
    if [ $? -ne 0 ]; then
        echo "Build failed."
        exit 1
    fi

    # Run the sample
    "./samples/${sample_name}_sample"
}

if [ $# -ne 1 ]; then
    echo "Usage: $0 <sample_name>"
    exit 1
fi

run_sample "$1"

cd "$PROJECT_ROOT_DIR" || { echo "Failed to change back to project root directory."; exit 1; }
