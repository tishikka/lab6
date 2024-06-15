#include "matrix.h"
#include <iostream>

int main() {
    Matrix m1;
    std::cout << "Matrix m1 (default 2x2 zero matrix):\n" << m1 << std::endl;

    Matrix m2(3, 3);
    std::cout << "Matrix m2 (3x3 matrix with random values):\n" << m2 << std::endl;

    Matrix m3 = m2;
    std::cout << "Matrix m3 (copy of m2):\n" << m3 << std::endl;

    Matrix m4(3, 3);
    std::cout << "Matrix m4 (3x3 matrix with random values):\n" << m4 << std::endl;

    Matrix sum = m2 + m4;
    std::cout << "Sum of m2 and m4:\n" << sum << std::endl;

    Matrix diff = m2 - m4;
    std::cout << "Difference of m2 and m4:\n" << diff << std::endl;

    Matrix prod = m2 * 2;
    std::cout << "Product of m2 and 2:\n" << prod << std::endl;

    std::cout << "Max value in m2: " << m2.max() << std::endl;

    std::cout << "Enter values for a 2x2 matrix:\n";
    Matrix m5(2, 2);
    std::cin >> m5;
    std::cout << "Matrix m5:\n" << m5 << std::endl;


    Convolution conv(3, 3);
    std::cout << "Convolution matrix (3x3 with random values):\n" << conv << std::endl;
    Matrix convResult = conv.convolve(m2);
    std::cout << "Convolution result of conv and m2:\n" << convResult << std::endl;


    Subsampling sub(4, 4);
    std::cout << "Subsampling matrix (4x4 with random values):\n" << sub << std::endl;
    Matrix subResult = sub.subsample();
    std::cout << "Subsampling result:\n" << subResult << std::endl;

    return 0;
}
