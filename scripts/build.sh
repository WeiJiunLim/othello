#!/bin/bash
set -e

# Default to Linux as Target
TARGET=${1:-linux}

# ===================================================================
# Paths
# ===================================================================

# Get script folder
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
echo "SCRIPT_DIR = $SCRIPT_DIR"

# GGet project root
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
echo "PROJECT_ROOT = $PROJECT_ROOT"

# Go to project root
cd "$PROJECT_ROOT"

# ===================================================================
# Build Folder
# ===================================================================

if [ "$TARGET" = "windows" ]; then
    BUILD_DIR="build-win"
else
    BUILD_DIR="build"
fi

echo "Deleting old build folder: $BUILD_DIR"
rm -rf "$BUILD_DIR"

echo "Creating build folder: $BUILD_DIR"
mkdir -p "$BUILD_DIR"

cd "$BUILD_DIR"

# ===================================================================
# Configure + Build
# ===================================================================

if [ "$TARGET" = "windows" ]; then

    echo "Configuring Windows cross-compile..."

    cmake .. \
        -DCMAKE_SYSTEM_NAME=Windows \
        -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc \
        -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++

elif [ "$TARGET" = "linux" ]; then

    echo "Configuring Linux build..."

    cmake ..

else
    echo "Unknown target: $TARGET"
    echo "Usage:"
    echo "  ./scripts/build.sh linux"
    echo "  ./scripts/build.sh windows"
    exit 1
fi

# ===================================================================
# Compile
# ===================================================================

echo "Building..."
cmake --build .
