#include <gtest/gtest.h>
#include <SOLEQ/linalg_operations.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>


TEST(LinalgOperations, MatrixVectorMultiplication) {
    size_t size_y[4] = { 0, 3, 3, 1 };
    size_t size_x[4] = { 0, 3, 5, 3 };
    kfsoleq::Matrix my_matrix;
    kfsoleq::Vector my_vector;
    kfsoleq::Vector result;
    kfsoleq::Matrix result_matrix;
    kfsoleq::soleq_float matrix_salt = 10000;
    kfsoleq::soleq_float vector_salt = 100;
    
    
    for (size_t i = 0; i < 3; ++i) {
        my_matrix = kfsoleq::Matrix(size_y[i], size_x[i]);
        my_vector = kfsoleq::Vector(size_x[i]);
        
        for (size_t j = 0; j < size_y[i]; ++j) {
            for (size_t z = 0; z < size_x[i]; ++z) {
                my_matrix(j, z) = matrix_salt * (kfsoleq::soleq_float)j + (kfsoleq::soleq_float)z;
            }
        }
        for (size_t j = 0; j < size_x[i]; ++j) {
            my_vector[j] = vector_salt * (kfsoleq::soleq_float)j;
        }
        
        // Checking
        result = my_matrix * my_vector;

        /* blank Matrix by blank Vector multiplication */
        if (0 == i) {
            EXPECT_EQ(result.getSize(), 0) << "Multiplicated Vector's size doesn't match";
            EXPECT_EQ(result.getValues().size(), 0) << "Multiplicated Vector's Values size doesn't match";
            EXPECT_EQ(result.getValues().capacity(), 0) << "Multiplicated Vector's Values capacity doesn't match";
        }
        /*  
         *  ||   0     1     2   || * ||  0  || = ||   500   ||
         *  || 10000 10001 10002 ||   || 100 ||   || 3000500 ||
         *  || 20000 20001 20002 ||   || 200 ||   || 6000500 ||
         */
        else if (1 == i) {
            EXPECT_EQ(result.getSize(), 3) << "Multiplicated Vector's size doesn't match";
            EXPECT_EQ(result.getValues().size(), 3) << "Multiplicated Vector's Values size doesn't match";
            EXPECT_EQ(result.getValues().capacity(), 3) << "Multiplicated Vector's Values capacity doesn't match";
            EXPECT_NEAR(result[0], 500, kfsoleq::tolerance) << "Multiplicated Vector's Values values doesn't match";
            EXPECT_NEAR(result[1], 3000500, kfsoleq::tolerance) << "Multiplicated Vector's Values values doesn't match";
            EXPECT_NEAR(result[2], 6000500, kfsoleq::tolerance) << "Multiplicated Vector's Values values doesn't match";
        }
        /*  
         *  ||   0     1     2     3     4   || * ||  0  || = ||   3000   ||
         *  || 10000 10001 10002 10003 10004 ||   || 100 ||   || 10003000 ||
         *  || 20000 20001 20002 20003 20004 ||   || 200 ||   || 20003000 ||
         *                                        || 300 ||
         *                                        || 400 ||
         */
        else if (2 == i) {
            EXPECT_EQ(result.getSize(), 3) << "Multiplicated Vector's size doesn't match";
            EXPECT_EQ(result.getValues().size(), 3) << "Multiplicated Vector's Values size doesn't match";
            EXPECT_EQ(result.getValues().capacity(), 3) << "Multiplicated Vector's Values capacity doesn't match";
            EXPECT_NEAR(result[0], 3000, kfsoleq::tolerance) << "Multiplicated Vector's Values values doesn't match";
            EXPECT_NEAR(result[1], 10003000, kfsoleq::tolerance) << "Multiplicated Vector's Values values doesn't match";
            EXPECT_NEAR(result[2], 20003000, kfsoleq::tolerance) << "Multiplicated Vector's Values values doesn't match";
        }
    }
    for (size_t i = 3; i < 4; ++i) {
        my_matrix = kfsoleq::Matrix(size_y[i], size_x[i]);
        my_vector = kfsoleq::Vector(size_x[i]);
        
        for (size_t j = 0; j < size_y[i]; ++j) {
            for (size_t z = 0; z < size_x[i]; ++z) {
                my_matrix(j, z) = matrix_salt * (kfsoleq::soleq_float)j + (kfsoleq::soleq_float)z;
            }
        }
        for (size_t j = 0; j < size_x[i]; ++j) {
            my_vector[j] = vector_salt * (kfsoleq::soleq_float)j;
        }
        
        // Checking
        result_matrix = my_vector * my_matrix;
        
        /*  
         *  ||  0  || * || 0 1 2 || = || 0  0   0  ||
         *  || 100 ||                 || 0 100 200 ||
         *  || 200 ||                 || 0 200 400 ||
         */
        kfsoleq::soleq_float result_data[3][3] = { { 0,   0,   0 },
                                                   { 0, 100, 200 },
                                                   { 0, 200, 400 } };
        if (3 == i) {
            EXPECT_EQ(result_matrix.getSizeY(), 3) << "Multiplicated Matrix's Size Y doesn't match";
            EXPECT_EQ(result_matrix.getSizeX(), 3) << "Multiplicated Matrix's Size X doesn't match";
            EXPECT_EQ(result_matrix.getValues().size(), 9) << "Multiplicated Matrix's Values size doesn't match";
            EXPECT_EQ(result_matrix.getValues().capacity(), 9) << "Multiplicated Matrix's Values capacity doesn't match";
            for (size_t j = 0; j < 3; ++j) {
                for (size_t z = 0; z < 3; ++z) {
                    EXPECT_NEAR(result_matrix(j, z), result_data[j][z], kfsoleq::tolerance) << "Multiplicated Matrix's Values values doesn't match";
                }
            }
        }
    }
}

