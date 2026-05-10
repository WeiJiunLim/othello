#!/bin/bash

# Get script folder
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
echo "SCRIPT_DIR = $SCRIPT_DIR"

# GGet project root
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
echo "PROJECT_ROOT = $PROJECT_ROOT"

# Go to project root
cd "$PROJECT_ROOT"

# Delete build folder if it exists
# echo "Deleting old build folder..."
# rm -rf build

# Create build folder
echo "Creating new build folder..."
mkdir -p build

# Go to build folder
cd build

# Run CMake
echo "Running CMake..."
cmake ..

# Compile 
echo "Running make..."
make
