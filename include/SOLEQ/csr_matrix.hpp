#ifndef CSR_MATRIX_HPP_UUID_0000
#define CSR_MATRIX_HPP_UUID_0000

#include <SOLEQ/DEFINES.hpp>
#include <list>
#include <utility>
#include <vector>


namespace kfsoleq
{

class CSR_Matrix {
private:
        std::vector<soleq_float> values;
        std::vector<size_t> col_ind;
        std::vector<size_t> row_ind;
public:
        // Constructors and destructors
        CSR_Matrix(); // Default constructor
        CSR_Matrix(const std::list<std::list<std::pair<size_t, soleq_float>>>& lil);
        
        // Getters and setters
        const std::vector<soleq_float>& getValues() const { return values; }
        const std::vector<size_t>& getColumnIndexes() const { return col_ind; }
        const std::vector<size_t>& getRowIndexes() const { return row_ind; }
        
        // Additional infrastructure
        void print() const;
};


}


#endif
