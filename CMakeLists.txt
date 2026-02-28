cmake_minimum_required(VERSION 4.2.3)

project(kfsoleq)

# Options
option(DIAGTHREE_BUILD "Build DiagThree" ON)
option(DIAGTHREE_TESTS_BUILD "Build DiagThree tests" ON)
option(MATRIX_BUILD "Build Matrix" ON)
option(MATRIX_TESTS_BUILD "Build Matrix tests" ON)
option(CSR_MATRIX_BUILD "Build CSR_Matrix" ON)
option(CSR_MATRIX_TESTS_BUILD "Build CSR_Matrix tests" ON)
option(VECTOR_BUILD "Build Vector" ON)
option(VECTOR_TESTS_BUILD "Build Vector tests" ON)

# For Google Testing enabling
enable_testing()


# Apply Source CMakeLists.txt
add_subdirectory(src)

# Build needed tests
if (DIAGTHREE_BUILD)
    if (DIAGTHREE_TESTS_BUILD)
        message("Adding DiagThree Test files...")
        add_subdirectory(tests/DiagThreeTests)
        message("Adding DiagThree Test files DONE!")
        message("[31;1mTHE MAIN TEST FOR DIAGTHREE IS 6th ONE, YOU CAN TRY TO SOLVE YOUR OWN TRIDIAGONAL SYSTEM OF LINEAR EQUATIONS WITH IT[0m")
    endif()
endif()
if (MATRIX_BUILD)
    if (MATRIX_TESTS_BUILD)
        message("Adding Matrix Test files...")
        add_subdirectory(tests/MatrixTests)
        message("Adding Matrix Test files DONE!")
    endif()
endif()
if (CSR_MATRIX_BUILD)
    if (CSR_MATRIX_TESTS_BUILD)
        message("Adding CSR_Matrix Test files...")
        add_subdirectory(tests/CSR_MatrixTests)
        message("Adding CSR_Matrix Test files DONE!")
    endif()
endif()
if (VECTOR_BUILD)
    if (VECTOR_TESTS_BUILD)
        message("Adding Vector Test files...")
        add_subdirectory(tests/VectorTests)
        message("Adding Vector Test files DONE!")
    endif()
endif()