TEST(LinalgOperations, CSRMatrixVectorMultiplication) {
    kfsoleq::CSR_Matrix my_matrix{};
    kfsoleq::Vector my_vector{};
    kfsoleq::Vector result;
    
    
    /* blank CSR_Matrix by blank Vector */
    result = my_matrix * my_vector;
    EXPECT_EQ(result.getSize(), 0) << "Multiplicated Vector's size doesn't match";
    EXPECT_EQ(result.getValues().size(), 0) << "Multiplicated Vector's Values size doesn't match";
    EXPECT_EQ(result.getValues().capacity(), 0) << "Multiplicated Vector's Values capacity doesn't match";
    
    /*  
     *  || 1 0 || * || 100 || = || 100 ||
     *  || 0 2 ||   || 200 ||   || 400 ||
     */
    my_vector = kfsoleq::Vector(2);
    my_vector[0] = 100;
    my_vector[1] = 200;
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_first_row = { std::make_pair(0, 1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>> lil_second_row = { std::make_pair(1, 2) };
    std::list<std::list<std::pair<size_t, kfsoleq::soleq_float>>> my_lil = { lil_first_row, lil_second_row };
    my_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    result = my_matrix * my_vector;
    EXPECT_EQ(result.getSize(), 2) << "Multiplicated Vector's size doesn't match";
    EXPECT_EQ(result.getValues().size(), 2) << "Multiplicated Vector's Values size doesn't match";
    EXPECT_EQ(result.getValues().capacity(), 2) << "Multiplicated Vector's Values capacity doesn't match";
    EXPECT_NEAR(result[0], 100, kfsoleq::tolerance) << "Multiplicated Vector's Values values doesn't match";
    EXPECT_NEAR(result[1], 400, kfsoleq::tolerance) << "Multiplicated Vector's Values values doesn't match";
    
    /*  
     *  || 1 2 0 3  || * || 100 || = || 1700 ||
     *  || 0 0 4 0  ||   || 200 ||   || 1200 ||
     *  || 0 1 0 11 ||   || 300 ||   || 4600 ||
     *                   || 400 ||
     */
    my_vector = kfsoleq::Vector(4);
    my_vector[0] = 100;
    my_vector[1] = 200;
    my_vector[2] = 300;
    my_vector[3] = 400;
    std::list<std::pair<size_t, kfsoleq::soleq_float>> lil_third_row{};
    lil_first_row =  { std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(3, 3) };
    lil_second_row = { std::make_pair(2, 4) };
    lil_third_row =  { std::make_pair(1, 1), std::make_pair(3, 11) };
    my_lil = { lil_first_row, lil_second_row, lil_third_row };
    my_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    result = my_matrix * my_vector;
    EXPECT_EQ(result.getSize(), 3) << "Multiplicated Vector's size doesn't match";
    EXPECT_EQ(result.getValues().size(), 3) << "Multiplicated Vector's Values size doesn't match";
    EXPECT_EQ(result.getValues().capacity(), 3) << "Multiplicated Vector's Values capacity doesn't match";
    EXPECT_NEAR(result[0], 1700, kfsoleq::tolerance) << "Multiplicated Vector's Values values doesn't match";
    EXPECT_NEAR(result[1], 1200, kfsoleq::tolerance) << "Multiplicated Vector's Values values doesn't match";
    EXPECT_NEAR(result[2], 4600, kfsoleq::tolerance) << "Multiplicated Vector's Values values doesn't match";
    
    /*  
     *  || 1 || * || 3 0 4 || = || 3 0 4 ||
     *  || 0 ||                 || 0 0 0 ||
     *  || 2 ||                 || 6 0 8 ||
     */
    my_vector = kfsoleq::Vector(3);
    my_vector[0] = 1;
    my_vector[1] = 0;
    my_vector[2] = 2;
    lil_first_row =  { std::make_pair(0, 3), std::make_pair(2, 4) };
    my_lil = { lil_first_row };
    my_matrix = kfsoleq::CSR_Matrix(my_lil);
    kfsoleq::soleq_float result_data_1[3][3] = { { 3, 0, 4 },
                                                 { 0, 0, 0 },
                                                 { 6, 0, 8 } };
    
    kfsoleq::Matrix result_matrix = my_vector * my_matrix;
    EXPECT_EQ(result_matrix.getSizeY(), 3) << "Result Matrix's Size Y doesn't match";
    EXPECT_EQ(result_matrix.getSizeX(), 3) << "Result Matrix's Size X doesn't match";
    EXPECT_EQ(result_matrix.getValues().size(), 9) << "Result Matrix's Values size doesn't match";
    EXPECT_EQ(result_matrix.getValues().capacity(), 9) << "Result Matrix's Values capacity doesn't match";
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_NEAR(result_matrix(i, j), result_data_1[i][j], kfsoleq::tolerance) << "Result Matrix's Values values doesn't match";
        }
    }
    
    /*  
     *  ||  3 || * || 3 0 4 0 -2 || = ||  9 0 12 0 -6 ||
     *  ||  3 ||                      ||  9 0 12 0 -6 ||
     *  ||  2 ||                      ||  6 0  8 0 -4 ||
     *  || -1 ||                      || -3 0 -4 0  2 ||
     *  ||  0 ||                      ||  0 0  0 0  0 ||
     */
    my_vector = kfsoleq::Vector(5);
    my_vector[0] =  3;
    my_vector[1] =  3;
    my_vector[2] =  2;
    my_vector[3] = -1;
    my_vector[4] =  0;
    lil_first_row =  { std::make_pair(0, 3), std::make_pair(2, 4), std::make_pair(4, -2) };
    my_lil = { lil_first_row };
    my_matrix = kfsoleq::CSR_Matrix(my_lil);
    kfsoleq::soleq_float result_data_2[5][5] = { {  9, 0, 12, 0, -6 },
                                                 {  9, 0, 12, 0, -6 },
                                                 {  6, 0,  8, 0, -4 },
                                                 { -3, 0, -4, 0,  2 },
                                                 {  0, 0,  0, 0,  0 } };
    
    result_matrix = my_vector * my_matrix;
    EXPECT_EQ(result_matrix.getSizeY(), 5) << "Result Matrix's Size Y doesn't match";
    EXPECT_EQ(result_matrix.getSizeX(), 5) << "Result Matrix's Size X doesn't match";
    EXPECT_EQ(result_matrix.getValues().size(), 25) << "Result Matrix's Values size doesn't match";
    EXPECT_EQ(result_matrix.getValues().capacity(), 25) << "Result Matrix's Values capacity doesn't match";
    
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            EXPECT_NEAR(result_matrix(i, j), result_data_2[i][j], kfsoleq::tolerance) << "Result Matrix's Values values doesn't match";
        }
    }
}

