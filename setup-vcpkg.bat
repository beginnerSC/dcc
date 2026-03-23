@echo off
setlocal enabledelayedexpansion

echo ================================
echo vcpkg Setup for Windows
echo ================================
echo.

REM Step 1: Clone vcpkg
echo Step 1: Cloning vcpkg repository...
if exist "%USERPROFILE%\vcpkg" (
    echo vcpkg already exists at %%USERPROFILE%%\vcpkg, skipping clone.
) else (
    git clone https://github.com/Microsoft/vcpkg.git "%USERPROFILE%\vcpkg"
    echo ✓ vcpkg cloned to %%USERPROFILE%%\vcpkg
)
echo.

REM Step 2: Bootstrap vcpkg
echo Step 2: Bootstrapping vcpkg...
cd /d "%USERPROFILE%\vcpkg"
call bootstrap-vcpkg.bat
echo ✓ vcpkg bootstrapped successfully
echo.

REM Step 3: Set VCPKG_ROOT environment variable
echo Step 3: Setting VCPKG_ROOT environment variable...
set "VCPKG_ROOT=%USERPROFILE%\vcpkg"
echo ✓ VCPKG_ROOT set to %%USERPROFILE%%\vcpkg in current session
echo.

REM Step 4: Set environment variable permanently (requires admin)
echo Step 4: Setting VCPKG_ROOT permanently (requires admin privileges)...
setx VCPKG_ROOT "%USERPROFILE%\vcpkg"
echo ✓ VCPKG_ROOT saved to Windows environment variables
echo Note: You may need to restart your terminal for changes to take effect.
echo.

REM Step 5: Initialize vcpkg for the project
echo Step 5: Initializing vcpkg for the project...
cd /d "%~dp0"
"%USERPROFILE%\vcpkg\vcpkg" new --application
echo ✓ vcpkg initialized for the project
echo.

echo ================================
echo Setup Complete!
echo ================================
echo.
echo You can now run the build script with:
echo   cnb.bat
echo.

endlocal
