#ifndef MATRIX_HPP_UUID_0000
#define MATRIX_HPP_UUID_0000

#include <SOLEQ/DEFINES.hpp>
#include <iostream>
#include <vector>


namespace kfsoleq
{

class Matrix {
private:
        size_t size_y, size_x;
        std::vector<SOLEQ_FLOAT> values;
public:
	// Constructors and destructors
        Matrix(); // Default constructor
        Matrix(size_t given_size_y, size_t given_size_x);
	
	// Getters and setters
        size_t getSizeY() const { return size_y; }
        size_t getSizeX() const { return size_x; }
        std::vector<SOLEQ_FLOAT> getValues() const { return values; }
        
	// Additional infrastructure
	void print() const;
        
        // Operators overload
        SOLEQ_FLOAT  operator () (size_t y, size_t x) const {
            return this->values[(y * size_x) + x];
        }
        SOLEQ_FLOAT& operator () (size_t y, size_t x) {
            return this->values[(y * size_x) + x];
        }
};


}


#endif
