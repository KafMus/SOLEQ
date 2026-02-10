#include "../src/threediag.hpp"
#include <iostream>
#include <array>

int main() {
    
    unsigned int n = 10;
    unsigned int k = 100;
    
    kfsoleq::DiagThree my_diag{};
    my_diag.print();
    my_diag.printDiagonals();
    
    // DiagThree filling check
    std::cout << "Filling DiagThree Directly...\n";
    auto& diagonals = my_diag.getDiagonalsRef();
    for (auto iter = diagonals.begin(); iter != diagonals.end(); ++iter) {
        for (unsigned int i = 0; i < n; ++i) {
            (*iter).push_back((SOLEQ_FLOAT)(k + i));
        }
        k += 100;
    }
    std::cout << "Filling DiagThree Directly DONE!\n";
    my_diag.printDiagonals();
    
    
    return 0;
}
