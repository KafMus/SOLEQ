#ifndef GENERATORS_CPP_UUID_0000
#define GENERATORS_CPP_UUID_0000

#include <SOLEQ/generators.hpp>
#include <SOLEQ/DEFINES.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <list>



kfsoleq::CSR_Matrix kfsoleq::generatorPoissonEquationMatrix(size_t size_y, size_t size_x) {
        std::list<std::list<std::pair<size_t, kfsoleq::soleq_float>>> result_lil;
        std::list<std::pair<size_t, kfsoleq::soleq_float>> lil_curr_row;
        
        
        size_t ind_curr = 0;
        for (size_t i = 0; i < size_y; ++i) {
            for (size_t j = 0; j < size_x; ++j) {
                if (i > 1) {
                    ind_curr += size_x * (i - 1);
                }
                if (i > 0) {
                    ind_curr += j;
                    lil_curr_row.push_back(std::make_pair(ind_curr, -1));
                    ind_curr++;
                    ind_curr += (size_x - j - 1);
                }
                
                if (j > 1) {
                    ind_curr += (j - 1);
                }
                if (j > 0) {
                    lil_curr_row.push_back(std::make_pair(ind_curr, -1));
                    ind_curr++;
                }
                lil_curr_row.push_back(std::make_pair(ind_curr, 4));
                ind_curr++;
                if (j + 1 < size_x) {
                    lil_curr_row.push_back(std::make_pair(ind_curr, -1));
                    ind_curr++;
                }
                if (j + 2 < size_x) {
                    ind_curr += (size_x - j - 2);
                }
                
                if (i + 1 < size_y) {
                    ind_curr += j;
                    lil_curr_row.push_back(std::make_pair(ind_curr, -1));
                    ind_curr++;
                    ind_curr += (size_x - j - 1);
                }
                
                result_lil.push_back(lil_curr_row);
                lil_curr_row.clear();
                ind_curr = 0;
            }
        }
        
        return CSR_Matrix(result_lil);
}



#endif