TEST(LinalgOperationsSideFunctions, GetMaxEigenValuePowerMethod) {
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

TEST(LinalgOperationsSideFunctions, GetChebyshevRoots) {
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

TEST(LinalgOperationsSideFunctions, ReorderChebyshevRoots) {
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

TEST(LinalgOperationsSideFunctions, GetTauFromChebyshevRoots) {
    kfsoleq::soleq_float tau_data[4] = { 0.180463, 0.588985, 0.226471, 0.354163 };
    
    kfsoleq::Vector roots = kfsoleq::reorderChebyshevRoots(kfsoleq::getChebyshevRoots(4));
    kfsoleq::Vector tau = kfsoleq::getTauFromChebyshevRoots(roots, 1.5395, 5.6996281);
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_NEAR(tau[i], tau_data[i], kfsoleq::tolerance) << "Tau from Reordered Chebyshev roots didn't match";
    }
}

TEST(LinalgOperations, GetQRDecompositionHouseholder) {
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
    std::pair<kfsoleq::Matrix, kfsoleq::Matrix> result = kfsoleq::getQRDecompositionHouseholder(my_matrix);
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
    result = kfsoleq::getQRDecompositionHouseholder(my_matrix);
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

TEST(LinalgOperationsSolvers, SolverQRDecomposition) {
    kfsoleq::Matrix my_matrix(3, 4);
    kfsoleq::soleq_float my_matrix_data_1[3][4] = { { 12, -51,   4, 1 },
                                                    {  6, 167, -68, 2 },
                                                    { -4,  24, -41, 3 } };
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            my_matrix(i, j) = my_matrix_data_1[i][j];
        }
    }
    kfsoleq::Vector roots = kfsoleq::solverQRDecomposition(my_matrix);
    
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
    auto [Q_Matrix, R_Matrix] = getQRDecompositionHouseholder(cutted_my_matrix);
    roots = kfsoleq::solverQRDecomposition(my_matrix, Q_Matrix, R_Matrix);
    
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
    roots = kfsoleq::solverQRDecomposition(my_matrix);
    
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

TEST(LinalgOperationsSolvers, SolverJacobi) {
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

TEST(LinalgOperationsSolvers, SolverFixedPointIteration) {
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
                                                               kfsoleq::Vector(3),
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
                                               kfsoleq::Vector(2),
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

TEST(LinalgOperationsSolvers, SolverGaussSeidel) {
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



TEST(LinalgOperationsSolvers, SolverChebyshevFixedPointIteration) {
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
