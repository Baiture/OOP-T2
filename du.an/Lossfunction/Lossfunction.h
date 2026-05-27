#pragma once
#include "matrix.h"
#include <string>

// ─── Abstract LossFunction ─────────────────────────────────────────────────
class LossFunction {
public:
    virtual double compute(const Matrix& pred, const Matrix& true_) const = 0;
    virtual Matrix gradient(const Matrix& pred, const Matrix& true_) const = 0;
    virtual ~LossFunction() = default;
};

// ─── Binary Cross-Entropy Loss ─────────────────────────────────────────────
class BCELoss : public LossFunction {
public:
    double epsilon;  // numerical stability

    explicit BCELoss(double epsilon = 1e-7);

    double compute(const Matrix& pred, const Matrix& true_) const override;
    Matrix gradient(const Matrix& pred, const Matrix& true_) const override;
};

// ─── Mean Squared Error Loss ───────────────────────────────────────────────
class MSELoss : public LossFunction {
public:
    double compute(const Matrix& pred, const Matrix& true_) const override;
    Matrix gradient(const Matrix& pred, const Matrix& true_) const override;
};
