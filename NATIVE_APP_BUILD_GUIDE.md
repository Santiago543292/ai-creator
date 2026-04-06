# AI Creator - Native Desktop Application Build Guide

Complete guide to compile AI Creator as a native Windows desktop application (.exe + .dll files).

## What You're Getting

A **real desktop application** that runs directly on Windows without any browser or web server:

- **ai_creator.exe** - Main application executable (native Windows GUI)
- **model_manager.dll** - Model management component
- **data_loader.dll** - Data loading and preprocessing
- **compiler.dll** - Compilation engine
- **neural_network.dll** - Neural network implementation
- **decision_tree.dll** - Decision tree implementation

## System Requirements

### Windows
- **OS:** Windows 7 or later (64-bit)
- **RAM:** 2 GB minimum, 4 GB recommended
- **Disk:** 500 MB free space
- **Build Tools:** Visual Studio 2017+ or MinGW

### Build Tools Installation

#### Option 1: Visual Studio (Recommended)

1. Download Visual Studio Community from: https://visualstudio.microsoft.com/
2. During installation, select "Desktop development with C++"
3. Install CMake: https://cmake.org/download/
4. Verify installation:
   ```bash
   cmake --version
   ```

#### Option 2: MinGW + CMake

1. Install MinGW from: https://www.mingw-w64.org/
2. Install CMake from: https://cmake.org/download/
3. Add both to PATH

## Project Structure

```
cpp-backend/
├── include/
│   ├── types.h                    # Core types
│   ├── ai_model.h
│   ├── neural_network.h
│   ├── decision_tree.h
│   ├── model_manager.h
│   ├── data_loader.h
│   ├── compiler.h
│   ├── dll_exports.h              # DLL export macros
│   └── gui/                       # GUI headers
│       ├── main_window.h
│       ├── home_page.h
│       ├── dashboard_page.h
│       ├── create_ai_page.h
│       ├── models_page.h
│       ├── settings_page.h
│       └── ui_utils.h
├── src/
│   ├── main.cpp                   # Application entry point (WinMain)
│   ├── ai_model.cpp
│   ├── neural_network.cpp
│   ├── decision_tree.cpp
│   ├── model_manager.cpp
│   ├── data_loader.cpp
│   ├── compiler.cpp
│   └── gui/                       # GUI implementations
│       ├── main_window.cpp
│       ├── home_page.cpp
│       ├── dashboard_page.cpp
│       ├── create_ai_page.cpp
│       ├── models_page.cpp
│       ├── settings_page.cpp
│       └── ui_utils.cpp
├── models/                        # Model storage
├── libs/                          # Framework integrations
├── output/                        # Compiled binaries
├── CMakeLists.txt                 # Build configuration
└── build_windows.bat              # Build script
```

## Building the Application

### Step 1: Extract Files

```bash
unzip ai-creator-production.zip
cd ai-creator/cpp-backend
```

### Step 2: Run Build Script (Recommended)

```bash
build_windows.bat
```

This script will:
1. Check for CMake installation
2. Create a build directory
3. Configure the project
4. Compile all source files
5. Generate .exe and .dll files

### Step 3: Manual Build (Alternative)

If the build script doesn't work:

```bash
# Create build directory
mkdir build
cd build

# Configure with Visual Studio
cmake .. -G "Visual Studio 16 2019"

# Build
cmake --build . --config Release

# Or with MinGW
cmake .. -G "MinGW Makefiles"
make -j4
```

## Output Files

After successful compilation, you'll find:

```
build/bin/
├── ai_creator.exe              # Main application
└── (public/)                   # [Removed - native GUI instead]

build/lib/
├── model_manager.dll
├── data_loader.dll
├── compiler.dll
├── neural_network.dll
└── decision_tree.dll
```

## Running the Application

### Method 1: From Command Line

```bash
cd build/bin
ai_creator.exe
```

### Method 2: Double-Click

Navigate to `build/bin/` and double-click `ai_creator.exe`

### Method 3: Create Shortcut

1. Right-click `ai_creator.exe`
2. Select "Send to" → "Desktop (create shortcut)"
3. Double-click the shortcut to run

## Application Features

### Main Window
- **Title:** "AI Creator - Intelligent AI Generation Platform"
- **Size:** 1200x800 pixels (resizable)
- **Theme:** Dark mode with neon green accents (QIX branding)

### Menu Bar
- **File** - Exit application
- **View** - Navigate between pages
- **Help** - About and documentation

### Pages (Accessible from View Menu)
1. **Home** - Welcome and overview
2. **Dashboard** - Real-time statistics
3. **Create AI** - Model creation wizard
4. **Models** - Manage all models
5. **Settings** - Configuration options

