@echo off
setlocal

if /I "%~1"=="-h" goto :usage
if /I "%~1"=="--help" goto :usage
if /I "%~1"=="/?" goto :usage

set "DCC_ROOT=%~dp0"
set "DCC_TARGET=%~1"
if "%DCC_TARGET%"=="" set "DCC_TARGET=vector"

poetry run python -c "import os, sys; from pathlib import Path; root = Path(os.environ['DCC_ROOT']).resolve(); sys.path.insert(0, str(root / 'src')); from dcc import reset_targets; target = os.environ['DCC_TARGET']; results = reset_targets([target], project_root=root); print('Reset complete:', ', '.join(results.keys()))"
if errorlevel 1 (
    echo Reset failed.
    exit /b 1
) 

echo Done.
exit /b 0

:usage
echo Usage: reset.bat [target^|all]
echo.
echo Examples:
echo   reset.bat vector
echo   reset.bat all
echo.
echo Default target is vector when omitted.
exit /b 0
