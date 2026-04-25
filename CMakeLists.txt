cmake_minimum_required(VERSION 4.2.3)

project(kfsoleq)

# Mandatory options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)

# Options
option(DIAGTHREE_BUILD "Build DiagThree" ON)
option(MATRIX_BUILD "Build Matrix" ON)
option(CSR_MATRIX_BUILD "Build CSR_Matrix" ON)
option(UPPER_TRIANGULAR_MATRIX_BUILD "Build UpperTriangularMatrix" ON)
option(VECTOR_BUILD "Build Vector" ON)
option(OPERATORS_BUILD "Build Operators" ON)
option(UTILITIES_BUILD "Build Utilities" ON)
option(GENERATORS_BUILD "Build Generators" ON)
option(SOLVERS_BUILD "Build Solvers" ON)
option(ACCELERATORS_BUILD "Build Accelerators" ON)
option(WITH_TOOLS "Build tools" ON)
option(WITH_TESTS "Build tests" ON)

# For Google Testing enabling
enable_testing()


# Adding library
add_library(SOLEQ)

# Apply Source CMakeLists.txt
message("Adding Source files...")
add_subdirectory(src)
message("Adding Source files DONE!")

# Adding tests
if (WITH_TESTS)
    message("Adding tests...")
    add_subdirectory(tests)
    message("Adding tests DONE!")
endif()

# Adding tools
if (WITH_TOOLS)
    message("Adding tools...")
    add_subdirectory(tools)
    message("Adding tools DONE!")
endif()
