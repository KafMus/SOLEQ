#include <gtest/gtest.h>
#include <SOLEQ/utilities.hpp>
#include <SOLEQ/DEFINES.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>
#include <cmath>
#include <list>
#include <numbers>
#include <utility>


TEST(Utilities, GetCSRMatrixFromMatrix) {
    kfsoleq::Matrix my_matrix(5, 4);
    kfsoleq::soleq_float my_matrix_data[5][4] = { { 1, 2, 3, 4 },
                                                  { 5, 0, 0, 0 },
                                                  { 0, 0, 0, 0 },
                                                  { 0, 0, 0, 6 },
                                                  { 0, 7, 8, 9 } };
    kfsoleq::soleq_float result_val_data[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    size_t result_col_data[9] = { 0, 1, 2, 3, 0, 3, 1, 2, 3 };
    size_t result_row_data[6] = { 0, 4, 5, 5, 6, 9 };
    
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            my_matrix(i, j) = my_matrix_data[i][j];
        }
    }
    
    kfsoleq::CSR_Matrix result = kfsoleq::getCSRMatrixFromMatrix(my_matrix, 0);
    result.print();
    
    for (size_t i = 0; i < 9; ++i) {
        EXPECT_NEAR(result.getValues()[i], result_val_data[i], kfsoleq::tolerance) << "CSR_Matrix's Values values doesn't match";
        EXPECT_EQ(result.getColumnIndexes()[i], result_col_data[i]) << "CSR_Matrix's Column Indexes' values doesn't match";
    }
    for (size_t i = 0; i < 6; ++i) {
        EXPECT_EQ(result.getRowIndexes()[i], result_row_data[i]) << "CSR_Matrix's Row Indexes' values doesn't match";
    }
}

