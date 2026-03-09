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
    EXPECT_EQ(my_matrix.getColumnIndexes()[0], 0) << "Matrix's Column Indexes values doesn't match";
    EXPECT_EQ(my_matrix.getColumnIndexes()[1], 1) << "Matrix's Column Indexes values doesn't match";
    EXPECT_EQ(my_matrix.getRowIndexes()[0], 0) << "Matrix's Row Indexes values doesn't match";
    EXPECT_EQ(my_matrix.getRowIndexes()[1], 1) << "Matrix's Row Indexes values doesn't match";
    EXPECT_EQ(my_matrix.getRowIndexes()[2], 2) << "Matrix's Row Indexes values doesn't match";
    
    
    std::list<std::pair<size_t, kfsoleq::soleq_float>> lil_third_row{};
    lil_first_row =  { std::make_pair(0, 1), std::make_pair(1, 2), std::make_pair(3, 3) };
    lil_second_row = { std::make_pair(2, 4) };
    lil_third_row =  { std::make_pair(1, 1), std::make_pair(3, 11) };
    my_lil = { lil_first_row, lil_second_row, lil_third_row };
    
    my_matrix = kfsoleq::CSR_Matrix(my_lil);
    EXPECT_NEAR(my_matrix.getValues()[0], 1, kfsoleq::tolerance) << "Matrix's Values values doesn't match";
    EXPECT_NEAR(my_matrix.getValues()[1], 2, kfsoleq::tolerance) << "Matrix's Values values doesn't match";
    EXPECT_NEAR(my_matrix.getValues()[2], 3, kfsoleq::tolerance) << "Matrix's Values values doesn't match";
    EXPECT_NEAR(my_matrix.getValues()[3], 4, kfsoleq::tolerance) << "Matrix's Values values doesn't match";
    EXPECT_NEAR(my_matrix.getValues()[4], 1, kfsoleq::tolerance) << "Matrix's Values values doesn't match";
    EXPECT_NEAR(my_matrix.getValues()[5], 11, kfsoleq::tolerance) << "Matrix's Values values doesn't match";
    EXPECT_EQ(my_matrix.getColumnIndexes()[0], 0) << "Matrix's Column Indexes values doesn't match";
    EXPECT_EQ(my_matrix.getColumnIndexes()[1], 1) << "Matrix's Column Indexes values doesn't match";
    EXPECT_EQ(my_matrix.getColumnIndexes()[2], 3) << "Matrix's Column Indexes values doesn't match";
    EXPECT_EQ(my_matrix.getColumnIndexes()[3], 2) << "Matrix's Column Indexes values doesn't match";
    EXPECT_EQ(my_matrix.getColumnIndexes()[4], 1) << "Matrix's Column Indexes values doesn't match";
    EXPECT_EQ(my_matrix.getColumnIndexes()[5], 3) << "Matrix's Column Indexes values doesn't match";
    EXPECT_EQ(my_matrix.getRowIndexes()[0], 0) << "Matrix's Row Indexes values doesn't match";
    EXPECT_EQ(my_matrix.getRowIndexes()[1], 3) << "Matrix's Row Indexes values doesn't match";
    EXPECT_EQ(my_matrix.getRowIndexes()[2], 4) << "Matrix's Row Indexes values doesn't match";
    EXPECT_EQ(my_matrix.getRowIndexes()[3], 6) << "Matrix's Row Indexes values doesn't match";
}
