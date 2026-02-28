#ifndef VECTOR_CPP_UUID_0000
#define VECTOR_CPP_UUID_0000

#include <SOLEQ/vector.hpp>
#include <iostream>
#include <vector>



// 
// 
// Vector part
// 
// 

// 
// Constructors and destructors
// 
kfsoleq::Vector::Vector() :
    size(0),
    values(std::vector<SOLEQ_FLOAT>{}) {}
kfsoleq::Vector::Vector(size_t given_size) :
    size(given_size) {
        this->values = std::vector<SOLEQ_FLOAT>(given_size);
}


// 
// Additional infrastructure
// 
void kfsoleq::Vector::print() const {
	std::cout << "Size:[" << this->size << "]\n";
        std::cout << "Values:[ ";
        for (auto iter = values.begin(); iter != values.end(); ++iter) {
            std::cout << (*iter) << ' ';
        }
        std::cout << "]\n";
}







#endif
