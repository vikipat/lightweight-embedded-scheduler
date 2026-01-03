#!/bin/bash
# Build script for Linux / WSL

set -e

# Move to project root (script may be run from anywhere)
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
cd "$PROJECT_ROOT"


set -e

echo "Cleaning previous builds..."
make clean

echo "Building debug version..."
make debug

echo "Building release version..."
make release

echo "Build completed successfully."
