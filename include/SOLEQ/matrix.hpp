#ifndef MATRIX_HPP_UUID_0000
#define MATRIX_HPP_UUID_0000

#include <SOLEQ/DEFINES.hpp>
#include <vector>


namespace kfsoleq
{

class Matrix {
private:
        size_t size_y, size_x;
        std::vector<soleq_float> values;
public:
        // Constructors and destructors
        Matrix(); // Default constructor
        Matrix(size_t given_size_y, size_t given_size_x);
        
        // Getters and setters
        size_t getSizeY() const { return size_y; }
        size_t getSizeX() const { return size_x; }
        const std::vector<soleq_float>& getValues() const { return values; }
        
        // Additional infrastructure
        void print() const;
        Matrix getTransposed() const;
        
        // Operators overload
        soleq_float  operator () (size_t y, size_t x) const {
            return this->values[(y * size_x) + x];
        }
        soleq_float& operator () (size_t y, size_t x) {
            return this->values[(y * size_x) + x];
        }
        Matrix& operator += (const Matrix& right_matrix);
        Matrix& operator -= (const Matrix& right_matrix);
        Matrix& operator *= (const Matrix& right_matrix);
};

Matrix operator + (Matrix left_matrix, const Matrix& right_matrix);
Matrix operator - (Matrix left_matrix, const Matrix& right_matrix);
Matrix operator * (const Matrix& left_matrix, const Matrix& right_matrix);


}


#endif
