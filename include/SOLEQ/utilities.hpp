#ifndef UTILITIES_HPP_UUID_0000
#define UTILITIES_HPP_UUID_0000

#include <SOLEQ/DEFINES.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>
#include <SOLEQ/operators.hpp>
#include <cmath>
#include <list>
#include <numbers>

namespace kfsoleq
{

CSR_Matrix getCSRMatrixFromMatrix(const Matrix& given_matrix,
                                  soleq_float given_tolerance);
Matrix getMatrixFromCSRMatrix(const CSR_Matrix& given_csr_matrix,
                              size_t size_x);
Vector getMatrixRow(const Matrix& given_matrix, size_t y);
Vector getMatrixCol(const Matrix& given_matrix, size_t x);
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
std::pair<Matrix, Matrix> getQRFactorizationHouseholder(Matrix given_matrix);

}

#endif
