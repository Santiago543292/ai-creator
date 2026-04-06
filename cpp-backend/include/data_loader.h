#ifndef AI_CREATOR_DATA_LOADER_H
#define AI_CREATOR_DATA_LOADER_H

#include "types.h"
#include <string>
#include <vector>

namespace AICreator {

/**
 * Data Loader
 * Handles loading, parsing, and preprocessing of training data
 */
class DataLoader {
public:
    DataLoader() = default;
    ~DataLoader() = default;

    // Data loading methods
    bool loadCSV(const std::string& filepath, TrainingData& data);
    bool loadJSON(const std::string& filepath, TrainingData& data);
    bool loadBinary(const std::string& filepath, TrainingData& data);

    // Data preprocessing
    bool normalizeData(TrainingData& data);
    bool standardizeData(TrainingData& data);
    bool handleMissingValues(TrainingData& data);
    
    // Data validation
    bool validateData(const TrainingData& data);
    bool checkDataConsistency(const TrainingData& data);
    
    // Data splitting
    bool trainTestSplit(const TrainingData& data, 
                       TrainingData& trainData, 
                       TrainingData& testData, 
                       float trainRatio = 0.8);
    
    // Data augmentation
    bool augmentData(TrainingData& data, int multiplier);
    
    // Statistics
    struct DataStatistics {
        float mean;
        float stdDev;
        float min;
        float max;
        int sampleCount;
    };
    
    DataStatistics getStatistics(const TrainingData& data);

private:
    // Helper methods
    std::vector<std::string> splitString(const std::string& str, char delimiter);
    bool parseCSVLine(const std::string& line, std::vector<float>& values);
    float calculateMean(const std::vector<float>& values);
    float calculateStdDev(const std::vector<float>& values, float mean);
};

} // namespace AICreator

#endif // AI_CREATOR_DATA_LOADER_H
