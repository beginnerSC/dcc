# Daily C++ Challenge

![2026 Yearly Heatmap](yearly_heatmaps/2026.png?ts=10022025)
![2025 Yearly Heatmap](yearly_heatmaps/2025.png?ts=10022025)

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
* TODO: upgrade poetry (which will break all other projects) and add a `build.py`
    * AI says I can run `poetry config --migrate` to fix `pyproject.toml`? 

### Notes

* Currently this project has an examples folder compiled but the executable is not run by `cnb.bat` nor `.vscode/launch.json`
* AI recommends to keep both examples and (not yet created) docs folders and have docs reference examples so that docs is synced
    * Look into sphinx `literalinclude` and `sphinx-gallery`
    * Examples can be smoked-tested in CI (build and optionally run with a CMake toggle `BUILD_EXAMPLES`) to ensure docs stay accurate
* TODO: `build.py` for poetry, `.vscode/launch.json` and `.vscode/tasks.json`, jupyter notebook demo, sphinx docs, pre-commit setup in README, general python related setup in README