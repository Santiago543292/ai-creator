@echo off
REM AI Creator - Quick Install (VS 2026 Compatible)
REM One-click installation with proper CMake cache handling

setlocal enabledelayedexpansion

title AI Creator - Quick Install (VS 2026)

echo.
echo ╔════════════════════════════════════════╗
echo ║   AI Creator - Quick Install v1.2.0    ║
echo ║        (VS 2026 Compatible)            ║
echo ╚════════════════════════════════════════╝
echo.

REM Check for administrator privileges
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo [!] This installer requires Administrator privileges
    echo [*] Requesting administrator access...
    powershell -Command "Start-Process cmd -ArgumentList '/c %0' -Verb RunAs"
    exit /b
)

set INSTALL_PATH=%USERPROFILE%\AI Creator
set SOURCE_DIR=%~dp0

echo [*] Installation will proceed with default settings
echo [*] Installation path: %INSTALL_PATH%
echo.

REM Create installation directory
if not exist "%INSTALL_PATH%" (
    mkdir "%INSTALL_PATH%"
)

echo [*] Checking prerequisites...

REM Check CMake
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo [!] CMake not found. Installing...
    powershell -Command "Invoke-WebRequest -Uri 'https://github.com/Kitware/CMake/releases/download/v3.27.0/cmake-3.27.0-windows-x86_64.msi' -OutFile '%TEMP%\cmake.msi'" >nul 2>&1
    if exist "%TEMP%\cmake.msi" (
        start /wait msiexec /i "%TEMP%\cmake.msi" /quiet
        del "%TEMP%\cmake.msi"
        echo [✓] CMake installed
    )
) else (
    echo [✓] CMake found
)

REM Check for Visual Studio
echo [*] Checking for Visual Studio...

set VS_FOUND=0
set VS_VERSION=

REM Check for VS 2026
reg query "HKLM\SOFTWARE\Microsoft\VisualStudio\18.0" >nul 2>&1
if %errorlevel% equ 0 (
    echo [✓] Visual Studio 2026 found
    set VS_FOUND=1
    set VS_VERSION=2026
    set CMAKE_GENERATOR=Visual Studio 18 2026
)

REM Check for VS 2022
if %VS_FOUND% equ 0 (
    reg query "HKLM\SOFTWARE\Microsoft\VisualStudio\17.0" >nul 2>&1
    if %errorlevel% equ 0 (
        echo [✓] Visual Studio 2022 found
        set VS_FOUND=1
        set VS_VERSION=2022
        set CMAKE_GENERATOR=Visual Studio 17 2022
    )
)

REM Check Program Files for VS 2026
if %VS_FOUND% equ 0 (
    if exist "C:\Program Files\Microsoft Visual Studio\2026" (
        echo [✓] Visual Studio 2026 found (Program Files)
        set VS_FOUND=1
        set VS_VERSION=2026
        set CMAKE_GENERATOR=Visual Studio 18 2026
    )
)

REM Check Program Files for VS 2022
if %VS_FOUND% equ 0 (
    if exist "C:\Program Files\Microsoft Visual Studio\2022" (
        echo [✓] Visual Studio 2022 found (Program Files)
        set VS_FOUND=1
        set VS_VERSION=2022
        set CMAKE_GENERATOR=Visual Studio 17 2022
    )
)

REM Generic check
if %VS_FOUND% equ 0 (
    if exist "C:\Program Files\Microsoft Visual Studio" (
        echo [✓] Visual Studio found
        set VS_FOUND=1
        set VS_VERSION=Latest
        set CMAKE_GENERATOR=Visual Studio 17 2022
    )
)

if %VS_FOUND% equ 0 (
    echo [✗] Visual Studio not found
    echo.
    echo [!] Visual Studio 2017 or later is required
    echo [*] Download from: https://visualstudio.microsoft.com/
    echo.
    pause
    exit /b 1
)

echo.
echo [✓] Prerequisites checked

echo [*] Copying files...
xcopy "%SOURCE_DIR%cpp-backend" "%INSTALL_PATH%\cpp-backend" /E /I /Y >nul
echo [✓] Files copied

set BUILD_PATH=%INSTALL_PATH%\build

