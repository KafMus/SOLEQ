if (DIAGTHREE_BUILD)
    message("Adding DiagThree Source files...")
    target_sources(SOLEQ
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
    target_sources(SOLEQ
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
    target_sources(SOLEQ
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
    target_sources(SOLEQ
        PRIVATE
            SOLEQ/vector.cpp
        PUBLIC
            FILE_SET HEADERS
            FILES
                SOLEQ/vector.hpp
    )
    message("Adding Vector Source files DONE!")
endif()
if (LINALG_OPERATIONS_BUILD)
    message("Adding LinalgOperations Source files...")
    target_sources(SOLEQ
        PRIVATE
            SOLEQ/linalg_operations.cpp
        PUBLIC
            FILE_SET HEADERS
            FILES
                SOLEQ/linalg_operations.hpp
                SOLEQ/matrix.hpp
                SOLEQ/csr_matrix.hpp
                SOLEQ/vector.hpp
    )
    message("Adding LinalgOperations Source files DONE!")
endif()
