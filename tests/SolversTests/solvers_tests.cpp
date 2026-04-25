#include <gtest/gtest.h>
#include <SOLEQ/solvers.hpp>
#include <SOLEQ/DEFINES.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>
#include <SOLEQ/utilities.hpp>
#include <list>
#include <utility>


TEST(Solvers, SolverQRFactorization) {
    kfsoleq::Matrix my_matrix(3, 4);
    kfsoleq::soleq_float my_matrix_data_1[3][4] = { { 12, -51,   4, 1 },
                                                    {  6, 167, -68, 2 },
                                                    { -4,  24, -41, 3 } };
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            my_matrix(i, j) = my_matrix_data_1[i][j];
        }
    }
    kfsoleq::Vector roots = kfsoleq::solverQRFactorization(my_matrix);
    
    EXPECT_EQ(roots.getSize(), 3) << "Roots Size doesn't match";
    EXPECT_EQ(roots.getValues().size(), 3) << "Roots Values size doesn't match";
    EXPECT_EQ(roots.getValues().capacity(), 3) << "Roots Values capacity doesn't match";
    kfsoleq::soleq_float tmp;
    for (size_t i = 0; i < 3; ++i) {
        tmp = 0;
        for (size_t j = 0; j < 3; ++j) {
            tmp += my_matrix_data_1[i][j] * roots[j];
        }
        EXPECT_NEAR(tmp, my_matrix_data_1[i][3], kfsoleq::tolerance) << "Roots Values doesn't match";
    }
    
    kfsoleq::Matrix cutted_my_matrix(3, 3);
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            cutted_my_matrix(i, j) = my_matrix_data_1[i][j];
        }
    }
    auto [Q_Matrix, R_Matrix] = getQRFactorizationHouseholder(cutted_my_matrix);
    roots = kfsoleq::solverQRFactorization(my_matrix, Q_Matrix, R_Matrix);
    
    EXPECT_EQ(roots.getSize(), 3) << "Roots Size doesn't match";
    EXPECT_EQ(roots.getValues().size(), 3) << "Roots Values size doesn't match";
    EXPECT_EQ(roots.getValues().capacity(), 3) << "Roots Values capacity doesn't match";
    for (size_t i = 0; i < 3; ++i) {
        tmp = 0;
        for (size_t j = 0; j < 3; ++j) {
            tmp += my_matrix_data_1[i][j] * roots[j];
        }
        EXPECT_NEAR(tmp, my_matrix_data_1[i][3], kfsoleq::tolerance) << "Roots Values doesn't match";
    }
    
    
    my_matrix = kfsoleq::Matrix(4, 4);
    kfsoleq::soleq_float my_matrix_data_2[4][4] = { {  1,  2,  3, 10 },
                                                    {  4,  5,  6, 20 },
                                                    {  7,  8,  9, 30 },
                                                    { 10, 11, 12, 40 } };
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            my_matrix(i, j) = my_matrix_data_2[i][j];
        }
    }
    roots = kfsoleq::solverQRFactorization(my_matrix);
    
    EXPECT_EQ(roots.getSize(), 4) << "Roots Size doesn't match";
    EXPECT_EQ(roots.getValues().size(), 4) << "Roots Values size doesn't match";
    EXPECT_EQ(roots.getValues().capacity(), 4) << "Roots Values capacity doesn't match";
    for (size_t i = 0; i < 4; ++i) {
        tmp = 0;
        for (size_t j = 0; j < 3; ++j) {
            tmp += my_matrix_data_2[i][j] * roots[j];
        }
        EXPECT_NEAR(tmp, my_matrix_data_2[i][3], kfsoleq::tolerance) << "Roots Values doesn't match";
    }
}

