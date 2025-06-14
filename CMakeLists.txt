cmake_minimum_required(VERSION 3.10)
project(mini_stl LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 1) Header-only DSA library (all headers in include/)
add_library(DSA INTERFACE)
target_include_directories(DSA
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 2) Fetch Catch2 v2.x
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.10
)
FetchContent_MakeAvailable(Catch2)

# 3) Enable CTest
enable_testing()

# 4) Add tests/ subdirectory
add_subdirectory(tests)
