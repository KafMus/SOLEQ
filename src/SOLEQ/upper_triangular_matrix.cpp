#ifndef UPPER_TRIANGULAR_MATRIX_CPP_UUID_0000
#define UPPER_TRIANGULAR_MATRIX_CPP_UUID_0000

#include <SOLEQ/upper_triangular_matrix.hpp>
#include <SOLEQ/DEFINES.hpp>
#include <array>
#include <iostream>
#include <vector>



// 
// Constructors and destructors
// 
kfsoleq::UpperTriangularMatrix::UpperTriangularMatrix() :
    size_y(0),
    size_x(0),
    values(std::vector<kfsoleq::soleq_float>{}) {}
kfsoleq::UpperTriangularMatrix::UpperTriangularMatrix(size_t given_size_y, size_t given_size_x) :
    size_y(given_size_y),
    size_x(given_size_x) {
        this->values = std::vector<kfsoleq::soleq_float>(((1 + given_size_x) * given_size_x) / 2);
}


// 
// Additional infrastructure
// 
void kfsoleq::UpperTriangularMatrix::print() const {
        std::cout << "Size Y:[" << this->size_y << "]\n";
        std::cout << "Size X:[" << this->size_x << "]\n";
        std::cout << "Values:\n";
        for (size_t i = 0; i < this->size_y; ++i) {
            std::cout << "[ ";
            for (size_t j = 0; j < this->size_x; ++j) {
                if (j >= i) {
                    std::cout << this->values[(((2 * size_x - i + 1) * i) / 2) + j - i] << ' ';
                }
                else {
                    std::cout << "0 ";
                }
            }
            std::cout << "]\n";
        }
}







#endif
