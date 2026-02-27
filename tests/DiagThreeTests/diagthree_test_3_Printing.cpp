#include <SOLEQ/diagthree.hpp>
#include <iostream>
#include <vector>
#include <array>

int main() {
    
    const unsigned int n = 5; // Size of SOLEQ
    unsigned int k = 100;
    
    
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
    
    
    // Creating DiagThree
    kfsoleq::DiagThree my_diag(n, diagonals, constant_terms);
    
    // Printing DiagThree
    std::cout << "Printing created DiagThree...\n";
    my_diag.print();
    std::cout << "Printing created DiagThree DONE!\n";
    std::cout << "Printing created DiagThree's Diagonals...\n";
    my_diag.printDiagonals();
    std::cout << "Printing created DiagThree's Diagonals DONE!\n";
    std::cout << "Printing created DiagThree's Constant Terms...\n";
    my_diag.printConstantTerms();
    std::cout << "Printing created DiagThree's Constant Terms DONE!\n";
    std::cout << "Printing created DiagThree's Roots (should be zeros)...\n";
    my_diag.printRoots();
    std::cout << "Printing created DiagThree's Roots (should be zeros) DONE!\n";
    
    
    
    return 0;
}
