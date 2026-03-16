if (DIAGTHREE_BUILD)
    message("Adding DiagThree Source files...")
    target_sources(SOLEQ
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src/SOLEQ/diagthree.cpp
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${PROJECT_SOURCE_DIR}/include
            FILES
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/diagthree.hpp
    )
    message("Adding DiagThree Source files DONE!")
endif()
if (MATRIX_BUILD)
    message("Adding Matrix Source files...")
    target_sources(SOLEQ
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src/SOLEQ/matrix.cpp
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${PROJECT_SOURCE_DIR}/include
            FILES
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/matrix.hpp
    )
    message("Adding Matrix Source files DONE!")
endif()
if (CSR_MATRIX_BUILD)
    message("Adding CSR_Matrix Source files...")
    target_sources(SOLEQ
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src/SOLEQ/csr_matrix.cpp
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${PROJECT_SOURCE_DIR}/include
            FILES
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/csr_matrix.hpp
    )
    message("Adding CSR_Matrix Source files DONE!")
endif()
if (VECTOR_BUILD)
    message("Adding Vector Source files...")
    target_sources(SOLEQ
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src/SOLEQ/vector.cpp
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${PROJECT_SOURCE_DIR}/include
            FILES
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/vector.hpp
    )
    message("Adding Vector Source files DONE!")
endif()
if (LINALG_OPERATIONS_BUILD)
    message("Adding LinalgOperations Source files...")
    target_sources(SOLEQ
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src/SOLEQ/linalg_operations.cpp
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${PROJECT_SOURCE_DIR}/include
            FILES
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/linalg_operations.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/matrix.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/csr_matrix.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/vector.hpp
    )
    message("Adding LinalgOperations Source files DONE!")
endif()
