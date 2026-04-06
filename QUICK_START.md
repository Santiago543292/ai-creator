# AI Creator - Quick Start Guide

Get AI Creator running in minutes!

## What You're Getting

✅ **ai_creator.exe** (or .app/.bin) - Single executable with embedded React frontend  
✅ **5 Specialized DLL files** - Model Manager, Data Loader, Compiler, Neural Network, Decision Tree  
✅ **React 19 Web Interface** - Fully embedded with QIX branding  
✅ **No External Dependencies** - Everything statically linked  

## 60-Second Setup

### Windows

```bash
# 1. Extract ZIP
unzip ai-creator-compiled.zip
cd ai-creator/cpp-backend

# 2. Run build script
build_windows.bat

# 3. Run application
cd build\bin
ai_creator.exe
```

### Linux

```bash
# 1. Extract ZIP
unzip ai-creator-compiled.zip
cd ai-creator/cpp-backend

# 2. Run build script
chmod +x build_linux.sh
./build_linux.sh

# 3. Run application
cd build/bin
./ai_creator
```

### macOS

```bash
# 1. Extract ZIP
unzip ai-creator-compiled.zip
cd ai-creator/cpp-backend

# 2. Run build script
chmod +x build_macos.sh
./build_macos.sh

# 3. Run application
cd build/bin
./ai_creator
```

## What Happens When You Run It

1. ✅ Application starts and initializes
2. ✅ Web server launches on http://localhost:8080
3. ✅ Browser automatically opens
4. ✅ Interactive menu appears
5. ✅ Ready to create AI models!

## Web Interface Features

| Feature | Description |
|---------|-------------|
| **Home** | Overview and getting started |
| **Dashboard** | Real-time model statistics |
| **Create AI** | Build new AI models with wizard |
| **AI Models** | Manage and view all models |
| **Settings** | Configure compilation and options |
| **Documentation** | API reference and guides |

## File Structure After Build

```
cpp-backend/build/
├── bin/
│   ├── ai_creator.exe (or ai_creator / ai_creator.app)
│   └── public/
│       ├── index.html
│       └── assets/
└── lib/
    ├── model_manager.dll
    ├── data_loader.dll
    ├── compiler.dll
    ├── neural_network.dll
    └── decision_tree.dll
```

## Troubleshooting

### "CMake not found"
- **Windows:** Install from https://cmake.org/download/
- **Linux:** `sudo apt-get install cmake`
- **macOS:** `brew install cmake`

### "Build failed"
- Check you have 2GB free disk space
- Ensure you have write permissions
- See `cpp-backend/BUILD_GUIDE.md` for detailed help

### "Port 8080 already in use"
- Edit `cpp-backend/src/main.cpp` line with `WebServer webServer_(8080, ...)`
- Change `8080` to another port like `8081`
- Rebuild

## Next Steps

1. **Explore the interface** - Click through all pages
2. **Create a model** - Use "Create AI" wizard
3. **Load data** - Import CSV training data
4. **Train model** - Click "Train" and watch metrics
5. **Export binary** - Compile model to standalone .exe/.dll

## Key Files

| File | Purpose |
|------|---------|
| `COMPILATION_GUIDE.md` | Detailed compilation instructions |
| `cpp-backend/BUILD_GUIDE.md` | Advanced build configuration |
| `cpp-backend/README.md` | Backend API documentation |
| `PROJECT_README.md` | Full project overview |

## Performance Tips

### Faster Build
```bash
# Linux/macOS: Use all CPU cores
make -j8

# Windows: Use multiple cores
cmake --build . -- /m:8
```

### Smaller Executable
```bash
# Strip debug symbols (Linux/macOS)
strip ai_creator
strip *.so
```

## System Requirements

| Requirement | Minimum | Recommended |
|-------------|---------|-------------|
| RAM | 2 GB | 8 GB |
| Disk | 500 MB | 2 GB |
| CPU | Dual-core | Quad-core |
| OS | Windows 7+ / Ubuntu 18.04+ / macOS 10.13+ | Latest |

## Architecture

```
┌─────────────────────────────────┐
│   ai_creator.exe (Main App)     │
│  ┌─────────────────────────────┐│
│  │  React 19 Frontend          ││
│  │  (Embedded Static Files)    ││
│  └─────────────────────────────┘│
│  ┌─────────────────────────────┐│
│  │  Web Server (Port 8080)     ││
│  └─────────────────────────────┘│
│  ┌─────────────────────────────┐│
│  │  C++ Backend (Main Logic)   ││
│  └─────────────────────────────┘│
└─────────────────────────────────┘
         ↓ Links to ↓
┌──────────────────────────────────┐
│  Specialized DLL Components      │
├──────────────────────────────────┤
│ • model_manager.dll              │
│ • data_loader.dll                │
│ • compiler.dll                   │
│ • neural_network.dll             │
│ • decision_tree.dll              │
└──────────────────────────────────┘
```

## Supported Platforms

- ✅ **Windows** - .exe + .dll files
- ✅ **Linux** - Binary + .so files  
- ✅ **macOS** - .app bundle + .dylib files

## What's NOT Included Yet

The following are placeholder stubs ready for implementation:
- ❌ Actual AI training algorithms (ready for implementation)
- ❌ Neural network backpropagation (stub provided)
- ❌ Decision tree splitting (stub provided)
- ❌ TensorFlow/PyTorch integration (framework stubs provided)

## Support

- **Documentation:** See `COMPILATION_GUIDE.md`
- **Build Issues:** See `cpp-backend/BUILD_GUIDE.md`
- **API Reference:** See `cpp-backend/README.md`
- **Project Overview:** See `PROJECT_README.md`

## Version Info

- **AI Creator:** 1.0.0
- **React:** 19
- **C++:** C++17
- **Build System:** CMake 3.15+

---

**That's it! You're ready to go. Run the build script and start creating AI models!** 🚀
