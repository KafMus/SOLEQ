# Getting all test files full paths
file(GLOB all_tests LIST_DIRECTORIES FALSE "matrix_test_*")
message("All found Matrix tests:")
foreach(i IN LISTS all_tests)
    message("\t${i}")
endforeach()


# Testname index (I am not sure this is good idea tho)
set(k 1)
foreach(test IN LISTS all_tests)
    
    # Add executable
    add_executable("MatrixTest_${k}")
    
    # Create target
    target_sources("MatrixTest_${k}"
        PRIVATE
            ${test}
    )
    
    # Link target to needed libraries
    target_link_libraries("MatrixTest_${k}"
        PRIVATE
            Matrix
    )
    
    # Testname index incremention
    math(EXPR k "${k} + 1")
endforeach()
