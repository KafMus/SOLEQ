#include <gtest/gtest.h>
#include <SOLEQ/diagthree.hpp>
#include <SOLEQ/DEFINES.hpp>
#include <array>
#include <vector>

TEST(DiagThreeInitialization, DefaultInitialization) {
    kfsoleq::DiagThree void_diagthree{};
    EXPECT_EQ(void_diagthree.getSize(), 0) << "DiagThree's Size doesn't match";
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(void_diagthree.getDiagonals()[i].size(), 0) << "DiagThree's Diagonals[" << i << "] size doesn't match";
        EXPECT_EQ(void_diagthree.getDiagonals()[i].capacity(), 0) << "DiagThree's Diagonals[" << i << "] capacity doesn't match";
    }
    EXPECT_EQ(void_diagthree.getConstantTerms().size(), 0) << "DiagThree's ConstantTerms size doesn't match";
    EXPECT_EQ(void_diagthree.getConstantTerms().capacity(), 0) << "DiagThree's ConstantTerms capacity doesn't match";
    EXPECT_EQ(void_diagthree.getRoots().size(), 0) << "DiagThree's Roots size doesn't match";
    EXPECT_EQ(void_diagthree.getRoots().capacity(), 0) << "DiagThree's Roots capacity doesn't match";
}

TEST(DiagThreeInitialization, FullInitialization) {
    
    size_t max_size = 5;
    kfsoleq::soleq_float diag_salt  = 100;
    kfsoleq::soleq_float cons_salt = 10000;
    kfsoleq::DiagThree my_diagthree{};
    
    
    for (size_t size = 3; size < max_size; ++size) {
        // Constructing DiagThree
        std::array<std::vector<kfsoleq::soleq_float>, 3> diagonals;
        std::vector<kfsoleq::soleq_float> constant_terms;
        
        for (size_t i = 0; i < 3; ++i) {
            diagonals[i] = std::vector<kfsoleq::soleq_float>(size);
            for (size_t j = 0; j < size; ++j) {
                diagonals[i][j] = (kfsoleq::soleq_float)i * diag_salt + (kfsoleq::soleq_float)j;
            }
        }
        constant_terms = std::vector<kfsoleq::soleq_float>(size);
        for (size_t i = 0; i < size; ++i) {
            constant_terms[i] = cons_salt + (kfsoleq::soleq_float)i;
        }
        my_diagthree = kfsoleq::DiagThree(size, diagonals, constant_terms);
        
        // Checking DiagThree
        EXPECT_EQ(my_diagthree.getSize(), size) << "DiagThree's Size doesn't match";
        for (size_t i = 0; i < 3; ++i) {
            EXPECT_EQ(my_diagthree.getDiagonals()[i].size(), size) << "DiagThree's Diagonals[" << i << "] size doesn't match";
            EXPECT_EQ(my_diagthree.getDiagonals()[i].capacity(), size) << "DiagThree's Diagonals[" << i << "] capacity doesn't match";
        }
        EXPECT_EQ(my_diagthree.getConstantTerms().size(), size) << "DiagThree's ConstantTerms size doesn't match";
        EXPECT_EQ(my_diagthree.getConstantTerms().capacity(), size) << "DiagThree's ConstantTerms capacity doesn't match";
        EXPECT_EQ(my_diagthree.getRoots().size(), size) << "DiagThree's Roots size doesn't match";
        EXPECT_EQ(my_diagthree.getRoots().capacity(), size) << "DiagThree's Roots capacity doesn't match";
        
        for (size_t i = 0; i < size; ++i) {
            EXPECT_NEAR(my_diagthree.getDiagonals()[0][i], (kfsoleq::soleq_float)i, kfsoleq::tolerance) << "DiagThree's Diagonals[0] values doesn't match";
            EXPECT_NEAR(my_diagthree.getDiagonals()[1][i], diag_salt + (kfsoleq::soleq_float)i, kfsoleq::tolerance) << "DiagThree's Diagonals[1] values doesn't match";
            EXPECT_NEAR(my_diagthree.getDiagonals()[2][i], 2 * diag_salt + (kfsoleq::soleq_float)i, kfsoleq::tolerance) << "DiagThree's Diagonals[2] values doesn't match";
            EXPECT_NEAR(my_diagthree.getConstantTerms()[i], cons_salt + (kfsoleq::soleq_float)i, kfsoleq::tolerance) << "DiagThree's ConstantTerms values doesn't match";
            EXPECT_NEAR(my_diagthree.getRoots()[i], 0, kfsoleq::tolerance) << "DiagThree's Roots values doesn't match";
        }
    }
}

