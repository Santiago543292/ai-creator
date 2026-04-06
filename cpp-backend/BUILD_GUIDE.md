# AI Creator - Build Guide

Complete guide to compile AI Creator into production-ready .exe and .dll files with embedded React frontend.

## Overview

AI Creator compiles into:
- **ai_creator.exe** (Windows) / **ai_creator** (Linux) / **ai_creator.app** (macOS) - Main executable with embedded React frontend
- **model_manager.dll** - Model creation and management
- **data_loader.dll** - Data loading and preprocessing
- **compiler.dll** - Compilation engine for model export
- **neural_network.dll** - Neural network implementation
- **decision_tree.dll** - Decision tree implementation

## Prerequisites

### Windows
- Visual Studio 2017 or later (with C++ workload)
- CMake 3.15+
- Git (optional)

**Installation:**
1. Install Visual Studio: https://visualstudio.microsoft.com/
2. Install CMake: https://cmake.org/download/
3. Ensure `cmake` is in your PATH

### Linux
- GCC 7+ or Clang 5+
- CMake 3.15+
- Build tools

**Installation (Ubuntu/Debian):**
```bash
sudo apt-get update
sudo apt-get install build-essential cmake git
```

**Installation (Fedora/RHEL):**
```bash
sudo dnf install gcc-c++ cmake git
```

### macOS
- Xcode Command Line Tools
- CMake 3.15+
- Homebrew (recommended)

**Installation:**
```bash
xcode-select --install
brew install cmake
```

## Building

### Windows

**Option 1: Using Build Script (Recommended)**
```bash
cd cpp-backend
build_windows.bat
```

