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
std::pair<kfsoleq::Matrix, kfsoleq::Matrix> kfsoleq::getQRDecompositionHouseholder(kfsoleq::Matrix given_matrix) {
        kfsoleq::Vector x{};
        kfsoleq::Vector v{};
        kfsoleq::Vector e{};
        kfsoleq::Vector x_result(given_matrix.getSizeY());
        for (size_t iter_num = 0; iter_num < given_matrix.getSizeY() - 1; ++iter_num) {
            x = kfsoleq::Vector(given_matrix.getSizeY() - iter_num);
            e = kfsoleq::Vector(given_matrix.getSizeY() - iter_num);
            for (size_t i = 0; i < (given_matrix.getSizeY() - iter_num); ++i) {
                x[i] = given_matrix(iter_num + i, iter_num);
            }
            e[0] = 1;
            v = x + (x.getNorm() * e);
            
            for (size_t i = 0; i < (given_matrix.getSizeX() - iter_num); ++i) {
                for (size_t j = 0; j < (given_matrix.getSizeY() - iter_num); ++j) {
                    x[j] = given_matrix(j + iter_num, i + iter_num);
                }
                x_result = x - 2 * ( (v * x) / (v * v) ) * v;
                for (size_t j = 0; j < (given_matrix.getSizeY() - iter_num); ++j) {
                    given_matrix(j + iter_num, i + iter_num) = x_result[j];
                }
            }
        }
        /* return pair as <Q_Matrix, R_Matrix> */
        return std::make_pair(kfsoleq::Matrix(given_matrix.getSizeY(), given_matrix.getSizeX()),
                              given_matrix);
}



#endif
