find_package(GTest REQUIRED)
include(GoogleTest)


if (DIAGTHREE_BUILD)
    message("Adding DiagThree Test files...")
    add_subdirectory(DiagThreeTests)
    message("Adding DiagThree Test files DONE!")
    message("[31;1mTHE MAIN TEST FOR DIAGTHREE IS 6th ONE, YOU CAN TRY TO SOLVE YOUR OWN TRIDIAGONAL SYSTEM OF LINEAR EQUATIONS WITH IT[0m")
endif()
if (MATRIX_BUILD)
    message("Adding Matrix Test files...")
    add_executable(
        MatrixTests
        MatrixTests/matrix_tests.cpp
    )
    target_link_libraries(
        MatrixTests
        GTest::gtest_main
        SOLEQ
    )
    gtest_discover_tests(MatrixTests)
    message("Adding Matrix Test files DONE!")
endif()
if (CSR_MATRIX_BUILD)
    message("Adding CSR_Matrix Test files...")
    add_executable(
        CSR_MatrixTests
        CSR_MatrixTests/csr_matrix_tests.cpp
    )
    target_link_libraries(
        CSR_MatrixTests
        GTest::gtest_main
        SOLEQ
    )
    gtest_discover_tests(CSR_MatrixTests)
    message("Adding CSR_Matrix Test files DONE!")
endif()
if (VECTOR_BUILD)
    message("Adding Vector Test files...")
    add_executable(
        VectorTests
        VectorTests/vector_tests.cpp
    )
    target_link_libraries(
        VectorTests
        GTest::gtest_main
        SOLEQ
    )
    gtest_discover_tests(VectorTests)
    message("Adding Vector Test files DONE!")
endif()
if (LINALG_OPERATIONS_BUILD)
    message("Adding Linalg Operations Test files...")
    add_executable(
        LinalgOperationsTests
        LinalgOperationsTests/linalg_operations_tests.cpp
    )
    target_link_libraries(
        LinalgOperationsTests
        GTest::gtest_main
        SOLEQ
    )
    gtest_discover_tests(LinalgOperationsTests)
    message("Adding Linalg Operations Test files DONE!")
endif()
