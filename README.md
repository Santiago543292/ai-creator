# AI Creator - Intelligent AI Generation Platform

A native Windows desktop application for creating, training, and deploying AI models with automatic code generation and compilation.

## Features

- 🤖 Create AI models with multiple algorithms (Neural Networks, Decision Trees, etc.)
- 📊 Real-time performance monitoring and metrics
- 💾 Save and load trained models
- 🔧 Automatic C++ code generation and compilation
- 📦 Export models as .exe and .dll files
- 🎨 Modern dark theme with neon green accents (QIX branding)
- ⚡ High-performance native Windows application

## Quick Start

### Download Pre-compiled Executable

1. Go to [Releases](../../releases)
2. Download the latest `ai-creator.exe`
3. Run it on your Windows computer
4. Done! No installation needed

### Build from Source

**Requirements:**
- Visual Studio 2017 or later
- CMake 3.15+

**Steps:**
```bash
git clone https://github.com/yourusername/ai-creator.git
cd ai-creator/cpp-backend
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

The compiled executable will be in `build/bin/ai_creator.exe`

## Project Structure

```
ai-creator/
├── cpp-backend/           # C++ source code
│   ├── src/              # Implementation files
│   ├── include/          # Header files
│   ├── CMakeLists.txt    # Build configuration
│   └── models/           # AI model templates
├── .github/workflows/    # GitHub Actions CI/CD
└── README.md            # This file
```

## Architecture

### Main Components

- **ai_creator.exe** - Main application with native GUI
- **model_manager.dll** - Model lifecycle management
- **data_loader.dll** - Data loading and preprocessing
- **compiler.dll** - C++ compilation engine
- **neural_network.dll** - Neural network implementation
- **decision_tree.dll** - Decision tree classifier

## Automated Builds

This project uses GitHub Actions to automatically compile Windows executables on every commit.

**Build Status:** [![Build Windows Executable](../../actions/workflows/build-windows.yml/badge.svg)](../../actions/workflows/build-windows.yml)

## Usage

1. Launch `ai_creator.exe`
2. Create a new AI model
3. Configure algorithm, framework, and target platform
4. Load training data
5. Train the model
6. Export as compiled executable or DLL

## System Requirements

- **OS:** Windows 10 or later
- **RAM:** 2 GB minimum, 8 GB recommended
- **Disk:** 500 MB free space
- **Processor:** Intel i5 or equivalent

## Development

### Adding New Features

1. Edit source files in `cpp-backend/src/`
2. Update headers in `cpp-backend/include/`
3. Commit and push to GitHub
4. GitHub Actions will automatically compile and create artifacts

### Debugging

Build with debug symbols:
```bash
cmake .. -G "Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
```

## Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request

## License

MIT License - See LICENSE file for details

## Support

For issues, questions, or suggestions:
- Open an [Issue](../../issues)
- Check [Discussions](../../discussions)
- Email: support@aicreator.dev

## Roadmap

- [ ] Web-based UI dashboard
- [ ] Cloud model deployment
- [ ] Real-time collaboration
- [ ] Advanced visualization tools
- [ ] Mobile app support
- [ ] API server

## Credits

Created by the AI Creator Team

---

**Download the latest release and start creating AI models today!**
