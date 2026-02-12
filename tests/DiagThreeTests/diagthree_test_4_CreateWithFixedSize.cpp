#include <diagthree.hpp>
#include <iostream>
#include <array>

int main() {
    
    unsigned int n = 10;
    unsigned int k = 100;
    
    // DiagThree constructing with fixed size check
    std::cout << "Constructing DiagThree with fixed size...\n";
    kfsoleq::DiagThree my_diag(n);
    std::cout << "Constructing DiagThree with fixed size DONE!\n";
    my_diag.print();
    my_diag.printDiagonals();
    
    auto& diagonals = my_diag.getDiagonalsRef();
    for (auto iter = diagonals.begin(); iter != diagonals.end(); ++iter) {
        for (unsigned int i = 0; i < n; ++i) {
            (*iter)[i] = (SOLEQ_FLOAT)(k + i);
        }
        k += 100;
    }
    my_diag.printDiagonals();
    
    
    return 0;
}
