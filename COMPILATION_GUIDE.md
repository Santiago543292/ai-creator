# AI Creator - Complete Compilation Guide

This guide walks you through compiling AI Creator from source code to production-ready .exe and .dll files.

## What You'll Get

After compilation, you'll have:

### Main Executable
- **Windows:** `ai_creator.exe` - Single executable with embedded React frontend
- **Linux:** `ai_creator` - Single executable with embedded React frontend  
- **macOS:** `ai_creator.app` - Application bundle with embedded React frontend

### Specialized DLL/SO/DYLIB Files
- `model_manager.dll` - Model creation and lifecycle management
- `data_loader.dll` - Data loading and preprocessing
- `compiler.dll` - Compilation engine for model export
- `neural_network.dll` - Neural network implementation
- `decision_tree.dll` - Decision tree implementation

### Embedded Frontend
- React 19 web interface with QIX branding
- Responsive design (mobile, tablet, desktop)
- Real-time model statistics and visualization
- All assets embedded in the executable

## System Requirements

### Windows
- **OS:** Windows 7 or later (64-bit)
- **RAM:** 4 GB minimum, 8 GB recommended
- **Disk:** 2 GB free space
- **Tools:** Visual Studio 2017+, CMake 3.15+

### Linux
- **OS:** Ubuntu 18.04+, Debian 10+, or equivalent
- **RAM:** 4 GB minimum, 8 GB recommended
- **Disk:** 2 GB free space
- **Tools:** GCC 7+, CMake 3.15+

### macOS
- **OS:** macOS 10.13 or later
- **RAM:** 4 GB minimum, 8 GB recommended
- **Disk:** 2 GB free space
- **Tools:** Xcode Command Line Tools, CMake 3.15+

## Step-by-Step Compilation

### Step 1: Prepare Your System

#### Windows
1. Install Visual Studio 2017 or later
2. Install CMake from https://cmake.org/download/
3. Verify CMake is in PATH:
   ```bash
   cmake --version
   ```

#### Linux
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install build-essential cmake git

# Verify installation
cmake --version
g++ --version
```

#### macOS
```bash
# Install Xcode Command Line Tools
xcode-select --install

# Install CMake via Homebrew
brew install cmake

# Verify installation
cmake --version
```

### Step 2: Extract and Navigate

```bash
# Extract the ZIP file
unzip ai-creator-complete.zip
cd ai-creator

# Verify structure
ls -la cpp-backend/
```

### Step 3: Build Frontend

The React frontend has already been built to static files. Verify:

```bash
# Check if frontend is built
ls -la cpp-backend/public/
# Should show: index.html, assets/, __manus__/
```

### Step 4: Compile C++ Backend

#### Windows (Recommended: Use Build Script)

```bash
cd cpp-backend
build_windows.bat
```

**Manual Build:**
```bash
cd cpp-backend
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
cd ..
```

#### Linux (Recommended: Use Build Script)

```bash
cd cpp-backend
chmod +x build_linux.sh
./build_linux.sh
```

**Manual Build:**
```bash
cd cpp-backend
mkdir build
cd build
cmake ..
make -j$(nproc)
cd ..
```

#### macOS (Recommended: Use Build Script)

```bash
cd cpp-backend
chmod +x build_macos.sh
./build_macos.sh
```

**Manual Build:**
```bash
cd cpp-backend
mkdir build
cd build
cmake ..
make -j$(sysctl -n hw.ncpu)
cd ..
```

### Step 5: Verify Build Output

#### Windows
```bash
cd cpp-backend/build
dir bin\
dir lib\
```

Expected files:
```
bin/
  ai_creator.exe
  public/
    index.html
    assets/
lib/
  model_manager.dll
  data_loader.dll
  compiler.dll
  neural_network.dll
  decision_tree.dll
```

#### Linux
```bash
cd cpp-backend/build
ls -la bin/
ls -la lib/
```

Expected files:
```
bin/
  ai_creator
  public/
    index.html
    assets/
lib/
  model_manager.so
  data_loader.so
  compiler.so
  neural_network.so
  decision_tree.so
```

#### macOS
```bash
cd cpp-backend/build
ls -la bin/
ls -la lib/
```

Expected files:
```
bin/
  ai_creator.app
  public/
    index.html
    assets/
lib/
  model_manager.dylib
  data_loader.dylib
  compiler.dylib
  neural_network.dylib
  decision_tree.dylib
