@echo off
REM AI Creator - Quick Install (FIXED for VS 2022+)
REM One-click installation to default location

setlocal enabledelayedexpansion

title AI Creator - Quick Install

echo.
echo ╔════════════════════════════════════════╗
echo ║   AI Creator - Quick Install v1.1.0    ║
echo ║        (Fixed for VS 2022+)            ║
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

REM Check for Visual Studio (Multiple methods)
echo [*] Checking for Visual Studio...

set VS_FOUND=0

REM Method 1: Check registry for VS 2022
reg query "HKLM\SOFTWARE\Microsoft\VisualStudio\17.0" >nul 2>&1
if %errorlevel% equ 0 (
    echo [✓] Visual Studio 2022 found
    set VS_FOUND=1
)

REM Method 2: Check registry for VS 2019
if %VS_FOUND% equ 0 (
    reg query "HKLM\SOFTWARE\Microsoft\VisualStudio\16.0" >nul 2>&1
    if %errorlevel% equ 0 (
        echo [✓] Visual Studio 2019 found
        set VS_FOUND=1
    )
)

REM Method 3: Check for VS 2017
if %VS_FOUND% equ 0 (
    reg query "HKLM\SOFTWARE\Microsoft\VisualStudio\15.0" >nul 2>&1
    if %errorlevel% equ 0 (
        echo [✓] Visual Studio 2017 found
        set VS_FOUND=1
    )
)

REM Method 4: Check Program Files for VS installation folders
if %VS_FOUND% equ 0 (
    if exist "C:\Program Files\Microsoft Visual Studio\2022" (
        echo [✓] Visual Studio 2022 found (Program Files)
        set VS_FOUND=1
    )
)

if %VS_FOUND% equ 0 (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019" (
        echo [✓] Visual Studio 2019 found (Program Files)
        set VS_FOUND=1
    )
)

if %VS_FOUND% equ 0 (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017" (
        echo [✓] Visual Studio 2017 found (Program Files)
        set VS_FOUND=1
    )
)

REM Method 5: Check for vswhere.exe (modern VS detection)
if %VS_FOUND% equ 0 (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" (
        "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest >nul 2>&1
        if %errorlevel% equ 0 (
            echo [✓] Visual Studio found (via vswhere)
            set VS_FOUND=1
        )
    )
)

REM If still not found, check common installation paths
if %VS_FOUND% equ 0 (
    if exist "C:\Program Files\Microsoft Visual Studio" (
        echo [✓] Visual Studio found (Program Files)
        set VS_FOUND=1
    )
)

if %VS_FOUND% equ 0 (
    echo [✗] Visual Studio not found
    echo.
    echo [!] Visual Studio 2017 or later is required
    echo [*] Download from: https://visualstudio.microsoft.com/
    echo.
    echo [*] Make sure to select "Desktop development with C++" during installation
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
if not exist "%BUILD_PATH%" mkdir "%BUILD_PATH%"

cd /d "%BUILD_PATH%"

echo [*] Building application (this may take a few minutes)...

REM Try to detect Visual Studio version and use appropriate generator
set VS_GENERATOR=Visual Studio 17 2022
set VS_FOUND_2022=0

REM Check for VS 2022
if exist "C:\Program Files\Microsoft Visual Studio\2022" (
    set VS_FOUND_2022=1
)

if %VS_FOUND_2022% equ 0 (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\2022" (
        set VS_FOUND_2022=1
    )
)

REM If VS 2022 not found, try 2019
if %VS_FOUND_2022% equ 0 (
    set VS_GENERATOR=Visual Studio 16 2019
)

echo [*] Using generator: %VS_GENERATOR%

cmake "%INSTALL_PATH%\cpp-backend" -G "%VS_GENERATOR%" -DCMAKE_BUILD_TYPE=Release >nul 2>&1
if %errorlevel% neq 0 (
    echo [!] CMake configuration warning - trying alternative generator
    cmake "%INSTALL_PATH%\cpp-backend" -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release >nul 2>&1
)

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
    echo [*] cmake .. -G "Visual Studio 17 2022"
    echo [*] cmake --build . --config Release
    echo.
)

pause
