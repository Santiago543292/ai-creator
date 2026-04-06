#!/bin/bash

# AI Creator Linux Build Script
# Compiles to ai-creator executable with embedded frontend and DLL components

echo "========================================"
echo "AI Creator - Linux Build Script"
echo "========================================"
echo ""

# Check if CMake is installed
if ! command -v cmake &> /dev/null; then
    echo "Error: CMake is not installed"
    echo "Install with: sudo apt-get install cmake"
    exit 1
fi

# Check if g++ is installed
if ! command -v g++ &> /dev/null; then
    echo "Error: g++ is not installed"
    echo "Install with: sudo apt-get install build-essential"
    exit 1
fi

# Create build directory
mkdir -p build
cd build

# Configure project
echo "[*] Configuring project with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

if [ $? -ne 0 ]; then
    echo "Error: CMake configuration failed"
    exit 1
fi

# Build project
echo "[*] Building project..."
make -j$(nproc)

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
echo "  - bin/ai_creator (Main Application)"
echo "  - lib/model_manager.so (Model Management)"
echo "  - lib/data_loader.so (Data Loading)"
echo "  - lib/compiler.so (Compilation Engine)"
echo "  - lib/neural_network.so (Neural Networks)"
echo "  - lib/decision_tree.so (Decision Trees)"
echo ""
echo "Frontend files:"
echo "  - bin/public/ (React Frontend)"
echo ""
echo "To run the application:"
echo "  cd bin"
echo "  ./ai_creator"
echo ""
