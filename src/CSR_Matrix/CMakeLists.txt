add_library(CSR_Matrix)

target_sources(CSR_Matrix
    PRIVATE
        csr_matrix.cpp
    
    PUBLIC
        FILE_SET HEADERS
        FILES
            csr_matrix.hpp
)
