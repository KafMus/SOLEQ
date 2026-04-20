#include <SOLEQ/DEFINES.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>
#include <SOLEQ/linalg_operations.hpp>
#include <chrono>
#include <list>
#include <utility>
#include <iostream>
#include <fstream>
#include "Parsers/MatrixMarketFilesParser.cpp"


int main(int argc, char* argv[]) {
    
    // Checking input
    if (argc < 2) {
        std::cout << "Need filepath to source Matrix as 1st argument!\n";
        exit(EXIT_FAILURE);
    }
    if (argc < 3) {
        std::cout << "Need filepath to save result data as 2nd argument!\n";
        exit(EXIT_FAILURE);
    }
    
    // Opening datafile in needed mode
    std::fstream datafile(argv[2], datafile.in | datafile.app);
    if (!datafile.is_open()) {
        std::cout << "SolverBenchmark:[ERROR:[Failed to open datafile]]\n";
        exit(EXIT_FAILURE);
    }
    datafile.setf(std::ios_base::unitbuf);
    datafile << "NEW ENTRY OF BENCHMARK DATA OF SUCCESSIVE OVER RELAXATION SOLVER" << std::endl;
    
    // Getting CSR_Matrix from data and filling constant_terms
    // auto my_lil = getLilFromRealCoordinateSymmetricMatrix<kfsoleq::soleq_float>(argv[1]);
    // kfsoleq::CSR_Matrix my_csr_matrix(my_lil);
    size_t poisson_inner_grid_size = 20;
    kfsoleq::soleq_float h = 0.1;
    kfsoleq::CSR_Matrix my_csr_matrix = kfsoleq::generatorPoissonEquationMatrix(poisson_inner_grid_size,
                                                                                poisson_inner_grid_size);
    
    kfsoleq::Vector constant_terms(my_csr_matrix.getRowIndexes().size() - 1);
    for (size_t i = 0; i < constant_terms.getSize(); ++i) {
        // constant_terms[i] = 1;
        constant_terms[i] = -std::pow(h, 2) * 1;
    }
    
    // Declaration of main stuff
    kfsoleq::Vector roots;
    kfsoleq::Vector residual;
    kfsoleq::Vector solver_initial_roots = kfsoleq::Vector(my_csr_matrix.getRowIndexes().size() - 1);
    // kfsoleq::soleq_float relaxation_factor = 1.9618181795466909100866814696928486227989196777344; // Optimal for SparseMatrix0
    kfsoleq::soleq_float relaxation_factor = 1.7405800107385851482888483587885275483131408691406; // Optimal for Poisson20x20
    size_t iters_block_size = 5000;
    size_t solver_iters_block_size = 1;
    size_t solver_max_iters = 8192 * 16 * 4;
    long double aver_time;
    long double aver_iters = 0;
    size_t tmp_iters;
    long long int time_duration_in_ns;
    std::chrono::time_point<std::chrono::high_resolution_clock> saved_time, current_time;
    
    // Writing main parametrs of benchmark
    datafile << "Matrix Size:\t" << constant_terms.getSize() * constant_terms.getSize()
             << "\t | Solver Invokations Iters Block Size:\t" << iters_block_size
             << "\t | Solver Iters Block Size:\t" << solver_iters_block_size
             << std::endl;
    
    
    // Main iterations loops
    kfsoleq::soleq_float solver_tolerance;
    kfsoleq::soleq_float max_solver_tolerance  = 0.00000001;
    kfsoleq::soleq_float min_solver_tolerance  = 0.0000000001;
    kfsoleq::soleq_float solver_tolerance_step = 0.0000000012625;
    std::cout << "Iterations loops with max_solver_tolerance:[" << max_solver_tolerance
              << "], min_solver_tolerance:[" << min_solver_tolerance
              << "], solver_tolerance_step:[" << solver_tolerance_step << "]...\n";
    
    // Loop with descending tolerance
    for (solver_tolerance = max_solver_tolerance; solver_tolerance >= min_solver_tolerance; solver_tolerance -= solver_tolerance_step) {
        // Loop with many solver invokations
        std::cout << "Iterations loop for solver_tolerance:[" << solver_tolerance << "]...\n";
        saved_time = std::chrono::high_resolution_clock::now();
        for (size_t iter_num = 0; iter_num < iters_block_size; ++iter_num) {
            roots = kfsoleq::solverSuccessiveOverRelaxation(solver_tolerance,
                                                            solver_initial_roots,
                                                            my_csr_matrix,
                                                            constant_terms,
                                                            relaxation_factor,
                                                            solver_iters_block_size,
                                                            solver_max_iters,
                                                            &tmp_iters);
            aver_iters += (long double)tmp_iters;
        }
        current_time = std::chrono::high_resolution_clock::now();
        time_duration_in_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - saved_time).count();
        
        // Post loop work
        aver_time = (long double)time_duration_in_ns / (long double)iters_block_size;
        aver_iters /= (long double)iters_block_size;
        
        residual = ((my_csr_matrix * roots) - constant_terms);
        
        std::cout << "Iterations loop for solver_tolerance:[" << solver_tolerance << "] DONE!\n";
        std::cout << "Residual's First Norm:[" << residual.getFirstNorm() << "]\n";
        
        datafile << "Residual:\t" << residual.getFirstNorm()
                 << "\t | Aver Time (ms):\t" << aver_time / 1000000
                 << "\t | Aver Iters:\t" << aver_iters
                 << std::endl;
    }
    std::cout << "Iterations loops with max_solver_tolerance:[" << max_solver_tolerance
              << "], min_solver_tolerance:[" << min_solver_tolerance
              << "], solver_tolerance_step:[" << solver_tolerance_step << "] DONE!\n";
    
    
    
    
    
    
    
    
    
    
    
    datafile.close();
    return 0;
}
