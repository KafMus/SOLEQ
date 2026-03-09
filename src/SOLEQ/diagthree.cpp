#ifndef DIAGTHREE_CPP_UUID_0000
#define DIAGTHREE_CPP_UUID_0000

#include <SOLEQ/diagthree.hpp>
#include <SOLEQ/DEFINES.hpp>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>



// 
// Constructors and destructors
// 
kfsoleq::DiagThree::DiagThree() :
    size(0),
    constant_terms(std::vector<kfsoleq::soleq_float>{}),
    roots(std::vector<kfsoleq::soleq_float>{}) {
        for (size_t i = 0; i < 3; ++i) {
            this->diagonals[i] = std::vector<kfsoleq::soleq_float>{};
        }
}
kfsoleq::DiagThree::DiagThree(size_t given_size,
                              const std::array<std::vector<kfsoleq::soleq_float>, 3>& given_diagonals,
                              const std::vector<kfsoleq::soleq_float>& given_constant_terms) :
    size(given_size),
    constant_terms(given_constant_terms),
    roots(std::vector<kfsoleq::soleq_float>(given_size)) {
        /*
         * shrink_to_fit() may not be the greatest way to shrink vectors,
         * because it doesn't necessarily do anything at all. Also maybe
         * I shouldn't shrink them here or shouldn't shrink them at all.
         */
        for (size_t i = 0; i < 3; ++i) {
            this->diagonals[i] = given_diagonals[i];
            this->diagonals[i].shrink_to_fit();
        }
        this->constant_terms.shrink_to_fit();
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
        for (size_t i = 0; i < 3; ++i) {
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
        std::vector<std::pair<kfsoleq::soleq_float, kfsoleq::soleq_float>> coeffs(this->size - 1);
        
        // Forward
        coeffs[0].first = -(this->diagonals[2][0] / this->diagonals[1][0]);
        coeffs[0].second = (this->constant_terms[0] / this->diagonals[1][0]);
        for (size_t i = 1; i < this->size - 1; ++i) {
            coeffs[i].first = -(this->diagonals[2][i] / (this->diagonals[0][i] * coeffs[i - 1].first + this->diagonals[1][i]));
            coeffs[i].second = (this->constant_terms[i] - this->diagonals[0][i] * coeffs[i - 1].second) / (this->diagonals[0][i] * coeffs[i - 1].first + this->diagonals[1][i]);
        }
        
        // Back
        this->roots[this->size - 1] = (constant_terms[this->size - 1] - diagonals[0][this->size - 1] * coeffs[this->size - 2].second) /
                                      (diagonals[0][this->size - 1] * coeffs[this->size - 2].first + diagonals[1][this->size - 1]);
        for (long long int i = (long long int)(this->size - 2); i >= 0; --i) {
            this->roots[(size_t)i] = coeffs[(size_t)i].first * roots[(size_t)i + 1] + coeffs[(size_t)i].second;
        }
}
bool kfsoleq::DiagThree::checkDiagonalDomination() const {
        if (std::abs(this->diagonals[1][0]) < std::abs(this->diagonals[2][0])) {
            return false;
        }
        for (size_t i = 1; i < this->size - 1; ++i) {
            if (std::abs(this->diagonals[1][i]) < (std::abs(this->diagonals[0][i]) + std::abs(this->diagonals[2][i]))) {
                return false;
            }
        }
        if (std::abs(this->diagonals[1][this->size - 1]) < std::abs(this->diagonals[0][this->size - 1])) {
            return false;
        }
        return true;
}







#endif
