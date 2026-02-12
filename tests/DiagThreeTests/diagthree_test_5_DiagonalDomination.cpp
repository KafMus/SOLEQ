#include <diagthree.hpp>
#include <iostream>
#include <vector>
#include <array>

int main() {
    
    const unsigned int n = 5; // Size of SOLEQ
    unsigned int k = 100;
    
    // Creating DiagThree
    std::array<std::vector<SOLEQ_FLOAT>, 3> diagonals;
    std::vector<SOLEQ_FLOAT> constant_terms(n);
    for (unsigned int i = 0; i < 3; ++i) {
        diagonals[i] = std::vector<SOLEQ_FLOAT>(n);
        for (unsigned int j = 0; j < n; ++j) {
            diagonals[i][j] = (SOLEQ_FLOAT)(k + j);
        }
        k += 100;
    }
    k = 10000;
    for (unsigned int i = 0; i < n; ++i) {
        constant_terms[i] = (SOLEQ_FLOAT)(k);
        k += 1000;
    }
    kfsoleq::DiagThree my_diag(n, diagonals, constant_terms);
    
    std::cout << "DiagThree:\n";
    my_diag.print();
    std::cout << "DiagThree Diagonals:\n";
    my_diag.printDiagonals();
    std::cout << "DiagThree Constant Terms:\n";
    my_diag.printConstantTerms();
    std::cout << "DiagThree Roots:\n";
    my_diag.printRoots();
    
    // Checking Diagonal Domination in DiagThree
    if (my_diag.checkDiagonalDomination()) {
        std::cout << "This DiagThree is Diagonally Dominated!\n";
    }
    else {
        std::cout << "This DiagThree is not Diagonally Dominated :(\n";
    }
    
    
    return 0;
}
