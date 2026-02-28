# Google Tests part
find_package(GTest REQUIRED)


add_executable(
    CSR_MatrixTests
    csr_matrix_tests.cpp
)
target_link_libraries(
    CSR_MatrixTests
    GTest::gtest_main
    CSR_Matrix
)


include(GoogleTest)
gtest_discover_tests(CSR_MatrixTests)