## Troubleshooting

### Build Fails: "CMake not found"
**Solution:**
1. Install CMake from https://cmake.org/download/
2. Add to PATH:
   - Right-click "This PC" → Properties
   - Advanced system settings → Environment Variables
   - Add CMake bin directory to PATH
3. Restart command prompt and try again

### Build Fails: "Visual Studio not found"
**Solution:**
1. Install Visual Studio 2017 or later
2. Or use MinGW: `cmake .. -G "MinGW Makefiles"`

### Application Won't Start
**Solution:**
1. Ensure all .dll files are in the same directory as .exe
2. Check Windows Event Viewer for error details
3. Try running from command line to see error messages

### DLL Not Found Error
**Solution:**
1. Copy all .dll files from `build/lib/` to `build/bin/`
2. Or add `build/lib/` to PATH

## Creating a Distribution Package

### Step 1: Gather Files

```bash
mkdir ai-creator-dist
cd ai-creator-dist

# Copy executable
copy ..\build\bin\ai_creator.exe .

# Copy all DLLs
copy ..\build\lib\*.dll .
```

### Step 2: Create ZIP Archive

```bash
# Using Windows Explorer
# Right-click folder → Send to → Compressed (zipped) folder

# Or using PowerShell
Compress-Archive -Path ai-creator-dist -DestinationPath ai-creator-windows.zip
```

### Step 3: Distribute

- Share `ai-creator-windows.zip` with users
- Users extract and run `ai_creator.exe`

## Advanced Configuration

### Changing Window Size

Edit `cpp-backend/src/gui/main_window.cpp`:

```cpp
hwnd_ = CreateWindowExW(
    0,
    CLASS_NAME,
    L"AI Creator - Intelligent AI Generation Platform",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    1400, 900,  // Change these values
    nullptr, nullptr,
    hInstance_,
    nullptr
);
```

### Changing Colors

Edit `cpp-backend/include/gui/ui_utils.h`:

```cpp
static constexpr COLORREF COLOR_NEON_GREEN = RGB(0, 221, 0);
static constexpr COLORREF COLOR_DARK_BG = RGB(20, 20, 20);
// Modify RGB values as needed
```

### Adding Application Icon

1. Create or find a .ico file
2. Create `resources/app.rc`:
   ```
   IDI_ICON1 ICON "app.ico"
   ```
3. In CMakeLists.txt, uncomment:
   ```cmake
   set_source_files_properties(resources/app.rc PROPERTIES LANGUAGE RC)
   target_sources(ai_creator PRIVATE resources/app.rc)
   ```
4. Rebuild

## Performance Optimization

### Faster Compilation

```bash
# Use all CPU cores
cmake --build . --config Release -- /m:8
```

### Smaller Executable

```bash
# Enable optimization flags in CMakeLists.txt
add_compile_options(/O2 /GL)
```

### Debug Build

For development:

```bash
cmake --build . --config Debug
```

## Development Workflow

1. **Edit source files** in `cpp-backend/src/` and `cpp-backend/include/`
2. **Rebuild:** Run `build_windows.bat` or `cmake --build . --config Release`
3. **Test:** Run `build/bin/ai_creator.exe`
4. **Iterate:** Repeat until satisfied

## Next Steps

After successful compilation:

1. **Run the application** - Double-click `ai_creator.exe`
2. **Explore the interface** - Navigate through all pages
3. **Test functionality** - Use the menu to switch between pages
4. **Customize** - Modify colors, fonts, and layout as needed
5. **Implement AI** - Add actual AI algorithms (currently placeholders)
6. **Package** - Create distribution ZIP with all files
7. **Deploy** - Share with users

## File Organization

### For Users (Distribution)

```
AI Creator/
├── ai_creator.exe
├── model_manager.dll
├── data_loader.dll
├── compiler.dll
├── neural_network.dll
├── decision_tree.dll
└── README.txt
```

### For Developers (Source)

```
ai-creator/
├── cpp-backend/          # C++ source
├── client/               # React frontend (not used in native app)
├── NATIVE_APP_BUILD_GUIDE.md
└── QUICK_START.md
```

## Support

For issues or questions:
1. Check this guide's Troubleshooting section
2. Review CMake error messages
3. Check Windows Event Viewer for runtime errors
4. Ensure all dependencies are installed

## Version Information

- **AI Creator:** 1.0.0
- **C++ Standard:** C++17
- **Windows API:** Modern (Windows 7+)
- **CMake Minimum:** 3.15
- **Last Updated:** April 5, 2026

---

**Ready to build? Start with Step 1 above!**
