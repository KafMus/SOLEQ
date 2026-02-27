#ifndef CSR_MATRIX_CPP_UUID_0000
#define CSR_MATRIX_CPP_UUID_0000

#include <csr_matrix.hpp>
#include <iostream>
#include <list>
#include <utility>
#include <vector>



// 
// 
// CSR_Matrix part
// 
// 

// 
// Constructors and destructors
// 
kfsoleq::CSR_Matrix::CSR_Matrix() :
    values(std::vector<SOLEQ_FLOAT>{}),
    col_ind(std::vector<size_t>{}),
    row_ind(std::vector<size_t>{}) {}
kfsoleq::CSR_Matrix::CSR_Matrix(const std::list<std::list<std::pair<size_t, SOLEQ_FLOAT>>>& lil) {
        row_ind.reserve(lil.size() + 1);
        size_t k = 0; // Number of non-zero elements above current row
        
        // Getting values and column indexes
        for (auto iter = lil.begin(); iter != lil.end(); ++iter) {
            values.reserve(iter->size());
            col_ind.reserve(iter->size());
            row_ind.push_back(k);
            for (auto jter = iter->begin(); jter != iter->end(); ++jter) {
                values.push_back(jter->second);
                col_ind.push_back(jter->first);
            }
            k += iter->size();
        }
        row_ind.push_back(k);
}


// 
// Additional infrastructure
// 
void kfsoleq::CSR_Matrix::print() const {
        std::cout << "Values:\t\t{ ";
        for (auto iter = values.begin(); iter != values.end(); ++iter) {
            std::cout << (*iter) << " ";
        }
        std::cout << "}\nColumn Indexes:\t{ ";
        for (auto iter = col_ind.begin(); iter != col_ind.end(); ++iter) {
            std::cout << (*iter) << " ";
        }
        std::cout << "}\nRow Indexes:\t{ ";
        for (auto iter = row_ind.begin(); iter != row_ind.end(); ++iter) {
            std::cout << (*iter) << " ";
        }
        std::cout << "}\n";
}







#endif
