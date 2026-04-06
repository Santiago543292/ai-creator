#ifndef AI_CREATOR_MODEL_MANAGER_H
#define AI_CREATOR_MODEL_MANAGER_H

#include "types.h"
#include "ai_model.h"
#include <map>
#include <memory>
#include <string>

namespace AICreator {

/**
 * Model Manager
 * Manages creation, storage, and lifecycle of AI models
 */
class ModelManager {
public:
    ModelManager();
    ~ModelManager() = default;

    // Model creation and management
    std::shared_ptr<AIModel> createModel(const ModelConfig& config);
    bool deleteModel(const std::string& modelId);
    std::shared_ptr<AIModel> getModel(const std::string& modelId);
    
    // Model listing and search
    std::vector<AIModelMetadata> listModels();
    std::vector<AIModelMetadata> searchModels(const std::string& query);
    
    // Model persistence
    bool saveModel(const std::string& modelId, const std::string& filepath);
    bool loadModel(const std::string& filepath);
    
    // Model operations
    bool trainModel(const std::string& modelId, const TrainingData& data);
    PredictionResult predictWithModel(const std::string& modelId, const std::vector<float>& input);
    
    // Statistics and monitoring
    int getTotalModels() const { return models_.size(); }
    ModelMetrics getModelMetrics(const std::string& modelId);
    std::vector<AIModelMetadata> getActiveModels();

private:
    std::map<std::string, std::shared_ptr<AIModel>> models_;
    std::map<std::string, AIModelMetadata> modelMetadata_;
    
    // Helper methods
    std::string generateModelId();
    bool validateModelConfig(const ModelConfig& config);
};

} // namespace AICreator

#endif // AI_CREATOR_MODEL_MANAGER_H
