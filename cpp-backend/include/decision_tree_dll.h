#ifndef AI_CREATOR_DECISION_TREE_DLL_H
#define AI_CREATOR_DECISION_TREE_DLL_H

#include "dll_exports.h"
#include "types.h"

namespace AICreator {

/**
 * Decision Tree DLL Interface
 * Exported functions for decision tree operations
 */

extern "C" {
    // Create decision tree model
    DLL_EXPORT void* CreateDecisionTree(const ModelConfig* config);
    
    // Delete decision tree
    DLL_EXPORT bool DeleteDecisionTree(void* model);
    
    // Train decision tree
    DLL_EXPORT bool TrainDecisionTree(void* model, const TrainingData* data);
    
    // Make prediction
    DLL_EXPORT PredictionResult PredictDecisionTree(void* model, const float* input, int inputSize);
    
    // Save model
    DLL_EXPORT bool SaveDecisionTree(void* model, const char* filepath);
    
    // Load model
    DLL_EXPORT bool LoadDecisionTree(void* model, const char* filepath);
    
    // Get model metrics
    DLL_EXPORT ModelMetrics GetDecisionTreeMetrics(void* model);
    
    // Get model status
    DLL_EXPORT int GetDecisionTreeStatus(void* model);
    
    // Set max depth
    DLL_EXPORT void SetMaxDepth(void* model, int depth);
    
    // Set min samples split
    DLL_EXPORT void SetMinSamplesSplit(void* model, int samples);
    
    // Set min samples leaf
    DLL_EXPORT void SetMinSamplesLeaf(void* model, int samples);
    
    // Prune tree
    DLL_EXPORT bool PruneTree(void* model, float threshold);
}

} // namespace AICreator

#endif // AI_CREATOR_DECISION_TREE_DLL_H