TEST(Utilities, GetMatrixFromCSRMatrix) {
    kfsoleq::soleq_float result_val_data[5][4] = { { 1, 2, 3, 4 },
                                                   { 5, 0, 0, 0 },
                                                   { 0, 0, 0, 0 },
                                                   { 0, 0, 0, 6 },
                                                   { 0, 7, 8, 9 } };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_first_row  = { std::make_pair(0, 1),
                                                                           std::make_pair(1, 2),
                                                                           std::make_pair(2, 3),
                                                                           std::make_pair(3, 4) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_second_row = { std::make_pair(0, 5) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_third_row  = { /* -------------- */ };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_fourth_row = { std::make_pair(3, 6) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_fifth_row  = { std::make_pair(1, 7),
                                                                           std::make_pair(2, 8),
                                                                           std::make_pair(3, 9) };
    std::list<std::list<std::pair<size_t, kfsoleq::soleq_float>>> my_lil = { lil_first_row,
                                                                             lil_second_row,
                                                                             lil_third_row,
                                                                             lil_fourth_row,
                                                                             lil_fifth_row  };
    kfsoleq::CSR_Matrix my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    kfsoleq::Matrix result = kfsoleq::getMatrixFromCSRMatrix(my_csr_matrix, 4);
    result.print();
    
    EXPECT_EQ(result.getSizeY(), 5) << "Result Matrix's Size Y doesn't match";
    EXPECT_EQ(result.getSizeX(), 4) << "Result Matrix's Size X doesn't match";
    EXPECT_EQ(result.getValues().size(), 20) << "Result Matrix's Values size doesn't match";
    EXPECT_EQ(result.getValues().capacity(), 20) << "Result Matrix's Values capacity doesn't match";
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            EXPECT_NEAR(result(i, j), result_val_data[i][j], kfsoleq::tolerance) << "Result Matrix's Values values doesn't match";
        }
    }
}

TEST(Utilities, GetMaxEigenValuePowerMethod) {
    size_t iters_num = 100;
    kfsoleq::CSR_Matrix my_csr_matrix;
    
    /*
     *  || 5 1 0 ||
     *  || 1 4 1 ||
     *  || 0 1 2 ||
     *  max_eigen_value \approx 5.6996281
     */
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_first_row = { std::make_pair(0, 5), std::make_pair(1, 1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>> lil_second_row = { std::make_pair(0, 1), std::make_pair(1, 4), std::make_pair(2, 1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_third_row = { std::make_pair(1, 1), std::make_pair(2, 2) };
    std::list<std::list<std::pair<size_t, kfsoleq::soleq_float>>> my_lil = { lil_first_row, lil_second_row, lil_third_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    kfsoleq::Vector initial_vector(3);
    for (size_t i = 0; i < 3; ++i) {
        initial_vector[i] = 1;
    }
    
    kfsoleq::soleq_float max_eigen_value = getMaxEigenValuePowerMethod(initial_vector,
                                                                       my_csr_matrix,
                                                                       iters_num);
    EXPECT_NEAR(max_eigen_value, 5.6996281, kfsoleq::tolerance) << "Max Eigen Value of CSR_Matrix doesn't match";
    
    /*
     *  || 10 1 ||
     *  || 1 40 ||
     *  max_eigen_value = 25 + sqrt(226)
     */
    lil_first_row  = { std::make_pair(0, 10), std::make_pair(1, 1) };
    lil_second_row = { std::make_pair(0, 1), std::make_pair(1, 40) };
    my_lil = { lil_first_row, lil_second_row };
    my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    max_eigen_value = getMaxEigenValuePowerMethod(initial_vector,
                                                  my_csr_matrix,
                                                  iters_num);
    EXPECT_NEAR(max_eigen_value, 25 + std::sqrt(226), kfsoleq::tolerance) << "Max Eigen Value of CSR_Matrix doesn't match";
}

TEST(Utilities, GetChebyshevRoots) {
    kfsoleq::soleq_float roots_data_1[2] = { 1.0f / std::sqrt(2), -1.0f / std::sqrt(2) };
    kfsoleq::soleq_float roots_data_2[5] = { std::sqrt(std::sqrt(5) + 5) / (2 * std::sqrt(2)),
                                             std::sqrt(5 - std::sqrt(5)) / (2 * std::sqrt(2)),
                                             0,
                                            -std::sqrt(5 - std::sqrt(5)) / (2 * std::sqrt(2)),
                                            -std::sqrt(std::sqrt(5) + 5) / (2 * std::sqrt(2)) };
    kfsoleq::soleq_float roots_data_3[6] = { std::cos(std::numbers::pi_v<kfsoleq::soleq_float> / 12),
                                             1.0f / std::sqrt(2),
                                             std::cos(5 * std::numbers::pi_v<kfsoleq::soleq_float> / 12),
                                            -std::cos(5 * std::numbers::pi_v<kfsoleq::soleq_float> / 12),
                                            -1.0f / std::sqrt(2),
                                            -std::cos(std::numbers::pi_v<kfsoleq::soleq_float> / 12) };
    
    kfsoleq::Vector roots = kfsoleq::getChebyshevRoots(2);
    for (size_t i = 0; i < 2; ++i) {
        EXPECT_NEAR(roots[i], roots_data_1[i], kfsoleq::tolerance) << "Chebyshev roots didn't match";
    }
    roots = kfsoleq::getChebyshevRoots(5);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_NEAR(roots[i], roots_data_2[i], kfsoleq::tolerance) << "Chebyshev roots didn't match";
    }
    roots = kfsoleq::getChebyshevRoots(6);
    for (size_t i = 0; i < 6; ++i) {
        EXPECT_NEAR(roots[i], roots_data_3[i], kfsoleq::tolerance) << "Chebyshev roots didn't match";
    }
}

TEST(Utilities, ReorderChebyshevRoots) {
    kfsoleq::soleq_float roots_data_1[2] = { 1.0f / std::sqrt(2), -1.0f / std::sqrt(2) };
    kfsoleq::soleq_float roots_data_2[4] = { std::sqrt((std::sqrt(2) + 1) / std::sqrt(8)),
                                            -std::sqrt((std::sqrt(2) + 1) / std::sqrt(8)),
                                             std::sqrt((std::sqrt(2) - 1) / std::sqrt(8)),
                                            -std::sqrt((std::sqrt(2) - 1) / std::sqrt(8)) };
    kfsoleq::Vector roots = kfsoleq::reorderChebyshevRoots(kfsoleq::getChebyshevRoots(2));
    for (size_t i = 0; i < 2; ++i) {
        EXPECT_NEAR(roots[i], roots_data_1[i], kfsoleq::tolerance) << "Reordered Chebyshev roots didn't match";
    }
    roots = kfsoleq::reorderChebyshevRoots(kfsoleq::getChebyshevRoots(4));
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_NEAR(roots[i], roots_data_2[i], kfsoleq::tolerance) << "Reordered Chebyshev roots didn't match";
    }
}

TEST(Utilities, GetTauFromChebyshevRoots) {
    kfsoleq::soleq_float tau_data[4] = { 0.180463, 0.588985, 0.226471, 0.354163 };
    
    kfsoleq::Vector roots = kfsoleq::reorderChebyshevRoots(kfsoleq::getChebyshevRoots(4));
    kfsoleq::Vector tau = kfsoleq::getTauFromChebyshevRoots(roots, 1.5395, 5.6996281);
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_NEAR(tau[i], tau_data[i], kfsoleq::tolerance) << "Tau from Reordered Chebyshev roots didn't match";
    }
}

TEST(Utilities, GetNewChebyshevAccelerationParameter) {
    kfsoleq::soleq_float spectral_radius = 1.1;
    kfsoleq::soleq_float mu_0 = 1;
    kfsoleq::soleq_float mu_1 = 1.0 / spectral_radius;
    kfsoleq::soleq_float mu_2 = kfsoleq::getNewChebyshevAccelerationParameter(spectral_radius, mu_0, mu_1);
    kfsoleq::soleq_float mu_3 = kfsoleq::getNewChebyshevAccelerationParameter(spectral_radius, mu_1, mu_2);
    
    EXPECT_NEAR(mu_2, 0.65289256, kfsoleq::tolerance) << "New Chebyshev Acceleration Parametr didn't match";
    EXPECT_NEAR(mu_3, 0.27798648, kfsoleq::tolerance) << "New Chebyshev Acceleration Parametr didn't match";
}

TEST(Utilities, GetQRFactorizationHouseholder) {
    kfsoleq::Matrix Q_Matrix, R_Matrix;
    kfsoleq::Matrix my_matrix(3, 3);
    kfsoleq::soleq_float my_matrix_data_1[3][3] = { { 12, -51,   4 },
                                                    {  6, 167, -68 },
                                                    { -4,  24, -41 } };
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            my_matrix(i, j) = my_matrix_data_1[i][j];
        }
    }
    std::pair<kfsoleq::Matrix, kfsoleq::Matrix> result = kfsoleq::getQRFactorizationHouseholder(my_matrix);
    Q_Matrix = result.first;
    R_Matrix = result.second;
    
    EXPECT_EQ(Q_Matrix.getSizeY(), 3) << "Q Matrix's Size Y doesn't match";
    EXPECT_EQ(Q_Matrix.getSizeX(), 3) << "Q Matrix's Size X doesn't match";
    EXPECT_EQ(Q_Matrix.getValues().size(), 9) << "Q Matrix's Values size doesn't match";
    EXPECT_EQ(Q_Matrix.getValues().capacity(), 9) << "Q Matrix's Values capacity doesn't match";
    EXPECT_EQ(R_Matrix.getSizeY(), 3) << "R Matrix's Size Y doesn't match";
    EXPECT_EQ(R_Matrix.getSizeX(), 3) << "R Matrix's Size X doesn't match";
    EXPECT_EQ(R_Matrix.getValues().size(), 9) << "R Matrix's Values size doesn't match";
    EXPECT_EQ(R_Matrix.getValues().capacity(), 9) << "R Matrix's Values capacity doesn't match";
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < i; ++j) {
            EXPECT_NEAR(R_Matrix(i, j), 0, kfsoleq::tolerance) << "R Matrix's Values values doesn't match";
        }
    }
    
    kfsoleq::Matrix tmp = Q_Matrix.getTransposed() * Q_Matrix;
    EXPECT_EQ(tmp.getSizeY(), 3) << "Q^T * Q Matrix's Size Y doesn't match";
    EXPECT_EQ(tmp.getSizeX(), 3) << "Q^T * Q Matrix's Size X doesn't match";
    EXPECT_EQ(tmp.getValues().size(), 9) << "Q^T * Q Matrix's Values size doesn't match";
    EXPECT_EQ(tmp.getValues().capacity(), 9) << "Q^T * Q Matrix's Values capacity doesn't match";
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_NEAR(tmp(i, i), 1, kfsoleq::tolerance) << "Q^T * Q Matrix's Values values doesn't match";
    }
    
    tmp = Q_Matrix * R_Matrix;
    EXPECT_EQ(tmp.getSizeY(), 3) << "Q * R Matrix's Size Y doesn't match";
    EXPECT_EQ(tmp.getSizeX(), 3) << "Q * R Matrix's Size X doesn't match";
    EXPECT_EQ(tmp.getValues().size(), 9) << "Q * R Matrix's Values size doesn't match";
    EXPECT_EQ(tmp.getValues().capacity(), 9) << "Q * R Matrix's Values capacity doesn't match";
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_NEAR(tmp(i, j),  my_matrix_data_1[i][j], kfsoleq::tolerance) << "Q * R Matrix's Values values doesn't match";
        }
    }
    
    
    my_matrix = kfsoleq::Matrix(5, 3);
    kfsoleq::soleq_float my_matrix_data_2[5][3] = { {  1,  1,  0 },
                                                    {  1,  0,  1 },
                                                    {  0,  1,  1 },
                                                    {  1,  1,  1 },
                                                    {  1,  1,  1 } };
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            my_matrix(i, j) = my_matrix_data_2[i][j];
        }
    }
    result = kfsoleq::getQRFactorizationHouseholder(my_matrix);
    Q_Matrix = result.first;
    R_Matrix = result.second;
    
    EXPECT_EQ(Q_Matrix.getSizeY(), 5) << "Q Matrix's Size Y doesn't match";
    EXPECT_EQ(Q_Matrix.getSizeX(), 5) << "Q Matrix's Size X doesn't match";
    EXPECT_EQ(Q_Matrix.getValues().size(), 25) << "Q Matrix's Values size doesn't match";
    EXPECT_EQ(Q_Matrix.getValues().capacity(), 25) << "Q Matrix's Values capacity doesn't match";
    EXPECT_EQ(R_Matrix.getSizeY(), 5) << "R Matrix's Size Y doesn't match";
    EXPECT_EQ(R_Matrix.getSizeX(), 3) << "R Matrix's Size X doesn't match";
    EXPECT_EQ(R_Matrix.getValues().size(), 15) << "R Matrix's Values size doesn't match";
    EXPECT_EQ(R_Matrix.getValues().capacity(), 15) << "R Matrix's Values capacity doesn't match";
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 3 && j < i; ++j) {
            EXPECT_NEAR(R_Matrix(i, j), 0, kfsoleq::tolerance) << "R Matrix's Values values doesn't match";
        }
    }
    
    tmp = Q_Matrix.getTransposed() * Q_Matrix;
    EXPECT_EQ(tmp.getSizeY(), 5) << "Q^T * Q Matrix's Size Y doesn't match";
    EXPECT_EQ(tmp.getSizeX(), 5) << "Q^T * Q Matrix's Size X doesn't match";
    EXPECT_EQ(tmp.getValues().size(), 25) << "Q^T * Q Matrix's Values size doesn't match";
    EXPECT_EQ(tmp.getValues().capacity(), 25) << "Q^T * Q Matrix's Values capacity doesn't match";
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_NEAR(tmp(i, i), 1, kfsoleq::tolerance) << "Q^T * Q Matrix's Values values doesn't match";
    }
    
    tmp = Q_Matrix * R_Matrix;
    EXPECT_EQ(tmp.getSizeY(), 5) << "Q * R Matrix's Size Y doesn't match";
    EXPECT_EQ(tmp.getSizeX(), 3) << "Q * R Matrix's Size X doesn't match";
    EXPECT_EQ(tmp.getValues().size(), 15) << "Q * R Matrix's Values size doesn't match";
    EXPECT_EQ(tmp.getValues().capacity(), 15) << "Q * R Matrix's Values capacity doesn't match";
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_NEAR(tmp(i, j),  my_matrix_data_2[i][j], kfsoleq::tolerance) << "Q * R Matrix's Values values doesn't match";
        }
    }
}
