#pragma once
#include "matrix.h"
#include <vector>
#include <string>

// Abstract base class for all layers
class Layer {
public:
    virtual Matrix forward(const Matrix& input) = 0;
    virtual Matrix backward(const Matrix& grad) = 0;
    virtual std::vector<Matrix*> get_parameters() = 0;
    virtual void update_parameters(double lr) = 0;
    virtual std::string get_type_name() const = 0;
    virtual ~Layer() = default;
};
