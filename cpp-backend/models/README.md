# AI Models Directory

This directory contains trained and compiled AI models organized by algorithm type.

## Directory Structure

```
models/
├── neural_networks/    # Deep learning and neural network models
├── decision_trees/     # Decision tree and random forest models
├── clustering/         # K-means and clustering algorithm models
├── regression/         # Linear and non-linear regression models
└── custom/             # Custom algorithm implementations
```

## Neural Networks

Stores trained neural network models including:
- Multi-layer perceptrons
- Convolutional neural networks
- Recurrent neural networks
- Transformer models

**File Format:** `.bin` (binary serialized model)

### Example Structure

```
neural_networks/
├── image_classifier_v1.bin
├── text_classifier_v2.bin
├── time_series_predictor.bin
└── custom_network.bin
```

## Decision Trees

Stores decision tree and ensemble models:
- Single decision trees
- Random forests
- Gradient boosting models
- XGBoost models

**File Format:** `.tree` (tree structure) or `.bin` (binary)

### Example Structure

```
decision_trees/
├── classification_tree_v1.tree
├── regression_tree_v1.tree
├── random_forest_classifier.bin
└── gradient_boost_model.bin
```

## Clustering

Stores clustering algorithm models:
- K-means models
- DBSCAN models
- Hierarchical clustering
- Gaussian mixture models

**File Format:** `.cluster` (cluster centers) or `.bin`

### Example Structure

```
clustering/
├── kmeans_k5.cluster
├── kmeans_k10.cluster
├── dbscan_model.bin
└── gmm_model.bin
```

## Regression

Stores regression models:
- Linear regression
- Polynomial regression
- Support vector regression
- Neural network regression

**File Format:** `.reg` (regression coefficients) or `.bin`

### Example Structure

```
regression/
├── linear_regression_v1.reg
├── polynomial_regression_v2.reg
├── svr_model.bin
└── neural_regression.bin
```

## Custom

Stores custom algorithm implementations and experimental models:
- User-defined algorithms
- Hybrid models
- Experimental architectures

**File Format:** `.custom` or `.bin`

### Example Structure

```
custom/
├── hybrid_model_v1.custom
├── experimental_algo_v1.bin
└── proprietary_model.bin
```

## Model Naming Convention

Follow this naming convention for consistency:

```
{algorithm_type}_{task}_{version}.{extension}

Examples:
- neural_network_classification_v1.bin
- decision_tree_regression_v2.tree
- kmeans_clustering_k5_v1.cluster
```

## Model Metadata

Each model should have an accompanying `.json` metadata file:

```json
{
  "name": "Image Classifier v1",
  "algorithm": "Neural Network",
  "framework": "TensorFlow",
  "version": "1.0.0",
  "created": "2026-04-05",
  "accuracy": 0.95,
  "precision": 0.93,
  "recall": 0.96,
  "f1_score": 0.945,
  "input_shape": [224, 224, 3],
  "output_shape": [10],
  "training_samples": 50000,
  "training_time": 3600,
  "file_size": 245000000,
  "target_platform": "Windows",
  "skills": ["Image Recognition", "Classification"],
  "dependencies": ["TensorFlow 2.10", "NumPy 1.21"]
}
```

## Model Deployment

### Compilation to Binary

Models are compiled to platform-specific binaries:

**Windows:**
```
output/
├── model_name.exe    # Executable
└── model_name.dll    # Dynamic library
```

**Linux:**
```
output/
├── model_name        # Executable
└── libmodel_name.so  # Shared object
```

**macOS:**
```
output/
├── model_name        # Executable
└── libmodel_name.dylib  # Dynamic library
```

## Loading Models

### C++ API

```cpp
#include "ai_model.h"
#include "neural_network.h"

using namespace AICreator;

// Load a neural network model
NeuralNetwork model(config);
model.load("models/neural_networks/image_classifier_v1.bin");

// Make predictions
std::vector<float> input = {...};
PredictionResult result = model.predict(input);
```

### Command Line

```bash
./ai_creator --load models/neural_networks/image_classifier_v1.bin
./ai_creator --predict input.csv --model models/neural_networks/image_classifier_v1.bin
```

## Model Version Control

Keep track of model versions:

```
models/
├── neural_networks/
│   ├── image_classifier_v1.bin
│   ├── image_classifier_v2.bin
│   ├── image_classifier_v3.bin
│   └── image_classifier_latest.bin (symlink to v3)
```

## Storage Optimization

- Compress large models: `gzip model.bin`
- Use binary format instead of text
- Remove training data after model finalization
- Archive old versions

## Performance Metrics

Track model performance in metadata:

- **Accuracy:** Overall correctness
- **Precision:** True positives / (True positives + False positives)
- **Recall:** True positives / (True positives + False negatives)
- **F1 Score:** Harmonic mean of precision and recall
- **Training Time:** Total training duration
- **Inference Time:** Average prediction time
- **Model Size:** File size in MB/GB

## Best Practices

1. **Version Control:** Always include version numbers
2. **Metadata:** Maintain JSON metadata for each model
3. **Testing:** Test models before deployment
4. **Documentation:** Document model purpose and usage
5. **Backup:** Keep backups of important models
6. **Cleanup:** Remove outdated model versions
7. **Performance:** Monitor model performance metrics
