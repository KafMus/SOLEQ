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
std::pair<Matrix, Matrix> getQRDecompositionHouseholder(Matrix given_matrix);
Vector solverQRDecomposition(const Matrix& given_matrix);
Vector solverQRDecomposition(const Matrix& given_matrix,
                             const Matrix& Q_Matrix,
                             const Matrix& R_Matrix);
Vector solverJacobi(const Vector& initial_root,
                    const CSR_Matrix& given_csr_matrix,
                    const Vector& constant_terms,
                    soleq_float needed_precision,
                    size_t iters_block_size,
                    size_t max_iters,
                    size_t* overall_iters_ptr = nullptr);
Vector solverFixedPointIteration(const Vector& initial_root,
                                 const CSR_Matrix& given_csr_matrix,
                                 const Vector& constant_terms,
                                 soleq_float tau,
                                 soleq_float needed_precision,
                                 size_t iters_block_size,
                                 size_t max_iters,
                                 size_t* overall_iters_ptr = nullptr);
Vector solverGaussSeidel(const Vector& initial_root,
                         const CSR_Matrix& given_csr_matrix,
                         const Vector& constant_terms,
                         soleq_float needed_precision,
                         size_t iters_block_size,
                         size_t max_iters,
                         size_t* overall_iters_ptr = nullptr);
Vector solverChebyshevFixedPointIteration(const Vector& initial_root,
                                          const CSR_Matrix& given_csr_matrix,
                                          const Vector& constant_terms,
                                          const Vector& tau,
                                          soleq_float needed_precision,
                                          size_t max_iters,
                                          size_t* overall_iters_ptr = nullptr);
Vector solverChebyshevFixedPointIteration(const Vector& initial_root,
                                          const CSR_Matrix& given_csr_matrix,
                                          const Vector& constant_terms,
                                          soleq_float min_eigen_value,
                                          soleq_float max_eigen_value,
                                          soleq_float needed_precision,
                                          size_t iters_block_size,
                                          size_t max_iters,
                                          size_t* overall_iters_ptr = nullptr);

}


#endif
