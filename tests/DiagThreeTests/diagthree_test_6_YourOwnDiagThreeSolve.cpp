#include <diagthree.hpp>
#include <iostream>
#include <vector>
#include <array>

int main() {
    
    char tmp;
    unsigned int n; // Size of SOLEQ
    std::cout << "Size: ";
    std::cin >> n;
    
    // Creating DiagThree
    std::array<std::vector<SOLEQ_FLOAT>, 3> diagonals;
    std::vector<SOLEQ_FLOAT> constant_terms(n);
    for (unsigned int i = 0; i < 3; ++i) {
        diagonals[i] = std::vector<SOLEQ_FLOAT>(n);
        for (unsigned int j = 0; j < n; ++j) {
            switch(i) {
                case 0:
                    if (0 == j) {
                        std::cout << "a_0: BLANK\n";
                        continue;
                    }
                    std::cout << "a_" << j << ": ";
                    break;
                case 1:
                    std::cout << "b_" << j << ": ";
                    break;
                case 2:
                    if (n - 1 == j) {
                        std::cout << "c_" << j << ": BLANK\n";
                        continue;
                    }
                    std::cout << "c_" << j << ": ";
                    break;
            }
            std::cin >> diagonals[i][j];
        }
    }
    for (unsigned int i = 0; i < n; ++i) {
        std::cout << "d_" << i << ": ";
        std::cin >> constant_terms[i];
    }
    kfsoleq::DiagThree my_diag(n, diagonals, constant_terms);
    
    std::cout << "DiagThree:\n";
    my_diag.print();
    std::cout << "DiagThree Diagonals:\n";
    my_diag.printDiagonals();
    std::cout << "DiagThree Constant Terms:\n";
    my_diag.printConstantTerms();
    
    // Checking Diagonal Domination in DiagThree
    if (my_diag.checkDiagonalDomination()) {
        std::cout << "This DiagThree is Diagonally Dominated!\n";
    }
    else {
        std::cout << "This DiagThree is not Diagonally Dominated :(\n";
        std::cout << "Are you sure that you want to try to solve it? [y/n] ";
        std::cin >> tmp;
        if ('y' != tmp) {
            return 0;
        }
    }
    
    // Solving SOLEQ
    my_diag.solve();
    std::cout << "DiagThree Roots:\n";
    my_diag.printRoots();
    
    
    
    return 0;
}
