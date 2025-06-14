#!/usr/bin/env zsh
set -euo pipefail

# Optional: allow passing a build‐dir name, default is "build"
BUILD_DIR=${1:-build}

# create & enter build dir
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# configure if needed
if [[ ! -f CMakeCache.txt ]]; then
  cmake ..
fi

# build & test
cmake --build . 
ctest --output-on-failure
