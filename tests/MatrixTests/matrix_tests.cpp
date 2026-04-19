#include <gtest/gtest.h>
#include <SOLEQ/matrix.hpp>
#include <vector>

TEST(MatrixInitialization, DefaultInitialization) {
    kfsoleq::Matrix void_matrix{};
    EXPECT_EQ(void_matrix.getSizeY(), 0) << "Matrix's Y size doesn't match";
    EXPECT_EQ(void_matrix.getSizeX(), 0) << "Matrix's X size doesn't match";
    EXPECT_EQ(void_matrix.getValues().size(), 0) << "Matrix's Values size doesn't match";
    EXPECT_EQ(void_matrix.getValues().capacity(), 0) << "Matrix's Values capacity doesn't match";
}

TEST(MatrixInitialisation, SizeBySizeInitialisation) {
    kfsoleq::Matrix my_matrix;
    std::vector<kfsoleq::soleq_float> my_matrix_values;
    size_t size_y[6] = { 0, 3, 3,  50,  1,   100 };
    size_t size_x[6] = { 0, 3, 10, 100, 100,   1 };
    
    for (size_t i = 0; i < 6; ++i) {
        my_matrix = kfsoleq::Matrix(size_y[i], size_x[i]);
        EXPECT_EQ(my_matrix.getSizeY(), size_y[i]) << "Matrix's Y size doesn't match";
        EXPECT_EQ(my_matrix.getSizeX(), size_x[i]) << "Matrix's X size doesn't match";
        EXPECT_EQ(my_matrix.getValues().size(), size_y[i] * size_x[i]) << "Matrix's Values size doesn't match";
        EXPECT_EQ(my_matrix.getValues().capacity(), size_y[i] * size_x[i]) << "Matrix's Values capacity doesn't match";
        
        my_matrix_values = my_matrix.getValues();
        for (size_t j = 0; j < size_y[i]; ++j) {
            for (size_t z = 0; z < size_x[i]; ++z) {
                EXPECT_NEAR(my_matrix_values[j * size_x[i] + z], 0, kfsoleq::tolerance) << "Matrix's Values values doesn't match";
            }
        }
    }
}

TEST(MatrixFunctions, GetTransposed) {
    kfsoleq::Matrix my_matrix(3, 3);
    kfsoleq::soleq_float my_matrix_data_1[3][3] = { { 1, 2, 3 },
                                                    { 4, 5, 6 },
                                                    { 7, 8, 9 } };
    kfsoleq::soleq_float result_data_1[3][3]    = { { 1, 4, 7 },
                                                    { 2, 5, 8 },
                                                    { 3, 6, 9 } };
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            my_matrix(i, j) = my_matrix_data_1[i][j];
        }
    }
    kfsoleq::Matrix result = my_matrix.getTransposed();
    EXPECT_EQ(result.getSizeY(), 3) << "Matrix's Y size doesn't match";
    EXPECT_EQ(result.getSizeX(), 3) << "Matrix's X size doesn't match";
    EXPECT_EQ(result.getValues().size(), 9) << "Matrix's Values size doesn't match";
    EXPECT_EQ(result.getValues().capacity(), 9) << "Matrix's Values capacity doesn't match";
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_NEAR(result(i, j), result_data_1[i][j], kfsoleq::tolerance) << "Matrix's Values values doesn't match";
        }
    }
    
    my_matrix = kfsoleq::Matrix(2, 6);
    kfsoleq::soleq_float my_matrix_data_2[2][6] = { { 1, 2, 3,  4,  5,  6, },
                                                    { 7, 8, 9, 10, 11, 12 } };
    kfsoleq::soleq_float result_data_2[6][2]    = { { 1,  7 },
                                                    { 2,  8 },
                                                    { 3,  9 },
                                                    { 4, 10 },
                                                    { 5, 11 },
                                                    { 6, 12 } };
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 6; ++j) {
            my_matrix(i, j) = my_matrix_data_2[i][j];
        }
    }
    result = my_matrix.getTransposed();
    EXPECT_EQ(result.getSizeY(), 6) << "Matrix's Y size doesn't match";
    EXPECT_EQ(result.getSizeX(), 2) << "Matrix's X size doesn't match";
    EXPECT_EQ(result.getValues().size(), 12) << "Matrix's Values size doesn't match";
    EXPECT_EQ(result.getValues().capacity(), 12) << "Matrix's Values capacity doesn't match";
    for (size_t i = 0; i < 6; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            EXPECT_NEAR(result(i, j), result_data_2[i][j], kfsoleq::tolerance) << "Matrix's Values values doesn't match";
        }
    }
}

