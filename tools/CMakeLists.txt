if(MATRIX_BUILD AND CSR_MATRIX_BUILD AND VECTOR_BUILD AND LINALG_OPERATIONS_BUILD)
    message("Adding Matrix Vector Multiplication Benchmark Executable...")
    add_executable(MatrixVectorMultiplicationBenchmark)

    target_sources(MatrixVectorMultiplicationBenchmark
        PRIVATE
            matrixbenchmark.cpp
    )
    target_link_libraries(MatrixVectorMultiplicationBenchmark
        PRIVATE
            SOLEQ
    )
    message("Adding Matrix Vector Multiplication Benchmark Executable DONE!")
endif()
