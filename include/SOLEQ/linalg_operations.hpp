#ifndef LINALG_OPERATIONS_HPP_UUID_0000
#define LINALG_OPERATIONS_HPP_UUID_0000

#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>
#include <cmath>
#include <numbers>

namespace kfsoleq
{

Vector operator * (const Matrix& left_matrix, const Vector& right_vector);
Matrix operator * (const Vector& left_vector, const Matrix& right_matrix);
Vector operator * (const CSR_Matrix& left_csr_matrix, const Vector& right_vector);
Matrix operator * (const Vector& left_vector, const CSR_Matrix& right_csr_matrix);
soleq_float getMaxEigenValuePowerMethod(const Vector initial_vector,
                                        const CSR_Matrix& given_csr_matrix,
                                        size_t iters_num);
Vector getChebyshevRoots(size_t degree);
Vector reorderChebyshevRoots(const Vector& roots);
Vector getTauFromChebyshevRoots(const Vector& roots,
                                soleq_float min_value,
                                soleq_float max_value);
soleq_float getNewChebyshevAccelerationParameter(soleq_float spectral_radius,
                                                 soleq_float prev_mu,
                                                 soleq_float curr_mu);
std::pair<Matrix, Matrix> getQRDecompositionHouseholder(Matrix given_matrix);
Vector solverQRDecomposition(const Matrix& given_matrix);
Vector solverQRDecomposition(const Matrix& given_matrix,
                             const Matrix& Q_Matrix,
                             const Matrix& R_Matrix);
void solverJacobiStep(Vector& roots,
                      const Vector& roots_prev,
                      const CSR_Matrix& given_csr_matrix,
                      const Vector& constant_terms,
                      size_t given_csr_matrix_size_y);
Vector solverJacobi(soleq_float needed_precision,
                    const Vector& initial_root,
                    const CSR_Matrix& given_csr_matrix,
                    const Vector& constant_terms,
                    size_t iters_block_size,
                    size_t max_iters,
                    size_t* overall_iters_ptr = nullptr);
Vector solverFixedPointIterationStep(Vector& roots,
                                   const CSR_Matrix& given_csr_matrix,
                                   const Vector& constant_terms,
                                   soleq_float tau);
Vector solverFixedPointIteration(soleq_float needed_precision,
                                 const CSR_Matrix& given_csr_matrix,
                                 const Vector& constant_terms,
                                 soleq_float tau,
                                 size_t iters_block_size,
                                 size_t max_iters,
                                 size_t* overall_iters_ptr = nullptr);
Vector solverGaussSeidelStep(Vector& roots,
                           const CSR_Matrix& given_csr_matrix,
                           const Vector& constant_terms,
                           size_t given_csr_matrix_size_y);
Vector solverGaussSeidel(soleq_float needed_precision,
                         const Vector& initial_root,
                         const CSR_Matrix& given_csr_matrix,
                         const Vector& constant_terms,
                         size_t iters_block_size,
                         size_t max_iters,
                         size_t* overall_iters_ptr = nullptr);
Vector solverChebyshevFixedPointIteration(soleq_float needed_precision,
                                          const Vector& initial_root,
                                          const CSR_Matrix& given_csr_matrix,
                                          const Vector& constant_terms,
                                          const Vector& tau,
                                          size_t max_iters,
                                          size_t* overall_iters_ptr = nullptr);
Vector solverChebyshevFixedPointIteration(soleq_float needed_precision,
                                          const Vector& initial_root,
                                          const CSR_Matrix& given_csr_matrix,
                                          const Vector& constant_terms,
                                          soleq_float min_eigen_value,
                                          soleq_float max_eigen_value,
                                          size_t iters_block_size,
                                          size_t max_iters,
                                          size_t* overall_iters_ptr = nullptr);
template <bool SolverStepRequiresPreviousRoots, typename SolverStepFunc, typename... Args>
Vector acceleratorChebyshev(soleq_float needed_precision,
                            const Vector& initial_root,
                            const CSR_Matrix& given_csr_matrix,
                            const Vector& constant_terms,
                            soleq_float spectral_radius,
                            size_t iters_block_size,
                            size_t max_iters,
                            size_t* overall_iters_ptr,
                            SolverStepFunc solver_step_func,
                            Args... solver_step_arguments) {
        Vector roots = initial_root;
        if constexpr (SolverStepRequiresPreviousRoots) {
            solver_step_func(roots, initial_root, given_csr_matrix, constant_terms, solver_step_arguments...);
        }
        else {
            solver_step_func(roots, given_csr_matrix, constant_terms, solver_step_arguments...);
        }
        soleq_float prev_mu = 1;
        soleq_float curr_mu = 1.0 / spectral_radius;
        soleq_float next_mu;
        
        
        size_t outer_ind = 2;
        
        if constexpr (SolverStepRequiresPreviousRoots) {
            Vector roots_prev = initial_root;
            Vector tmp_roots; // I don't want this, but I need to choose lesser of two evils
            
            while (outer_ind < max_iters && ((given_csr_matrix * roots) - constant_terms).getFirstNorm() > needed_precision) {
                for (size_t iter_num = 0; iter_num < iters_block_size; ++iter_num) {
                    next_mu = getNewChebyshevAccelerationParameter(spectral_radius, prev_mu, curr_mu);
                    
                    tmp_roots = roots;
                    solver_step_func(roots, tmp_roots, given_csr_matrix, constant_terms, solver_step_arguments...);
                    roots = ((2 * curr_mu) / (spectral_radius * next_mu)) * roots - (prev_mu / next_mu) * roots_prev;
                    roots_prev = tmp_roots;
                    
                    prev_mu = std::exchange(curr_mu, next_mu);
                }
                outer_ind += iters_block_size;
            }
        }        
        else {
            Vector roots_prev = initial_root;
            
            while (outer_ind < max_iters && ((given_csr_matrix * roots) - constant_terms).getFirstNorm() > needed_precision) {
                for (size_t iter_num = 0; iter_num < iters_block_size; ++iter_num) {
                    next_mu = getNewChebyshevAccelerationParameter(spectral_radius, prev_mu, curr_mu);
                    
                    roots_prev = std::exchange(roots, ((2 * curr_mu) / (spectral_radius * next_mu)) *
                                                      solver_step_func(roots, given_csr_matrix, constant_terms, solver_step_arguments...) -
                                                      (prev_mu / next_mu) * roots_prev);
                    
                    prev_mu = std::exchange(curr_mu, next_mu);
                }
                outer_ind += iters_block_size;
            }
        }
        
        
        if (overall_iters_ptr) { (*overall_iters_ptr) = outer_ind; }
        return roots;
}

}

#endif
