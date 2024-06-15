#include "matrix.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

Matrix::Matrix() : rows_(2), cols_(2) {
    allocateMemory();
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            data_[i][j] = 0;
}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    allocateMemory();
    fillRandomValues();
}

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    allocateMemory();
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            data_[i][j] = other.data_[i][j];
}

Matrix::~Matrix() {
    deallocateMemory();
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");
    }

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            result.data_[i][j] = data_[i][j] + other.data_[i][j];

    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrices must have the same dimensions for subtraction.");
    }

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            result.data_[i][j] = data_[i][j] - other.data_[i][j];

    return result;
}

Matrix Matrix::operator*(int scalar) const {
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            result.data_[i][j] = data_[i][j] * scalar;

    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Matrices dimensions are not suitable for multiplication.");
    }

    Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < other.cols_; ++j) {
            result.data_[i][j] = 0;
            for (int k = 0; k < cols_; ++k) {
                result.data_[i][j] += data_[i][k] * other.data_[k][j];
            }
        }
    }

    return result;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;

    deallocateMemory();

    rows_ = other.rows_;
    cols_ = other.cols_;
    allocateMemory();
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            data_[i][j] = other.data_[i][j];

    return *this;
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) return false;
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            if (data_[i][j] != other.data_[i][j]) return false;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (int i = 0; i < matrix.rows_; ++i) {
        for (int j = 0; j < matrix.cols_; ++j) {
            os << std::setw(4) << matrix.data_[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& matrix) {
    for (int i = 0; i < matrix.rows_; ++i)
        for (int j = 0; j < matrix.cols_; ++j)
            is >> matrix.data_[i][j];
    return is;
}

int Matrix::max() const {
    int maxVal = data_[0][0];
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            if (data_[i][j] > maxVal)
                maxVal = data_[i][j];
    return maxVal;
}

Matrix Convolution::convolve(const Matrix& other) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw std::invalid_argument("Matrices must have the same dimensions for convolution.");
    }

    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            int sum = 0;
            for (int k = 0; k < rows_; ++k) {
                for (int l = 0; l < cols_; ++l) {
                    sum += data_[(i + k) % rows_][(j + l) % cols_] * other.data_[k][l];
                }
            }
            result.data_[i][j] = sum;
        }
    }

    return result;
}

Matrix Subsampling::subsample() {
    Matrix result((rows_ + 1) / 2, (cols_ + 1) / 2);
    for (int i = 0; i < rows_; i += 2) {
        for (int j = 0; j < cols_; j += 2) {
            int maxVal = data_[i][j];
            if (i + 1 < rows_) maxVal = std::max(maxVal, data_[i + 1][j]);
            if (j + 1 < cols_) maxVal = std::max(maxVal, data_[i][j + 1]);
            if (i + 1 < rows_ && j + 1 < cols_) maxVal = std::max(maxVal, data_[i + 1][j + 1]);
            result.data_[i / 2][j / 2] = maxVal;
        }
    }
    return result;
}

void Matrix::allocateMemory() {
    data_ = new int*[rows_];
    for (int i = 0; i < rows_; ++i)
        data_[i] = new int[cols_];
}

void Matrix::deallocateMemory() {
    for (int i = 0; i < rows_; ++i)
        delete[] data_[i];
    delete[] data_;
}

void Matrix::fillRandomValues() {
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            data_[i][j] = rand() % 100;
}
