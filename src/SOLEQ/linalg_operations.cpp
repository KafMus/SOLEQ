#ifndef LINALG_OPERATIONS_CPP_UUID_0000
#define LINALG_OPERATIONS_CPP_UUID_0000

#include <SOLEQ/linalg_operations.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>
#include <cmath>
#include <numbers>


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
kfsoleq::Vector kfsoleq::solverQRDecomposition(const kfsoleq::Matrix& given_matrix) {
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
        
        auto [Q_Matrix, R_Matrix] = kfsoleq::getQRDecompositionHouseholder(system_matrix);
        
        constant_terms = Q_Matrix.getTransposed() * constant_terms;
        
        for (size_t i = R_Matrix.getSizeX(); i --> 0 ;) {
            roots[i] = constant_terms[i];
            for (size_t j = R_Matrix.getSizeX(); j --> i + 1 ;) {
                roots[i] -= R_Matrix(i, j) * roots[j];
            }
            roots[i] /= R_Matrix(i, i);
        }
        return roots;
}
kfsoleq::Vector kfsoleq::solverQRDecomposition(const kfsoleq::Matrix& given_matrix,
                                               const kfsoleq::Matrix& Q_Matrix,
                                               const kfsoleq::Matrix& R_Matrix) {
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
        
        constant_terms = Q_Matrix.getTransposed() * constant_terms;
        
        for (size_t i = R_Matrix.getSizeX(); i --> 0 ;) {
            roots[i] = constant_terms[i];
            for (size_t j = R_Matrix.getSizeX(); j --> i + 1 ;) {
                roots[i] -= R_Matrix(i, j) * roots[j];
            }
            roots[i] /= R_Matrix(i, i);
        }
        return roots;
}
kfsoleq::Vector kfsoleq::solverJacobi(const kfsoleq::Vector& initial_root,
                                      const kfsoleq::CSR_Matrix& given_csr_matrix,
                                      const kfsoleq::Vector& constant_terms,
                                      kfsoleq::soleq_float needed_precision,
                                      size_t iters_block_size,
                                      size_t max_iters,
                                      size_t* overall_iters_ptr) {
        const size_t size_y = given_csr_matrix.getRowIndexes().size() - 1;
        size_t begin_ind, end_ind, col_ind;
        kfsoleq::Vector roots_prev = initial_root;
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
        
        if (overall_iters_ptr) {
            (*overall_iters_ptr) = outer_ind;
        }
        return roots;
}
kfsoleq::Vector kfsoleq::solverFixedPointIteration(const kfsoleq::Vector& initial_root,
                                                   const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                   const kfsoleq::Vector& constant_terms,
                                                   kfsoleq::soleq_float tau,
                                                   kfsoleq::soleq_float needed_precision,
                                                   size_t iters_block_size,
                                                   size_t max_iters,
                                                   size_t* overall_iters_ptr) {
        kfsoleq::Vector roots_prev = initial_root;
        kfsoleq::Vector roots(given_csr_matrix.getRowIndexes().size() - 1);
        
        size_t outer_ind = 0;
        while (((given_csr_matrix * roots) - constant_terms).getFirstNorm() > needed_precision && outer_ind < max_iters) {
            for (size_t iter_num = 0; iter_num < iters_block_size; ++iter_num) {
                roots = roots_prev - (given_csr_matrix * roots_prev - constant_terms) * tau;
                roots_prev = roots;
            }
            outer_ind += iters_block_size;
        }
        
        if (overall_iters_ptr) {
            (*overall_iters_ptr) = outer_ind;
        }
        return roots;
}
kfsoleq::Vector kfsoleq::solverGaussSeidel(const kfsoleq::Vector& initial_root,
                                           const kfsoleq::CSR_Matrix& given_csr_matrix,
                                           const kfsoleq::Vector& constant_terms,
                                           kfsoleq::soleq_float needed_precision,
                                           size_t iters_block_size,
                                           size_t max_iters,
                                           size_t* overall_iters_ptr) {
        const size_t size_y = given_csr_matrix.getRowIndexes().size() - 1;
        size_t begin_ind, end_ind, col_ind;
        kfsoleq::Vector roots = initial_root;
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
                        mult_LUx += given_csr_matrix.getValues()[val_ind] * roots[col_ind];
                    }
                    
                    roots[row_ind] = (constant_terms[row_ind] - mult_LUx) / diagonal_element;
                }
            }
            outer_ind += iters_block_size;
        }
        
        if (overall_iters_ptr) {
            (*overall_iters_ptr) = outer_ind;
        }
        return roots;
}
kfsoleq::Vector kfsoleq::solverChebyshevFixedPointIteration(const kfsoleq::Vector& initial_root,
                                                            const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                            const kfsoleq::Vector& constant_terms,
                                                            const kfsoleq::Vector& tau,
                                                            kfsoleq::soleq_float needed_precision,
                                                            size_t max_iters,
                                                            size_t* overall_iters_ptr) {
        kfsoleq::Vector roots_prev = initial_root;
        kfsoleq::Vector roots(given_csr_matrix.getRowIndexes().size() - 1);
        
        size_t outer_ind = 0;
        while (((given_csr_matrix * roots) - constant_terms).getFirstNorm() > needed_precision && outer_ind < max_iters) {
            for (size_t iter_num = 0; iter_num < tau.getSize(); ++iter_num) {
                roots = roots_prev - (given_csr_matrix * roots_prev - constant_terms) * tau[iter_num];
                roots_prev = roots;
            }
            outer_ind += tau.getSize();
        }
        
        if (overall_iters_ptr) {
            (*overall_iters_ptr) = outer_ind;
        }
        return roots;
}
kfsoleq::Vector kfsoleq::solverChebyshevFixedPointIteration(const kfsoleq::Vector& initial_root,
                                                            const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                            const kfsoleq::Vector& constant_terms,
                                                            kfsoleq::soleq_float min_eigen_value,
                                                            kfsoleq::soleq_float max_eigen_value,
                                                            kfsoleq::soleq_float needed_precision,
                                                            size_t iters_block_size,
                                                            size_t max_iters,
                                                            size_t* overall_iters_ptr) {
        kfsoleq::Vector roots_prev = initial_root;
        kfsoleq::Vector roots(given_csr_matrix.getRowIndexes().size() - 1);
        kfsoleq::Vector tau = kfsoleq::getTauFromChebyshevRoots(
                              kfsoleq::reorderChebyshevRoots(
                              kfsoleq::getChebyshevRoots(iters_block_size)), min_eigen_value, max_eigen_value);
        
        size_t outer_ind = 0;
        while (((given_csr_matrix * roots) - constant_terms).getFirstNorm() > needed_precision && outer_ind < max_iters) {
            for (size_t iter_num = 0; iter_num < iters_block_size; ++iter_num) {
                roots = roots_prev - (given_csr_matrix * roots_prev - constant_terms) * tau[iter_num];
                roots_prev = roots;
            }
            outer_ind += iters_block_size;
        }
        
        if (overall_iters_ptr) {
            (*overall_iters_ptr) = outer_ind;
        }
        return roots;
}



#endif
