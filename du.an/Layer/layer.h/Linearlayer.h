#pragma once
#include "layer.h"

class LinearLayer : public Layer {
public:
    Matrix weights;
    Matrix biases;
    Matrix d_weights;
    Matrix d_biases;
    Matrix last_input;

    LinearLayer(int in_features, int out_features);

    Matrix forward(const Matrix& input) override;
    Matrix backward(const Matrix& grad) override;
    std::vector<Matrix*> get_parameters() override;
    void update_parameters(double lr) override;
    std::string get_type_name() const override;
};
