#include <diagthree.hpp>
#include <iostream>
#include <array>

int main() {
    
    const unsigned int n = 5;
    unsigned int k = 100;
    
    // DiagThree constructing with fixed size check
    kfsoleq::DiagThree my_diag(n);
    my_diag.print();
    my_diag.printDiagonals();
    my_diag.printConstantTerms();
    
    auto& diagonals = my_diag.getDiagonalsRef();
    for (auto iter = diagonals.begin(); iter != diagonals.end(); ++iter) {
        for (unsigned int i = 0; i < n; ++i) {
            (*iter)[i] = (SOLEQ_FLOAT)(k + i);
        }
        k += 100;
    }
    my_diag.printDiagonals();
    
    k = 10000;
    auto& constant_terms = my_diag.getConstantTermsRef();
    for (auto iter = constant_terms.begin(); iter != constant_terms.end(); ++iter) {
        (*iter) = (SOLEQ_FLOAT)(k);
        k += 1000;
    }
    my_diag.printConstantTerms();
    
    
    std::cout << "Solving...\n";
    my_diag.solve();
    std::cout << "Solving DONE!\n";
    std::cout << "Roots:\n";
    my_diag.printRoots();
    
    
    return 0;
}
