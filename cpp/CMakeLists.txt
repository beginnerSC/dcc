cmake_minimum_required(VERSION 3.15)
project(dcc_core)

# Add the core library from all .cpp files in src/
file(GLOB CORE_SOURCES src/*.cpp)
add_library(dcc_core STATIC ${CORE_SOURCES})

# Include directories for the core library
# Add more include directories as needed
target_include_directories(dcc_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# pybind11 CMake integration:

# Easy
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)
pybind11_add_module(point bindings/point_bindings.cpp)
target_link_libraries(point PRIVATE dcc_core)

# # Advanced
# find_package(Python COMPONENTS Interpreter Development)
# find_package(pybind11 CONFIG REQUIRED)
# Python_add_library(MyModule2 src2.cpp)
# target_link_libraries(MyModule2 PRIVATE pybind11::headers)


################ old working pybind setup ##################

# set(pybind11_DIR ".venv/Lib/site-packages/pybind11/share/cmake/pybind11")
# set(PYBIND11_FINDPYTHON ON)
# find_package(pybind11 CONFIG REQUIRED)

# pybind11_add_module(_core MODULE
#     src/main.cpp
# )
# install(TARGETS _core DESTINATION dcc)


# add_executable(_core_exe    # build an executable to debug; one must specify a main function
#     src/main.cpp
# )

# target_link_libraries(_core_exe PRIVATE pybind11::module)