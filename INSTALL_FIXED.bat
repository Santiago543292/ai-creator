@echo off
REM AI Creator Installer (FIXED for VS 2022+)
REM Automated setup wizard for Windows

setlocal enabledelayedexpansion

REM Color codes (using title bar for visual feedback)
title AI Creator - Setup Wizard (Fixed)

echo.
echo ╔════════════════════════════════════════╗
echo ║   AI Creator - Setup Wizard v1.1.0     ║
echo ║  Intelligent AI Generation Platform    ║
echo ║        (Fixed for VS 2022+)            ║
echo ╚════════════════════════════════════════╝
echo.

REM Check if running as administrator
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo [!] This installer requires Administrator privileges
    echo [*] Please run this script as Administrator
    pause
    exit /b 1
)

echo [✓] Administrator privileges confirmed
echo.

REM ============================================
REM Check Prerequisites
REM ============================================

echo ╔════════════════════════════════════════╗
echo ║      Checking Prerequisites            ║
echo ╚════════════════════════════════════════╝
echo.

REM Check for CMake
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo [!] CMake not found in PATH
    echo [*] CMake is required to build AI Creator
    echo.
    set /p INSTALL_CMAKE="Install CMake now? (Y/N): "
    if /i "!INSTALL_CMAKE!"=="Y" (
        echo [*] Downloading CMake...
        powershell -Command "Invoke-WebRequest -Uri 'https://github.com/Kitware/CMake/releases/download/v3.27.0/cmake-3.27.0-windows-x86_64.msi' -OutFile '%TEMP%\cmake-installer.msi'" >nul 2>&1
        if exist "%TEMP%\cmake-installer.msi" (
            echo [*] Running CMake installer...
            start /wait msiexec /i "%TEMP%\cmake-installer.msi" /quiet
            del "%TEMP%\cmake-installer.msi"
            echo [✓] CMake installed
        ) else (
            echo [✗] Failed to download CMake
            echo [*] Please install CMake manually from: https://cmake.org/download/
            pause
            exit /b 1
        )
    ) else (
        echo [✗] CMake is required. Installation cancelled.
        pause
        exit /b 1
    )
) else (
    echo [✓] CMake found
)

REM Check for Visual Studio (Multiple detection methods)
echo [*] Checking for Visual Studio...

set VS_FOUND=0
set VS_VERSION=

REM Method 1: Check registry for VS 2022
reg query "HKLM\SOFTWARE\Microsoft\VisualStudio\17.0" >nul 2>&1
if %errorlevel% equ 0 (
    echo [✓] Visual Studio 2022 found (Registry)
    set VS_FOUND=1
    set VS_VERSION=2022
)

REM Method 2: Check registry for VS 2019
if %VS_FOUND% equ 0 (
    reg query "HKLM\SOFTWARE\Microsoft\VisualStudio\16.0" >nul 2>&1
    if %errorlevel% equ 0 (
        echo [✓] Visual Studio 2019 found (Registry)
        set VS_FOUND=1
        set VS_VERSION=2019
    )
)

REM Method 3: Check registry for VS 2017
if %VS_FOUND% equ 0 (
    reg query "HKLM\SOFTWARE\Microsoft\VisualStudio\15.0" >nul 2>&1
    if %errorlevel% equ 0 (
        echo [✓] Visual Studio 2017 found (Registry)
        set VS_FOUND=1
        set VS_VERSION=2017
    )
)

REM Method 4: Check Program Files for VS 2022
if %VS_FOUND% equ 0 (
    if exist "C:\Program Files\Microsoft Visual Studio\2022" (
        echo [✓] Visual Studio 2022 found (Program Files)
        set VS_FOUND=1
        set VS_VERSION=2022
    )
)

REM Method 5: Check Program Files for VS 2019
if %VS_FOUND% equ 0 (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019" (
        echo [✓] Visual Studio 2019 found (Program Files)
        set VS_FOUND=1
        set VS_VERSION=2019
    )
)

REM Method 6: Check Program Files for VS 2017
if %VS_FOUND% equ 0 (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017" (
        echo [✓] Visual Studio 2017 found (Program Files)
        set VS_FOUND=1
        set VS_VERSION=2017
    )
)

REM Method 7: Use vswhere.exe for modern detection
if %VS_FOUND% equ 0 (
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" (
        "C:\Program Files (x86)\Microsoft Visual Studio\Installer\vswhere.exe" -latest >nul 2>&1
        if %errorlevel% equ 0 (
            echo [✓] Visual Studio found (vswhere)
            set VS_FOUND=1
            set VS_VERSION=Latest
        )
    )
)

REM Method 8: Generic Program Files check
if %VS_FOUND% equ 0 (
    if exist "C:\Program Files\Microsoft Visual Studio" (
        echo [✓] Visual Studio found (Program Files)
        set VS_FOUND=1
        set VS_VERSION=Unknown
    )
)

if %VS_FOUND% equ 0 (
    echo [✗] Visual Studio 2017 or later is required
    echo.
    echo [!] Installation cannot continue without Visual Studio
    echo [*] Download from: https://visualstudio.microsoft.com/
    echo [*] Make sure to install "Desktop development with C++"
    echo.
    pause
    exit /b 1
)

echo.

REM ============================================
REM Select Installation Path
REM ============================================

echo ╔════════════════════════════════════════╗
echo ║    Select Installation Path            ║
echo ╚════════════════════════════════════════╝
echo.

set DEFAULT_PATH=%USERPROFILE%\AI Creator
echo [*] Default path: %DEFAULT_PATH%
echo.

set /p CUSTOM_PATH="Use custom path? (leave blank for default): "
if not "!CUSTOM_PATH!"=="" (
    set INSTALL_PATH=!CUSTOM_PATH!
) else (
    set INSTALL_PATH=%DEFAULT_PATH%
)

