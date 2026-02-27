#include <SOLEQ/csr_matrix.hpp>
#include <iostream>
#include <list>
#include <utility>

int main() {
    
    std::cout << "CSR_Matrix constructed by default constructor:\n";
    kfsoleq::CSR_Matrix my_matrix{};
    my_matrix.print();
    
    
    std::cout << "CSR_Matrix constructed by LIL constructor:\n";
    
    std::list<std::pair<size_t, SOLEQ_FLOAT>>  lil_first_row = { std::make_pair(0, 1) };
    std::list<std::pair<size_t, SOLEQ_FLOAT>> lil_second_row = { std::make_pair(1, 2) };
    std::list<std::list<std::pair<size_t, SOLEQ_FLOAT>>> my_lil = { lil_first_row, lil_second_row };
    
    kfsoleq::CSR_Matrix my_matrix2(my_lil);
    my_matrix2.print();
    
    
    std::cout << "Another CSR_Matrix constructed by LIL constructor:\n";
    
    std::list<std::pair<size_t, SOLEQ_FLOAT>> lil_third_row{};
    lil_first_row =  { std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(3, 3) };
    lil_second_row = { std::make_pair(2, 4) };
    lil_third_row =  { std::make_pair(1, 1), std::make_pair(3, 11) };
    my_lil = { lil_first_row, lil_second_row, lil_third_row };
    
    kfsoleq::CSR_Matrix my_matrix3(my_lil);
    my_matrix3.print();
    
    
    return 0;
}
