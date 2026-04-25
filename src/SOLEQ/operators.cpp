#ifndef OPERATORS_CPP_UUID_0000
#define OPERATORS_CPP_UUID_0000

#include <SOLEQ/operators.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>



kfsoleq::Vector kfsoleq::operator * (const kfsoleq::Matrix& left_matrix, const kfsoleq::Vector& right_vector) {
        kfsoleq::Vector result = kfsoleq::Vector(left_matrix.getSizeY());
        size_t size_y, size_x, jmp_ind;
        size_y = left_matrix.getSizeY();
        size_x = left_matrix.getSizeX();
        
        for (size_t i = 0; i < size_y; ++i) {
            jmp_ind = i * size_x;
            for (size_t j = 0; j < size_x; ++j) {
                result[i] += left_matrix.getValues()[jmp_ind + j] * right_vector[j];
            }
        }
        return result;
}
kfsoleq::Matrix kfsoleq::operator * (const kfsoleq::Vector& left_vector, const kfsoleq::Matrix& right_matrix) {
        kfsoleq::Matrix result = kfsoleq::Matrix(left_vector.getSize(), right_matrix.getSizeX());
        for (size_t i = 0; i < left_vector.getSize(); ++i) {
            for (size_t j = 0; j < right_matrix.getSizeX(); ++j) {
                result(i, j) = left_vector[i] * right_matrix(0, j);
            }
        }
        return result;
}
kfsoleq::Vector kfsoleq::operator * (const kfsoleq::CSR_Matrix& left_csr_matrix, const kfsoleq::Vector& right_vector) {
        if (0 == left_csr_matrix.getRowIndexes().size()) {
            return kfsoleq::Vector{};
        }
        kfsoleq::Vector result = kfsoleq::Vector(left_csr_matrix.getRowIndexes().size() - 1);
        size_t begin_ind, end_ind;
        
        for (size_t i = 0; i < left_csr_matrix.getRowIndexes().size() - 1; ++i) {
            begin_ind = left_csr_matrix.getRowIndexes()[i];
            end_ind   = left_csr_matrix.getRowIndexes()[i + 1];
            for (size_t j = begin_ind; j < end_ind; ++j) {
                result[i] += left_csr_matrix.getValues()[j] * right_vector[left_csr_matrix.getColumnIndexes()[j]];
            }
        }
        return result;
}
kfsoleq::Matrix kfsoleq::operator * (const kfsoleq::Vector& left_vector, const kfsoleq::CSR_Matrix& right_csr_matrix) {
        if (0 == right_csr_matrix.getRowIndexes().size()) {
            return kfsoleq::Matrix{};
        }
        kfsoleq::Matrix result = kfsoleq::Matrix(left_vector.getSize(), right_csr_matrix.getColumnIndexes().back() + 1);
        for (size_t i = 0; i < left_vector.getSize(); ++i) {
            for (size_t j = 0; j < right_csr_matrix.getColumnIndexes().size(); ++j) {
                result(i, right_csr_matrix.getColumnIndexes()[j]) = left_vector[i] * right_csr_matrix.getValues()[j];
            }
        }
        return result;
}
 


#endif
