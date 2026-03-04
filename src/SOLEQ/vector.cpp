#ifndef VECTOR_CPP_UUID_0000
#define VECTOR_CPP_UUID_0000

#include <SOLEQ/vector.hpp>
#include <cmath>
#include <iostream>
#include <vector>



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
SOLEQ_FLOAT kfsoleq::Vector::getNorm() const {
        SOLEQ_FLOAT result = 0;
        for (auto iter = values.begin(); iter != values.end(); ++iter) {
            result += std::pow((*iter), 2);
        }
        return std::sqrt(result);
}


// 
// Operator Overloading
// 
kfsoleq::Vector& kfsoleq::Vector::operator += (const kfsoleq::Vector& right_vector) {
        for (size_t i = 0; i < this->size; ++i) {
            this->values[i] += right_vector.values[i];
        }
        return (*this);
}
SOLEQ_FLOAT kfsoleq::Vector::operator *= (const kfsoleq::Vector& right_vector) {
        SOLEQ_FLOAT result = 0;
        for (size_t i = 0; i < this->size; ++i) {
            result += this->values[i] * right_vector.values[i];
        }
        return result;
}
kfsoleq::Vector& kfsoleq::Vector::operator *= (SOLEQ_FLOAT right_value) {
        for (auto iter = this->values.begin(); iter != this->values.end(); ++iter) {
            (*iter) *= right_value;
        }
        return (*this);
}
kfsoleq::Vector kfsoleq::operator + (kfsoleq::Vector left_vector, const kfsoleq::Vector& right_vector) {
        return left_vector += right_vector;
}
SOLEQ_FLOAT kfsoleq::operator * (kfsoleq::Vector left_vector, const kfsoleq::Vector& right_vector) {
        return left_vector *= right_vector;
}
kfsoleq::Vector kfsoleq::operator * (kfsoleq::Vector left_vector, SOLEQ_FLOAT right_value) {
        return left_vector *= right_value;
}
kfsoleq::Vector kfsoleq::operator * (SOLEQ_FLOAT left_value, kfsoleq::Vector right_vector) {
        return right_vector *= left_value;
}






#endif
