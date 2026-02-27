#ifndef MATRIX_CPP_UUID_0000
#define MATRIX_CPP_UUID_0000

#include <SOLEQ/matrix.hpp>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>



// 
// 
// Matrix part
// 
// 

// 
// Constructors and destructors
// 
kfsoleq::Matrix::Matrix() :
    size_y(0),
    size_x(0),
    values(std::vector<SOLEQ_FLOAT>{}) {}
kfsoleq::Matrix::Matrix(size_t given_size_y, size_t given_size_x) :
    size_y(given_size_y),
    size_x(given_size_x) {
        this->values = std::vector<SOLEQ_FLOAT>(given_size_y * given_size_x);
}


// 
// Additional infrastructure
// 
void kfsoleq::Matrix::print() const {
	std::cout << "Size Y:[" << this->size_y << "]\n";
        std::cout << "Size X:[" << this->size_x << "]\n";
        std::cout << "Values:\n";
        for (size_t i = 0; i < this->size_y; ++i) {
            std::cout << "[";
            for (size_t j = 0; j < this->size_x; ++j) {
                std::cout << this->values[(i * this->size_x) + j] << ' ';
            }
            std::cout << "]\n";
        }
}







#endif