echo [✓] Installation path: %INSTALL_PATH%
echo.

REM Create installation directory
if not exist "%INSTALL_PATH%" (
    mkdir "%INSTALL_PATH%"
    echo [✓] Installation directory created
)

REM ============================================
REM Copy Files
REM ============================================

echo ╔════════════════════════════════════════╗
echo ║        Copying Files                   ║
echo ╚════════════════════════════════════════╝
echo.

set SCRIPT_DIR=%~dp0

echo [*] Copying source files...
xcopy "%SCRIPT_DIR%cpp-backend" "%INSTALL_PATH%\cpp-backend" /E /I /Y >nul
if %errorlevel% equ 0 (
    echo [✓] Files copied successfully
) else (
    echo [✗] Failed to copy files
    pause
    exit /b 1
)

echo.

REM ============================================
REM Build Application
REM ============================================

echo ╔════════════════════════════════════════╗
echo ║       Building AI Creator              ║
echo ║  (This may take several minutes)       ║
echo ╚════════════════════════════════════════╝
echo.

set BUILD_PATH=%INSTALL_PATH%\build

if not exist "%BUILD_PATH%" (
    mkdir "%BUILD_PATH%"
)

cd /d "%BUILD_PATH%"

echo [*] Configuring project with CMake...

REM Determine Visual Studio version for CMake
set CMAKE_GENERATOR=Visual Studio 17 2022
if "!VS_VERSION!"=="2019" (
    set CMAKE_GENERATOR=Visual Studio 16 2019
)
if "!VS_VERSION!"=="2017" (
    set CMAKE_GENERATOR=Visual Studio 15 2017
)

echo [*] Using CMake generator: !CMAKE_GENERATOR!

cmake "%INSTALL_PATH%\cpp-backend" -G "!CMAKE_GENERATOR!" -DCMAKE_BUILD_TYPE=Release
if %errorlevel% neq 0 (
    echo [!] CMake configuration had issues, trying alternative...
    cmake "%INSTALL_PATH%\cpp-backend" -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release
    if %errorlevel% neq 0 (
        echo [✗] CMake configuration failed
        pause
        exit /b 1
    )
)
echo [✓] Project configured

echo.
echo [*] Building project...
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo [✗] Build failed
    echo.
    echo [!] Troubleshooting:
    echo [*] 1. Ensure Visual Studio is fully installed
    echo [*] 2. Check that C++ workload is installed
    echo [*] 3. Ensure you have at least 2 GB free disk space
    echo [*] 4. Try running the installer again
    echo.
    pause
    exit /b 1
)
echo [✓] Build completed successfully

echo.

REM ============================================
REM Create Shortcuts
REM ============================================

echo ╔════════════════════════════════════════╗
echo ║      Creating Shortcuts                ║
echo ╚════════════════════════════════════════╝
echo.

set EXE_PATH=%INSTALL_PATH%\build\bin\ai_creator.exe
set DESKTOP_PATH=%USERPROFILE%\Desktop
set START_MENU_PATH=%APPDATA%\Microsoft\Windows\Start Menu\Programs

REM Create desktop shortcut using VBScript
set VBS_FILE=%TEMP%\create_shortcut.vbs
(
    echo Set oWS = WScript.CreateObject("WScript.Shell"^)
    echo sLinkFile = "%DESKTOP_PATH%\AI Creator.lnk"
    echo Set oLink = oWS.CreateShortcut(sLinkFile^)
    echo oLink.TargetPath = "%EXE_PATH%"
    echo oLink.WorkingDirectory = "%INSTALL_PATH%\build\bin"
    echo oLink.Description = "AI Creator - Intelligent AI Generation Platform"
    echo oLink.Save
) > "%VBS_FILE%"

cscript.exe "%VBS_FILE%" >nul
del "%VBS_FILE%"
echo [✓] Desktop shortcut created

REM Create Start Menu folder and shortcut
if not exist "%START_MENU_PATH%\AI Creator" (
    mkdir "%START_MENU_PATH%\AI Creator"
)

set VBS_FILE=%TEMP%\create_startmenu_shortcut.vbs
(
    echo Set oWS = WScript.CreateObject("WScript.Shell"^)
    echo sLinkFile = "%START_MENU_PATH%\AI Creator\AI Creator.lnk"
    echo Set oLink = oWS.CreateShortcut(sLinkFile^)
    echo oLink.TargetPath = "%EXE_PATH%"
    echo oLink.WorkingDirectory = "%INSTALL_PATH%\build\bin"
    echo oLink.Description = "AI Creator - Intelligent AI Generation Platform"
    echo oLink.Save
) > "%VBS_FILE%"

cscript.exe "%VBS_FILE%" >nul
del "%VBS_FILE%"
echo [✓] Start Menu shortcut created

echo.

REM ============================================
REM Installation Complete
REM ============================================

echo ╔════════════════════════════════════════╗
echo ║    Installation Complete!              ║
echo ╚════════════════════════════════════════╝
echo.

echo [✓] AI Creator has been installed successfully
echo.
echo Installation Details:
echo   Location: %INSTALL_PATH%
echo   Executable: %EXE_PATH%
echo   Visual Studio: !VS_VERSION!
echo.

echo Next Steps:
echo   1. Look for "AI Creator" shortcut on your Desktop
echo   2. Double-click to launch the application
echo   3. Explore the interface and create AI models
echo.

set /p LAUNCH="Launch AI Creator now? (Y/N): "
if /i "!LAUNCH!"=="Y" (
    start "" "%EXE_PATH%"
)

echo.
echo Thank you for installing AI Creator!
echo.
pause
