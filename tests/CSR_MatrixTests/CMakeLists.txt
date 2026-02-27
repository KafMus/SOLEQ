# Getting all test files full paths
file(GLOB all_tests LIST_DIRECTORIES FALSE "csr_matrix_test_*")
message("All found CSR_Matrix tests:")
foreach(i IN LISTS all_tests)
    message("\t${i}")
endforeach()


# Testname index (I am not sure this is good idea tho)
set(k 1)
foreach(test IN LISTS all_tests)
    
    # Add executable
    add_executable("CSR_MatrixTest_${k}")
    
    # Create target
    target_sources("CSR_MatrixTest_${k}"
        PRIVATE
            ${test}
    )
    
    # Link target to needed libraries
    target_link_libraries("CSR_MatrixTest_${k}"
        PRIVATE
            CSR_Matrix
    )
    
    # Testname index incremention
    math(EXPR k "${k} + 1")
endforeach()
