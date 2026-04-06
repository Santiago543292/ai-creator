#ifndef AI_CREATOR_DECISION_TREE_H
#define AI_CREATOR_DECISION_TREE_H

#include "ai_model.h"
#include <memory>

namespace AICreator {

/**
 * Decision Tree implementation
 * Supports classification and regression tasks
 */
class DecisionTree : public AIModel {
public:
    DecisionTree(const ModelConfig& config);
    ~DecisionTree() override = default;

    // Core operations
    bool train(const TrainingData& data) override;
    PredictionResult predict(const std::vector<float>& input) override;
    bool save(const std::string& filepath) override;
    bool load(const std::string& filepath) override;

    // Model information
    ModelMetrics getMetrics() const override { return metrics_; }

    // Data management
    bool loadTrainingData(const std::string& filepath) override;
    bool validateData(const TrainingData& data) const override;

    // Tree configuration
    void setMaxDepth(int depth) { maxDepth_ = depth; }
    void setMinSamplesSplit(int samples) { minSamplesSplit_ = samples; }
    void setMinSamplesLeaf(int samples) { minSamplesLeaf_ = samples; }

private:
    struct TreeNode {
        bool isLeaf;
        int featureIndex;
        float threshold;
        float value; // For leaf nodes
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
    };

    std::shared_ptr<TreeNode> root_;
    int maxDepth_;
    int minSamplesSplit_;
    int minSamplesLeaf_;

    // Tree building methods
    std::shared_ptr<TreeNode> buildTree(const TrainingData& data, int depth);
    float calculateGini(const std::vector<float>& labels);
    void findBestSplit(const TrainingData& data, int& bestFeature, float& bestThreshold);
    
    // Prediction helper
    float traverseTree(const std::shared_ptr<TreeNode>& node, const std::vector<float>& input);
};

} // namespace AICreator

#endif // AI_CREATOR_DECISION_TREE_H
