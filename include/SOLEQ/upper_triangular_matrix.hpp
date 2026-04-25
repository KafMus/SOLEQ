#ifndef UPPER_TRIANGULAR_MATRIX_HPP_UUID_0000
#define UPPER_TRIANGULAR_MATRIX_HPP_UUID_0000

#include <SOLEQ/DEFINES.hpp>
#include <vector>


namespace kfsoleq
{

class UpperTriangularMatrix {
private:
        size_t size_y, size_x;
        std::vector<soleq_float> values;
public:
        // Constructors and destructors
        UpperTriangularMatrix(); // Default constructor
        UpperTriangularMatrix(size_t given_size_y, size_t given_size_x);
        
        // Getters and setters
        size_t getSizeY() const { return size_y; }
        size_t getSizeX() const { return size_x; }
        const std::vector<soleq_float>& getValues() const { return values; }
        
        // Additional infrastructure
        void print() const;
        
        // Operators overload
        soleq_float  operator () (size_t y, size_t x) const {
            return this->values[(((2 * size_x - y + 1) * y) / 2) + x - y];
        }
        soleq_float& operator () (size_t y, size_t x) {
            return this->values[(((2 * size_x - y + 1) * y) / 2) + x - y];
        }
};


}


#endif
