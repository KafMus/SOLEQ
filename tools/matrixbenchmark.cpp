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

#define SIZES_NUM  5
#define DENSES_NUM 9
#define DATAFILE_PATH "./data.csv"
int main() {
    
    // Opening datafile in needed mode
    std::fstream datafile("./data.csv", datafile.in | datafile.app);
    if (!datafile.is_open()) {
        std::cout << "Failed to open datafile!\n";
        exit(EXIT_FAILURE);
    }
    datafile.setf(std::ios_base::unitbuf);
    
    // Main stuff declaration and/or initialization
    kfsoleq::Vector etalon_vector;
    kfsoleq::Matrix my_matrix;
    kfsoleq::CSR_Matrix my_csr_matrix;
    kfsoleq::Vector result;
    std::list<std::list<std::pair<size_t, SOLEQ_FLOAT>>> my_lil;
    size_t size_y[SIZES_NUM] = { 10, 50, 250, 500, 1000 };
    size_t size_x[SIZES_NUM] = { 10, 50, 250, 500, 1000 };
    unsigned int number_of_iterations = 10;
    SOLEQ_FLOAT salt = 420;
    SOLEQ_FLOAT vector_salt = 100;
    
    /*
     * We will fill matrix somewhere. every_which
     * describes which element we will fill.
     */
    unsigned int every_which[DENSES_NUM] = { 2, 5, 10, 20, 50, 200, 500, 1000, 2000 };
    double aver_matrix_time[DENSES_NUM * SIZES_NUM]     = { 0 };
    double aver_csr_matrix_time[DENSES_NUM * SIZES_NUM] = { 0 };
    double actual_density[DENSES_NUM * SIZES_NUM]       = { 0 };
    
    
    // Main benchmark loop
    for (size_t i = 0; i < SIZES_NUM; ++i) {
        for (size_t dens_ind = 0; dens_ind < DENSES_NUM; ++dens_ind) {
            // Creating etalon Vector
            std::cout << "Creating etalon Vector...\n";
            etalon_vector = kfsoleq::Vector(size_x[i]);
            for (size_t j = 0; j < size_x[i]; ++j) {
                etalon_vector[j] = (SOLEQ_FLOAT)(j + 1) * vector_salt;
            }
            std::cout << "Creating etalon Vector DONE!\n";
            
            // Creating Matrix
            std::cout << "Creating Matrix...\n";
            my_matrix = kfsoleq::Matrix(size_y[i], size_x[i]);
            unsigned int k = 1;
            for (size_t j = 0; j < size_y[i]; ++j) {
                for (size_t z = 0; z < size_x[i]; ++z) {
                    if (every_which[dens_ind] == k) {
                        k = 0;
                        my_matrix(j, z) = salt * (SOLEQ_FLOAT)(j + z);
                    }
                    k++;
                }
            }
            std::cout << "Creating Matrix DONE!\n";
            
            // Creating CSR_Matrix using Matrix
            std::cout << "Creating CSR_Matrix...\n";
            for (size_t j = 0; j < size_y[i]; ++j) {
                std::list<std::pair<size_t, SOLEQ_FLOAT>> tmp_list;
                for (size_t z = 0; z < size_x[i]; ++z) {
                    // We can use '0 !=' even with the fact, that this is SOLEQ_FLOAT
                    if (0 != my_matrix(j, z)) {
                        tmp_list.push_back(std::make_pair(z, my_matrix(j, z)));
                    }
                }
                my_lil.push_back(std::list(tmp_list));
            }
            my_csr_matrix = kfsoleq::CSR_Matrix(my_lil);
            my_lil = std::list<std::list<std::pair<size_t, SOLEQ_FLOAT>>>{};
            std::cout << "Creating CSR_Matrix DONE!\n";
           
            // Calculation of actual density that we've got
            actual_density[i * SIZES_NUM + dens_ind] = (double)(my_csr_matrix.getRowIndexes().back()) / (double)(size_y[i] * size_x[i]);
            
            // Main iterations loops
            std::cout << "Iterations loops...\n";
            long long int time_duration_in_ns = 0;
            std::chrono::high_resolution_clock::time_point current_time, saved_time;
            for (unsigned int iter_num = 0; iter_num < number_of_iterations; ++iter_num) {
                saved_time = std::chrono::high_resolution_clock::now();
                
                result = my_matrix * etalon_vector;
                
                current_time = std::chrono::high_resolution_clock::now();
                time_duration_in_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - saved_time).count();
            }
            aver_matrix_time[i * SIZES_NUM + dens_ind] = (double)time_duration_in_ns / (double)number_of_iterations;
            time_duration_in_ns = 0;
            for (unsigned int iter_num = 0; iter_num < number_of_iterations; ++iter_num) {
                saved_time = std::chrono::high_resolution_clock::now();
                
                result = my_csr_matrix * etalon_vector;
                
                current_time = std::chrono::high_resolution_clock::now();
                time_duration_in_ns += std::chrono::duration_cast<std::chrono::nanoseconds>(current_time - saved_time).count();
            }
            aver_csr_matrix_time[i * SIZES_NUM + dens_ind] = (double)time_duration_in_ns / (double)number_of_iterations;
            std::cout << "Iterations loops DONE!\n";
            
            // Output
            std::cout << "Density: " << every_which[dens_ind] << '\n';
            std::cout << "Actual Density in %: " << actual_density[i * SIZES_NUM + dens_ind] * 100 << '\n';
            std::cout << "\tSize Y: " << size_y[i] << '\n';
            std::cout << "\tSize X: " << size_x[i] << '\n';
            std::cout << "\t\tAverage Matrix time in ns:\t" << aver_matrix_time[i * SIZES_NUM + dens_ind] << '\n';
            std::cout << "\t\tAverage CSR_Matrix time in ns:\t" << aver_csr_matrix_time[i * SIZES_NUM + dens_ind] << '\n';
            std::cout << "\t\tAverage Matrix time in us:\t" << aver_matrix_time[i * SIZES_NUM + dens_ind] / 1000 << '\n';
            std::cout << "\t\tAverage CSR_Matrix time in us:\t" << aver_csr_matrix_time[i * SIZES_NUM + dens_ind] / 1000 << '\n';
            std::cout << "\t\tAverage Matrix time in ms:\t" << aver_matrix_time[i * SIZES_NUM + dens_ind] / 1000000 << '\n';
            std::cout << "\t\tAverage CSR_Matrix time in ms:\t" << aver_csr_matrix_time[i * SIZES_NUM + dens_ind] / 1000000 << '\n';
            
            // Saving to datafile
            datafile << "Size:\t" << size_y[i] * size_x[i]
                     << "\tActual Density:\t" << actual_density[i * SIZES_NUM + dens_ind] * 100
                     << "\tMatrix:\t" << aver_matrix_time[i * SIZES_NUM + dens_ind] / 1000000
                     << "\tCSR_Matrix:\t" << aver_csr_matrix_time[i * SIZES_NUM + dens_ind] / 1000000 << std::endl;
        }
    }
    
    
    datafile.close();
    return 0;
}
