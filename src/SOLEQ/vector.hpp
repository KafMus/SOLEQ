#ifndef VECTOR_HPP_UUID_0000
#define VECTOR_HPP_UUID_0000

#include <iostream>
#include <vector>


namespace kfsoleq
{

#ifndef SOLEQ_FLOAT
#define SOLEQ_FLOAT double // Probably should be included with some "main_defines.hpp" or something file.
#endif

class Vector {
private:
        size_t size;
        std::vector<SOLEQ_FLOAT> values;
public:
	// Constructors and destructors
        Vector(); // Default constructor
        Vector(size_t given_size);
	
	// Getters and setters
        size_t getSize() const { return size; }
        std::vector<SOLEQ_FLOAT> getValues() const { return values; }
        
	// Additional infrastructure
	void print() const;
        
        // Operators overload
        SOLEQ_FLOAT  operator [] (size_t ind) const {
            return this->values[ind];
        }
        SOLEQ_FLOAT& operator [] (size_t ind) {
            return this->values[ind];
        }
};


}


#endif
