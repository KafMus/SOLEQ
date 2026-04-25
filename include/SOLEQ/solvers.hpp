#ifndef SOLVERS_HPP_UUID_0000
#define SOLVERS_HPP_UUID_0000

#include <SOLEQ/DEFINES.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>
#include <SOLEQ/operators.hpp>
#include <SOLEQ/utilities.hpp>

namespace kfsoleq
{

Vector solverQRFactorization(const Matrix& given_matrix);
Vector solverQRFactorization(const Matrix& given_matrix,
                             const Matrix& Q_Matrix,
                             const Matrix& R_Matrix);
void solverJacobiStep(Vector& roots,
                      const Vector& roots_prev,
                      const CSR_Matrix& given_csr_matrix,
                      const Vector& constant_terms,
                      size_t given_csr_matrix_size_y);
Vector solverJacobi(soleq_float needed_precision,
                    const Vector& initial_roots,
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
                         const Vector& initial_roots,
                         const CSR_Matrix& given_csr_matrix,
                         const Vector& constant_terms,
                         size_t iters_block_size,
                         size_t max_iters,
                         size_t* overall_iters_ptr = nullptr);
Vector solverSuccessiveOverRelaxationStep(Vector& roots,
                                          const CSR_Matrix& given_csr_matrix,
                                          const Vector& constant_terms,
                                          size_t given_csr_matrix_size_y,
                                          soleq_float relaxation_factor);
Vector solverSuccessiveOverRelaxation(soleq_float needed_precision,
                                      const Vector& initial_roots,
                                      const CSR_Matrix& given_csr_matrix,
                                      const Vector& constant_terms,
                                      soleq_float relaxation_factor,
                                      size_t iters_block_size,
                                      size_t max_iters,
                                      size_t* overall_iters_ptr = nullptr);
Vector solverChebyshevFixedPointIteration(soleq_float needed_precision,
                                          const Vector& initial_roots,
                                          const CSR_Matrix& given_csr_matrix,
                                          const Vector& constant_terms,
                                          const Vector& tau,
                                          size_t max_iters,
                                          size_t* overall_iters_ptr = nullptr);
Vector solverChebyshevFixedPointIteration(soleq_float needed_precision,
                                          const Vector& initial_roots,
                                          const CSR_Matrix& given_csr_matrix,
                                          const Vector& constant_terms,
                                          soleq_float min_eigen_value,
                                          soleq_float max_eigen_value,
                                          size_t iters_block_size,
                                          size_t max_iters,
                                          size_t* overall_iters_ptr = nullptr);
Vector solverSteepestGradientDescentStep(Vector& roots,
                                         const CSR_Matrix& given_csr_matrix,
                                         const Vector& constant_terms,
                                         Vector& residual,
                                         soleq_float& alpha);
Vector solverSteepestGradientDescent(soleq_float needed_precision,
                                     const Vector& initial_roots,
                                     const CSR_Matrix& given_csr_matrix,
                                     const Vector& constant_terms,
                                     size_t iters_block_size,
                                     size_t max_iters,
                                     size_t* overall_iters_ptr = nullptr);
Vector solverConjugateGradientStep(Vector& roots,
                                   const CSR_Matrix& given_csr_matrix,
                                   const Vector& constant_terms,
                                   Vector& residual,
                                   Vector& delta,
                                   soleq_float& residual_square,
                                   soleq_float& alpha);
Vector solverConjugateGradient(soleq_float needed_precision,
                               const Vector& initial_roots,
                               const CSR_Matrix& given_csr_matrix,
                               const Vector& constant_terms,
                               size_t iters_block_size,
                               size_t max_iters,
                               size_t* overall_iters_ptr = nullptr);

}

#endif
