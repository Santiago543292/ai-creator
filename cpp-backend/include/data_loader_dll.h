#ifndef AI_CREATOR_DATA_LOADER_DLL_H
#define AI_CREATOR_DATA_LOADER_DLL_H

#include "dll_exports.h"
#include "types.h"

namespace AICreator {

/**
 * Data Loader DLL Interface
 * Exported functions for data loading and preprocessing
 */

extern "C" {
    // Load CSV data
    DLL_EXPORT bool LoadCSV(const char* filepath, TrainingData* output);
    
    // Load JSON data
    DLL_EXPORT bool LoadJSON(const char* filepath, TrainingData* output);
    
    // Load binary data
    DLL_EXPORT bool LoadBinary(const char* filepath, TrainingData* output);
    
    // Normalize data
    DLL_EXPORT bool NormalizeData(TrainingData* data);
    
    // Standardize data
    DLL_EXPORT bool StandardizeData(TrainingData* data);
    
    // Handle missing values
    DLL_EXPORT bool HandleMissingValues(TrainingData* data);
    
    // Validate data
    DLL_EXPORT bool ValidateData(const TrainingData* data);
    
    // Train/test split
    DLL_EXPORT bool TrainTestSplit(const TrainingData* data, 
                                   TrainingData* trainData, 
                                   TrainingData* testData, 
                                   float trainRatio);
    
    // Data augmentation
    DLL_EXPORT bool AugmentData(TrainingData* data, int multiplier);
    
    // Get data statistics
    DLL_EXPORT void GetDataStatistics(const TrainingData* data, 
                                      float* mean, 
                                      float* stdDev, 
                                      float* min, 
                                      float* max);
}

} // namespace AICreator

#endif // AI_CREATOR_DATA_LOADER_DLL_H
