# Daily C++ Challenge

![2025 Yearly Heatmap](yearly_heatmaps/2025.png?ts=10022025)

## How To Run

* Run `build.bat` to build both executable and pybind
    * This requires [CMake](https://cmake.org/download/) installed in your system
* Run `.venv\Scripts\activate` to activate the venv
* Run `python -c "from dcc import hello; hello()"` to confirm the pybind is installed successfully

## Notes

* This project is modified from the skeleton obtained by running `uv init dcc --lib --build-backend=scikit` 
* Currently `uv.lock` is gitignored
* Comment out the below in `CMakeLists.txt` if not building pybind
```cmake
pybind11_add_module(_core MODULE src/main.cpp)
install(TARGETS _core DESTINATION dcc)
```
* Run `git clean -ffdx -e .venv` to wipe out everything except the venv