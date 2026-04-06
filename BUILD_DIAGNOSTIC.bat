@echo off
REM AI Creator - Build Diagnostic Script
REM Shows all compilation errors and warnings

setlocal enabledelayedexpansion

title AI Creator - Build Diagnostic

echo.
echo ╔════════════════════════════════════════╗
echo ║   AI Creator - Build Diagnostic        ║
echo ║      (Shows all error details)         ║
echo ╚════════════════════════════════════════╝
echo.

set BUILD_PATH=%USERPROFILE%\AI Creator\build

if not exist "%BUILD_PATH%" (
    echo [!] Build directory not found
    echo [*] Please run QUICK_INSTALL_VS2026.bat first
    pause
    exit /b 1
)

cd /d "%BUILD_PATH%"

echo [*] Cleaning previous build...
rmdir /s /q CMakeFiles >nul 2>&1
del /q CMakeCache.txt >nul 2>&1
del /q cmake_install.cmake >nul 2>&1

echo [✓] Build directory cleaned
echo.

echo [*] Configuring project...
cmake "%USERPROFILE%\AI Creator\cpp-backend" -G "Visual Studio 18 2026"
if %errorlevel% neq 0 (
    echo [✗] CMake configuration failed
    pause
    exit /b 1
)

echo [✓] Configuration successful
echo.

echo [*] Building project (showing all output)...
echo [*] This will show all errors and warnings...
echo.

REM Build with full output
cmake --build . --config Release --verbose

if %errorlevel% equ 0 (
    echo.
    echo [✓] Build successful!
    echo [*] Executable: "%BUILD_PATH%\bin\ai_creator.exe"
) else (
    echo.
    echo [✗] Build failed
    echo [*] Check the errors above
    echo [*] Common issues:
    echo [*]   - Missing #include statements
    echo [*]   - Syntax errors in source files
    echo [*]   - Missing function implementations
)

echo.
pause
