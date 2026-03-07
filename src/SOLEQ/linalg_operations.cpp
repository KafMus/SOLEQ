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
        for (size_t i = 0; i < left_csr_matrix.getRowIndexes().size() - 1; ++i) {
            for (size_t j = left_csr_matrix.getRowIndexes()[i]; j < left_csr_matrix.getRowIndexes()[i + 1]; ++j) {
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
std::pair<kfsoleq::Matrix, kfsoleq::Matrix> kfsoleq::getQRDecompositionHouseholder(kfsoleq::Matrix given_matrix) {
        kfsoleq::Vector v;
        kfsoleq::Vector x_result;
        SOLEQ_FLOAT dot_product;
        
        kfsoleq::Matrix Q_Matrix(given_matrix.getSizeY(), given_matrix.getSizeX());
        for (size_t i = 0; i < given_matrix.getSizeY(); ++i) {
            Q_Matrix(i, i) = 1;
        }
        
        // Main part
        for (size_t iter_num = 0; iter_num < given_matrix.getSizeY() - 1; ++iter_num) {
            v = kfsoleq::Vector(given_matrix.getSizeY() - iter_num);
            
            for (size_t i = 0; i < (given_matrix.getSizeY() - iter_num); ++i) {
                v[i] = given_matrix(iter_num + i, iter_num);
            }
            v[0] += v.getNorm();
            
            // R_Matrix part
            for (size_t i = 0; i < (given_matrix.getSizeX() - iter_num); ++i) {
                dot_product = 0;
                for (size_t j = 0; j < (given_matrix.getSizeY() - iter_num); ++j) {
                    dot_product += given_matrix(j + iter_num, i + iter_num) * v[j];
                }
                x_result = (2 * dot_product / (v * v)) * v;
                for (size_t j = 0; j < (given_matrix.getSizeY() - iter_num); ++j) {
                    given_matrix(j + iter_num, i + iter_num) -= x_result[j];
                }
            }
            
            // Q_Matrix part
            for (size_t i = 0; i < (Q_Matrix.getSizeY()); ++i) {
                dot_product = 0;
                for (size_t j = 0; j < (Q_Matrix.getSizeX() - iter_num); ++j) {
                    dot_product += Q_Matrix(i, j + iter_num) * v[j];
                }
                x_result = (2 * dot_product / (v * v)) * v;
                for (size_t j = 0; j < (Q_Matrix.getSizeX() - iter_num); ++j) {
                    Q_Matrix(i, j + iter_num) -= x_result[j];
                }
            }
        }
        /* return as std::pair<Q_Matrix, R_Matrix> */
        return std::make_pair(Q_Matrix, given_matrix);
}



#endif
