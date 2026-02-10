#ifndef THREEDIAG_CPP_UUID_0000
#define THREEDIAG_CPP_UUID_0000

#include "threediag.hpp"
#include <iostream>
#include <array>
#include <vector>



// 
// 
// DiagThree part
// 
// 

// 
// Constructors and destructors
// 
kfsoleq::DiagThree::DiagThree() {
        for (auto iter = this->diagonals.begin(); iter != this->diagonals.end(); ++iter) {
            (*iter) = new std::vector<SOLEQ_FLOAT>{};
        }
}
kfsoleq::DiagThree::DiagThree(const kfsoleq::DiagThree& root_diagThree) {
	this->diagonals = root_diagThree.diagonals;
}
kfsoleq::DiagThree::DiagThree(kfsoleq::DiagThree&& base_diagThree) {
	(*this) = std::move(base_diagThree);
}
kfsoleq::DiagThree::~DiagThree() {
        for (auto iter = this->diagonals.begin(); iter != this->diagonals.end(); ++iter) {
            delete (*iter);
        }
}


// 
// Getters and setters
// 



// 
// Additional infrastructure
// 
void kfsoleq::DiagThree::print() const {
	std::cout << "Diagonals ptr:[" << &this->diagonals << "]\n";
}
void kfsoleq::DiagThree::printMatrix() const {
        std::cout << "Diagonals:\n";
        for (auto iter = this->diagonals.begin(); iter != this->diagonals.end(); ++iter) {
            std::cout << "[";
            for (auto jter = (*iter)->begin(); jter != (*iter)->end(); ++jter) {
                std::cout << (*jter) << ' ';
            }
            std::cout << "]\n";
        }
}


// 
// Operators overload
// 
kfsoleq::DiagThree& kfsoleq::DiagThree::operator = (const kfsoleq::DiagThree& root_diagThree) {
	
	// Check self assignment
	if (this == &root_diagThree) {
		return *this;
	}
	
	this->diagonals = root_diagThree.diagonals;
	return *this;
}
kfsoleq::DiagThree& kfsoleq::DiagThree::operator = (kfsoleq::DiagThree&& base_diagThree) {
	this->diagonals = base_diagThree.diagonals;
        base_diagThree.diagonals = std::array<std::vector<SOLEQ_FLOAT>*, 3>{};
        for (auto iter = base_diagThree.diagonals.begin(); iter != base_diagThree.diagonals.end(); ++iter) {
            (*iter) = new std::vector<SOLEQ_FLOAT>{};
        }
	return (*this);
}






#endif
