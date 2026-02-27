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
