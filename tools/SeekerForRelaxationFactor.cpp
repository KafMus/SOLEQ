#include <SOLEQ/DEFINES.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>
#include <SOLEQ/linalg_operations.hpp>
#include <chrono>
#include <cmath>
#include <list>
#include <utility>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "Parsers/MatrixMarketFilesParser.cpp"


int main(int argc, char* argv[]) {
    
    std::cout << std::setprecision(50);
    
    // Checking input
    if (argc < 2) {
        std::cout << "Need filepath to source Matrix as 1st argument!\n";
        exit(EXIT_FAILURE);
    }
    
    // Getting CSR_Matrix from data and filling constant_terms
    // auto my_matrix = getMatrixFromRealCoordinateSymmetricMatrix<kfsoleq::soleq_float>(argv[1]);
    size_t poisson_inner_grid_size = 20;
    kfsoleq::CSR_Matrix my_csr_matrix = kfsoleq::generatorPoissonEquationMatrix(poisson_inner_grid_size,
                                                                                poisson_inner_grid_size);
    kfsoleq::Matrix my_matrix = kfsoleq::getMatrixFromCSRMatrix(my_csr_matrix,
                                                                my_csr_matrix.getRowIndexes().size() - 1);
    argv[1] = nullptr; // Imitate argv[1] usage if we examine Poisson Equation Matrix
    
    size_t iters_to_seek_max_eigen_value = 65536;
    kfsoleq::soleq_float max_eigen_value;
    kfsoleq::soleq_float relaxation_factor;
    kfsoleq::soleq_float spectral_radius;
    
    
    kfsoleq::Matrix identity_matrix(my_matrix.getSizeY(), my_matrix.getSizeX());
    for (size_t i = 0; i < my_matrix.getSizeY(); ++i) {
        identity_matrix(i, i) = 1;
    }
    
    kfsoleq::Matrix inverted_diagonal_matrix(my_matrix.getSizeY(), my_matrix.getSizeX());
    for (size_t i = 0; i < my_matrix.getSizeY(); ++i) {
        inverted_diagonal_matrix(i, i) = (1.0 / my_matrix(i, i));
    }
    
    kfsoleq::Matrix examined_matrix = identity_matrix - (inverted_diagonal_matrix * my_matrix);
    kfsoleq::CSR_Matrix examined_csr_matrix = kfsoleq::getCSRMatrixFromMatrix(examined_matrix, 0);
    
    kfsoleq::Vector initial_vector(my_matrix.getSizeY());
    for (size_t i = 0; i < my_matrix.getSizeY(); ++i) {
        initial_vector[i] = 1;
    }
    
    max_eigen_value = kfsoleq::getMaxEigenValuePowerMethod(initial_vector,
                                                           examined_csr_matrix,
                                                           iters_to_seek_max_eigen_value);
    max_eigen_value = std::abs(max_eigen_value);
    std::cout << "Max Eigen Value of (I - D^{-1}A) Matrix: " << max_eigen_value << std::endl;
    
    relaxation_factor = 1 + std::pow((max_eigen_value / (1 + std::sqrt(1 - std::pow(max_eigen_value, 2)))), 2);
    std::cout << "Relaxation Factor: " << relaxation_factor << std::endl;
    
    spectral_radius = std::pow(((relaxation_factor * max_eigen_value) +
                                std::sqrt(std::pow(relaxation_factor * max_eigen_value, 2) - 4 * (relaxation_factor - 1)) ), 2) / 4;
    std::cout << "Spectral Radius: " << spectral_radius << std::endl;
    
    
    return 0;
}
