#include <gtest/gtest.h>
#include <SOLEQ/generators.hpp>
#include <SOLEQ/DEFINES.hpp>
#include <SOLEQ/csr_matrix.hpp>


TEST(Generators, GeneratorPoissonEquationMatrix) {
    size_t size_y = 3;
    size_t size_x = 3;
    kfsoleq::soleq_float result_val_data_1[33] = {  4, -1, -1,
                                                   -1,  4, -1, -1,
                                                   -1,  4, -1,
                                                   -1,  4, -1, -1,
                                                   -1, -1,  4, -1, -1,
                                                   -1, -1,  4, -1,
                                                   -1,  4, -1,
                                                   -1, -1,  4, -1,
                                                   -1, -1,  4 };
    size_t result_col_data_1[33] = { 0, 1, 3,
                                     0, 1, 2, 4,
                                     1, 2, 5,
                                     0, 3, 4, 6,
                                     1, 3, 4, 5, 7,
                                     2, 4, 5, 8,
                                     3, 6, 7,
                                     4, 6, 7, 8,
                                     5, 7, 8 };
    size_t result_row_data_1[10] = { 0, 3, 7, 10, 14, 19, 23, 26, 30, 33 };
    
    kfsoleq::CSR_Matrix result = kfsoleq::generatorPoissonEquationMatrix(size_y, size_x);
    
    for (size_t i = 0; i < 33; ++i) {
        EXPECT_NEAR(result.getValues()[i], result_val_data_1[i], kfsoleq::tolerance) << "Poisson Equation CSR_Matrix's Values values doesn't match";
        EXPECT_EQ(result.getColumnIndexes()[i], result_col_data_1[i]) << "Poisson Equation CSR_Matrix's Column Indexes' values doesn't match";
    }
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(result.getRowIndexes()[i], result_row_data_1[i]) << "Poisson Equation CSR_Matrix's Row Indexes' values doesn't match";
    }
    
    
    size_y = 3;
    size_x = 2;
    kfsoleq::soleq_float result_val_data_2[20] = {  4, -1, -1,
                                                   -1,  4, -1,
                                                   -1,  4, -1, -1,
                                                   -1, -1,  4, -1,
                                                   -1,  4, -1,
                                                   -1, -1,  4 };
    size_t result_col_data_2[20] = { 0, 1, 2,
                                     0, 1, 3,
                                     0, 2, 3, 4,
                                     1, 2, 3, 5,
                                     2, 4, 5,
                                     3, 4, 5 };
    size_t result_row_data_2[7]  = { 0, 3, 6, 10, 14, 17, 20 };
    
    result = kfsoleq::generatorPoissonEquationMatrix(size_y, size_x);
    
    for (size_t i = 0; i < 20; ++i) {
        EXPECT_NEAR(result.getValues()[i], result_val_data_2[i], kfsoleq::tolerance) << "Poisson Equation CSR_Matrix's Values values doesn't match";
        EXPECT_EQ(result.getColumnIndexes()[i], result_col_data_2[i]) << "Poisson Equation CSR_Matrix's Column Indexes' values doesn't match";
    }
    for (size_t i = 0; i < 7; ++i) {
        EXPECT_EQ(result.getRowIndexes()[i], result_row_data_2[i]) << "Poisson Equation CSR_Matrix's Row Indexes' values doesn't match";
    }
}
