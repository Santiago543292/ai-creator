#ifndef AI_CREATOR_NEURAL_NETWORK_H
#define AI_CREATOR_NEURAL_NETWORK_H

#include "ai_model.h"
#include <vector>

namespace AICreator {

/**
 * Neural Network implementation
 * Supports multi-layer perceptron with configurable architecture
 */
class NeuralNetwork : public AIModel {
public:
    NeuralNetwork(const ModelConfig& config);
    ~NeuralNetwork() override = default;

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

    // Network configuration
    void addLayer(int neurons, const std::string& activation = "relu");
    void setLearningRate(float rate) { config_.learningRate = rate; }
    void setEpochs(int epochs) { config_.epochs = epochs; }

private:
    struct Layer {
        std::vector<std::vector<float>> weights;
        std::vector<float> biases;
        std::string activation;
        int neurons;
    };

    std::vector<Layer> layers_;
    
    // Training methods
    void forwardPass(const std::vector<float>& input, std::vector<std::vector<float>>& layerOutputs);
    void backwardPass(const std::vector<float>& target, const std::vector<std::vector<float>>& layerOutputs);
    void updateWeights();
    
    // Activation functions
    float activationFunction(float x, const std::string& type);
    float activationDerivative(float x, const std::string& type);
};

} // namespace AICreator

#endif // AI_CREATOR_NEURAL_NETWORK_H