TEST(Solvers, SolverJacobi) {
    size_t iters_block_size = 16;
    size_t max_iters = 1000;
    kfsoleq::CSR_Matrix my_csr_matrix;
    kfsoleq::soleq_float my_matrix_data_1[3][3] = { { 5, 1,  0 },
                                                    { 0, 4, -1 },
                                                    { 1, 0,  2 } };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_first_row = { std::make_pair(0, 5), std::make_pair(1,  1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>> lil_second_row = { std::make_pair(1, 4), std::make_pair(2, -1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_third_row = { std::make_pair(0, 1), std::make_pair(2,  2) };
    std::list<std::list<std::pair<size_t, kfsoleq::soleq_float>>> my_lil = { lil_first_row, lil_second_row, lil_third_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    kfsoleq::Vector constant_terms(3);
    kfsoleq::soleq_float const_terms_data_1[3] = { 44, 4, 32 };
    for (size_t i = 0; i < 3; ++i) {
        constant_terms[i] = const_terms_data_1[i];
    }
    kfsoleq::Vector roots = kfsoleq::solverJacobi(kfsoleq::tolerance,
                                                  kfsoleq::Vector(3),
                                                  my_csr_matrix,
                                                  constant_terms,
                                                  iters_block_size,
                                                  max_iters);
    
    
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
    
    
    
    kfsoleq::soleq_float my_matrix_data_2[2][2] = { { 10,  4 },
                                                    {  2, -4 } };
    lil_first_row  = { std::make_pair(0, 10), std::make_pair(1, 4) };
    lil_second_row = { std::make_pair(0, 2), std::make_pair(1, -4) };
    my_lil = { lil_first_row, lil_second_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    constant_terms = kfsoleq::Vector(2);
    kfsoleq::soleq_float const_terms_data_2[2] = { 2, 10 };
    for (size_t i = 0; i < 2; ++i) {
        constant_terms[i] = const_terms_data_2[i];
    }
    roots = kfsoleq::solverJacobi(kfsoleq::tolerance,
                                  kfsoleq::Vector(2),
                                  my_csr_matrix,
                                  constant_terms,
                                  iters_block_size,
                                  max_iters);
    
    
    EXPECT_EQ(roots.getSize(), 2) << "Roots Size doesn't match";
    EXPECT_EQ(roots.getValues().size(), 2) << "Roots Values size doesn't match";
    EXPECT_EQ(roots.getValues().capacity(), 2) << "Roots Values capacity doesn't match";
    for (size_t i = 0; i < 2; ++i) {
        tmp = 0;
        for (size_t j = 0; j < 2; ++j) {
            tmp += my_matrix_data_2[i][j] * roots[j];
        }
        EXPECT_NEAR(tmp, const_terms_data_2[i], kfsoleq::tolerance) << "Roots Values doesn't match";
    }
}

TEST(Solvers, SolverFixedPointIteration) {
    size_t iters_block_size = 16;
    size_t max_iters = 1000;
    kfsoleq::CSR_Matrix my_csr_matrix;
    kfsoleq::soleq_float my_matrix_data_1[3][3] = { { 5, 1,  0 },
                                                    { 0, 4, -1 },
                                                    { 1, 0,  2 } };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_first_row = { std::make_pair(0, 5), std::make_pair(1,  1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>> lil_second_row = { std::make_pair(1, 4), std::make_pair(2, -1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_third_row = { std::make_pair(0, 1), std::make_pair(2,  2) };
    std::list<std::list<std::pair<size_t, kfsoleq::soleq_float>>> my_lil = { lil_first_row, lil_second_row, lil_third_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    kfsoleq::Vector constant_terms(3);
    kfsoleq::soleq_float const_terms_data_1[3] = { 44, 4, 32 };
    for (size_t i = 0; i < 3; ++i) {
        constant_terms[i] = const_terms_data_1[i];
    }
    kfsoleq::Vector roots = kfsoleq::solverFixedPointIteration(kfsoleq::tolerance,
                                                               my_csr_matrix,
                                                               constant_terms,
                                                               0.2,
                                                               iters_block_size,
                                                               max_iters);
    
    
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
    
    
    
    kfsoleq::soleq_float my_matrix_data_2[2][2] = { { 10, 4 },
                                                    {  2, 3 } };
    lil_first_row  = { std::make_pair(0, 10), std::make_pair(1, 4) };
    lil_second_row = { std::make_pair(0, 2),  std::make_pair(1, 3) };
    my_lil = { lil_first_row, lil_second_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    constant_terms = kfsoleq::Vector(2);
    kfsoleq::soleq_float const_terms_data_2[2] = { 2, 10 };
    for (size_t i = 0; i < 2; ++i) {
        constant_terms[i] = const_terms_data_2[i];
    }
    roots = kfsoleq::solverFixedPointIteration(kfsoleq::tolerance,
                                               my_csr_matrix,
                                               constant_terms,
                                               0.153846153846,
                                               iters_block_size,
                                               max_iters);
    
    
    EXPECT_EQ(roots.getSize(), 2) << "Roots Size doesn't match";
    EXPECT_EQ(roots.getValues().size(), 2) << "Roots Values size doesn't match";
    EXPECT_EQ(roots.getValues().capacity(), 2) << "Roots Values capacity doesn't match";
    for (size_t i = 0; i < 2; ++i) {
        tmp = 0;
        for (size_t j = 0; j < 2; ++j) {
            tmp += my_matrix_data_2[i][j] * roots[j];
        }
        EXPECT_NEAR(tmp, const_terms_data_2[i], kfsoleq::tolerance) << "Roots Values doesn't match";
    }
}

TEST(Solvers, SolverGaussSeidel) {
    size_t iters_block_size = 16;
    size_t max_iters = 1000;
    kfsoleq::CSR_Matrix my_csr_matrix;
    kfsoleq::soleq_float my_matrix_data_1[3][3] = { { 5, 1,  0 },
                                                    { 0, 4, -1 },
                                                    { 1, 0,  2 } };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_first_row = { std::make_pair(0, 5), std::make_pair(1,  1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>> lil_second_row = { std::make_pair(1, 4), std::make_pair(2, -1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_third_row = { std::make_pair(0, 1), std::make_pair(2,  2) };
    std::list<std::list<std::pair<size_t, kfsoleq::soleq_float>>> my_lil = { lil_first_row, lil_second_row, lil_third_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    kfsoleq::Vector constant_terms(3);
    kfsoleq::soleq_float const_terms_data_1[3] = { 44, 4, 32 };
    for (size_t i = 0; i < 3; ++i) {
        constant_terms[i] = const_terms_data_1[i];
    }
    kfsoleq::Vector roots = kfsoleq::solverGaussSeidel(kfsoleq::tolerance,
                                                       kfsoleq::Vector(3),
                                                       my_csr_matrix,
                                                       constant_terms,
                                                       iters_block_size,
                                                       max_iters);
    
    
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
    
    
    
    kfsoleq::soleq_float my_matrix_data_2[2][2] = { { 10, 4 },
                                                    {  2, 3 } };
    lil_first_row  = { std::make_pair(0, 10), std::make_pair(1, 4) };
    lil_second_row = { std::make_pair(0, 2),  std::make_pair(1, 3) };
    my_lil = { lil_first_row, lil_second_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    constant_terms = kfsoleq::Vector(2);
    kfsoleq::soleq_float const_terms_data_2[2] = { 2, 10 };
    for (size_t i = 0; i < 2; ++i) {
        constant_terms[i] = const_terms_data_2[i];
    }
    roots = kfsoleq::solverGaussSeidel(kfsoleq::tolerance,
                                       kfsoleq::Vector(2),
                                       my_csr_matrix,
                                       constant_terms,
                                       iters_block_size,
                                       max_iters);
    
    
    EXPECT_EQ(roots.getSize(), 2) << "Roots Size doesn't match";
    EXPECT_EQ(roots.getValues().size(), 2) << "Roots Values size doesn't match";
    EXPECT_EQ(roots.getValues().capacity(), 2) << "Roots Values capacity doesn't match";
    for (size_t i = 0; i < 2; ++i) {
        tmp = 0;
        for (size_t j = 0; j < 2; ++j) {
            tmp += my_matrix_data_2[i][j] * roots[j];
        }
        EXPECT_NEAR(tmp, const_terms_data_2[i], kfsoleq::tolerance) << "Roots Values doesn't match";
    }
}

TEST(Solvers, SolverSuccessiveOverRelaxation) {
    size_t iters_block_size = 16;
    size_t max_iters = 1000;
    kfsoleq::soleq_float relaxation_factor_1 = 1.02234044238634747812;
    kfsoleq::CSR_Matrix my_csr_matrix;
    kfsoleq::soleq_float my_matrix_data_1[3][3] = { { 5, 1,  0 },
                                                    { 0, 4, -1 },
                                                    { 1, 0,  2 } };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_first_row = { std::make_pair(0, 5), std::make_pair(1,  1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>> lil_second_row = { std::make_pair(1, 4), std::make_pair(2, -1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_third_row = { std::make_pair(0, 1), std::make_pair(2,  2) };
    std::list<std::list<std::pair<size_t, kfsoleq::soleq_float>>> my_lil = { lil_first_row, lil_second_row, lil_third_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    kfsoleq::Vector constant_terms(3);
    kfsoleq::soleq_float const_terms_data_1[3] = { 44, 4, 32 };
    for (size_t i = 0; i < 3; ++i) {
        constant_terms[i] = const_terms_data_1[i];
    }
    kfsoleq::Vector roots = kfsoleq::solverSuccessiveOverRelaxation(kfsoleq::tolerance,
                                                                    kfsoleq::Vector(3),
                                                                    my_csr_matrix,
                                                                    constant_terms,
                                                                    relaxation_factor_1,
                                                                    iters_block_size,
                                                                    max_iters);
    
    
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
    
    
    
    kfsoleq::soleq_float relaxation_factor_2 = 1.07738371066743548994;
    kfsoleq::soleq_float my_matrix_data_2[2][2] = { { 10, 4 },
                                                    {  2, 3 } };
    lil_first_row  = { std::make_pair(0, 10), std::make_pair(1, 4) };
    lil_second_row = { std::make_pair(0, 2),  std::make_pair(1, 3) };
    my_lil = { lil_first_row, lil_second_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    constant_terms = kfsoleq::Vector(2);
    kfsoleq::soleq_float const_terms_data_2[2] = { 2, 10 };
    for (size_t i = 0; i < 2; ++i) {
        constant_terms[i] = const_terms_data_2[i];
    }
    roots = kfsoleq::solverSuccessiveOverRelaxation(kfsoleq::tolerance,
                                                    kfsoleq::Vector(2),
                                                    my_csr_matrix,
                                                    constant_terms,
                                                    relaxation_factor_2,
                                                    iters_block_size,
                                                    max_iters);
    
    
    EXPECT_EQ(roots.getSize(), 2) << "Roots Size doesn't match";
    EXPECT_EQ(roots.getValues().size(), 2) << "Roots Values size doesn't match";
    EXPECT_EQ(roots.getValues().capacity(), 2) << "Roots Values capacity doesn't match";
    for (size_t i = 0; i < 2; ++i) {
        tmp = 0;
        for (size_t j = 0; j < 2; ++j) {
            tmp += my_matrix_data_2[i][j] * roots[j];
        }
        EXPECT_NEAR(tmp, const_terms_data_2[i], kfsoleq::tolerance) << "Roots Values doesn't match";
    }
}

TEST(Solvers, SolverChebyshevFixedPointIteration) {
    size_t max_iters = 1000;
    kfsoleq::CSR_Matrix my_csr_matrix;
    kfsoleq::soleq_float my_matrix_data_1[3][3] = { { 5, 1, 0 },
                                                    { 1, 4, 1 },
                                                    { 0, 1, 2 } };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_first_row = { std::make_pair(0, 5), std::make_pair(1, 1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>> lil_second_row = { std::make_pair(0, 1), std::make_pair(1, 4), std::make_pair(2, 1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_third_row = { std::make_pair(1, 1), std::make_pair(2, 2) };
    std::list<std::list<std::pair<size_t, kfsoleq::soleq_float>>> my_lil = { lil_first_row, lil_second_row, lil_third_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    kfsoleq::Vector constant_terms(3);
    kfsoleq::soleq_float const_terms_data_1[3] = { 44, 4, 32 };
    for (size_t i = 0; i < 3; ++i) {
        constant_terms[i] = const_terms_data_1[i];
    }
    kfsoleq::soleq_float min_eigen_value = 1.5395;
    kfsoleq::soleq_float max_eigen_value = 5.6996281;
    kfsoleq::Vector tau = kfsoleq::getTauFromChebyshevRoots(
                          kfsoleq::reorderChebyshevRoots(
                          kfsoleq::getChebyshevRoots(4)), min_eigen_value, max_eigen_value);
    kfsoleq::Vector roots = kfsoleq::solverChebyshevFixedPointIteration(kfsoleq::tolerance,
                                                                        kfsoleq::Vector(3),
                                                                        my_csr_matrix,
                                                                        constant_terms,
                                                                        tau,
                                                                        max_iters);
    
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
    
    
    roots = kfsoleq::Vector(42);
    roots = kfsoleq::solverChebyshevFixedPointIteration(kfsoleq::tolerance,
                                                        kfsoleq::Vector(3),
                                                        my_csr_matrix,
                                                        constant_terms,
                                                        min_eigen_value,
                                                        max_eigen_value,
                                                        4,
                                                        max_iters);
    
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

TEST(Solvers, SolverSteepestGradientDescent) {
    size_t iters_block_size = 16;
    size_t max_iters = 1000;
    kfsoleq::CSR_Matrix my_csr_matrix;
    kfsoleq::soleq_float my_matrix_data_1[3][3] = { { 5,  1,  0 },
                                                    { 1,  4, -1 },
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
    kfsoleq::Vector roots = kfsoleq::solverSteepestGradientDescent(kfsoleq::tolerance,
                                                                   kfsoleq::Vector(3),
                                                                   my_csr_matrix,
                                                                   constant_terms,
                                                                   iters_block_size,
                                                                   max_iters);
    
    
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
    
    
    
    kfsoleq::soleq_float my_matrix_data_2[2][2] = { { 10, 3 },
                                                    {  3, 7 } };
    lil_first_row  = { std::make_pair(0, 10), std::make_pair(1, 3) };
    lil_second_row = { std::make_pair(0, 3),  std::make_pair(1, 7) };
    my_lil = { lil_first_row, lil_second_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    constant_terms = kfsoleq::Vector(2);
    kfsoleq::soleq_float const_terms_data_2[2] = { 2, 10 };
    for (size_t i = 0; i < 2; ++i) {
        constant_terms[i] = const_terms_data_2[i];
    }
    roots = kfsoleq::solverSteepestGradientDescent(kfsoleq::tolerance,
                                                   kfsoleq::Vector(2),
                                                   my_csr_matrix,
                                                   constant_terms,
                                                   iters_block_size,
                                                   max_iters);
    
    
    EXPECT_EQ(roots.getSize(), 2) << "Roots Size doesn't match";
    EXPECT_EQ(roots.getValues().size(), 2) << "Roots Values size doesn't match";
    EXPECT_EQ(roots.getValues().capacity(), 2) << "Roots Values capacity doesn't match";
    for (size_t i = 0; i < 2; ++i) {
        tmp = 0;
        for (size_t j = 0; j < 2; ++j) {
            tmp += my_matrix_data_2[i][j] * roots[j];
        }
        EXPECT_NEAR(tmp, const_terms_data_2[i], kfsoleq::tolerance) << "Roots Values doesn't match";
    }
}

TEST(Solvers, SolverConjugateGradient) {
    size_t iters_block_size = 1;
    size_t max_iters = 1000;
    kfsoleq::CSR_Matrix my_csr_matrix;
    kfsoleq::soleq_float my_matrix_data_1[3][3] = { { 5,  1,  0 },
                                                    { 1,  4, -1 },
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
    kfsoleq::Vector roots = kfsoleq::solverConjugateGradient(kfsoleq::tolerance,
                                                             kfsoleq::Vector(3),
                                                             my_csr_matrix,
                                                             constant_terms,
                                                             iters_block_size,
                                                             max_iters);
    roots.print();
    
    
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
    
    
    
    kfsoleq::soleq_float my_matrix_data_2[2][2] = { { 10, 3 },
                                                    {  3, 7 } };
    lil_first_row  = { std::make_pair(0, 10), std::make_pair(1, 3) };
    lil_second_row = { std::make_pair(0, 3),  std::make_pair(1, 7) };
    my_lil = { lil_first_row, lil_second_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    constant_terms = kfsoleq::Vector(2);
    kfsoleq::soleq_float const_terms_data_2[2] = { 2, 10 };
    for (size_t i = 0; i < 2; ++i) {
        constant_terms[i] = const_terms_data_2[i];
    }
    roots = kfsoleq::solverConjugateGradient(kfsoleq::tolerance,
                                             kfsoleq::Vector(2),
                                             my_csr_matrix,
                                             constant_terms,
                                             iters_block_size,
                                             max_iters);
    roots.print();
    
    
    EXPECT_EQ(roots.getSize(), 2) << "Roots Size doesn't match";
    EXPECT_EQ(roots.getValues().size(), 2) << "Roots Values size doesn't match";
    EXPECT_EQ(roots.getValues().capacity(), 2) << "Roots Values capacity doesn't match";
    for (size_t i = 0; i < 2; ++i) {
        tmp = 0;
        for (size_t j = 0; j < 2; ++j) {
            tmp += my_matrix_data_2[i][j] * roots[j];
        }
        EXPECT_NEAR(tmp, const_terms_data_2[i], kfsoleq::tolerance) << "Roots Values doesn't match";
    }
}
