#include <gtest/gtest.h>
#include <SOLEQ/linalg_operations.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>

TEST(LinalgOperationsMatrixVector, Multiplication) {
    size_t size_y[4] = { 0, 3, 3, 1 };
    size_t size_x[4] = { 0, 3, 5, 3 };
    kfsoleq::Matrix my_matrix;
    kfsoleq::Vector my_vector;
    kfsoleq::Vector result;
    kfsoleq::Matrix result_matrix;
    SOLEQ_FLOAT matrix_salt = 10000;
    SOLEQ_FLOAT vector_salt = 100;
    
    
    for (size_t i = 0; i < 3; ++i) {
        my_matrix = kfsoleq::Matrix(size_y[i], size_x[i]);
        my_vector = kfsoleq::Vector(size_x[i]);
        
        for (size_t j = 0; j < size_y[i]; ++j) {
            for (size_t z = 0; z < size_x[i]; ++z) {
                my_matrix(j, z) = matrix_salt * (SOLEQ_FLOAT)j + (SOLEQ_FLOAT)z;
            }
        }
        for (size_t j = 0; j < size_x[i]; ++j) {
            my_vector[j] = vector_salt * (SOLEQ_FLOAT)j;
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
            EXPECT_NEAR(result[0], 500, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Vector's Values values doesn't match";
            EXPECT_NEAR(result[1], 3000500, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Vector's Values values doesn't match";
            EXPECT_NEAR(result[2], 6000500, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Vector's Values values doesn't match";
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
            EXPECT_NEAR(result[0], 3000, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Vector's Values values doesn't match";
            EXPECT_NEAR(result[1], 10003000, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Vector's Values values doesn't match";
            EXPECT_NEAR(result[2], 20003000, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Vector's Values values doesn't match";
        }
    }
    for (size_t i = 3; i < 4; ++i) {
        my_matrix = kfsoleq::Matrix(size_y[i], size_x[i]);
        my_vector = kfsoleq::Vector(size_x[i]);
        
        for (size_t j = 0; j < size_y[i]; ++j) {
            for (size_t z = 0; z < size_x[i]; ++z) {
                my_matrix(j, z) = matrix_salt * (SOLEQ_FLOAT)j + (SOLEQ_FLOAT)z;
            }
        }
        for (size_t j = 0; j < size_x[i]; ++j) {
            my_vector[j] = vector_salt * (SOLEQ_FLOAT)j;
        }
        
        // Checking
        result_matrix = my_vector * my_matrix;
        
        /*  
         *  ||  0  || * || 0 1 2 || = || 0  0   0  ||
         *  || 100 ||                 || 0 100 200 ||
         *  || 200 ||                 || 0 200 400 ||
         */
        if (3 == i) {
            EXPECT_EQ(result_matrix.getSizeY(), 3) << "Multiplicated Matrix's Size Y doesn't match";
            EXPECT_EQ(result_matrix.getSizeX(), 3) << "Multiplicated Matrix's Size X doesn't match";
            EXPECT_EQ(result_matrix.getValues().size(), 9) << "Multiplicated Matrix's Values size doesn't match";
            EXPECT_EQ(result_matrix.getValues().capacity(), 9) << "Multiplicated Matrix's Values capacity doesn't match";
            EXPECT_NEAR(result_matrix(0, 0),   0, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Matrix's Values values doesn't match";
            EXPECT_NEAR(result_matrix(0, 1),   0, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Matrix's Values values doesn't match";
            EXPECT_NEAR(result_matrix(0, 2),   0, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Matrix's Values values doesn't match";
            EXPECT_NEAR(result_matrix(1, 0),   0, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Matrix's Values values doesn't match";
            EXPECT_NEAR(result_matrix(1, 1), 100, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Matrix's Values values doesn't match";
            EXPECT_NEAR(result_matrix(1, 2), 200, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Matrix's Values values doesn't match";
            EXPECT_NEAR(result_matrix(2, 0),   0, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Matrix's Values values doesn't match";
            EXPECT_NEAR(result_matrix(2, 1), 200, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Matrix's Values values doesn't match";
            EXPECT_NEAR(result_matrix(2, 2), 400, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Matrix's Values values doesn't match";
        }
    }
}

TEST(LinalgOperationsCSRMatrixVector, Multiplication) {
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
    std::list<std::pair<size_t, SOLEQ_FLOAT>>  lil_first_row = { std::make_pair(0, 1) };
    std::list<std::pair<size_t, SOLEQ_FLOAT>> lil_second_row = { std::make_pair(1, 2) };
    std::list<std::list<std::pair<size_t, SOLEQ_FLOAT>>> my_lil = { lil_first_row, lil_second_row };
    my_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    result = my_matrix * my_vector;
    EXPECT_EQ(result.getSize(), 2) << "Multiplicated Vector's size doesn't match";
    EXPECT_EQ(result.getValues().size(), 2) << "Multiplicated Vector's Values size doesn't match";
    EXPECT_EQ(result.getValues().capacity(), 2) << "Multiplicated Vector's Values capacity doesn't match";
    EXPECT_NEAR(result[0], 100, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Vector's Values values doesn't match";
    EXPECT_NEAR(result[1], 400, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Vector's Values values doesn't match";
    
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
    std::list<std::pair<size_t, SOLEQ_FLOAT>> lil_third_row{};
    lil_first_row =  { std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(3, 3) };
    lil_second_row = { std::make_pair(2, 4) };
    lil_third_row =  { std::make_pair(1, 1), std::make_pair(3, 11) };
    my_lil = { lil_first_row, lil_second_row, lil_third_row };
    my_matrix = kfsoleq::CSR_Matrix(my_lil);
    
    result = my_matrix * my_vector;
    EXPECT_EQ(result.getSize(), 3) << "Multiplicated Vector's size doesn't match";
    EXPECT_EQ(result.getValues().size(), 3) << "Multiplicated Vector's Values size doesn't match";
    EXPECT_EQ(result.getValues().capacity(), 3) << "Multiplicated Vector's Values capacity doesn't match";
    EXPECT_NEAR(result[0], 1700, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Vector's Values values doesn't match";
    EXPECT_NEAR(result[1], 1200, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Vector's Values values doesn't match";
    EXPECT_NEAR(result[2], 4600, SOLEQ_FLOAT_THRESHOLD) << "Multiplicated Vector's Values values doesn't match";
    
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
    
    kfsoleq::Matrix result_matrix = my_vector * my_matrix;
    EXPECT_EQ(result_matrix.getSizeY(), 3) << "Result Matrix's Size Y doesn't match";
    EXPECT_EQ(result_matrix.getSizeX(), 3) << "Result Matrix's Size X doesn't match";
    EXPECT_EQ(result_matrix.getValues().size(), 9) << "Result Matrix's Values size doesn't match";
    EXPECT_EQ(result_matrix.getValues().capacity(), 9) << "Result Matrix's Values capacity doesn't match";
    EXPECT_NEAR(result_matrix(0, 0), 3, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(0, 1), 0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(0, 2), 4, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(1, 0), 0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(1, 1), 0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(1, 2), 0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(2, 0), 6, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(2, 1), 0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(2, 2), 8, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    
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
    
    result_matrix = my_vector * my_matrix;
    result_matrix.print();
    EXPECT_EQ(result_matrix.getSizeY(), 5) << "Result Matrix's Size Y doesn't match";
    EXPECT_EQ(result_matrix.getSizeX(), 5) << "Result Matrix's Size X doesn't match";
    EXPECT_EQ(result_matrix.getValues().size(), 25) << "Result Matrix's Values size doesn't match";
    EXPECT_EQ(result_matrix.getValues().capacity(), 25) << "Result Matrix's Values capacity doesn't match";
    EXPECT_NEAR(result_matrix(0, 0),  9, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(0, 1),  0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(0, 2), 12, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(0, 3),  0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(0, 4), -6, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(1, 0),  9, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(1, 1),  0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(1, 2), 12, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(1, 3),  0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(1, 4), -6, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(2, 0),  6, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(2, 1),  0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(2, 2),  8, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(2, 3),  0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(2, 4), -4, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(3, 0), -3, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(3, 1),  0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(3, 2), -4, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(3, 3),  0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(3, 4),  2, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(4, 0),  0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(4, 1),  0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(4, 2),  0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(4, 3),  0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
    EXPECT_NEAR(result_matrix(4, 4),  0, SOLEQ_FLOAT_THRESHOLD) << "Result Matrix's Values values doesn't match";
}
