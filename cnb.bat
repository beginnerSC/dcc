cmake --preset=vcpkg
@REM cmake --build build --config Release
@REM .\build\tests\cpp\Release\dcc_core_test.exe
cmake --build build --config Debug
.\build\tests\cpp\Debug\dcc_core_test.exe