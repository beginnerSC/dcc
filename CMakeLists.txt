cmake_minimum_required(VERSION 3.15)
project(dcc LANGUAGES CXX)

set(pybind11_DIR ".venv/Lib/site-packages/pybind11/share/cmake/pybind11")
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(_core MODULE 
    src/main.cpp
)
install(TARGETS _core DESTINATION dcc)


add_executable(_core_exe    # build an executable to debug; one must specify a main function
    src/main.cpp
)

target_link_libraries(_core_exe PRIVATE pybind11::module)