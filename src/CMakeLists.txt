if (DIAGTHREE_BUILD)
    message("Adding DiagThree Source files...")
    add_library(DiagThree)
    target_sources(DiagThree
        PRIVATE
        SOLEQ/diagthree.cpp
        PUBLIC
            FILE_SET HEADERS
            FILES
            SOLEQ/diagthree.hpp
    )
    message("Adding DiagThree Source files DONE!")
endif()
if (MATRIX_BUILD)
    message("Adding Matrix Source files...")
    add_library(Matrix)
    target_sources(Matrix
        PRIVATE
        SOLEQ/matrix.cpp
        PUBLIC
            FILE_SET HEADERS
            FILES
            SOLEQ/matrix.hpp
    )
    message("Adding Matrix Source files DONE!")
endif()
if (CSR_MATRIX_BUILD)
    message("Adding CSR_Matrix Source files...")
    add_library(CSR_Matrix)
    target_sources(CSR_Matrix
        PRIVATE
        SOLEQ/csr_matrix.cpp
        PUBLIC
            FILE_SET HEADERS
            FILES
            SOLEQ/csr_matrix.hpp
    )
    message("Adding CSR_Matrix Source files DONE!")
endif()
if (VECTOR_BUILD)
    message("Adding Vector Source files...")
    add_library(Vector)
    target_sources(Vector
        PRIVATE
        SOLEQ/vector.cpp
        PUBLIC
            FILE_SET HEADERS
            FILES
            SOLEQ/vector.hpp
    )
    message("Adding Vector Source files DONE!")
endif()
