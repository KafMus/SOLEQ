#ifndef LINALG_OPERATIONS_HPP_UUID_0000
#define LINALG_OPERATIONS_HPP_UUID_0000

#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>

namespace kfsoleq
{

Vector operator * (const Matrix& left_matrix, const Vector& right_vector);
Matrix operator * (const Vector& left_vector, const Matrix& right_matrix);
Vector operator * (const CSR_Matrix& left_csr_matrix, const Vector& right_vector);
Matrix operator * (const Vector& left_vector, const CSR_Matrix& right_csr_matrix);
std::pair<Matrix, Matrix> getQRDecompositionHouseholder(Matrix given_matrix);

}


#endif
