#ifndef LINALG_OPERATIONS_HPP_UUID_0000
#define LINALG_OPERATIONS_HPP_UUID_0000

#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>
#include <cmath>

namespace kfsoleq
{

Vector operator * (const Matrix& left_matrix, const Vector& right_vector);
Matrix operator * (const Vector& left_vector, const Matrix& right_matrix);
Vector operator * (const CSR_Matrix& left_csr_matrix, const Vector& right_vector);
Matrix operator * (const Vector& left_vector, const CSR_Matrix& right_csr_matrix);
std::pair<Matrix, Matrix> getQRDecompositionHouseholder(Matrix given_matrix);
Vector solveUsingQRDecomposition(const Matrix& given_matrix);
Vector solveUsingQRDecomposition(const Matrix& given_matrix,
                                const Matrix& Q_Matrix,
                                const Matrix& R_Matrix);
Vector solveUsingJacobiMethod(const CSR_Matrix& given_csr_matrix,
                              const Vector& constant_terms,
                              soleq_float needed_precision,
                              size_t iters_block_size,
                              size_t max_iters);
Vector solveUsingFixedPointIterationMethod(const CSR_Matrix& given_csr_matrix,
                              const Vector& constant_terms,
                              soleq_float needed_precision,
                              const Vector& initial_root,
                              soleq_float tau,
                              size_t iters_block_size,
                              size_t max_iters);
Vector solveUsingGaussSeidelMethod(const CSR_Matrix& given_csr_matrix,
                              const Vector& constant_terms,
                              soleq_float needed_precision,
                              const Vector& initial_root,
                              size_t iters_block_size,
                              size_t max_iters);

}


#endif
