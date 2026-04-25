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
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/DEFINES.hpp
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
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/DEFINES.hpp
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
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/DEFINES.hpp
    )
    message("Adding CSR_Matrix Source files DONE!")
endif()
if (UPPER_TRIANGULAR_MATRIX_BUILD)
    message("Adding UpperTriangularMatrix Source files...")
    target_sources(SOLEQ
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src/SOLEQ/upper_triangular_matrix.cpp
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${PROJECT_SOURCE_DIR}/include
            FILES
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/upper_triangular_matrix.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/DEFINES.hpp
    )
    message("Adding UpperTriangularMatrix Source files DONE!")
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
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/DEFINES.hpp
    )
    message("Adding Vector Source files DONE!")
endif()
if (OPERATORS_BUILD)
    message("Adding Operators Source files...")
    target_sources(SOLEQ
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src/SOLEQ/operators.cpp
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${PROJECT_SOURCE_DIR}/include
            FILES
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/operators.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/matrix.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/csr_matrix.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/vector.hpp
    )
    message("Adding Operators Source files DONE!")
endif()
if (UTILITIES_BUILD)
    message("Adding Utilities Source files...")
    target_sources(SOLEQ
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src/SOLEQ/utilities.cpp
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${PROJECT_SOURCE_DIR}/include
            FILES
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/utilities.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/DEFINES.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/matrix.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/csr_matrix.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/vector.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/operators.hpp
    )
    message("Adding Utilities Source files DONE!")
endif()
if (GENERATORS_BUILD)
    message("Adding Generators Source files...")
    target_sources(SOLEQ
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src/SOLEQ/generators.cpp
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${PROJECT_SOURCE_DIR}/include
            FILES
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/generators.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/DEFINES.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/csr_matrix.hpp
    )
    message("Adding Generators Source files DONE!")
endif()
if (SOLVERS_BUILD)
    message("Adding Solvers Source files...")
    target_sources(SOLEQ
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src/SOLEQ/solvers.cpp
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${PROJECT_SOURCE_DIR}/include
            FILES
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/solvers.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/DEFINES.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/matrix.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/csr_matrix.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/vector.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/operators.hpp
    )
    message("Adding Solvers Source files DONE!")
endif()
#[[
/*
 * Currently accelerators have only header file,
 * so there is no need to build accelerators.cpp,
 * because it doesn't exist. But this section will
 * stay for more clear and generalized structure.
 */
if (ACCELERATORS_BUILD)
    message("Adding Accelerators Source files...")
    target_sources(SOLEQ
        PRIVATE
            ${PROJECT_SOURCE_DIR}/src/SOLEQ/accelerators.cpp
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS
                ${PROJECT_SOURCE_DIR}/include
            FILES
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/accelerators.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/DEFINES.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/csr_matrix.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/vector.hpp
                ${PROJECT_SOURCE_DIR}/include/SOLEQ/operators.hpp
    )
    message("Adding Accelerators Source files DONE!")
endif()
]]
