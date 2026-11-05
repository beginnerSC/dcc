@echo off
setlocal

set "PROJECT=D:\pyscripts\dcc"
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"

if not exist "%VSWHERE%" (
    echo ERROR: Visual Studio locator not found.
    goto :error
)

for /f "usebackq delims=" %%I in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VSROOT=%%I"

if not defined VSROOT (
    echo ERROR: Visual Studio C++ tools not found.
    goto :error
)

call "%VSROOT%\Common7\Tools\VsDevCmd.bat" -arch=amd64 -host_arch=amd64
if errorlevel 1 goto :error

where cl.exe >nul 2>&1
if errorlevel 1 goto :error

cd /d "%PROJECT%"
if errorlevel 1 goto :error

code --new-window "%PROJECT%"
exit /b 0

:error
echo.
echo Failed to launch VS Code with MSVC.
pause
exit /b 1