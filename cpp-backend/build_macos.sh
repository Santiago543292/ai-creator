#!/bin/bash

# AI Creator macOS Build Script
# Compiles to ai-creator.app with embedded frontend and DLL components

echo "========================================"
echo "AI Creator - macOS Build Script"
echo "========================================"
echo ""

# Check if CMake is installed
if ! command -v cmake &> /dev/null; then
    echo "Error: CMake is not installed"
    echo "Install with: brew install cmake"
    exit 1
fi

# Check if clang is installed
if ! command -v clang++ &> /dev/null; then
    echo "Error: Xcode Command Line Tools are not installed"
    echo "Install with: xcode-select --install"
    exit 1
fi

# Create build directory
mkdir -p build
cd build

# Configure project
echo "[*] Configuring project with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang++

if [ $? -ne 0 ]; then
    echo "Error: CMake configuration failed"
    exit 1
fi

# Build project
echo "[*] Building project..."
make -j$(sysctl -n hw.ncpu)

if [ $? -ne 0 ]; then
    echo "Error: Build failed"
    exit 1
fi

# Display results
echo ""
echo "========================================"
echo "Build Complete!"
echo "========================================"
echo ""
echo "Output files:"
echo "  - bin/ai_creator.app (Main Application)"
echo "  - lib/model_manager.dylib (Model Management)"
echo "  - lib/data_loader.dylib (Data Loading)"
echo "  - lib/compiler.dylib (Compilation Engine)"
echo "  - lib/neural_network.dylib (Neural Networks)"
echo "  - lib/decision_tree.dylib (Decision Trees)"
echo ""
echo "Frontend files:"
echo "  - bin/public/ (React Frontend)"
echo ""
echo "To run the application:"
echo "  cd bin"
echo "  ./ai_creator.app/Contents/MacOS/ai_creator"
echo ""
