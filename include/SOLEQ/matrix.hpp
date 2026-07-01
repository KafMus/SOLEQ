#ifndef MATRIX_HPP_UUID_0000
#define MATRIX_HPP_UUID_0000

#include <SOLEQ/DEFINES.hpp>
#include <array>
#include <iostream>
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
        void print(bool /*---*/) const;
        void addRows(size_t n);
        void addCols(size_t n);
        void cutRows(size_t n);
        void cutCols(size_t n);
        Matrix getTransposed() const;
        
        // Operators overload
        soleq_float  operator () (size_t y, size_t x) const {
            return this->values[(y * size_x) + x];
        }
        soleq_float& operator () (size_t y, size_t x) {
            return this->values[(y * size_x) + x];
        }
        
        /*
         * I don't think, that this is a good solution,
         * but I do think, that it is better, than making
         * the whole new structure, just to change the way
         * we iterate. Maybe there is some superior
         * another solution, but idk.
         */
        soleq_float  operator () (size_t x, size_t y, bool /*---*/) const {
            return this->values[(x * size_y) + y];
        }
        soleq_float& operator () (size_t x, size_t y, bool /*---*/) {
            return this->values[(x * size_y) + y];
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
