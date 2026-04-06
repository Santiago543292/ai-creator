# External Libraries Directory

This directory contains integration stubs for popular AI/ML frameworks.

## Directory Structure

```
libs/
├── tensorflow/      # TensorFlow C++ API
├── pytorch/         # PyTorch C++ API
├── opencv/          # OpenCV computer vision library
└── scikit_learn/    # Scikit-learn integration (via ONNX)
```

## TensorFlow Integration

TensorFlow C++ API for model inference and training.

### Setup

1. Download TensorFlow C++ library from: https://www.tensorflow.org/install/lang_cc
2. Extract to `libs/tensorflow/`
3. Update CMakeLists.txt with TensorFlow paths

### Directory Structure

```
tensorflow/
├── include/
│   ├── tensorflow/
│   └── third_party/
├── lib/
│   ├── libtensorflow.so (Linux)
│   ├── libtensorflow.dylib (macOS)
│   └── tensorflow.dll (Windows)
└── README.md
```

### Usage Example

```cpp
#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/cc_ops.h"

using namespace tensorflow;
using namespace tensorflow::ops;

// Create a simple TensorFlow operation
Scope root = Scope::NewRootScope();
auto A = Const(root, {{3.f, 2.f}, {-1.f, 0.f}});
auto b = Const(root, {{3.f, 5.f}});
auto v = MatMul(root, A, b);

// Create session and run
ClientSession session(root);
TF_CHECK_OK(root.status());

std::vector<Tensor> outputs;
TF_CHECK_OK(session.Run({v}, &outputs));
```

## PyTorch Integration

PyTorch C++ API (LibTorch) for model inference.

### Setup

1. Download LibTorch from: https://pytorch.org/get-started/locally/
2. Extract to `libs/pytorch/`
3. Update CMakeLists.txt with LibTorch paths

### Directory Structure

```
pytorch/
├── include/
│   ├── torch/
│   └── ATen/
├── lib/
│   ├── libtorch.so (Linux)
│   ├── libtorch.dylib (macOS)
│   └── torch.dll (Windows)
└── README.md
```

### Usage Example

```cpp
#include <torch/torch.h>

// Load a PyTorch model
torch::jit::script::Module module = torch::jit::load("model.pt");

// Create input tensor
std::vector<torch::jit::IValue> inputs;
inputs.push_back(torch::ones({1, 3, 224, 224}));

// Run inference
auto output = module.forward(inputs).toTensor();
```

## OpenCV Integration

OpenCV for computer vision and image processing.

### Setup

1. Download OpenCV from: https://opencv.org/releases/
2. Build and install to `libs/opencv/`
3. Update CMakeLists.txt with OpenCV paths

### Directory Structure

```
opencv/
├── include/
│   └── opencv2/
├── lib/
│   ├── libopencv_core.so (Linux)
│   ├── libopencv_imgproc.dylib (macOS)
│   └── opencv_core.dll (Windows)
└── README.md
```

### Usage Example

```cpp
#include <opencv2/opencv.hpp>

using namespace cv;

// Load image
Mat image = imread("image.jpg");

// Process image
Mat gray;
cvtColor(image, gray, COLOR_BGR2GRAY);

// Apply filter
Mat blurred;
GaussianBlur(gray, blurred, Size(5, 5), 0);
```

## Scikit-learn Integration

Scikit-learn models via ONNX format.

### Setup

1. Export scikit-learn models to ONNX format
2. Use ONNX Runtime C++ API
3. Place ONNX models in `libs/scikit_learn/`

### Directory Structure

```
scikit_learn/
├── models/
│   ├── classifier.onnx
│   ├── regressor.onnx
│   └── clustering.onnx
├── include/
│   └── onnxruntime/
├── lib/
│   ├── libonnxruntime.so (Linux)
│   ├── libonnxruntime.dylib (macOS)
│   └── onnxruntime.dll (Windows)
└── README.md
```

### Usage Example

```cpp
#include <onnxruntime_cxx_api.h>

// Create ONNX Runtime session
Ort::SessionOptions session_options;
Ort::Session session(env, "model.onnx", session_options);

// Prepare input
std::vector<float> input_data = {...};
std::vector<int64_t> input_shape = {1, 10};

// Run inference
auto output = session.Run(Ort::RunOptions{nullptr}, 
                          input_names.data(), 
                          input_tensors.data(), 
                          input_tensors.size(),
                          output_names.data(), 
                          output_names.size());
```

## CMakeLists.txt Integration

Add to your CMakeLists.txt:

```cmake
# TensorFlow
find_package(TensorFlow REQUIRED)
target_link_libraries(ai_creator PUBLIC TensorFlow::TensorFlow)

# PyTorch/LibTorch
find_package(Torch REQUIRED)
target_link_libraries(ai_creator PUBLIC ${TORCH_LIBRARIES})

# OpenCV
find_package(OpenCV REQUIRED)
target_link_libraries(ai_creator PUBLIC ${OpenCV_LIBS})

# ONNX Runtime
find_package(onnxruntime REQUIRED)
target_link_libraries(ai_creator PUBLIC onnxruntime)
```

## Version Management

Keep track of library versions:

```
libs/
├── tensorflow/
│   ├── VERSION.txt (2.10.0)
│   └── ...
├── pytorch/
│   ├── VERSION.txt (1.13.0)
│   └── ...
├── opencv/
│   ├── VERSION.txt (4.7.0)
│   └── ...
└── scikit_learn/
    ├── VERSION.txt (ONNX Runtime 1.14.0)
    └── ...
```

## Compatibility Matrix

| Framework | Windows | Linux | macOS | Min Version |
|-----------|---------|-------|-------|-------------|
| TensorFlow | ✓ | ✓ | ✓ | 2.8.0 |
| PyTorch | ✓ | ✓ | ✓ | 1.12.0 |
| OpenCV | ✓ | ✓ | ✓ | 4.5.0 |
| ONNX Runtime | ✓ | ✓ | ✓ | 1.13.0 |

## Performance Tips

1. **Link Optimization:** Use `-O3` compiler flag
2. **SIMD:** Enable SIMD instructions for faster computation
3. **GPU Support:** Link CUDA libraries for GPU acceleration
4. **Memory:** Use memory pools for large tensor operations
5. **Caching:** Cache model weights in memory

## Troubleshooting

### Missing Headers

```bash
# Check include paths
g++ -I libs/tensorflow/include -I libs/pytorch/include ...
```

### Linking Errors

```bash
# Check library paths
g++ -L libs/tensorflow/lib -L libs/pytorch/lib ...
```

### Runtime Errors

```bash
# Set library path
export LD_LIBRARY_PATH=libs/tensorflow/lib:libs/pytorch/lib:$LD_LIBRARY_PATH
```

## Additional Resources

- TensorFlow C++ Guide: https://www.tensorflow.org/guide/cc
- PyTorch C++ API: https://pytorch.org/cppdocs/
- OpenCV Documentation: https://docs.opencv.org/
- ONNX Runtime: https://onnxruntime.ai/
