cmake_minimum_required(VERSION 3.15)
project(dcc)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # Optional: Force CMake to error if the compiler doesn't support C++23
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(cpp)
add_subdirectory(examples/cpp)
add_subdirectory(tests/cpp)