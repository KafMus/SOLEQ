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
    std::vector<SOLEQ_FLOAT> my_matrix_values;
    size_t size_y[6] = { 0, 3, 3,  5000,  1,     10000 };
    size_t size_x[6] = { 0, 3, 10, 10000, 10000, 1     };
    
    for (size_t i = 0; i < 6; ++i) {
        my_matrix = kfsoleq::Matrix(size_y[i], size_x[i]);
        EXPECT_EQ(my_matrix.getSizeY(), size_y[i]) << "Matrix's Y size doesn't match";
        EXPECT_EQ(my_matrix.getSizeX(), size_x[i]) << "Matrix's X size doesn't match";
        EXPECT_EQ(my_matrix.getValues().size(), size_y[i] * size_x[i]) << "Matrix's Values size doesn't match";
        EXPECT_EQ(my_matrix.getValues().capacity(), size_y[i] * size_x[i]) << "Matrix's Values capacity doesn't match";
        
        my_matrix_values = my_matrix.getValues();
        for (size_t j = 0; j < size_y[i]; ++j) {
            for (size_t z = 0; z < size_x[i]; ++z) {
                EXPECT_NEAR(my_matrix_values[j * size_x[i] + z], 0, SOLEQ_FLOAT_THRESHOLD) << "Matrix's Values values doesn't match";
            }
        }
    }
}

TEST(MatrixOperators, AccessOperator) {
    kfsoleq::Matrix my_matrix(10, 30);
    std::vector<SOLEQ_FLOAT> my_matrix_values;
    SOLEQ_FLOAT salt_num = 11037;
    
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 30; ++j) {
            my_matrix(i, j) = (salt_num * (SOLEQ_FLOAT)(i * j)) + (SOLEQ_FLOAT)i;
        }
    }
    
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 30; ++j) {
            EXPECT_NEAR(my_matrix(i, j), (salt_num * (SOLEQ_FLOAT)(i * j)) + (SOLEQ_FLOAT)i, SOLEQ_FLOAT_THRESHOLD) << "Matrix's Values values doesn't match";
        }
    }
    
    my_matrix_values = my_matrix.getValues();
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 30; ++j) {
            EXPECT_NEAR(my_matrix_values[i * 30 + j], (salt_num * (SOLEQ_FLOAT)(i * j)) + (SOLEQ_FLOAT)i, SOLEQ_FLOAT_THRESHOLD) << "Matrix's Values values doesn't match";
        }
    }
}
