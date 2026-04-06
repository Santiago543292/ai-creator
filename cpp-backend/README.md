# AI Creator C++ Backend

Professional C++ backend for AI model compilation and deployment. Generates native .exe, .dll, .so, and .dylib files.

## Directory Structure

```
cpp-backend/
├── include/          # Header files (.h)
│   ├── types.h       # Core data types and enums
│   ├── ai_model.h    # Base AI model class
│   ├── neural_network.h
│   ├── decision_tree.h
│   ├── model_manager.h
│   ├── data_loader.h
│   └── compiler.h
├── src/              # Implementation files (.cpp)
│   ├── main.cpp
│   ├── ai_model.cpp
│   ├── neural_network.cpp
│   ├── decision_tree.cpp
│   ├── model_manager.cpp
│   ├── data_loader.cpp
│   └── compiler.cpp
├── build/            # Build output directory
├── libs/             # External libraries
├── models/           # Trained AI models
├── output/           # Compiled binaries (.exe, .dll, .so, .dylib)
├── CMakeLists.txt    # CMake build configuration
└── README.md         # This file
```

## Building the Project

### Prerequisites

- CMake 3.15 or higher
- C++17 compatible compiler
- On Windows: Visual Studio 2017+ or MinGW
- On Linux: GCC 7+ or Clang 5+
- On macOS: Xcode Command Line Tools

### Build Instructions

#### Windows (Visual Studio)

```bash
cd cpp-backend
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019"
cmake --build . --config Release
```

Output files:
- `bin/ai_creator.exe` - Executable
- `lib/ai_creator.dll` - Dynamic library

#### Linux

```bash
cd cpp-backend
mkdir build
cd build
cmake ..
make
```

Output files:
- `bin/ai_creator` - Executable
- `lib/ai_creator.so` - Shared object

#### macOS

```bash
cd cpp-backend
mkdir build
cd build
cmake ..
make
```

Output files:
- `bin/ai_creator` - Executable
- `lib/ai_creator.dylib` - Dynamic library

## Core Components

### AIModel (Base Class)
Abstract base class for all AI models. Provides:
- Training interface
- Prediction interface
- Model persistence (save/load)
- Metadata management

### NeuralNetwork
Multi-layer perceptron implementation with:
- Configurable layers
- Multiple activation functions (ReLU, Sigmoid, Tanh)
- Backpropagation training
- Forward pass prediction

### DecisionTree
Classification and regression tree with:
- Gini impurity calculation
- Recursive tree building
- Pruning support
- Leaf value prediction

### ModelManager
Manages multiple AI models:
- Create, delete, retrieve models
- Model persistence
- Training and prediction
- Metrics tracking

### DataLoader
Data handling and preprocessing:
- CSV, JSON, Binary format support
- Normalization and standardization
- Train/test splitting
- Data augmentation
- Statistical analysis

### Compiler
Compilation to native binaries:
- C++ code generation
- CMake integration
- Platform-specific compilation
- Optimization levels
- Debug mode support

## API Usage

### Creating a Model

```cpp
#include "model_manager.h"
#include "types.h"

using namespace AICreator;

ModelConfig config;
config.name = "MyModel";
config.algorithm = AlgorithmType::NEURAL_NETWORK;
config.framework = FrameworkType::TENSORFLOW;
config.targetPlatform = TargetPlatform::WINDOWS;
config.epochs = 100;
config.batchSize = 32;

ModelManager manager;
auto model = manager.createModel(config);
```

### Training a Model

```cpp
DataLoader loader;
TrainingData data;
loader.loadCSV("training_data.csv", data);
loader.standardizeData(data);

model->train(data);
```

### Making Predictions

```cpp
std::vector<float> input = {1.0, 2.5, 3.2};
PredictionResult result = model->predict(input);

std::cout << "Prediction: " << result.prediction << std::endl;
std::cout << "Confidence: " << result.confidence << std::endl;
```

### Compiling to Binary

```cpp
Compiler compiler;
compiler.setOptimizationLevel(2);

CompilationOutput output = compiler.compileModel(config, "model_path");

if (output.success) {
    std::cout << "EXE: " << output.exePath << std::endl;
    std::cout << "DLL: " << output.dllPath << std::endl;
}
```

## Supported Algorithms

- Neural Networks (Deep Learning)
- Decision Trees
- Random Forests
- Support Vector Machines (SVM)
- K-Means Clustering
- Linear Regression
- Custom C++ implementations

## Supported Frameworks

- TensorFlow
- PyTorch
- OpenCV
- Scikit-learn
- Custom C++

## Target Platforms

- Windows (.exe, .dll)
- Linux (.so)
- macOS (.dylib)

## Performance Optimization

- Compiler optimization levels: 0-3
- Multi-threaded training support
- SIMD vectorization ready
- Memory-efficient data structures

## License

MIT License - See LICENSE file for details

## Contributing

Contributions welcome! Please follow C++17 standards and include tests for new features.