```

## Running the Application

### Windows
```bash
cd cpp-backend/build/bin
ai_creator.exe
```

### Linux
```bash
cd cpp-backend/build/bin
./ai_creator
```

### macOS
```bash
cd cpp-backend/build/bin
./ai_creator
```

The application will:
1. Display startup information
2. Initialize all components
3. Start a web server on http://localhost:8080
4. Automatically open your browser
5. Display an interactive menu

## Web Interface

Once running, access the web interface at:
```
http://localhost:8080
```

Features:
- **Home** - Overview and getting started
- **Dashboard** - Real-time model statistics
- **Create AI** - Create new AI models
- **AI Models** - Manage existing models
- **Settings** - Configuration options
- **Documentation** - API reference and guides

## Creating a Distribution Package

### Windows

```bash
# Create distribution folder
mkdir ai-creator-dist
cd ai-creator-dist

# Copy executable
copy ..\cpp-backend\build\bin\ai_creator.exe .

# Copy DLL files
copy ..\cpp-backend\build\lib\*.dll .

# Copy frontend
xcopy ..\cpp-backend\build\bin\public public /E

# Create ZIP
powershell -Command "Compress-Archive -Path . -DestinationPath ..\ai-creator-windows.zip"
```

### Linux

```bash
# Create distribution folder
mkdir ai-creator-dist
cd ai-creator-dist

# Copy executable
cp ../cpp-backend/build/bin/ai_creator .

# Copy SO files
cp ../cpp-backend/build/lib/*.so .

# Copy frontend
cp -r ../cpp-backend/build/bin/public .

# Create TAR.GZ
cd ..
tar -czf ai-creator-linux.tar.gz ai-creator-dist/
```

### macOS

```bash
# Create distribution folder
mkdir ai-creator-dist
cd ai-creator-dist

# Copy application bundle
cp -r ../cpp-backend/build/bin/ai_creator.app .

# Copy DYLIB files
cp ../cpp-backend/build/lib/*.dylib .

# Copy frontend
cp -r ../cpp-backend/build/bin/public .

# Create DMG (optional)
cd ..
hdiutil create -volname "AI Creator" -srcfolder ai-creator-dist -ov -format UDZO ai-creator-macos.dmg
```

## Troubleshooting

### Build Fails with "CMake not found"
**Solution:**
- Windows: Add CMake to PATH or reinstall with PATH option
- Linux: `sudo apt-get install cmake`
- macOS: `brew install cmake`

### Build Fails with "Visual Studio not found"
**Solution:**
- Install Visual Studio 2017 or later
- Or use MinGW: `cmake .. -G "MinGW Makefiles"`

### Build Fails with "g++ not found"
**Solution:**
- Linux: `sudo apt-get install build-essential`
- macOS: `xcode-select --install`

### Application Won't Start
**Solution:**
1. Ensure `public/` directory exists with frontend files
2. Check that port 8080 is not in use
3. Try a different port by modifying `main.cpp`

### DLL/SO/DYLIB Not Found at Runtime
**Solution:**
- Windows: Ensure all .dll files are in the same directory as .exe
- Linux: Set `LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH`
- macOS: Set `DYLD_LIBRARY_PATH=.:$DYLD_LIBRARY_PATH`

## Performance Tips

### Faster Compilation
```bash
# Use parallel build
make -j8              # Linux/macOS
cmake --build . -- /m:8  # Windows
```

### Smaller Binary Size
```bash
# Strip symbols (Linux/macOS)
strip ai_creator
strip *.so

# Use Release build with optimization
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-Os"
```

### Better Performance
```bash
# Use optimization flags
cmake .. -DCMAKE_CXX_FLAGS="-O3 -march=native"
```

## Next Steps

1. **Run the application** - Start ai_creator and explore the interface
2. **Create models** - Use the web interface to create AI models
3. **Train models** - Load data and train your models
4. **Export models** - Compile models to standalone executables
5. **Deploy** - Distribute your compiled binaries

## Support

For detailed information, see:
- `cpp-backend/README.md` - Backend documentation
- `cpp-backend/BUILD_GUIDE.md` - Detailed build instructions
- `PROJECT_README.md` - Project overview
- `cpp-backend/models/README.md` - Model management
- `cpp-backend/libs/README.md` - Framework integration

## Version Information

- **AI Creator Version:** 1.0.0
- **React Version:** 19
- **C++ Standard:** C++17
- **CMake Minimum:** 3.15
- **Last Updated:** April 5, 2026

---

**Ready to compile? Start with Step 1 above!**
