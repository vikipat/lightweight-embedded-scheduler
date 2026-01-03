#!/bin/bash
# Build script for Windows (Git Bash + MinGW)

set -e

echo "Cleaning previous builds..."
make clean

echo "Building debug version..."
make debug

echo "Building release version..."
make release

echo "Build completed successfully."
