@echo off
REM AI Creator Windows Build Script
REM Compiles to ai-creator.exe with embedded frontend and DLL components

echo ========================================
echo AI Creator - Windows Build Script
echo ========================================
echo.

REM Check if CMake is installed
where cmake >nul 2>nul
if errorlevel 1 (
    echo Error: CMake is not installed or not in PATH
    echo Please install CMake from https://cmake.org/download/
    pause
    exit /b 1
)

REM Create build directory
if not exist "build" mkdir build
cd build

REM Configure with Visual Studio
echo [*] Configuring project with CMake...
cmake .. -G "Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release

if errorlevel 1 (
    echo Error: CMake configuration failed
    pause
    exit /b 1
)

REM Build project
echo [*] Building project...
cmake --build . --config Release

if errorlevel 1 (
    echo Error: Build failed
    pause
    exit /b 1
)

REM Display results
echo.
echo ========================================
echo Build Complete!
echo ========================================
echo.
echo Output files:
echo   - bin\ai_creator.exe (Main Application)
echo   - lib\model_manager.dll (Model Management)
echo   - lib\data_loader.dll (Data Loading)
echo   - lib\compiler.dll (Compilation Engine)
echo   - lib\neural_network.dll (Neural Networks)
echo   - lib\decision_tree.dll (Decision Trees)
echo.
echo Frontend files:
echo   - bin\public\ (React Frontend)
echo.
echo To run the application:
echo   cd bin
echo   ai_creator.exe
echo.
pause
