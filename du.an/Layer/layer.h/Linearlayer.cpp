#include "linearlayer.h"
#include <cmath>

LinearLayer::LinearLayer(int in_features, int out_features)
    : weights(Matrix::random(in_features, out_features, std::sqrt(2.0 / in_features))),
      biases(Matrix::zeros(1, out_features)),
      d_weights(Matrix::zeros(in_features, out_features)),
      d_biases(Matrix::zeros(1, out_features)),
      last_input(Matrix::zeros(1, in_features)) {}

Matrix LinearLayer::forward(const Matrix& input) {
    last_input = input;
    // output = input * weights + biases (broadcast)
    Matrix result = input.multiply(weights);
    // Add bias to each row
    for (int i = 0; i < result.get_rows(); ++i)
        for (int j = 0; j < result.get_cols(); ++j)
            result.at(i, j) += biases.at(0, j);
    return result;
}

Matrix LinearLayer::backward(const Matrix& grad) {
    // d_weights = last_input^T * grad
    d_weights = last_input.transpose().multiply(grad);

    // d_biases = sum of grad over rows
    d_biases = Matrix::zeros(1, grad.get_cols());
    for (int i = 0; i < grad.get_rows(); ++i)
        for (int j = 0; j < grad.get_cols(); ++j)
            d_biases.at(0, j) += grad.at(i, j);

    // grad_input = grad * weights^T
    return grad.multiply(weights.transpose());
}

std::vector<Matrix*> LinearLayer::get_parameters() {
    return {&weights, &biases};
}

void LinearLayer::update_parameters(double lr) {
    for (int i = 0; i < weights.get_rows(); ++i)
        for (int j = 0; j < weights.get_cols(); ++j)
            weights.at(i, j) -= lr * d_weights.at(i, j);

    for (int j = 0; j < biases.get_cols(); ++j)
        biases.at(0, j) -= lr * d_biases.at(0, j);
}

std::string LinearLayer::get_type_name() const {
    return "LinearLayer";
}
