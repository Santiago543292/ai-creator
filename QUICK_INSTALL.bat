@echo off
REM AI Creator - Quick Install
REM One-click installation to default location

setlocal enabledelayedexpansion

title AI Creator - Quick Install

echo.
echo ╔════════════════════════════════════════╗
echo ║   AI Creator - Quick Install v1.0.0    ║
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
)

echo [✓] Prerequisites checked

echo [*] Copying files...
xcopy "%SOURCE_DIR%cpp-backend" "%INSTALL_PATH%\cpp-backend" /E /I /Y >nul
echo [✓] Files copied

set BUILD_PATH=%INSTALL_PATH%\build
if not exist "%BUILD_PATH%" mkdir "%BUILD_PATH%"

cd /d "%BUILD_PATH%"

echo [*] Building application (this may take a few minutes)...
cmake "%INSTALL_PATH%\cpp-backend" -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release >nul 2>&1
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
    echo [*] Please check your Visual Studio installation
)

pause
