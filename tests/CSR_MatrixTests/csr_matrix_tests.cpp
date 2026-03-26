#include <gtest/gtest.h>
#include <SOLEQ/csr_matrix.hpp>
#include <list>
#include <utility>

TEST(CSRMatrixInitialization, DefaultInitialization) {
    kfsoleq::CSR_Matrix void_matrix{};
    EXPECT_EQ(void_matrix.getValues().size(), 0) << "Matrix's Values size doesn't match";
    EXPECT_EQ(void_matrix.getValues().capacity(), 0) << "Matrix's Values capacity doesn't match";
    EXPECT_EQ(void_matrix.getColumnIndexes().size(), 0) << "Matrix's Column Indexes size doesn't match";
    EXPECT_EQ(void_matrix.getColumnIndexes().capacity(), 0) << "Matrix's Column Indexes capacity doesn't match";
    EXPECT_EQ(void_matrix.getRowIndexes().size(), 0) << "Matrix's Row Indexes size doesn't match";
    EXPECT_EQ(void_matrix.getRowIndexes().capacity(), 0) << "Matrix's Row Indexes capacity doesn't match";
}

TEST(CSRMatrixInitialisation, LILInitialisation) {
    std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_first_row = { std::make_pair(0, 1) };
    std::list<std::pair<size_t, kfsoleq::soleq_float>> lil_second_row = { std::make_pair(1, 2) };
    std::list<std::list<std::pair<size_t, kfsoleq::soleq_float>>> my_lil = { lil_first_row, lil_second_row };
    
    kfsoleq::CSR_Matrix my_matrix(my_lil);
    EXPECT_NEAR(my_matrix.getValues()[0], 1, kfsoleq::tolerance) << "Matrix's Values values doesn't match";
    EXPECT_NEAR(my_matrix.getValues()[1], 2, kfsoleq::tolerance) << "Matrix's Values values doesn't match";
    for (size_t i = 0; i < 2; ++i) {
        EXPECT_EQ(my_matrix.getColumnIndexes()[i], i) << "Matrix's Column Indexes values doesn't match";
    }
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(my_matrix.getRowIndexes()[i], i) << "Matrix's Row Indexes values doesn't match";
    }
    
    
    std::list<std::pair<size_t, kfsoleq::soleq_float>> lil_third_row{};
    lil_first_row =  { std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(3, 3) };
    lil_second_row = { std::make_pair(2, 4) };
    lil_third_row =  { std::make_pair(1, 1), std::make_pair(3, 11) };
    my_lil = { lil_first_row, lil_second_row, lil_third_row };
    kfsoleq::soleq_float val_data[6] = { 1, 2, 3, 4, 1, 11 };
    kfsoleq::soleq_float col_data[6] = { 0, 1, 3, 2, 1,  3 };
    kfsoleq::soleq_float row_data[4] = { 0, 3, 4, 6 };
    
    my_matrix = kfsoleq::CSR_Matrix(my_lil);
    for (size_t i = 0; i < 6; ++i) {
        EXPECT_NEAR(my_matrix.getValues()[i], val_data[i], kfsoleq::tolerance) << "Matrix's Values values doesn't match";
    }
    for (size_t i = 0; i < 6; ++i) {
        EXPECT_EQ(my_matrix.getColumnIndexes()[i], col_data[i]) << "Matrix's Column Indexes values doesn't match";
    }
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(my_matrix.getRowIndexes()[i], row_data[i]) << "Matrix's Row Indexes values doesn't match";
    }
}
