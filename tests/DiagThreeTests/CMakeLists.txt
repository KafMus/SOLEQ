# Getting all test files full paths
file(GLOB all_tests LIST_DIRECTORIES FALSE "diagthree_test_*")
message("All found DiagThree tests:")
foreach(i IN LISTS all_tests)
    message("\t${i}")
endforeach()


# Testname index (I am not sure this is good idea tho)
set(k 1)
foreach(test IN LISTS all_tests)
    
    # Add executable
    add_executable("DiagThreeTest_${k}")
    
    # Create target
    target_sources("DiagThreeTest_${k}"
        PRIVATE
            ${test}
    )
    
    # Link target to needed libraries
    target_link_libraries("DiagThreeTest_${k}"
        PRIVATE
            DiagThree
    )
    
    # Testname index incremention
    math(EXPR k "${k} + 1")
endforeach()
