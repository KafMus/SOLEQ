#ifndef DIAGTHREE_CPP_UUID_0000
#define DIAGTHREE_CPP_UUID_0000

#include <diagthree.hpp>
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
kfsoleq::DiagThree::DiagThree() : size(0) {
        for (auto iter = this->diagonals.begin(); iter != this->diagonals.end(); ++iter) {
            (*iter) = std::vector<SOLEQ_FLOAT>{};
        }
}
kfsoleq::DiagThree::DiagThree(const kfsoleq::DiagThree& root_diagThree) {
	this->size = root_diagThree.size;
	this->diagonals = root_diagThree.diagonals;
}
kfsoleq::DiagThree::DiagThree(kfsoleq::DiagThree&& base_diagThree) {
	(*this) = std::move(base_diagThree);
}
kfsoleq::DiagThree::~DiagThree() { }
kfsoleq::DiagThree::DiagThree(unsigned int size) {
        for (auto iter = this->diagonals.begin(); iter != this->diagonals.end(); ++iter) {
            
            // May not be the best way to do this
            (*iter) = std::vector<SOLEQ_FLOAT>(size);
            (*iter).shrink_to_fit();
        }
        this->size = size;
}


// 
// Getters and setters



// 
// Additional infrastructure
// 
void kfsoleq::DiagThree::print() const {
	std::cout << "Size:[" << this->size << "]\n";
	std::cout << "Diagonals ptr:[" << &this->diagonals << "]\n";
}
void kfsoleq::DiagThree::printDiagonals() const {
        for (auto iter = this->diagonals.begin(); iter != this->diagonals.end(); ++iter) {
            std::cout << "[ ";
            for (auto jter = (*iter).begin(); jter != (*iter).end(); ++jter) {
                std::cout << (*jter) << ' ';
            }
            std::cout << "]\n";
        }
}
/*void kfsoleq::getCoefficientsByIndex(unsigned int index, std::pair<SOLEQ_FLOAT, SOLEQ_FLOAT> coefficients) const {
        ddd
}*/


// 
// Operators overload
// 
kfsoleq::DiagThree& kfsoleq::DiagThree::operator = (const kfsoleq::DiagThree& root_diagThree) {
	
	// Check self assignment
	if (this == &root_diagThree) {
		return *this;
	}
	
	this->size = root_diagThree.size;
	this->diagonals = root_diagThree.diagonals;
	return *this;
}
kfsoleq::DiagThree& kfsoleq::DiagThree::operator = (kfsoleq::DiagThree&& base_diagThree) {
	this->size = base_diagThree.size;
	this->diagonals = base_diagThree.diagonals;
        
        base_diagThree.size = 0;
        base_diagThree.diagonals = std::array<std::vector<SOLEQ_FLOAT>, 3>{};
        for (auto iter = base_diagThree.diagonals.begin(); iter != base_diagThree.diagonals.end(); ++iter) {
            (*iter) = std::vector<SOLEQ_FLOAT>{};
        }
	return (*this);
}






#endif
