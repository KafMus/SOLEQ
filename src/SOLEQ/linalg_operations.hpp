#ifndef LINALG_OPERATIONS_HPP_UUID_0000
#define LINALG_OPERATIONS_HPP_UUID_0000

#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>

namespace kfsoleq
{

Vector operator * (const Matrix& left_matrix, const Vector& right_vector);
Vector operator * (const CSR_Matrix& left_csr_matrix, const Vector& right_vector);
std::pair<Matrix, Matrix> getQRDecompositionHouseholder(Matrix given_matrix);

}


#endif
