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
    message("Adding Solver Jacobi Benchmark Executable...")
    add_executable(SolverJacobiBenchmark)

    target_sources(SolverJacobiBenchmark
        PRIVATE
            solverJacobiBenchmark.cpp
    )
    target_link_libraries(SolverJacobiBenchmark
        PRIVATE
            SOLEQ
    )
    message("Adding Solver Jacobi Benchmark Executable DONE!")
    message("Adding Solver Seidel Benchmark Executable...")
    add_executable(SolverSeidelBenchmark)

    target_sources(SolverSeidelBenchmark
        PRIVATE
            solverSeidelBenchmark.cpp
    )
    target_link_libraries(SolverSeidelBenchmark
        PRIVATE
            SOLEQ
    )
    message("Adding Solver Seidel Benchmark Executable DONE!")
    message("Adding Solver Fixed Point Iteration Benchmark Executable...")
    add_executable(SolverFixedPointIterationBenchmark)

    target_sources(SolverFixedPointIterationBenchmark
        PRIVATE
            solverFixedPointIterationBenchmark.cpp
    )
    target_link_libraries(SolverFixedPointIterationBenchmark
        PRIVATE
            SOLEQ
    )
    message("Adding Solver Fixed Point Iteration Benchmark Executable DONE!")
endif()
