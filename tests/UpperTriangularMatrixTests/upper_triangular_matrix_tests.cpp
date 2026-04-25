#include <gtest/gtest.h>
#include <SOLEQ/upper_triangular_matrix.hpp>
#include <vector>

TEST(UpperTriangularMatrixInitialization, DefaultInitialization) {
    kfsoleq::UpperTriangularMatrix void_up_matrix{};
    EXPECT_EQ(void_up_matrix.getSizeY(), 0) << "UpperTriangularMatrix's Y size doesn't match";
    EXPECT_EQ(void_up_matrix.getSizeX(), 0) << "UpperTriangularMatrix's X size doesn't match";
    EXPECT_EQ(void_up_matrix.getValues().size(), 0) << "UpperTriangularMatrix's Values size doesn't match";
    EXPECT_EQ(void_up_matrix.getValues().capacity(), 0) << "UpperTriangularMatrix's Values capacity doesn't match";
    void_up_matrix.print();
}

TEST(UpperTriangularMatrixInitialisation, SizeBySizeInitialisation) {
    kfsoleq::UpperTriangularMatrix my_up_matrix;
    std::vector<kfsoleq::soleq_float> my_up_matrix_values;
    size_t size_y[6] = { 0, 3, 10, 100, 100, 100 };
    size_t size_x[6] = { 0, 3,  3,  50,   1,  10 };
    size_t result_up_matrix_values_size[6] = { 0, 6, 6, 1275, 1, 55 };
    
    for (size_t i = 0; i < 6; ++i) {
        my_up_matrix = kfsoleq::UpperTriangularMatrix(size_y[i], size_x[i]);
        EXPECT_EQ(my_up_matrix.getSizeY(), size_y[i]) << "UpperTriangularMatrix's Y size doesn't match";
        EXPECT_EQ(my_up_matrix.getSizeX(), size_x[i]) << "UpperTriangularMatrix's X size doesn't match";
        EXPECT_EQ(my_up_matrix.getValues().size(), result_up_matrix_values_size[i]) << "UpperTriangularMatrix's Values size doesn't match";
        EXPECT_EQ(my_up_matrix.getValues().capacity(), result_up_matrix_values_size[i]) << "UpperTriangularMatrix's Values capacity doesn't match";
        
        my_up_matrix_values = my_up_matrix.getValues();
        for (size_t j = 0; j < size_y[i]; ++j) {
            for (size_t z = 0; z < size_x[i]; ++z) {
                if (z >= j) {
                    EXPECT_NEAR(my_up_matrix_values[(((2 * size_x[i] - j + 1) * j) / 2) + z - j], 0, kfsoleq::tolerance) << "UpperTriangularMatrix's Values values doesn't match";
                }
            }
        }
    }
}

TEST(UpperTriangularMatrixOperators, AccessOperator) {
    kfsoleq::UpperTriangularMatrix my_up_matrix(10, 5);
    kfsoleq::soleq_float result_up_matrix_data[15] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    size_t result_up_matrix_data_y[15]             = { 0, 0, 0, 0, 0, 1, 1, 1, 1,  2,  2,  2,  3,  3,  4 };
    size_t result_up_matrix_data_x[15]             = { 0, 1, 2, 3, 4, 1, 2, 3, 4,  2,  3,  4,  3,  4,  4 };
    
    size_t k = 0;
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            if (j >= i) {
                my_up_matrix(i, j) = result_up_matrix_data[k];
                ++k;
            }
        }
    }
    
    for (size_t i = 0; i < 15; ++i) {
        EXPECT_NEAR(my_up_matrix(result_up_matrix_data_y[i], result_up_matrix_data_x[i]),
                    result_up_matrix_data[i], kfsoleq::tolerance) << "UpperTriangularMatrix's Values values doesn't match";
    }
}
