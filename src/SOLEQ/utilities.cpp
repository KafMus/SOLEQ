#ifndef UTILITIES_CPP_UUID_0000
#define UTILITIES_CPP_UUID_0000

#include <SOLEQ/utilities.hpp>
#include <SOLEQ/DEFINES.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>
#include <SOLEQ/operators.hpp>
#include <cmath>
#include <list>
#include <numbers>



kfsoleq::CSR_Matrix kfsoleq::getCSRMatrixFromMatrix(const kfsoleq::Matrix& given_matrix,
                                                    kfsoleq::soleq_float given_tolerance) {
        std::list<std::pair<size_t, kfsoleq::soleq_float>>  lil_tmp_row;
        std::list<std::list<std::pair<size_t, kfsoleq::soleq_float>>> result_lil;
        
        for (size_t i = 0; i < given_matrix.getSizeY(); ++i) {
            for (size_t j = 0; j < given_matrix.getSizeX(); ++j) {
                if (given_matrix(i, j) > given_tolerance || given_matrix(i, j) < -given_tolerance) {
                    lil_tmp_row.push_back(std::make_pair(j, given_matrix(i, j)));
                }
            }
            result_lil.push_back(lil_tmp_row);
            lil_tmp_row.clear();
        }
        kfsoleq::CSR_Matrix result(result_lil);
        return result;
}
kfsoleq::Matrix kfsoleq::getMatrixFromCSRMatrix(const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                size_t size_x) {
        size_t size_y = (given_csr_matrix.getRowIndexes().size() - 1);
        size_t begin_ind, end_ind, col_ind;
        kfsoleq::Matrix result(size_y, size_x);
        
        for (size_t row_ind = 0; row_ind < size_y; ++row_ind) {
            begin_ind = given_csr_matrix.getRowIndexes()[row_ind];
            end_ind   = given_csr_matrix.getRowIndexes()[row_ind + 1];
            for (size_t val_ind = begin_ind; val_ind < end_ind; ++val_ind) {
                col_ind = given_csr_matrix.getColumnIndexes()[val_ind];
                result(row_ind, col_ind) = given_csr_matrix.getValues()[val_ind];
            }
        }
        return result;
}
kfsoleq::soleq_float kfsoleq::getMaxEigenValuePowerMethod(const kfsoleq::Vector initial_vector,
                                                          const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                          size_t iters_num) {
        kfsoleq::Vector eigen_vector = given_csr_matrix * initial_vector;
        eigen_vector /= eigen_vector.getEuclidNorm();
        for (size_t i = 0; i < iters_num - 1; ++i) {
            eigen_vector = given_csr_matrix * eigen_vector;
            eigen_vector /= eigen_vector.getEuclidNorm();
        }
        return (eigen_vector * (given_csr_matrix * eigen_vector)) / (eigen_vector * eigen_vector);
}
kfsoleq::Vector kfsoleq::getChebyshevRoots(size_t degree) {
        kfsoleq::Vector roots(degree);
        kfsoleq::soleq_float init_sin = std::numbers::pi_v<soleq_float> / (kfsoleq::soleq_float)(2 * degree);
        kfsoleq::soleq_float sin_pi_n = std::numbers::pi_v<soleq_float> / (kfsoleq::soleq_float)degree;
        kfsoleq::soleq_float cos_pi_n;
        
        roots[0] = std::cos(init_sin);
        init_sin = std::sin(init_sin);
        cos_pi_n = std::cos(sin_pi_n);
        sin_pi_n = std::sin(sin_pi_n);
        
        for (size_t i = 1; i < degree / 2; ++i) {
            roots[i] = (roots[i - 1] * cos_pi_n) - (init_sin * sin_pi_n);
            init_sin = (init_sin * cos_pi_n) + (roots[i - 1] * sin_pi_n);
        }
        for (size_t i = degree / 2; i < degree; ++i) {
            roots[i] = -roots[degree - i - 1];
        }
        return roots;
}
kfsoleq::Vector kfsoleq::reorderChebyshevRoots(const kfsoleq::Vector& roots) {
        kfsoleq::Vector result(roots.getSize());
        for (size_t i = 0; i < roots.getSize() / 2; ++i) {
            result[2 * i] = roots[i];
            result[2 * i + 1] = roots[roots.getSize() - i - 1];
        }
        return result;
}
kfsoleq::Vector kfsoleq::getTauFromChebyshevRoots(const kfsoleq::Vector& roots,
                                                  kfsoleq::soleq_float min_value,
                                                  kfsoleq::soleq_float max_value) {
        kfsoleq::Vector result(roots.getSize());
        for (size_t i = 0; i < roots.getSize(); ++i) {
            result[i] = 2 / (min_value + max_value + (max_value - min_value) * roots[i]);
        }
        return result;
}
kfsoleq::soleq_float kfsoleq::getNewChebyshevAccelerationParameter(kfsoleq::soleq_float spectral_radius,
                                                                   kfsoleq::soleq_float prev_mu,
                                                                   kfsoleq::soleq_float curr_mu) {
        return (2.0 / spectral_radius) * curr_mu - prev_mu;
}
std::pair<kfsoleq::Matrix, kfsoleq::Matrix> kfsoleq::getQRFactorizationHouseholder(kfsoleq::Matrix given_matrix) {
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



#endif
