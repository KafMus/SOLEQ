#ifndef LINALG_OPERATIONS_CPP_UUID_0000
#define LINALG_OPERATIONS_CPP_UUID_0000

#include <SOLEQ/linalg_operations.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>
#include <cmath>


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
std::pair<kfsoleq::Matrix, kfsoleq::Matrix> kfsoleq::getQRDecompositionHouseholder(kfsoleq::Matrix given_matrix) {
        kfsoleq::Vector v;
        kfsoleq::Vector x_result;
        kfsoleq::soleq_float dot_product;
        
        kfsoleq::Matrix Q_Matrix(given_matrix.getSizeY(), given_matrix.getSizeY());
        for (size_t i = 0; i < given_matrix.getSizeY(); ++i) {
            Q_Matrix(i, i) = 1;
        }
        
        // Main part
        for (size_t iter_num = 0; iter_num < given_matrix.getSizeX(); ++iter_num) {
            v = kfsoleq::Vector(given_matrix.getSizeY() - iter_num);
            
            for (size_t i = 0; i < given_matrix.getSizeY() - iter_num; ++i) {
                v[i] = given_matrix(iter_num + i, iter_num);
            }
            v[0] -= v.getEuclidNorm();
            v /= v.getEuclidNorm();
            
            // R_Matrix part
            for (size_t i = 0; i < given_matrix.getSizeX() - iter_num; ++i) {
                dot_product = 0;
                for (size_t j = 0; j < given_matrix.getSizeY() - iter_num; ++j) {
                    dot_product += given_matrix(j + iter_num, i + iter_num) * v[j];
                }
                x_result = (2 * dot_product / (v * v)) * v;
                for (size_t j = 0; j < given_matrix.getSizeY() - iter_num; ++j) {
                    given_matrix(j + iter_num, i + iter_num) -= x_result[j];
                }
            }
            
            // Q_Matrix part
            for (size_t i = 0; i < Q_Matrix.getSizeY(); ++i) {
                dot_product = 0;
                for (size_t j = 0; j < Q_Matrix.getSizeX() - iter_num; ++j) {
                    dot_product += Q_Matrix(i, j + iter_num) * v[j];
                }
                x_result = (2 * dot_product / (v * v)) * v;
                for (size_t j = 0; j < Q_Matrix.getSizeX() - iter_num; ++j) {
                    Q_Matrix(i, j + iter_num) -= x_result[j];
                }
            }
        }
        /* return as std::pair<Q_Matrix, R_Matrix> */
        return std::make_pair(Q_Matrix, given_matrix);
}
kfsoleq::Vector kfsoleq::solveUsingQRDecompostion(const kfsoleq::Matrix& given_matrix) {
        kfsoleq::Vector roots(given_matrix.getSizeY());
        kfsoleq::Matrix system_matrix(given_matrix.getSizeY(), given_matrix.getSizeX() - 1);
        kfsoleq::Vector constant_terms(given_matrix.getSizeY());
        
        for (size_t i = 0; i < given_matrix.getSizeY(); ++i) {
            for (size_t j = 0; j < given_matrix.getSizeX() - 1; ++j) {
                system_matrix(i, j) = given_matrix(i, j);
            }
        }
        for (size_t i = 0; i < given_matrix.getSizeY(); ++i) {
            constant_terms[i] = given_matrix(i, given_matrix.getSizeX() - 1);
        }
        
        std::pair<kfsoleq::Matrix, kfsoleq::Matrix> qr_decomposition = kfsoleq::getQRDecompositionHouseholder(system_matrix);
        kfsoleq::Matrix Q_Matrix = qr_decomposition.first;
        kfsoleq::Matrix R_Matrix = qr_decomposition.second;
        
        constant_terms = Q_Matrix.getTransposed() * constant_terms;
        
        for (long long int i = (long long int)R_Matrix.getSizeX() - 1; i >= 0; --i) {
            roots[(size_t)i] = constant_terms[(size_t)i];
            for (long long int j = (long long int)R_Matrix.getSizeX() - 1; j > i; --j) {
                roots[(size_t)i] -= R_Matrix((size_t)i, (size_t)j) * roots[(size_t)j];
            }
            roots[(size_t)i] /= R_Matrix((size_t)i, (size_t)i);
        }
        return roots;
}
kfsoleq::Vector kfsoleq::solveUsingJacobiMethod(const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                const kfsoleq::Vector& constant_terms,
                                                kfsoleq::soleq_float needed_precision,
                                                size_t iters_block_size,
                                                size_t max_iters) {
        const size_t size_y = given_csr_matrix.getRowIndexes().size() - 1;
        size_t begin_ind, end_ind, col_ind;
        kfsoleq::Vector roots_prev(size_y);
        kfsoleq::Vector roots(size_y);
        kfsoleq::soleq_float mult_LUx;
        kfsoleq::soleq_float diagonal_element = 0;
        
        size_t outer_ind = 0;
        while (((given_csr_matrix * roots) - constant_terms).getFirstNorm() > needed_precision && outer_ind < max_iters) {
            for (size_t iter_num = 0; iter_num < iters_block_size; ++iter_num) {
                for (size_t row_ind = 0; row_ind < size_y; ++row_ind) {
                    mult_LUx = 0;
                    begin_ind = given_csr_matrix.getRowIndexes()[row_ind];
                    end_ind   = given_csr_matrix.getRowIndexes()[row_ind + 1];
                    for (size_t val_ind = begin_ind; val_ind < end_ind; ++val_ind) {
                        col_ind = given_csr_matrix.getColumnIndexes()[val_ind];
                        if (row_ind == col_ind) {
                            diagonal_element = given_csr_matrix.getValues()[val_ind];
                            continue;
                        }
                        mult_LUx += given_csr_matrix.getValues()[val_ind] * roots_prev[col_ind];
                    }
                    
                    roots[row_ind] = (constant_terms[row_ind] - mult_LUx) / diagonal_element;
                }
                roots_prev = roots;
            }
            outer_ind += iters_block_size;
        }
        
        return roots;
}



#endif
