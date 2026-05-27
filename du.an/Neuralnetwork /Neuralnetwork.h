#pragma once
#include "layer.h"
#include "lossfunction.h"
#include <vector>
#include <memory>
#include <string>
 
class NeuralNetwork {
public:
    std::vector<std::unique_ptr<Layer>> pipeline;
    double learning_rate;
 
    explicit NeuralNetwork(double lr = 0.01);
 
    void add_layer(std::unique_ptr<Layer> layer);
    Matrix forward(const Matrix& input);
    void backward(const Matrix& loss_grad);
    void train(const Matrix& X, const Matrix& y, int epochs);
    Matrix predict(const Matrix& X);
 
    // ── Serialisation (save "brain" to text file) ──────────────────────────
    void save(const std::string& path) const;
    void load(const std::string& path);
};
 
