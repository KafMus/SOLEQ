#ifndef CSR_MATRIX_HPP_UUID_0000
#define CSR_MATRIX_HPP_UUID_0000

#include <iostream>
#include <list>
#include <utility>
#include <vector>


namespace kfsoleq
{

#ifndef SOLEQ_FLOAT
#define SOLEQ_FLOAT double // Probably should be included with some "main_defines.hpp" or something file.
#endif

class CSR_Matrix {
private:
        std::vector<SOLEQ_FLOAT> values;
        std::vector<size_t> col_ind;
        std::vector<size_t> row_ind;
public:
	// Constructors and destructors
        CSR_Matrix(); // Default constructor
        CSR_Matrix(const std::list<std::list<std::pair<size_t, SOLEQ_FLOAT>>>& lil);
	
	// Getters and setters
        std::vector<SOLEQ_FLOAT> getValues() const { return values; }
        std::vector<size_t> getColumnIndexes() const { return col_ind; }
        std::vector<size_t> getRowIndexes() const { return row_ind; }
        
	// Additional infrastructure
        void print() const;
        
        // Operators overload
};


}


#endif
