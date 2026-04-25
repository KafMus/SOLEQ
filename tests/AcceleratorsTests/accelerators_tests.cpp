#include <gtest/gtest.h>
#include <SOLEQ/accelerators.hpp>
#include <SOLEQ/DEFINES.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>
#include <SOLEQ/solvers.hpp>
#include <list>
#include <utility>


TEST(Accelerators, AcceleratorChebyshev) {
    size_t outer_iters_block_size = 8;
    size_t outer_max_iters = 8192;
    kfsoleq::CSR_Matrix my_csr_matrix;
    kfsoleq::soleq_float my_matrix_data_1[3][3] = { { 5, 1,  0 },
                                                    { 1, 4, -1 },
                                                    { 0, -1,  2 } };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_first_row = { std::make_pair(0,  5), std::make_pair(1, 1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>> lil_second_row = { std::make_pair(0,  1), std::make_pair(1, 4), std::make_pair(2, -1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_third_row = { std::make_pair(1, -1), std::make_pair(2, 2) };
    std::list<std::list<std::pair<size_t, kfsoleq::soleq_float>>> my_lil = { lil_first_row, lil_second_row, lil_third_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    kfsoleq::Vector constant_terms(3);
    kfsoleq::soleq_float const_terms_data_1[3] = { 44, 4, 32 };
    for (size_t i = 0; i < 3; ++i) {
        constant_terms[i] = const_terms_data_1[i];
    }
    
    
    kfsoleq::soleq_float spectral_radius = 0.5;
    kfsoleq::Vector roots = kfsoleq::acceleratorChebyshev<true>(kfsoleq::tolerance,
                                                                kfsoleq::Vector(3),
                                                                my_csr_matrix,
                                                                constant_terms,
                                                                spectral_radius,
                                                                outer_iters_block_size,
                                                                outer_max_iters,
                                                                nullptr,
                                                                kfsoleq::solverJacobiStep,
                                                                constant_terms.getSize());
    
    EXPECT_EQ(roots.getSize(), 3) << "Roots Size doesn't match";
    EXPECT_EQ(roots.getValues().size(), 3) << "Roots Values size doesn't match";
    EXPECT_EQ(roots.getValues().capacity(), 3) << "Roots Values capacity doesn't match";
    kfsoleq::soleq_float tmp;
    for (size_t i = 0; i < 3; ++i) {
        tmp = 0;
        for (size_t j = 0; j < 3; ++j) {
            tmp += my_matrix_data_1[i][j] * roots[j];
        }
        EXPECT_NEAR(tmp, const_terms_data_1[i], kfsoleq::tolerance) << "Roots Values doesn't match";
    }
    
    
    roots = kfsoleq::acceleratorChebyshev<false>(kfsoleq::tolerance,
                                                 kfsoleq::Vector(3),
                                                 my_csr_matrix,
                                                 constant_terms,
                                                 spectral_radius,
                                                 outer_iters_block_size,
                                                 outer_max_iters,
                                                 nullptr,
                                                 kfsoleq::solverGaussSeidelStep,
                                                 constant_terms.getSize());
    
    EXPECT_EQ(roots.getSize(), 3) << "Roots Size doesn't match";
    EXPECT_EQ(roots.getValues().size(), 3) << "Roots Values size doesn't match";
    EXPECT_EQ(roots.getValues().capacity(), 3) << "Roots Values capacity doesn't match";
    for (size_t i = 0; i < 3; ++i) {
        tmp = 0;
        for (size_t j = 0; j < 3; ++j) {
            tmp += my_matrix_data_1[i][j] * roots[j];
        }
        EXPECT_NEAR(tmp, const_terms_data_1[i], kfsoleq::tolerance) << "Roots Values doesn't match";
    }
    
    
    roots = kfsoleq::acceleratorChebyshev<false>(kfsoleq::tolerance,
                                                 kfsoleq::Vector(3),
                                                 my_csr_matrix,
                                                 constant_terms,
                                                 spectral_radius,
                                                 outer_iters_block_size,
                                                 outer_max_iters,
                                                 nullptr,
                                                 kfsoleq::solverFixedPointIterationStep,
                                                 0.27627629286944701919);
    
    EXPECT_EQ(roots.getSize(), 3) << "Roots Size doesn't match";
    EXPECT_EQ(roots.getValues().size(), 3) << "Roots Values size doesn't match";
    EXPECT_EQ(roots.getValues().capacity(), 3) << "Roots Values capacity doesn't match";
    for (size_t i = 0; i < 3; ++i) {
        tmp = 0;
        for (size_t j = 0; j < 3; ++j) {
            tmp += my_matrix_data_1[i][j] * roots[j];
        }
        EXPECT_NEAR(tmp, const_terms_data_1[i], kfsoleq::tolerance) << "Roots Values doesn't match";
    }
}
