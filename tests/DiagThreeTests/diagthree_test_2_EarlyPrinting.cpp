#include <diagthree.hpp>
#include <iostream>
#include <array>

int main() {
    
    kfsoleq::DiagThree my_diag{};
    
    // DiagThree printing check
    std::cout << "DiagThree Printing...\n";
    my_diag.print();
    std::cout << "DiagThree Printing DONE!\n";
    std::cout << "DiagThree Printing Diagonals...\n";
    my_diag.printDiagonals();
    std::cout << "DiagThree Printing Diagonals DONE!\n";
    
    
    return 0;
}
