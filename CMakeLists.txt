cmake_minimum_required(VERSION 4.2.3)

project(kfsoleq)

# Options
option(DIAGTHREE_BUILD "Build DiagThree" ON)
option(MATRIX_BUILD "Build Matrix" ON)
option(CSR_MATRIX_BUILD "Build CSR_Matrix" ON)
option(VECTOR_BUILD "Build Vector" ON)
option(LINALG_OPERATIONS_BUILD "Build Linalg Operations" ON)
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