TEST(MatrixOperators, AccessOperator) {
    kfsoleq::Matrix my_matrix(10, 30);
    std::vector<kfsoleq::soleq_float> my_matrix_values;
    kfsoleq::soleq_float salt_num = 11037;
    
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 30; ++j) {
            my_matrix(i, j) = (salt_num * (kfsoleq::soleq_float)(i * j)) + (kfsoleq::soleq_float)i;
        }
    }
    
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 30; ++j) {
            EXPECT_NEAR(my_matrix(i, j), (salt_num * (kfsoleq::soleq_float)(i * j)) + (kfsoleq::soleq_float)i, kfsoleq::tolerance) << "Matrix's Values values doesn't match";
        }
    }
    
    my_matrix_values = my_matrix.getValues();
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 30; ++j) {
            EXPECT_NEAR(my_matrix_values[i * 30 + j], (salt_num * (kfsoleq::soleq_float)(i * j)) + (kfsoleq::soleq_float)i, kfsoleq::tolerance) << "Matrix's Values values doesn't match";
        }
    }
}

TEST(MatrixOperators, MatrixSum) {
    kfsoleq::Matrix  left_matrix(3, 3);
    kfsoleq::Matrix right_matrix(3, 3);
    
    
    kfsoleq::soleq_float  left_data[3][3] =  { { 1, 1, 1 },
                                               { 1, 0, 1 },
                                               { 1, 1, 1 } };
    kfsoleq::soleq_float right_data[3][3] =  { { 3, 4, 5 },
                                               { 4, 5, 6 },
                                               { 5, 6, 7 } };
    kfsoleq::soleq_float result_data[3][3] = { { 4, 5, 6 },
                                               { 5, 5, 7 },
                                               { 6, 7, 8 } };
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            left_matrix(i, j)   = left_data[i][j];
            right_matrix(i, j)  = right_data[i][j];
        }
    }
    kfsoleq::Matrix result_matrix = left_matrix + right_matrix;
    
    EXPECT_EQ(result_matrix.getSizeY(), 3) << "Matrix's Y size doesn't match";
    EXPECT_EQ(result_matrix.getSizeX(), 3) << "Matrix's X size doesn't match";
    EXPECT_EQ(result_matrix.getValues().size(), 9) << "Matrix's Values size doesn't match";
    EXPECT_EQ(result_matrix.getValues().capacity(), 9) << "Matrix's Values capacity doesn't match";
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_NEAR(result_matrix(i, j), result_data[i][j], kfsoleq::tolerance) << "Matrix's values doesn't match";
        }
    }
}

TEST(MatrixOperators, MatrixSubtraction) {
    kfsoleq::Matrix  left_matrix(3, 3);
    kfsoleq::Matrix right_matrix(3, 3);
    
    
    kfsoleq::soleq_float  left_data[3][3] =  { { 3, 4, 5 },
                                               { 4, 5, 6 },
                                               { 5, 6, 7 } };
    kfsoleq::soleq_float right_data[3][3] =  { { 1, 1, 1 },
                                               { 1, 0, 1 },
                                               { 1, 1, 1 } };
    kfsoleq::soleq_float result_data[3][3] = { { 2, 3, 4 },
                                               { 3, 5, 5 },
                                               { 4, 5, 6 } };
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            left_matrix(i, j)   = left_data[i][j];
            right_matrix(i, j)  = right_data[i][j];
        }
    }
    kfsoleq::Matrix result_matrix = left_matrix - right_matrix;
    
    EXPECT_EQ(result_matrix.getSizeY(), 3) << "Matrix's Y size doesn't match";
    EXPECT_EQ(result_matrix.getSizeX(), 3) << "Matrix's X size doesn't match";
    EXPECT_EQ(result_matrix.getValues().size(), 9) << "Matrix's Values size doesn't match";
    EXPECT_EQ(result_matrix.getValues().capacity(), 9) << "Matrix's Values capacity doesn't match";
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_NEAR(result_matrix(i, j), result_data[i][j], kfsoleq::tolerance) << "Matrix's values doesn't match";
        }
    }
}

TEST(MatrixOperators, ToMatrixMultiplicationOperator) {
    kfsoleq::Matrix  left_matrix(3, 3);
    kfsoleq::Matrix right_matrix(3, 3);
    
    
    kfsoleq::soleq_float  left_data[3][3] =  { { 1, 1, 1 },
                                               { 1, 0, 1 },
                                               { 1, 1, 1 } };
    kfsoleq::soleq_float right_data[3][3] =  { { 3, 4, 5 },
                                               { 4, 5, 6 },
                                               { 5, 6, 7 } };
    kfsoleq::soleq_float result_data[3][3] = { { 12, 15, 18 },
                                               {  8, 10, 12 },
                                               { 12, 15, 18 } };
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            left_matrix(i, j)   = left_data[i][j];
            right_matrix(i, j)  = right_data[i][j];
        }
    }
    kfsoleq::Matrix result_matrix = left_matrix * right_matrix;
    
    EXPECT_EQ(result_matrix.getSizeY(), 3) << "Matrix's Y size doesn't match";
    EXPECT_EQ(result_matrix.getSizeX(), 3) << "Matrix's X size doesn't match";
    EXPECT_EQ(result_matrix.getValues().size(), 9) << "Matrix's Values size doesn't match";
    EXPECT_EQ(result_matrix.getValues().capacity(), 9) << "Matrix's Values capacity doesn't match";
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            EXPECT_NEAR(result_matrix(i, j), result_data[i][j], kfsoleq::tolerance) << "Matrix's values doesn't match";
        }
    }
}
