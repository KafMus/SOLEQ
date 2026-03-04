#include <gtest/gtest.h>
#include <SOLEQ/vector.hpp>
#include <SOLEQ/DEFINES.hpp>
#include <cmath>
#include <vector>

TEST(VectorInitialization, DefaultInitialization) {
    kfsoleq::Vector void_vector{};
    EXPECT_EQ(void_vector.getSize(), 0) << "Vector's Size doesn't match";
    EXPECT_EQ(void_vector.getValues().size(), 0) << "Vector's Values size doesn't match";
    EXPECT_EQ(void_vector.getValues().capacity(), 0) << "Vector's Values capacity doesn't match";
}

TEST(VectorInitialisation, BySizeInitialisation) {
    kfsoleq::Vector my_vector;
    std::vector<SOLEQ_FLOAT> my_vector_values;
    size_t size[6] = { 0, 3, 5, 5000, 1, 10000 };
    
    for (size_t i = 0; i < 6; ++i) {
        my_vector = kfsoleq::Vector(size[i]);
        EXPECT_EQ(my_vector.getSize(), size[i]) << "Vector's Size doesn't match";
        EXPECT_EQ(my_vector.getValues().size(), size[i]) << "Vector's Values size doesn't match";
        EXPECT_EQ(my_vector.getValues().capacity(), size[i]) << "Vector's Values capacity doesn't match";
        
        my_vector_values = my_vector.getValues();
        for (size_t j = 0; j < size[i]; ++j) {
            EXPECT_NEAR(my_vector_values[j], 0, SOLEQ_FLOAT_THRESHOLD) << "Vector's Values values doesn't match";
        }
    }
}

TEST(VectorOperators, AccessOperator) {
    kfsoleq::Vector my_vector(10);
    std::vector<SOLEQ_FLOAT> my_vector_values;
    SOLEQ_FLOAT salt_num = 11037;
    
    for (size_t i = 0; i < 10; ++i) {
        my_vector[i] = (salt_num * (SOLEQ_FLOAT)i);
    }
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_NEAR(my_vector[i], (salt_num * (SOLEQ_FLOAT)i), SOLEQ_FLOAT_THRESHOLD) << "Vector's Values values doesn't match";
    }
    
    my_vector_values = my_vector.getValues();
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_NEAR(my_vector_values[i], (salt_num * (SOLEQ_FLOAT)i), SOLEQ_FLOAT_THRESHOLD) << "Vector's Values values doesn't match";
    }
}

TEST(VectorOperators, VectorSum) {
    const size_t iters = 4;
    const size_t size  = 5;
    kfsoleq::Vector  left_vector(size);
    kfsoleq::Vector right_vector(size);
    kfsoleq::Vector result_vector{};
    
    SOLEQ_FLOAT left_vector_data[iters][size]   = { { 3, 5, 7, 9, 11 },
                                                    { 3, 5, 7, 9, 11 },
                                                    { 1, 1, 1, 1,  1 },
                                                    { 3, 5, 7, 9, 11 } };

    SOLEQ_FLOAT right_vector_data[iters][size]  = { { 0, 0, 0, 0,  0 },
                                                    { 1, 1, 1, 1,  1 },
                                                    { 3, 5, 7, 9, 11 },
                                                    { 2, 4, 6, 8, 10 } };
    
    SOLEQ_FLOAT result_vector_data[iters][size] = { { 3, 5,  7,  9, 11 },
                                                    { 4, 6,  8, 10, 12 },
                                                    { 4, 6,  8, 10, 12 },
                                                    { 5, 9, 13, 17, 21 } };
    
    for (size_t i = 0; i < iters; ++i) {
        for (size_t j = 0; j < size; ++j) {
            left_vector[j]  =  left_vector_data[i][j];
            right_vector[j] = right_vector_data[i][j];
        }
        result_vector = left_vector + right_vector;
        for (size_t j = 0; j < size; ++j) {
            EXPECT_NEAR(result_vector[j],
                        result_vector_data[i][j],
                        SOLEQ_FLOAT_THRESHOLD) << "Result Vector's values doesn't match";
        }
    }
}

