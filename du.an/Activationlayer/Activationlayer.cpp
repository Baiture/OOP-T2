#include "activationlayer.h"
#include <cmath>

// ─── SigmoidLayer ──────────────────────────────────────────────────────────

SigmoidLayer::SigmoidLayer()
    : last_output(Matrix::zeros(1, 1)) {}

double SigmoidLayer::sigmoid(double x) const {
    return 1.0 / (1.0 + std::exp(-x));
}

Matrix SigmoidLayer::forward(const Matrix& input) {
    last_output = input.applyFunction([this](double x) { return sigmoid(x); });
    return last_output;
}

Matrix SigmoidLayer::backward(const Matrix& grad) {
    // derivative: sigmoid(x) * (1 - sigmoid(x))
    Matrix sig_deriv = last_output.applyFunction([](double s) { return s * (1.0 - s); });
    return grad.elementwise_multiply(sig_deriv);
}

std::vector<Matrix*> SigmoidLayer::get_parameters() { return {}; }
void SigmoidLayer::update_parameters(double /*lr*/) {}
std::string SigmoidLayer::get_type_name() const { return "SigmoidLayer"; }


// ─── ReLULayer ─────────────────────────────────────────────────────────────

ReLULayer::ReLULayer()
    : last_input(Matrix::zeros(1, 1)) {}

Matrix ReLULayer::forward(const Matrix& input) {
    last_input = input;
    return input.applyFunction([](double x) { return x > 0.0 ? x : 0.0; });
}

Matrix ReLULayer::backward(const Matrix& grad) {
    Matrix mask = last_input.applyFunction([](double x) { return x > 0.0 ? 1.0 : 0.0; });
    return grad.elementwise_multiply(mask);
}

std::vector<Matrix*> ReLULayer::get_parameters() { return {}; }
void ReLULayer::update_parameters(double /*lr*/) {}
std::string ReLULayer::get_type_name() const { return "ReLULayer"; }
