#include "lossfunction.h"
#include <cmath>
#include <stdexcept>

// ─── BCELoss ───────────────────────────────────────────────────────────────

BCELoss::BCELoss(double epsilon) : epsilon(epsilon) {}

double BCELoss::compute(const Matrix& pred, const Matrix& true_) const {
    if (pred.get_rows() != true_.get_rows() || pred.get_cols() != true_.get_cols())
        throw std::invalid_argument("BCELoss: pred and true must have same shape");

    double loss = 0.0;
    int n = pred.get_rows() * pred.get_cols();
    for (int i = 0; i < pred.get_rows(); ++i)
        for (int j = 0; j < pred.get_cols(); ++j) {
            double p = std::max(epsilon, std::min(1.0 - epsilon, pred.at(i, j)));
            double y = true_.at(i, j);
            loss += -(y * std::log(p) + (1.0 - y) * std::log(1.0 - p));
        }
    return loss / n;
}

Matrix BCELoss::gradient(const Matrix& pred, const Matrix& true_) const {
    if (pred.get_rows() != true_.get_rows() || pred.get_cols() != true_.get_cols())
        throw std::invalid_argument("BCELoss: pred and true must have same shape");

    int n = pred.get_rows() * pred.get_cols();
    Matrix grad(pred.get_rows(), pred.get_cols());
    for (int i = 0; i < pred.get_rows(); ++i)
        for (int j = 0; j < pred.get_cols(); ++j) {
            double p = std::max(epsilon, std::min(1.0 - epsilon, pred.at(i, j)));
            double y = true_.at(i, j);
            grad.at(i, j) = (-(y / p) + (1.0 - y) / (1.0 - p)) / n;
        }
    return grad;
}

// ─── MSELoss ───────────────────────────────────────────────────────────────

double MSELoss::compute(const Matrix& pred, const Matrix& true_) const {
    if (pred.get_rows() != true_.get_rows() || pred.get_cols() != true_.get_cols())
        throw std::invalid_argument("MSELoss: pred and true must have same shape");

    double loss = 0.0;
    int n = pred.get_rows() * pred.get_cols();
    for (int i = 0; i < pred.get_rows(); ++i)
        for (int j = 0; j < pred.get_cols(); ++j) {
            double diff = pred.at(i, j) - true_.at(i, j);
            loss += diff * diff;
        }
    return loss / n;
}

Matrix MSELoss::gradient(const Matrix& pred, const Matrix& true_) const {
    if (pred.get_rows() != true_.get_rows() || pred.get_cols() != true_.get_cols())
        throw std::invalid_argument("MSELoss: pred and true must have same shape");

    int n = pred.get_rows() * pred.get_cols();
    Matrix grad(pred.get_rows(), pred.get_cols());
    for (int i = 0; i < pred.get_rows(); ++i)
        for (int j = 0; j < pred.get_cols(); ++j)
            grad.at(i, j) = 2.0 * (pred.at(i, j) - true_.at(i, j)) / n;
    return grad;
}
