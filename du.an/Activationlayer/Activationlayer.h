#pragma once
#include "layer.h"
#include <string>

// ─── Sigmoid ───────────────────────────────────────────────────────────────
class SigmoidLayer : public Layer {
public:
    Matrix last_output;

    SigmoidLayer();

    Matrix forward(const Matrix& input) override;
    Matrix backward(const Matrix& grad) override;
    std::vector<Matrix*> get_parameters() override;
    void update_parameters(double lr) override;
    std::string get_type_name() const override;

    double sigmoid(double x) const;
};

// ─── ReLU ──────────────────────────────────────────────────────────────────
class ReLULayer : public Layer {
public:
    Matrix last_input;

    ReLULayer();

    Matrix forward(const Matrix& input) override;
    Matrix backward(const Matrix& grad) override;
    std::vector<Matrix*> get_parameters() override;
    void update_parameters(double lr) override;
    std::string get_type_name() const override;
};