TEST(DiagThreeFunctions, Solver) {
    
    size_t size = 5;
    kfsoleq::DiagThree my_diagthree{};
    
    std::array<std::vector<kfsoleq::soleq_float>, 3> diagonals;
    std::vector<kfsoleq::soleq_float> constant_terms;
    
    /*
     *  || 3 2 0 0 0  || * || x1 || = || 5 ||
     *  || 1 5 2 0 0  ||   || x2 ||   || 5 ||
     *  || 0 1 7 2 0  ||   || x3 ||   || 5 ||
     *  || 0 0 1 9 2  ||   || x4 ||   || 5 ||
     *  || 0 0 0 1 11 ||   || x5 ||   || 5 ||
     *
     *  || x1 || = ( 1.3148637, 0.5277045, 0.5233069, 0.4045734, 0.4177661 )^T
     *  || x2 ||
     *  || x3 ||
     *  || x4 ||
     *  || x5 ||
     */
    diagonals[0] =   { 0, 1, 1, 1, 1  };
    diagonals[1] =   { 3, 5, 7, 9, 11 };
    diagonals[2] =   { 2, 2, 2, 2, 0  };
    constant_terms = { 5, 5, 5, 5, 5  };
    kfsoleq::soleq_float roots_data[5] = { 1.3148637, 0.5277045, 0.5233069, 0.4045734, 0.4177661 };
    
    my_diagthree = kfsoleq::DiagThree(size, diagonals, constant_terms);
    my_diagthree.solve();
    
    // Checking DiagThree
    EXPECT_EQ(my_diagthree.getRoots().size(), size) << "DiagThree's Roots size doesn't match";
    EXPECT_EQ(my_diagthree.getRoots().capacity(), size) << "DiagThree's Roots capacity doesn't match";
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_NEAR(my_diagthree.getRoots()[i], roots_data[i], kfsoleq::tolerance) << "DiagThree's Roots values doesn't match";
    }
}

TEST(DiagThreeFunctions, CheckDiagonalDomination) {
    
    size_t size = 5;
    kfsoleq::DiagThree my_diagthree{};
    
    std::array<std::vector<kfsoleq::soleq_float>, 3> diagonals;
    std::vector<kfsoleq::soleq_float> constant_terms;
    
    /*
     *  || 3 2 0 0 0  ||
     *  || 1 5 2 0 0  ||
     *  || 0 1 7 2 0  ||
     *  || 0 0 1 9 2  ||
     *  || 0 0 0 1 11 ||
     */
    diagonals[0] =   { 0, 1, 1, 1, 1  };
    diagonals[1] =   { 3, 5, 7, 9, 11 };
    diagonals[2] =   { 2, 2, 2, 2, 0  };
    constant_terms = { 1, 1, 1, 1, 1  };
    
    my_diagthree = kfsoleq::DiagThree(size, diagonals, constant_terms);
    EXPECT_TRUE(my_diagthree.checkDiagonalDomination()) << "DiagThree's checkDiagonalDomination() made a mistake";
    
    /*
     *  || 3 7 0 0 0  ||
     *  || 7 5 7 0 0  ||
     *  || 0 7 7 7 0  ||
     *  || 0 0 7 9 7  ||
     *  || 0 0 0 7 11 ||
     */
    diagonals[0] =   { 0, 7, 7, 7, 7  };
    diagonals[1] =   { 3, 5, 7, 9, 11 };
    diagonals[2] =   { 7, 7, 7, 7, 0  };
    constant_terms = { 1, 1, 1, 1, 1  };
    
    my_diagthree = kfsoleq::DiagThree(size, diagonals, constant_terms);
    EXPECT_FALSE(my_diagthree.checkDiagonalDomination()) << "DiagThree's checkDiagonalDomination() made a mistake";
    
    /*
     *  || 1 1 0 ||
     *  || 1 1 1 ||
     *  || 0 1 1 ||
     */
    size = 3;
    diagonals[0] =   { 0, 1, 1 };
    diagonals[1] =   { 1, 1, 1 };
    diagonals[2] =   { 1, 1, 0 };
    constant_terms = { 1, 1, 1 };
    
    my_diagthree = kfsoleq::DiagThree(size, diagonals, constant_terms);
    EXPECT_FALSE(my_diagthree.checkDiagonalDomination()) << "DiagThree's checkDiagonalDomination() made a mistake";
    
    /*
     *  || 1 1 ||
     *  || 1 1 ||
     */
    size = 2;
    diagonals[0] =   { 0, 1 };
    diagonals[1] =   { 1, 1 };
    diagonals[2] =   { 1, 0 };
    constant_terms = { 1, 1 };
    
    my_diagthree = kfsoleq::DiagThree(size, diagonals, constant_terms);
    EXPECT_TRUE(my_diagthree.checkDiagonalDomination()) << "DiagThree's checkDiagonalDomination() made a mistake";
    
    /*
     *  || 1 0 ||
     *  || 0 1 ||
     */
    diagonals[0] =   { 0, 0 };
    diagonals[1] =   { 1, 1 };
    diagonals[2] =   { 0, 0 };
    constant_terms = { 1, 1 };
    
    my_diagthree = kfsoleq::DiagThree(size, diagonals, constant_terms);
    EXPECT_TRUE(my_diagthree.checkDiagonalDomination()) << "DiagThree's checkDiagonalDomination() made a mistake";
    
    /*
     *  || 1 2 ||
     *  || 2 1 ||
     */
    diagonals[0] =   { 0, 2 };
    diagonals[1] =   { 1, 1 };
    diagonals[2] =   { 2, 0 };
    constant_terms = { 1, 1 };
    
    my_diagthree = kfsoleq::DiagThree(size, diagonals, constant_terms);
    EXPECT_FALSE(my_diagthree.checkDiagonalDomination()) << "DiagThree's checkDiagonalDomination() made a mistake";
}