TEST(VectorOperators, VectorScalarMultiplication) {
    const size_t iters = 4;
    const size_t size  = 5;
    kfsoleq::Vector  left_vector(size);
    kfsoleq::Vector right_vector(size);
    SOLEQ_FLOAT result;
    
    SOLEQ_FLOAT left_vector_data[iters][size]   = { { 3, 5, 7, 9, 11 },
                                                    { 3, 5, 7, 9, 11 },
                                                    { 1, 1, 1, 1,  1 },
                                                    { 3, 5, 7, 9, 11 } };
    
    SOLEQ_FLOAT right_vector_data[iters][size]  = { { 0, 0, 0, 0,  0 },
                                                    { 1, 1, 1, 1,  1 },
                                                    { 3, 5, 7, 9, 11 },
                                                    { 2, 4, 6, 8, 10 } };
    
    SOLEQ_FLOAT result_data[iters] = { 0, 35, 35, 250 };
    
    for (size_t i = 0; i < iters; ++i) {
        for (size_t j = 0; j < size; ++j) {
            left_vector[j]  =  left_vector_data[i][j];
            right_vector[j] = right_vector_data[i][j];
        }
        result = left_vector * right_vector;
        EXPECT_NEAR(result,
                    result_data[i],
                    SOLEQ_FLOAT_THRESHOLD) << "Result value doesn't match";
    }
}

TEST(VectorOperators, ToScalarMultiplication) {
    const size_t iters = 4;
    const size_t size  = 5;
    kfsoleq::Vector  left_vector(size);
    SOLEQ_FLOAT right_value;
    kfsoleq::Vector result_vector(size);
    
    SOLEQ_FLOAT left_vector_data[iters][size]   = { { 3, 5, 7, 9, 11 },
                                                    { 3, 5, 7, 9, 11 },
                                                    { 3, 5, 7, 9, 11 },
                                                    { 3, 5, 7, 9, 11 } };
    
    SOLEQ_FLOAT right_value_data[iters]  = { 0, 1, 3, -1 };
    
    SOLEQ_FLOAT result_vector_data[iters][size] = { {  0,  0,  0,  0,   0 },
                                                    {  3,  5,  7,  9,  11 },
                                                    {  9, 15, 21, 27,  33 },
                                                    { -3, -5, -7, -9, -11 } };
    
    for (size_t i = 0; i < iters; ++i) {
        for (size_t j = 0; j < size; ++j) {
            left_vector[j] = left_vector_data[i][j];
        }
        right_value = right_value_data[i];
        
        result_vector = left_vector * right_value;
        for (size_t j = 0; j < size; ++j) {
            EXPECT_NEAR(result_vector[j],
                        result_vector_data[i][j],
                        SOLEQ_FLOAT_THRESHOLD) << "Result Vector's values doesn't match";
        }
    }
    for (size_t i = 0; i < iters; ++i) {
        for (size_t j = 0; j < size; ++j) {
            left_vector[j] = left_vector_data[i][j];
        }
        right_value = right_value_data[i];
        
        result_vector = right_value * left_vector;
        for (size_t j = 0; j < size; ++j) {
            EXPECT_NEAR(result_vector[j],
                        result_vector_data[i][j],
                        SOLEQ_FLOAT_THRESHOLD) << "Result Vector's values doesn't match";
        }
    }
}

TEST(VectorFunctions, GetNorm) {
    kfsoleq::Vector my_vector(3);
    
    my_vector[0] = 2;
    my_vector[1] = 2;
    my_vector[2] = 2;
    EXPECT_NEAR(my_vector.getNorm(), (SOLEQ_FLOAT)(2 * std::sqrt(3)), SOLEQ_FLOAT_THRESHOLD) << "Vector's getNorm() made a mistake";
    my_vector[0] = 0;
    my_vector[1] = 0;
    my_vector[2] = 0;
    EXPECT_NEAR(my_vector.getNorm(), (SOLEQ_FLOAT)0, SOLEQ_FLOAT_THRESHOLD) << "Vector's getNorm() made a mistake";
    my_vector[0] = 1;
    my_vector[1] = 10;
    my_vector[2] = 100;
    EXPECT_NEAR(my_vector.getNorm(), (SOLEQ_FLOAT)(std::sqrt(10101)), SOLEQ_FLOAT_THRESHOLD) << "Vector's getNorm() made a mistake";
    my_vector = kfsoleq::Vector(1);
    my_vector[0] = -42;
    EXPECT_NEAR(my_vector.getNorm(), 42, SOLEQ_FLOAT_THRESHOLD) << "Vector's getNorm() made a mistake";
    my_vector = kfsoleq::Vector(5);
    my_vector[0] = 1;
    my_vector[1] = 1;
    my_vector[2] = 1;
    my_vector[3] = 1;
    my_vector[4] = 1;
    EXPECT_NEAR(my_vector.getNorm(), (SOLEQ_FLOAT)(std::sqrt(5)), SOLEQ_FLOAT_THRESHOLD) << "Vector's getNorm() made a mistake";
}
