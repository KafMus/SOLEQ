#ifndef LINALG_OPERATIONS_CPP_UUID_0000
#define LINALG_OPERATIONS_CPP_UUID_0000

#include <SOLEQ/linalg_operations.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>



kfsoleq::Vector kfsoleq::operator * (const kfsoleq::Matrix& left_matrix, const kfsoleq::Vector& right_vector) {
        kfsoleq::Vector result = kfsoleq::Vector(left_matrix.getSizeY());
        for (size_t i = 0; i < left_matrix.getSizeY(); ++i) {
            for (size_t j = 0; j < left_matrix.getSizeX(); ++j) {
                result[i] += left_matrix(i, j) * right_vector[j];
            }
        }
        return result;
}
kfsoleq::Vector kfsoleq::operator * (const kfsoleq::CSR_Matrix& left_csr_matrix, const kfsoleq::Vector& right_vector) {
        if (0 == left_csr_matrix.getRowIndexes().size()) {
            return kfsoleq::Vector{};
        }
        kfsoleq::Vector result = kfsoleq::Vector(left_csr_matrix.getRowIndexes().size() - 1);
        for (size_t i = 0; i < left_csr_matrix.getRowIndexes().size() - 1; ++i) {
            for (size_t j = left_csr_matrix.getRowIndexes()[i]; j < left_csr_matrix.getRowIndexes()[i + 1]; ++j) {
                result[i] += left_csr_matrix.getValues()[j] * right_vector[left_csr_matrix.getColumnIndexes()[j]];
            }
        }
        return result;
}



#endif