REM CRITICAL: Clean old CMake cache to avoid conflicts
if exist "%BUILD_PATH%" (
    echo [*] Cleaning old build files...
    rmdir /s /q "%BUILD_PATH%\CMakeFiles" >nul 2>&1
    del /q "%BUILD_PATH%\CMakeCache.txt" >nul 2>&1
    del /q "%BUILD_PATH%\cmake_install.cmake" >nul 2>&1
    del /q "%BUILD_PATH%\Makefile" >nul 2>&1
    echo [✓] Old build files cleaned
)

if not exist "%BUILD_PATH%" mkdir "%BUILD_PATH%"

cd /d "%BUILD_PATH%"

echo [*] Building application (this may take a few minutes)...
echo [*] Using Visual Studio: !VS_VERSION!
echo [*] CMake Generator: !CMAKE_GENERATOR!
echo.

REM Configure with the correct generator
cmake "%INSTALL_PATH%\cpp-backend" -G "!CMAKE_GENERATOR!" -DCMAKE_BUILD_TYPE=Release
if %errorlevel% neq 0 (
    echo [!] CMake configuration failed
    echo [*] Attempting to clean and retry...
    
    REM Clean everything and try again
    cd /d "%INSTALL_PATH%"
    rmdir /s /q "%BUILD_PATH%" >nul 2>&1
    mkdir "%BUILD_PATH%"
    cd /d "%BUILD_PATH%"
    
    echo [*] Retrying with clean build directory...
    cmake "%INSTALL_PATH%\cpp-backend" -G "!CMAKE_GENERATOR!" -DCMAKE_BUILD_TYPE=Release
    if %errorlevel% neq 0 (
        echo [✗] Build configuration failed
        echo.
        echo [!] Troubleshooting:
        echo [*] 1. Ensure Visual Studio is fully installed
        echo [*] 2. Check that C++ workload is installed
        echo [*] 3. Try manually:
        echo [*]    cd "%BUILD_PATH%"
        echo [*]    cmake .. -G "!CMAKE_GENERATOR!"
        echo [*]    cmake --build . --config Release
        echo.
        pause
        exit /b 1
    )
)

echo [✓] CMake configuration successful
echo.
echo [*] Compiling (this may take 5-10 minutes)...
cmake --build . --config Release >nul 2>&1

if exist "%INSTALL_PATH%\build\bin\ai_creator.exe" (
    echo [✓] Build successful
    
    REM Create desktop shortcut
    set VBS_FILE=%TEMP%\create_shortcut.vbs
    (
        echo Set oWS = WScript.CreateObject("WScript.Shell"^)
        echo sLinkFile = "%USERPROFILE%\Desktop\AI Creator.lnk"
        echo Set oLink = oWS.CreateShortcut(sLinkFile^)
        echo oLink.TargetPath = "%INSTALL_PATH%\build\bin\ai_creator.exe"
        echo oLink.WorkingDirectory = "%INSTALL_PATH%\build\bin"
        echo oLink.Description = "AI Creator"
        echo oLink.Save
    ) > "%VBS_FILE%"
    cscript.exe "%VBS_FILE%" >nul
    del "%VBS_FILE%"
    
    echo [✓] Desktop shortcut created
    echo.
    echo ╔════════════════════════════════════════╗
    echo ║   Installation Complete!               ║
    echo ╚════════════════════════════════════════╝
    echo.
    echo [✓] AI Creator is ready to use
    echo [*] Visual Studio Version: !VS_VERSION!
    echo [*] Installation Path: %INSTALL_PATH%
    echo [*] Look for the shortcut on your Desktop
    echo.
    
    set /p LAUNCH="Launch now? (Y/N): "
    if /i "!LAUNCH!"=="Y" (
        start "" "%INSTALL_PATH%\build\bin\ai_creator.exe"
    )
) else (
    echo [✗] Build failed
    echo.
    echo [!] Troubleshooting:
    echo [*] 1. Make sure Visual Studio is fully installed
    echo [*] 2. Check that you have at least 2 GB free disk space
    echo [*] 3. Try running the installer again
    echo [*] 4. Check that C++ workload is installed in Visual Studio
    echo.
    echo [*] For manual build, run:
    echo [*] cd "%BUILD_PATH%"
    echo [*] cmake .. -G "!CMAKE_GENERATOR!"
    echo [*] cmake --build . --config Release
    echo.
)

pause
