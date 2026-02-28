# Google Tests part
find_package(GTest REQUIRED)


add_executable(
    LinalgOperationsTests
    linalg_operations_tests.cpp
)
target_link_libraries(
    LinalgOperationsTests
    GTest::gtest_main
    LinalgOperations
)


include(GoogleTest)
gtest_discover_tests(LinalgOperationsTests)
