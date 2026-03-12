# Daily C++ Challenge

![2026 Yearly Heatmap](yearly_heatmaps/2026.png?ts=10022025)
![2025 Yearly Heatmap](yearly_heatmaps/2025.png?ts=10022025)

* This project is for me to practice C++. In this project there is a reset.bat to delete contents of target h and cpp files. For example `reset vector` deletes contents of `vector.h` and `vector.cpp` so that I can rewrite from scratch and run unittests. One can [diff the master and the dev branches on GitHub](https://github.com/beginnerSC/dcc/compare/master..dev)
* TODO: Move List of Vector's Member Functions to README
* TODO: Note that any single-argument constructor that acts as a type conversion should be explicit unless you intentionally want implicit conversion. For iterators, pointer-to-iterator conversion should never be implicit
* TODO: Note that it's pointless to const a by-value argument
* TODO: Note that `other.size_ = 0` and `other.capacity_ = 0` are still recommended or otherwise when calling other functions like `Resize` from the supposedly hollow object it might break
* TODO: Note that best practice is to use `++(*this)`. This way `Vector::Iterator::operator++(int)` will reuse `Vector::Iterator::operator++()` and the logic stays in one place

## vcpkg + GoogleTest

* [One time initial vcpkg setup](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-cmd)
    * `git clone https://github.com/microsoft/vcpkg.git`
    * `cd vcpkg && bootstrap-vcpkg.bat`
    * `set "VCPKG_ROOT=C:\path\to\vcpkg"`
    * `set PATH=%VCPKG_ROOT%;%PATH%`
    * In project root `vcpkg new --application`
        * In `vcpkg-configuration.json`, the `baseline` in `default-registry` is the HEAD commit of the vcpkg registry at the time running `vcpkg new --application`
    * The `CMakePresets.json` in this guide has `"generator": "Ninja",` which should be replaced by the default generator in the current platform
        * `cmake --help` to check
* To configure cmake and build and run gtest: 
    * Run `cnb` if not using VS Code,
        * Comment out `cmake --preset=vcpkg` to skip repeated config step
        * `cmake --preset=vcpkg` does what `cmake -S . -B build` does which is to configure cmake
        * `cd build & ctest` also runs the test but I like gtest output format more
        * CTest looks for `CTestTestfile.cmake` which is in `build`, as CTest is included and enabled in project root's `CMakeLists.txt`
    * `F5` if using VS Code
        * In `.vscode/launch.json`, use `"preLaunchTask": "CMake: build"` instead of `"preLaunchTask": "CMake: config and build"` to skip repeated config step
    * When to reconfigured: 
        * New cpp/h files added
        * `build` folder deleted, clean rebuild
* `vcpkg add port fmt` to add the `fmt` library to C++ dependencies

## Python Development

* `poetry shell` to create/activate venv for the project
    * This requires `poetry` and `poetry-plugin-shell` pip installed in the system
* `poetry install` to install packages as specified in `pyproject.toml`
* `poetry add numpy` to add `numpy` to Python dependencies
* `poetry build` to build wheel
* Run `update_package.bat` to pip uninstall and pip install the dcc package in the project venv 

## Notes

* Currently this project has an examples folder compiled but the executable is not run by `cnb.bat` nor `.vscode/launch.json`
* AI recommends to keep both examples and docs folders and have docs reference examples so that docs is synced
    * Look into sphinx `literalinclude` and `sphinx-gallery`
    * Examples can be smoked-tested in CI (build and optionally run with a CMake toggle `BUILD_EXAMPLES`) to ensure docs stay accurate
* TODO: jupyter notebook demo, sphinx docs
* TODO: Is `.vscode/c_cpp_properties.json` needed in order for IntelliSense to work properly? That's not the case for dlc
* TODO: After poetry upgrade, run `poetry config --migrate` to fix `pyproject.toml` for broken projects
* In the `Vector` class, reallocation invalidates the iterator. See below example. `std::vector` has the same issue too. It's user's responsibility not to use invalidated iterators. `std::vector` provides `reserve()` to pre-allocate space (prevent reallocation)
```cpp
Vector v;  // capacity_ = 10 by default
v.PushBack(1);
v.PushBack(2);
v.PushBack(3);
// Now size_ = 3, capacity_ = 10 - okay so far

Vector::Iterator it = v.begin();
// it.ptr_ points to v.a_[0]

// Fill up to cause reallocation (capacity becomes 10)
for (int i = 4; i <= 10; ++i) {
  v.PushBack(i);
}
// size_ = 10, capacity_ = 10, no reallocation yet

// THIS push causes reallocation:
v.PushBack(11);  // size_ (10) == capacity_ (10), so:
                 // 1. Allocate new array with capacity_ = 20
                 // 2. Copy old data to new array
                 // 3. delete[] old array  ← OLD ARRAY DELETED!
                 // 4. a_ = new array

// Now it.ptr_ still points to the OLD deleted array!
std::cout << *it;  // Undefined behavior! Crashes or garbage value
```

## List of Vector's Member Functions

* 要照順序寫才能直接看 git diff 對答案
* 所有用到 private member variables 時也照 `a_`，`size_`，`capacity_` 的順序
* Constructors
    * `Vector()`
    * `Vector(int)`
    * Copy constructor
    * Move constructor
* Destructor
* class iterator
    * Constructor
    * Destructor?
    * operators `*`, `->`, `++`, `++(int)`, `==`, `!=`
* begin
* end
* Print
* PushBack
* Resize
* Size
* Copy assignment
* Move assignment
* operator[]