#ifndef AI_CREATOR_MODEL_MANAGER_DLL_H
#define AI_CREATOR_MODEL_MANAGER_DLL_H

#include "dll_exports.h"
#include "types.h"
#include <vector>
#include <string>

namespace AICreator {

/**
 * Model Manager DLL Interface
 * Exported functions for model creation and management
 */

extern "C" {
    // Create new model
    DLL_EXPORT void* CreateModel(const ModelConfig* config);
    
    // Delete model
    DLL_EXPORT bool DeleteModel(const char* modelId);
    
    // Get model
    DLL_EXPORT void* GetModel(const char* modelId);
    
    // List all models
    DLL_EXPORT int ListModels(AIModelMetadata* output, int maxCount);
    
    // Train model
    DLL_EXPORT bool TrainModel(const char* modelId, const TrainingData* data);
    
    // Make prediction
    DLL_EXPORT PredictionResult PredictWithModel(const char* modelId, const float* input, int inputSize);
    
    // Get metrics
    DLL_EXPORT ModelMetrics GetModelMetrics(const char* modelId);
    
    // Get total models count
    DLL_EXPORT int GetTotalModels();
    
    // Save model to file
    DLL_EXPORT bool SaveModel(const char* modelId, const char* filepath);
    
    // Load model from file
    DLL_EXPORT bool LoadModel(const char* filepath);
}

} // namespace AICreator

#endif // AI_CREATOR_MODEL_MANAGER_DLL_H
