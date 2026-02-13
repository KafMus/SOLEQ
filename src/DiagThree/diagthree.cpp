#ifndef DIAGTHREE_CPP_UUID_0000
#define DIAGTHREE_CPP_UUID_0000

#include <diagthree.hpp>
#include <array>
#include <iostream>
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
        this->constant_terms = std::vector<SOLEQ_FLOAT>{};
        this->roots = std::vector<SOLEQ_FLOAT>{};
}
kfsoleq::DiagThree::DiagThree(const kfsoleq::DiagThree& root_diagThree) {
	this->size = root_diagThree.size;
	this->diagonals = root_diagThree.diagonals;
        this->constant_terms = root_diagThree.constant_terms;
        this->roots = root_diagThree.roots;
}
kfsoleq::DiagThree::DiagThree(kfsoleq::DiagThree&& base_diagThree) {
	(*this) = std::move(base_diagThree);
}
kfsoleq::DiagThree::~DiagThree() { }
kfsoleq::DiagThree::DiagThree(unsigned int size,
                              const std::array<std::vector<SOLEQ_FLOAT>, 3>& diagonals,
                              const std::vector<SOLEQ_FLOAT>& constant_terms) {
        /*
         * shrink_to_fit() may not be the greatest way to shrink vectors,
         * because it doesn't necessarily do anything at all. Also maybe
         * I shouldn't shrink them here or shouldn't shrink them at all.
         */
        this->size = size;
        for (unsigned int i = 0; i < 3; ++i) {
            this->diagonals[i] = diagonals[i];
            this->diagonals[i].shrink_to_fit();
        }
        this->constant_terms = constant_terms;
        this->constant_terms.shrink_to_fit();
        this->roots = std::vector<SOLEQ_FLOAT>(size);
        this->roots.shrink_to_fit();
}


// 
// Additional infrastructure
// 
void kfsoleq::DiagThree::print() const {
	std::cout << "Size:[" << this->size << "]\n";
	std::cout << "Diagonals ptr:[" << &this->diagonals << "]\n";
	std::cout << "Constant Terms ptr:[" << &this->constant_terms << "]\n";
	std::cout << "Roots ptr:[" << &this->roots << "]\n";
}
void kfsoleq::DiagThree::printDiagonals() const {
        for (unsigned int i = 0; i < 3; ++i) {
            switch (i) {
                case 0:
                    std::cout << "a: ";
                    break;
                case 1:
                    std::cout << "b: ";
                    break;
                case 2:
                    std::cout << "c: ";
                    break;
            }
            std::cout << "[ ";
            for (auto jter = this->diagonals[i].begin(); jter != this->diagonals[i].end(); ++jter) {
                std::cout << (*jter) << ' ';
            }
            std::cout << "]\n";
        }
}
void kfsoleq::DiagThree::printConstantTerms() const {
        std::cout << "d: [ ";
        for (auto iter = this->constant_terms.begin(); iter != this->constant_terms.end(); ++iter) {
            std::cout << (*iter) << ' ';
        }
        std::cout << "]\n";
}
void kfsoleq::DiagThree::printRoots() const {
        std::cout << "x: [ ";
        for (auto iter = this->roots.begin(); iter != this->roots.end(); ++iter) {
            std::cout << (*iter) << ' ';
        }
        std::cout << "]\n";
}
void kfsoleq::DiagThree::solve() {
        std::vector<std::pair<SOLEQ_FLOAT, SOLEQ_FLOAT>> coeffs(this->size - 1);
        
        // Forward
        coeffs[0].first = -(this->diagonals[2][0] / this->diagonals[1][0]);
        coeffs[0].second = (this->constant_terms[0] / this->diagonals[1][0]);
        for (unsigned int i = 1; i < this->size - 1; ++i) {
            coeffs[i].first = -(this->diagonals[2][i] / (this->diagonals[0][i] * coeffs[i - 1].first + this->diagonals[1][i]));
            coeffs[i].second = (this->constant_terms[i] - this->diagonals[0][i] * coeffs[i - 1].second) / (this->diagonals[0][i] * coeffs[i - 1].first + this->diagonals[1][i]);
        }
        
        // Back
        this->roots[this->size - 1] = (constant_terms[this->size - 1] - diagonals[0][this->size - 1] * coeffs[this->size - 2].second) /
                                      (diagonals[0][this->size - 1] * coeffs[this->size - 2].first + diagonals[1][this->size - 1]);
        for (long i = this->size - 2; i >= 0; --i) {
            this->roots[i] = coeffs[i].first * roots[i + 1] + coeffs[i].second;
        }
}
bool kfsoleq::DiagThree::checkDiagonalDomination() const {
        if (abs(this->diagonals[1][0]) < abs(this->diagonals[2][0])) {
            return false;
        }
        for (unsigned int i = 1; i < this->size - 1; ++i) {
            if (abs(this->diagonals[1][i]) < (abs(this->diagonals[0][i]) + abs(this->diagonals[2][i]))) {
                return false;
            }
        }
        if (abs(this->diagonals[1][this->size - 1]) < abs(this->diagonals[0][this->size - 1])) {
            return false;
        }
        return true;
}


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
	this->constant_terms = root_diagThree.constant_terms;
	this->roots = root_diagThree.roots;
	return *this;
}
kfsoleq::DiagThree& kfsoleq::DiagThree::operator = (kfsoleq::DiagThree&& base_diagThree) {
	this->size = base_diagThree.size;
	this->diagonals = base_diagThree.diagonals;
	this->constant_terms = base_diagThree.constant_terms;
	this->roots = base_diagThree.roots;
        
        base_diagThree.size = 0;
        base_diagThree.diagonals = std::array<std::vector<SOLEQ_FLOAT>, 3>{};
        for (auto iter = base_diagThree.diagonals.begin(); iter != base_diagThree.diagonals.end(); ++iter) {
            (*iter) = std::vector<SOLEQ_FLOAT>{};
        }
        this->constant_terms = std::vector<SOLEQ_FLOAT>{};
        this->roots = std::vector<SOLEQ_FLOAT>{};
	return (*this);
}






#endif
