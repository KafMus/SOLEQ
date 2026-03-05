#ifndef VECTOR_HPP_UUID_0000
#define VECTOR_HPP_UUID_0000

#include <SOLEQ/DEFINES.hpp>
#include <vector>


namespace kfsoleq
{

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
        Vector& operator += (const Vector& right_vector);
        Vector& operator -= (const Vector& right_vector);
        SOLEQ_FLOAT operator * (const Vector& right_vector); // Scalar Multiplication
        Vector& operator *= (SOLEQ_FLOAT right_value);
};

Vector operator + (Vector left_vector, const Vector& right_vector);
Vector operator - (Vector left_vector, const Vector& right_vector);
Vector operator * (Vector left_vector, SOLEQ_FLOAT right_value);
Vector operator * (SOLEQ_FLOAT left_value, Vector right_vector);


}


#endif
