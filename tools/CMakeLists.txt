if(MATRIX_BUILD AND CSR_MATRIX_BUILD AND VECTOR_BUILD AND LINALG_OPERATIONS_BUILD)
    message("Adding Matrix And CSR_Matrix To Vector Multiplication Benchmark Executable...")
    add_executable(MatrixAndCSRMatrixToVectorMultiplicationBenchmark)

    target_sources(MatrixAndCSRMatrixToVectorMultiplicationBenchmark
        PRIVATE
            MatrixAndCSRMatrixToVectorMultiplicationBenchmark.cpp
    )
    target_link_libraries(MatrixAndCSRMatrixToVectorMultiplicationBenchmark
        PRIVATE
            SOLEQ
    )
    message("Adding Matrix And CSR_Matrix To Vector Multiplication Benchmark Executable DONE!")
    message("Adding Solver Jacobi Benchmark Executable...")
    add_executable(SolverJacobiBenchmark)

    target_sources(SolverJacobiBenchmark
        PRIVATE
            SolverJacobiBenchmark.cpp
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
            SolverSeidelBenchmark.cpp
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
            SolverFixedPointIterationBenchmark.cpp
    )
    target_link_libraries(SolverFixedPointIterationBenchmark
        PRIVATE
            SOLEQ
    )
    message("Adding Solver Fixed Point Iteration Benchmark Executable DONE!")
    message("Adding Solver Chebyshev Fixed Point Iteration Benchmark Executable...")
    add_executable(SolverChebyshevFixedPointIterationBenchmark)

    target_sources(SolverChebyshevFixedPointIterationBenchmark
        PRIVATE
            SolverChebyshevFixedPointIterationBenchmark.cpp
    )
    target_link_libraries(SolverChebyshevFixedPointIterationBenchmark
        PRIVATE
            SOLEQ
    )
    message("Adding Solver Chebyshev Fixed Point Iteration Benchmark Executable DONE!")
endif()
