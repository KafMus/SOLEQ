#ifndef SOLVERS_CPP_UUID_0000
#define SOLVERS_CPP_UUID_0000

#include <SOLEQ/solvers.hpp>
#include <SOLEQ/DEFINES.hpp>
#include <SOLEQ/matrix.hpp>
#include <SOLEQ/csr_matrix.hpp>
#include <SOLEQ/vector.hpp>
#include <SOLEQ/operators.hpp>
#include <SOLEQ/utilities.hpp>



kfsoleq::Vector kfsoleq::solverQRFactorization(const kfsoleq::Matrix& given_matrix) {
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
        
        auto [Q_Matrix, R_Matrix] = kfsoleq::getQRFactorizationHouseholder(system_matrix);
        
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
kfsoleq::Vector kfsoleq::solverQRFactorization(const kfsoleq::Matrix& given_matrix,
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
void kfsoleq::solverJacobiStep(kfsoleq::Vector& roots,
                               const kfsoleq::Vector& roots_prev,
                               const kfsoleq::CSR_Matrix& given_csr_matrix,
                               const kfsoleq::Vector& constant_terms,
                               size_t given_csr_matrix_size_y) {
        size_t begin_ind, end_ind, col_ind;
        kfsoleq::soleq_float mult_LUx;
        kfsoleq::soleq_float diagonal_element = 0;
        
        for (size_t row_ind = 0; row_ind < given_csr_matrix_size_y; ++row_ind) {
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
}
kfsoleq::Vector kfsoleq::solverJacobi(kfsoleq::soleq_float needed_precision,
                                      const kfsoleq::Vector& initial_roots,
                                      const kfsoleq::CSR_Matrix& given_csr_matrix,
                                      const kfsoleq::Vector& constant_terms,
                                      size_t iters_block_size,
                                      size_t max_iters,
                                      size_t* overall_iters_ptr) {
        const size_t size_y = given_csr_matrix.getRowIndexes().size() - 1;
        kfsoleq::Vector roots_prev = initial_roots;
        kfsoleq::Vector roots(size_y);
        
        size_t outer_ind = 0;
        while (outer_ind < max_iters && ((given_csr_matrix * roots) - constant_terms).getFirstNorm() > needed_precision) {
            for (size_t iter_num = 0; iter_num < iters_block_size; ++iter_num) {
                kfsoleq::solverJacobiStep(roots, roots_prev, given_csr_matrix, constant_terms, size_y);
                roots_prev = roots;
            }
            outer_ind += iters_block_size;
        }
        
        if (overall_iters_ptr) {
            (*overall_iters_ptr) = outer_ind;
        }
        return roots;
}
kfsoleq::Vector kfsoleq::solverFixedPointIterationStep(kfsoleq::Vector& roots,
                                                       const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                       const kfsoleq::Vector& constant_terms,
                                                       kfsoleq::soleq_float tau) {
        roots = roots - (given_csr_matrix * roots - constant_terms) * tau;
        return roots;
}
kfsoleq::Vector kfsoleq::solverFixedPointIteration(kfsoleq::soleq_float needed_precision,
                                                   const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                   const kfsoleq::Vector& constant_terms,
                                                   kfsoleq::soleq_float tau,
                                                   size_t iters_block_size,
                                                   size_t max_iters,
                                                   size_t* overall_iters_ptr) {
        kfsoleq::Vector roots(given_csr_matrix.getRowIndexes().size() - 1);
        
        size_t outer_ind = 0;
        while (outer_ind < max_iters && ((given_csr_matrix * roots) - constant_terms).getFirstNorm() > needed_precision) {
            for (size_t iter_num = 0; iter_num < iters_block_size; ++iter_num) {
                kfsoleq::solverFixedPointIterationStep(roots, given_csr_matrix, constant_terms, tau);
            }
            outer_ind += iters_block_size;
        }
        
        if (overall_iters_ptr) {
            (*overall_iters_ptr) = outer_ind;
        }
        return roots;
}
kfsoleq::Vector kfsoleq::solverGaussSeidelStep(kfsoleq::Vector& roots,
                                               const kfsoleq::CSR_Matrix& given_csr_matrix,
                                               const kfsoleq::Vector& constant_terms,
                                               size_t given_csr_matrix_size_y) {
        size_t begin_ind, end_ind, col_ind;
        kfsoleq::soleq_float mult_LUx;
        kfsoleq::soleq_float diagonal_element = 0;
        
        for (size_t row_ind = 0; row_ind < given_csr_matrix_size_y; ++row_ind) {
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
        return roots;
}
kfsoleq::Vector kfsoleq::solverGaussSeidel(kfsoleq::soleq_float needed_precision,
                                           const kfsoleq::Vector& initial_roots,
                                           const kfsoleq::CSR_Matrix& given_csr_matrix,
                                           const kfsoleq::Vector& constant_terms,
                                           size_t iters_block_size,
                                           size_t max_iters,
                                           size_t* overall_iters_ptr) {
        const size_t size_y = given_csr_matrix.getRowIndexes().size() - 1;
        kfsoleq::Vector roots = initial_roots;
        
        size_t outer_ind = 0;
        while (outer_ind < max_iters && ((given_csr_matrix * roots) - constant_terms).getFirstNorm() > needed_precision) {
            for (size_t iter_num = 0; iter_num < iters_block_size; ++iter_num) {
                kfsoleq::solverGaussSeidelStep(roots, given_csr_matrix, constant_terms, size_y);
            }
            outer_ind += iters_block_size;
        }
        
        if (overall_iters_ptr) {
            (*overall_iters_ptr) = outer_ind;
        }
        return roots;
}
kfsoleq::Vector kfsoleq::solverSuccessiveOverRelaxationStep(kfsoleq::Vector& roots,
                                                            const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                            const kfsoleq::Vector& constant_terms,
                                                            size_t given_csr_matrix_size_y,
                                                            kfsoleq::soleq_float relaxation_factor) {
        size_t begin_ind, end_ind, col_ind;
        kfsoleq::soleq_float mult_LUx;
        kfsoleq::soleq_float diagonal_element = 0;
        
        for (size_t row_ind = 0; row_ind < given_csr_matrix_size_y; ++row_ind) {
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
            
            roots[row_ind] = relaxation_factor * (constant_terms[row_ind] - mult_LUx) / diagonal_element +
                             (1 - relaxation_factor) * roots[row_ind];
        }
        return roots;
}
kfsoleq::Vector kfsoleq::solverSuccessiveOverRelaxation(kfsoleq::soleq_float needed_precision,
                                                        const kfsoleq::Vector& initial_roots,
                                                        const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                        const kfsoleq::Vector& constant_terms,
                                                        kfsoleq::soleq_float relaxation_factor,
                                                        size_t iters_block_size,
                                                        size_t max_iters,
                                                        size_t* overall_iters_ptr) {
        const size_t size_y = given_csr_matrix.getRowIndexes().size() - 1;
        kfsoleq::Vector roots = initial_roots;
        
        size_t outer_ind = 0;
        while (outer_ind < max_iters && ((given_csr_matrix * roots) - constant_terms).getFirstNorm() > needed_precision) {
            for (size_t iter_num = 0; iter_num < iters_block_size; ++iter_num) {
                kfsoleq::solverSuccessiveOverRelaxationStep(roots, given_csr_matrix, constant_terms, size_y, relaxation_factor);
            }
            outer_ind += iters_block_size;
        }
        
        if (overall_iters_ptr) {
            (*overall_iters_ptr) = outer_ind;
        }
        return roots;
}
kfsoleq::Vector kfsoleq::solverChebyshevFixedPointIteration(kfsoleq::soleq_float needed_precision,
                                                            const kfsoleq::Vector& initial_roots,
                                                            const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                            const kfsoleq::Vector& constant_terms,
                                                            const kfsoleq::Vector& tau,
                                                            size_t max_iters,
                                                            size_t* overall_iters_ptr) {
        kfsoleq::Vector roots_prev = initial_roots;
        kfsoleq::Vector roots(given_csr_matrix.getRowIndexes().size() - 1);
        
        size_t outer_ind = 0;
        while (outer_ind < max_iters && ((given_csr_matrix * roots) - constant_terms).getFirstNorm() > needed_precision) {
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
kfsoleq::Vector kfsoleq::solverChebyshevFixedPointIteration(kfsoleq::soleq_float needed_precision,
                                                            const kfsoleq::Vector& initial_roots,
                                                            const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                            const kfsoleq::Vector& constant_terms,
                                                            kfsoleq::soleq_float min_eigen_value,
                                                            kfsoleq::soleq_float max_eigen_value,
                                                            size_t iters_block_size,
                                                            size_t max_iters,
                                                            size_t* overall_iters_ptr) {
        kfsoleq::Vector roots_prev = initial_roots;
        kfsoleq::Vector roots(given_csr_matrix.getRowIndexes().size() - 1);
        kfsoleq::Vector tau = kfsoleq::getTauFromChebyshevRoots(
                              kfsoleq::reorderChebyshevRoots(
                              kfsoleq::getChebyshevRoots(iters_block_size)), min_eigen_value, max_eigen_value);
        
        size_t outer_ind = 0;
        while (outer_ind < max_iters && ((given_csr_matrix * roots) - constant_terms).getFirstNorm() > needed_precision) {
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
kfsoleq::Vector kfsoleq::solverSteepestGradientDescentStep(kfsoleq::Vector& roots,
                                                           const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                           const kfsoleq::Vector& constant_terms,
                                                           kfsoleq::Vector& residual,
                                                           kfsoleq::soleq_float& alpha) {
        roots -= residual * alpha;
        residual = given_csr_matrix * roots - constant_terms;
        alpha = ((residual * residual) / (residual * (given_csr_matrix * residual)));
        return roots;
}
kfsoleq::Vector kfsoleq::solverSteepestGradientDescent(kfsoleq::soleq_float needed_precision,
                                                       const kfsoleq::Vector& initial_roots,
                                                       const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                       const kfsoleq::Vector& constant_terms,
                                                       size_t iters_block_size,
                                                       size_t max_iters,
                                                       size_t* overall_iters_ptr) {
        kfsoleq::Vector roots = initial_roots;
        kfsoleq::Vector residual = ((given_csr_matrix * roots) - constant_terms);
        kfsoleq::soleq_float alpha = (residual * residual) / (residual * (given_csr_matrix * residual));
        
        size_t outer_ind = 0;
        while (outer_ind < max_iters && residual.getFirstNorm() > needed_precision) {
            for (size_t iter_num = 0; iter_num < iters_block_size; ++iter_num) {
                kfsoleq::solverSteepestGradientDescentStep(roots, given_csr_matrix, constant_terms, residual, alpha);
            }
            outer_ind += iters_block_size;
        }
        
        if (overall_iters_ptr) {
            (*overall_iters_ptr) = outer_ind;
        }
        return roots;
}
kfsoleq::Vector kfsoleq::solverConjugateGradientStep(kfsoleq::Vector& roots,
                                                     const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                     const kfsoleq::Vector& constant_terms,
                                                     kfsoleq::Vector& residual,
                                                     kfsoleq::Vector& delta,
                                                     kfsoleq::soleq_float& residual_square,
                                                     kfsoleq::soleq_float& alpha) {
        roots -= (alpha * delta);
        
        kfsoleq::soleq_float beta = residual_square;
        
        residual = ((given_csr_matrix * roots) - constant_terms);
        residual_square = residual * residual;
        
        beta = residual_square / beta;
        
        delta = residual + (beta * delta);
        alpha = residual_square / (delta * (given_csr_matrix * delta));
        
        return roots;
}
kfsoleq::Vector kfsoleq::solverConjugateGradient(kfsoleq::soleq_float needed_precision,
                                                 const kfsoleq::Vector& initial_roots,
                                                 const kfsoleq::CSR_Matrix& given_csr_matrix,
                                                 const kfsoleq::Vector& constant_terms,
                                                 size_t iters_block_size,
                                                 size_t max_iters,
                                                 size_t* overall_iters_ptr) {
        kfsoleq::Vector roots = initial_roots;
        kfsoleq::Vector residual = ((given_csr_matrix * roots) - constant_terms);
        kfsoleq::Vector delta = residual;
        kfsoleq::soleq_float residual_square = residual * residual;
        kfsoleq::soleq_float alpha = residual_square / (delta * (given_csr_matrix * delta));
        
        size_t outer_ind = 0;
        while (outer_ind < max_iters && ((given_csr_matrix * roots) - constant_terms).getFirstNorm() > needed_precision) {
            for (size_t iter_num = 0; iter_num < iters_block_size; ++iter_num) {
                kfsoleq::solverConjugateGradientStep(roots,
                                                     given_csr_matrix,
                                                     constant_terms,
                                                     residual,
                                                     delta,
                                                     residual_square,
                                                     alpha);
            }
            outer_ind += iters_block_size;
        }
        
        if (overall_iters_ptr) {
            (*overall_iters_ptr) = outer_ind;
        }
        return roots;
}



#endif
