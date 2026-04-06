#ifndef AI_CREATOR_NEURAL_NETWORK_DLL_H
#define AI_CREATOR_NEURAL_NETWORK_DLL_H

#include "dll_exports.h"
#include "types.h"

namespace AICreator {

/**
 * Neural Network DLL Interface
 * Exported functions for neural network operations
 */

extern "C" {
    // Create neural network model
    DLL_EXPORT void* CreateNeuralNetwork(const ModelConfig* config);
    
    // Delete neural network
    DLL_EXPORT bool DeleteNeuralNetwork(void* model);
    
    // Train neural network
    DLL_EXPORT bool TrainNeuralNetwork(void* model, const TrainingData* data);
    
    // Make prediction
    DLL_EXPORT PredictionResult PredictNeuralNetwork(void* model, const float* input, int inputSize);
    
    // Save model
    DLL_EXPORT bool SaveNeuralNetwork(void* model, const char* filepath);
    
    // Load model
    DLL_EXPORT bool LoadNeuralNetwork(void* model, const char* filepath);
    
    // Add layer to network
    DLL_EXPORT bool AddLayer(void* model, int neurons, const char* activation);
    
    // Get model metrics
    DLL_EXPORT ModelMetrics GetNeuralNetworkMetrics(void* model);
    
    // Get model status
    DLL_EXPORT int GetNeuralNetworkStatus(void* model);
    
    // Set learning rate
    DLL_EXPORT void SetLearningRate(void* model, float rate);
    
    // Set epochs
    DLL_EXPORT void SetEpochs(void* model, int epochs);
    
    // Set batch size
    DLL_EXPORT void SetBatchSize(void* model, int batchSize);
}

} // namespace AICreator

#endif // AI_CREATOR_NEURAL_NETWORK_DLL_H
