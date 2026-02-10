#include "../src/threediag.hpp"
#include <iostream>
#include <array>

int main() {
    
    unsigned int n = 10;
    unsigned int k = 100;
    
    // DiagThree initialisation check
    kfsoleq::DiagThree my_diag{};
    
    // DiagThree printing check
    my_diag.print();
    my_diag.printMatrix();
    
    // DiagThree filling check
    std::cout << "Filling my_diag...\n";
    auto diagonals = my_diag.getDiagonals();
    for (auto iter = diagonals.begin(); iter != diagonals.end(); ++iter) {
        for (unsigned int i = 0; i < n; ++i) {
            (*iter)->push_back((SOLEQ_FLOAT)(k + i));
        }
        k += 100;
    }
    std::cout << "Filling my_diag DONE!\n";
    my_diag.printMatrix();
    
    
    return 0;
}
