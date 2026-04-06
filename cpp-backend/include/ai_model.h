#ifndef AI_CREATOR_AI_MODEL_H
#define AI_CREATOR_AI_MODEL_H

#include "types.h"
#include <vector>
#include <string>

namespace AICreator {

/**
 * Base class for all AI models
 * Provides core functionality for training, prediction, and model management
 */
class AIModel {
public:
    AIModel(const ModelConfig& config);
    virtual ~AIModel() = default;

    // Core model operations
    virtual bool train(const TrainingData& data) = 0;
    virtual PredictionResult predict(const std::vector<float>& input) = 0;
    virtual bool save(const std::string& filepath) = 0;
    virtual bool load(const std::string& filepath) = 0;

    // Model information
    virtual ModelMetrics getMetrics() const = 0;
    virtual ModelStatus getStatus() const { return status_; }
    virtual void setStatus(ModelStatus status) { status_ = status; }

    // Configuration access
    const ModelConfig& getConfig() const { return config_; }
    const AIModelMetadata& getMetadata() const { return metadata_; }

    // Data management
    virtual bool loadTrainingData(const std::string& filepath) = 0;
    virtual bool validateData(const TrainingData& data) const = 0;

protected:
    ModelConfig config_;
    AIModelMetadata metadata_;
    ModelStatus status_;
    TrainingData trainingData_;
    ModelMetrics metrics_;

    // Helper methods
    void updateMetadata();
    void logMessage(const std::string& message);
};

} // namespace AICreator

#endif // AI_CREATOR_AI_MODEL_H
