#include <diagthree.hpp>
#include <iostream>
#include <array>

int main() {
    
    unsigned int n = 10;
    unsigned int k = 100;
    
    // DiagThree constructing with fixed size check
    kfsoleq::DiagThree my_diag(n);
    my_diag.print();
    my_diag.printDiagonals();
    std::cout << "Printing Constant Terms...\n";
    my_diag.printConstantTerms();
    std::cout << "Printing Constant Terms DONE!\n";
    
    auto& diagonals = my_diag.getDiagonalsRef();
    for (auto iter = diagonals.begin(); iter != diagonals.end(); ++iter) {
        for (unsigned int i = 0; i < n; ++i) {
            (*iter)[i] = (SOLEQ_FLOAT)(k + i);
        }
        k += 100;
    }
    my_diag.printDiagonals();
    
    std::cout << "Filling Constant Terms...\n";
    k = 10000;
    auto& constant_terms = my_diag.getConstantTermsRef();
    for (auto iter = constant_terms.begin(); iter != constant_terms.end(); ++iter) {
        (*iter) = (SOLEQ_FLOAT)(k);
        k += 1000;
    }
    std::cout << "Filling Constant Terms DONE!\n";
    my_diag.printConstantTerms();
    
    
    return 0;
}
