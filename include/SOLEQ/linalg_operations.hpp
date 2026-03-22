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
soleq_float getMaxEigenValuePowerMethod(const CSR_Matrix& given_csr_matrix,
                                        const Vector initial_vector,
                                        size_t iters_num);
Vector getChebyshevPolynomialRoots(size_t degree);
Vector reorderChebyshevPolynomialRoots(const Vector& roots);
Vector getTauFromChebyshevPolynomialRoots(const Vector& roots,
                                          soleq_float min_value,
                                          soleq_float max_value);
std::pair<Matrix, Matrix> getQRDecompositionHouseholder(Matrix given_matrix);
Vector solveUsingQRDecomposition(const Matrix& given_matrix);
Vector solveUsingQRDecomposition(const Matrix& given_matrix,
                                 const Matrix& Q_Matrix,
                                 const Matrix& R_Matrix);
Vector solveUsingJacobiMethod(const CSR_Matrix& given_csr_matrix,
                              const Vector& constant_terms,
                              soleq_float needed_precision,
                              const Vector& initial_root,
                              size_t iters_block_size,
                              size_t max_iters,
                              size_t* overall_iters_ptr = nullptr);
Vector solveUsingFixedPointIterationMethod(const CSR_Matrix& given_csr_matrix,
                                           const Vector& constant_terms,
                                           soleq_float needed_precision,
                                           const Vector& initial_root,
                                           soleq_float tau,
                                           size_t iters_block_size,
                                           size_t max_iters,
                                           size_t* overall_iters_ptr = nullptr);
Vector solveUsingGaussSeidelMethod(const CSR_Matrix& given_csr_matrix,
                                   const Vector& constant_terms,
                                   soleq_float needed_precision,
                                   const Vector& initial_root,
                                   size_t iters_block_size,
                                   size_t max_iters,
                                   size_t* overall_iters_ptr = nullptr);
Vector solveUsingChebyshevFixedPointIterationMethod(const CSR_Matrix& given_csr_matrix,
                                                    const Vector& constant_terms,
                                                    soleq_float needed_precision,
                                                    const Vector& initial_root,
                                                    const Vector& tau,
                                                    size_t max_iters,
                                                    size_t* overall_iters_ptr = nullptr);
Vector solveUsingChebyshevFixedPointIterationMethod(const CSR_Matrix& given_csr_matrix,
                                                    const Vector& constant_terms,
                                                    soleq_float needed_precision,
                                                    const Vector& initial_root,
                                                    soleq_float min_eigen_value,
                                                    soleq_float max_eigen_value,
                                                    size_t iters_block_size,
                                                    size_t max_iters,
                                                    size_t* overall_iters_ptr = nullptr);

}


#endif
