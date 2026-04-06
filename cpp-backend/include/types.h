#ifndef AI_CREATOR_TYPES_H
#define AI_CREATOR_TYPES_H

#include <string>
#include <vector>
#include <map>
#include <memory>

namespace AICreator {

// Enum for algorithm types
enum class AlgorithmType {
    NEURAL_NETWORK,
    DECISION_TREE,
    RANDOM_FOREST,
    SVM,
    K_MEANS,
    LINEAR_REGRESSION,
    DEEP_LEARNING,
    CUSTOM
};

// Enum for model status
enum class ModelStatus {
    CREATED,
    TRAINING,
    TRAINED,
    TESTING,
    DEPLOYED,
    ERROR
};

// Enum for framework types
enum class FrameworkType {
    TENSORFLOW,
    PYTORCH,
    OPENCV,
    SCIKIT_LEARN,
    CUSTOM_CPP
};

// Enum for target platforms
enum class TargetPlatform {
    WINDOWS,
    LINUX,
    MACOS
};

// Data structure for model configuration
struct ModelConfig {
    std::string name;
    std::string description;
    AlgorithmType algorithm;
    FrameworkType framework;
    TargetPlatform targetPlatform;
    std::vector<std::string> skills;
    float learningRate;
    int epochs;
    int batchSize;
    std::string outputPath;
};

// Data structure for training data
struct TrainingData {
    std::vector<std::vector<float>> features;
    std::vector<float> labels;
    int featureCount;
    int sampleCount;
};

// Data structure for model metrics
struct ModelMetrics {
    float accuracy;
    float precision;
    float recall;
    float f1Score;
    float loss;
    int trainingTime;
};

// Data structure for prediction result
struct PredictionResult {
    float prediction;
    float confidence;
    std::vector<float> probabilities;
    std::string label;
};

// Data structure for compilation output
struct CompilationOutput {
    bool success;
    std::string exePath;
    std::string dllPath;
    std::string errorMessage;
    int compilationTime;
    long fileSize;
};

// Data structure for AI model metadata
struct AIModelMetadata {
    std::string modelId;
    std::string name;
    ModelStatus status;
    AlgorithmType algorithm;
    FrameworkType framework;
    TargetPlatform targetPlatform;
    ModelMetrics metrics;
    std::string createdDate;
    std::string lastModified;
    std::vector<std::string> skills;
};

} // namespace AICreator

#endif // AI_CREATOR_TYPES_H
