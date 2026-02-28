# Google Tests part
find_package(GTest REQUIRED)


add_executable(
    VectorTests
    vector_tests.cpp
)
target_link_libraries(
    VectorTests
    GTest::gtest_main
    Vector
)


include(GoogleTest)
gtest_discover_tests(VectorTests)
