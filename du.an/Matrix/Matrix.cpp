#include "matrix.h"
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <random>
#include <iomanip>

Matrix::Matrix(int rows, int cols)
    : rows(rows), cols(cols), data_(rows * cols, 0.0) {}

Matrix::Matrix(int rows, int cols, double init_val)
    : rows(rows), cols(cols), data_(rows * cols, init_val) {}

int Matrix::get_rows() const { return rows; }
int Matrix::get_cols() const { return cols; }

double& Matrix::at(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols)
        throw std::out_of_range("Matrix index out of range");
    return data_[row * cols + col];
}

double Matrix::at(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols)
        throw std::out_of_range("Matrix index out of range");
    return data_[row * cols + col];
}

Matrix Matrix::multiply(const Matrix& other) const {
    if (cols != other.rows)
        throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i)
        for (int k = 0; k < cols; ++k)
            for (int j = 0; j < other.cols; ++j)
                result.at(i, j) += at(i, k) * other.at(k, j);
    return result;
}

Matrix Matrix::add(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix dimensions must match for addition");
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; ++i)
        result.data_[i] = data_[i] + other.data_[i];
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            result.at(j, i) = at(i, j);
    return result;
}

Matrix Matrix::elementwise_multiply(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols)
        throw std::invalid_argument("Matrix dimensions must match for elementwise multiply");
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; ++i)
        result.data_[i] = data_[i] * other.data_[i];
    return result;
}

Matrix Matrix::applyFunction(std::function<double(double)> func) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows * cols; ++i)
        result.data_[i] = func(data_[i]);
    return result;
}

Matrix Matrix::zeros(int rows, int cols) {
    return Matrix(rows, cols, 0.0);
}

Matrix Matrix::random(int rows, int cols, double scale) {
    static std::mt19937 gen(42);
    std::normal_distribution<double> dist(0.0, scale);
    Matrix result(rows, cols);
    for (auto& v : result.data_)
        v = dist(gen);
    return result;
}

void Matrix::fill_from_span(const std::vector<double>& src) {
    if ((int)src.size() != rows * cols)
        throw std::invalid_argument("Source size does not match matrix size");
    data_ = src;
}

void Matrix::print(const std::string& label) const {
    if (!label.empty()) std::cout << label << ":\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            std::cout << std::setw(10) << std::setprecision(4) << at(i, j) << " ";
        std::cout << "\n";
    }
}
