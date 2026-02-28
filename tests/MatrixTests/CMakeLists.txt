# Google Tests part
find_package(GTest REQUIRED)


add_executable(
    MatrixTests
    matrix_tests.cpp
)
target_link_libraries(
    MatrixTests
    GTest::gtest_main
    Matrix
)


include(GoogleTest)
gtest_discover_tests(MatrixTests)
