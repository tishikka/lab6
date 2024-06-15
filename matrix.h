#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <algorithm>
#include <iomanip>
/**
 * @brief Класс, определяющий матрицу
 */
class Matrix {

public:
    int rows_;
    int cols_;
    int** data_;
    /**
     * @brief Конструктор по умолчанию
     */
    Matrix();
    /**
     * @brief Конструктор с параметрами
     */
    Matrix(int rows, int cols);
    /**
     * @brief Конструктор копирования
     */
    Matrix(const Matrix& other);
    /**
     * @brief Деструктор
     */
    ~Matrix();

    /**
     * @brief Оператор сложения
     */
    Matrix operator+(const Matrix& other) const;
    /**
     * @brief Оператор вычитания
     */
    Matrix operator-(const Matrix& other) const;
    /**
     * @brief Оператор умножения на число
     */
    Matrix operator*(int scalar) const;
    /**
     * @brief Оператор умножения матриц
     */
    Matrix operator*(const Matrix& other) const;
    /**
     * @brief Оператор присваивания
     */
    Matrix& operator=(const Matrix& other);
    /**
     * @brief Оператор сравнения на равенство
     */
    bool operator==(const Matrix& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>>(std::istream& is, Matrix& matrix);

    int max() const;

private:
    void allocateMemory();
    void deallocateMemory();
    void fillRandomValues();
};

/**
* @brief Класс, определяющий свёртку
*/
class Convolution : public Matrix {


public:
    using Matrix::Matrix;
    Matrix convolve(const Matrix& other);
    Matrix convolve(int rows, int cols);
};

/**
* @brief Класс, определяющий субдискретизацию
*/
class Subsampling : public Matrix {


public:
    using Matrix::Matrix;
    Matrix subsample();
};

#endif 
