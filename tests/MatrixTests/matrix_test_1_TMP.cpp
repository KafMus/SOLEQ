#include <SOLEQ/matrix.hpp>
#include <iostream>

int main() {
    
    kfsoleq::Matrix my_matrix{};
    std::cout << "Size Y:[" << my_matrix.getSizeY() << "]\n";
    std::cout << "Size X:[" << my_matrix.getSizeX() << "]\n";
    
    kfsoleq::Matrix matrix2(10, 30);
    std::cout << "Printing constructed with (size_x, size_y) constructor matrix:\n";
    matrix2.print();
    
    std::cout << "Testing manual matrix filling with overloaded operator ():\n";
    matrix2(0, 0) = 100;
    matrix2(1, 2) = 112;
    matrix2(1, 6) = 116;
    matrix2(1, 29) = 1129;
    matrix2(9, 0) = 190;
    matrix2(9, 11) = 1933;
    matrix2(9, 22) = 1922;
    matrix2(9, 29) = 1929;
    matrix2.print();
    
    
    return 0;
}
