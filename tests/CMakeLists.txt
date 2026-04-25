find_package(GTest REQUIRED)
include(GoogleTest)


if (DIAGTHREE_BUILD)
    message("Adding DiagThree Test files...")
    add_executable(
        DiagThreeTests
        DiagThreeTests/diagthree_tests.cpp
    )
    target_link_libraries(
        DiagThreeTests
        GTest::gtest_main
        SOLEQ
    )
    gtest_discover_tests(DiagThreeTests)
    message("Adding DiagThree Test files DONE!")
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
if (UPPER_TRIANGULAR_MATRIX_BUILD)
    message("Adding UpperTriangularMatrix Test files...")
    add_executable(
        UpperTriangularMatrixTests
        UpperTriangularMatrixTests/upper_triangular_matrix_tests.cpp
    )
    target_link_libraries(
        UpperTriangularMatrixTests
        GTest::gtest_main
        SOLEQ
    )
    gtest_discover_tests(UpperTriangularMatrixTests)
    message("Adding UpperTriangularMatrix Test files DONE!")
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
if (OPERATORS_BUILD)
    message("Adding Operators Test files...")
    add_executable(
        OperatorsTests
        OperatorsTests/operators_tests.cpp
    )
    target_link_libraries(
        OperatorsTests
        GTest::gtest_main
        SOLEQ
    )
    gtest_discover_tests(OperatorsTests)
    message("Adding Operators Test files DONE!")
endif()
if (UTILITIES_BUILD)
    message("Adding Utilities Test files...")
    add_executable(
        UtilitiesTests
        UtilitiesTests/utilities_tests.cpp
    )
    target_link_libraries(
        UtilitiesTests
        GTest::gtest_main
        SOLEQ
    )
    gtest_discover_tests(UtilitiesTests)
    message("Adding Utilities Test files DONE!")
endif()
if (GENERATORS_BUILD)
    message("Adding Generators Test files...")
    add_executable(
        GeneratorsTests
        GeneratorsTests/generators_tests.cpp
    )
    target_link_libraries(
        GeneratorsTests
        GTest::gtest_main
        SOLEQ
    )
    gtest_discover_tests(GeneratorsTests)
    message("Adding Generators Test files DONE!")
endif()
if (SOLVERS_BUILD)
    message("Adding Solvers Test files...")
    add_executable(
        SolversTests
        SolversTests/solvers_tests.cpp
    )
    target_link_libraries(
        SolversTests
        GTest::gtest_main
        SOLEQ
    )
    gtest_discover_tests(SolversTests)
    message("Adding Solvers Test files DONE!")
endif()
if (ACCELERATORS_BUILD)
    message("Adding Accelerators Test files...")
    add_executable(
        AcceleratorsTests
        AcceleratorsTests/accelerators_tests.cpp
    )
    target_link_libraries(
        AcceleratorsTests
        GTest::gtest_main
        SOLEQ
    )
    gtest_discover_tests(AcceleratorsTests)
    message("Adding Accelerators Test files DONE!")
endif()
