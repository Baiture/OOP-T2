#pragma once
#include <vector>
#include <functional>
#include <string>

class Matrix {
public:
    int rows;
    int cols;
    std::vector<double> data_;

    Matrix(int rows, int cols);
    Matrix(int rows, int cols, double init_val);

    int get_rows() const;
    int get_cols() const;
    double& at(int row, int col);
    double at(int row, int col) const;

    Matrix multiply(const Matrix& other) const;
    Matrix add(const Matrix& other) const;
    Matrix transpose() const;
    Matrix elementwise_multiply(const Matrix& other) const;
    Matrix applyFunction(std::function<double(double)> func) const;

    static Matrix zeros(int rows, int cols);
    static Matrix random(int rows, int cols, double scale = 1.0);
    void fill_from_span(const std::vector<double>& src);

    void print(const std::string& label = "") const;
};