**Option 2: Manual Build**
```bash
cd cpp-backend
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

**Output:**
```
build/bin/ai_creator.exe
build/lib/model_manager.dll
build/lib/data_loader.dll
build/lib/compiler.dll
build/lib/neural_network.dll
build/lib/decision_tree.dll
build/bin/public/          (React frontend)
```

### Linux

**Option 1: Using Build Script (Recommended)**
```bash
cd cpp-backend
chmod +x build_linux.sh
./build_linux.sh
```

**Option 2: Manual Build**
```bash
cd cpp-backend
mkdir build
cd build
cmake ..
make -j$(nproc)
```

**Output:**
```
build/bin/ai_creator
build/lib/model_manager.so
build/lib/data_loader.so
build/lib/compiler.so
build/lib/neural_network.so
build/lib/decision_tree.so
build/bin/public/          (React frontend)
```

### macOS

**Option 1: Using Build Script (Recommended)**
```bash
cd cpp-backend
chmod +x build_macos.sh
./build_macos.sh
```

**Option 2: Manual Build**
```bash
cd cpp-backend
mkdir build
cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
```

**Output:**
```
build/bin/ai_creator.app
build/lib/model_manager.dylib
build/lib/data_loader.dylib
build/lib/compiler.dylib
build/lib/neural_network.dylib
build/lib/decision_tree.dylib
build/bin/public/          (React frontend)
```

## Running the Application

### Windows
```bash
cd build/bin
ai_creator.exe
```

### Linux
```bash
cd build/bin
./ai_creator
```

### macOS
```bash
cd build/bin
./ai_creator
```

The application will:
1. Initialize the AI Creator system
2. Start a web server on http://localhost:8080
3. Automatically open your browser
4. Display an interactive menu

## Project Structure

```
cpp-backend/
├── include/                    # Header files
│   ├── types.h                # Core types
│   ├── ai_model.h
│   ├── neural_network.h
│   ├── decision_tree.h
│   ├── model_manager.h
│   ├── data_loader.h
│   ├── compiler.h
│   ├── dll_exports.h          # DLL export macros
│   ├── model_manager_dll.h    # DLL interfaces
│   ├── data_loader_dll.h
│   ├── compiler_dll.h
│   ├── neural_network_dll.h
│   └── decision_tree_dll.h
├── src/                       # Implementation files
│   ├── main.cpp              # Application entry point
│   ├── ai_model.cpp
│   ├── neural_network.cpp
│   ├── decision_tree.cpp
│   ├── model_manager.cpp
│   ├── data_loader.cpp
│   └── compiler.cpp
├── public/                    # React frontend (embedded)
│   ├── index.html
│   ├── assets/
│   └── __manus__/
├── models/                    # Model storage
│   ├── neural_networks/
│   ├── decision_trees/
│   ├── clustering/
│   ├── regression/
│   └── custom/
├── libs/                      # Framework integrations
│   ├── tensorflow/
│   ├── pytorch/
│   ├── opencv/
│   └── scikit_learn/
├── output/                    # Compiled binaries
├── build/                     # CMake build directory
├── CMakeLists.txt            # CMake configuration
├── build_windows.bat         # Windows build script
├── build_linux.sh            # Linux build script
├── build_macos.sh            # macOS build script
└── README.md                 # Backend documentation
```

## CMakeLists.txt Configuration

The CMakeLists.txt file handles:
- **DLL Creation:** Separate DLL for each component
- **Frontend Embedding:** Copies React frontend to binary directory
- **Platform Detection:** Automatically configures for Windows/Linux/macOS
- **Compiler Optimization:** Release builds with -O2 optimization
- **Linking:** Statically links all dependencies

## Troubleshooting

### CMake Configuration Fails

**Error:** `cmake: command not found`
- **Solution:** Install CMake or add to PATH

**Error:** `Visual Studio not found`
- **Solution:** Install Visual Studio or specify generator: `cmake .. -G "MinGW Makefiles"`

### Build Fails

**Error:** `undefined reference to ...`
- **Solution:** Ensure all source files are included in CMakeLists.txt

**Error:** `cannot find -lXXX`
- **Solution:** Install missing development libraries

### Runtime Errors

**Error:** `cannot open shared object file`
- **Linux Solution:** Set `LD_LIBRARY_PATH`: 
  ```bash
  export LD_LIBRARY_PATH=./lib:$LD_LIBRARY_PATH
  ```

**Error:** `The application failed to initialize properly`
- **Solution:** Ensure `public/` directory exists with frontend files

## Performance Optimization

### Compiler Flags

Modify CMakeLists.txt to add optimization flags:

**For Speed:**
```cmake
add_compile_options(-O3 -march=native)
```

**For Size:**
```cmake
add_compile_options(-Os)
```

**For Debugging:**
```cmake
add_compile_options(-g -O0)
```

### Parallel Build

Use multiple cores during build:

**Windows:**
```bash
cmake --build . --config Release -- /m:4
```

**Linux/macOS:**
```bash
make -j8
```

## Distribution

### Creating Distribution Package

**Windows:**
```bash
mkdir ai-creator-dist
copy build\bin\ai_creator.exe ai-creator-dist\
copy build\lib\*.dll ai-creator-dist\
xcopy build\bin\public ai-creator-dist\public /E
```

**Linux:**
```bash
mkdir ai-creator-dist
cp build/bin/ai_creator ai-creator-dist/
cp build/lib/*.so ai-creator-dist/
cp -r build/bin/public ai-creator-dist/
```

**macOS:**
```bash
mkdir ai-creator-dist
cp -r build/bin/ai_creator.app ai-creator-dist/
cp build/lib/*.dylib ai-creator-dist/
cp -r build/bin/public ai-creator-dist/
```

### Packaging

**Windows (ZIP):**
```bash
powershell -Command "Compress-Archive -Path ai-creator-dist -DestinationPath ai-creator-windows.zip"
```

**Linux/macOS (TAR.GZ):**
```bash
tar -czf ai-creator-linux.tar.gz ai-creator-dist/
```

## Advanced Configuration

### Custom Build Directory

```bash
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/custom/path
```

### Specific Compiler

```bash
cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/clang++
```

### Verbose Build

```bash
cmake --build . --verbose
```

## Support

For build issues, check:
1. CMake version: `cmake --version`
2. Compiler version: `g++ --version` or `clang++ --version`
3. Build logs in `build/` directory
4. README.md for additional information

## Next Steps

After successful build:
1. Run the application: `./ai_creator` (or `ai_creator.exe` on Windows)
2. Open web interface at http://localhost:8080
3. Create and train AI models
4. Export models to standalone binaries
5. Deploy to your system

---

**Version:** 1.0.0  
**Last Updated:** April 5, 2026
