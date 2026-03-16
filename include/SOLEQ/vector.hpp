#ifndef VECTOR_HPP_UUID_0000
#define VECTOR_HPP_UUID_0000

#include <SOLEQ/DEFINES.hpp>
#include <vector>


namespace kfsoleq
{

class Vector {
private:
        size_t size;
        std::vector<soleq_float> values;
public:
	// Constructors and destructors
        Vector(); // Default constructor
        Vector(size_t given_size);
	
	// Getters and setters
        size_t getSize() const { return size; }
        const std::vector<soleq_float>& getValues() const { return values; }
        
	// Additional infrastructure
	void print() const;
        soleq_float getFirstNorm() const;
        soleq_float getEuclidNorm() const;
        
        // Operators overload
        soleq_float  operator [] (size_t ind) const {
            return this->values[ind];
        }
        soleq_float& operator [] (size_t ind) {
            return this->values[ind];
        }
        Vector& operator += (const Vector& right_vector);
        Vector& operator -= (const Vector& right_vector);
        soleq_float operator * (const Vector& right_vector); // Scalar Multiplication
        Vector& operator *= (soleq_float right_value);
        Vector& operator /= (soleq_float right_value);
};

Vector operator + (Vector left_vector, const Vector& right_vector);
Vector operator - (Vector left_vector, const Vector& right_vector);
Vector operator * (Vector left_vector, soleq_float right_value);
Vector operator * (soleq_float left_value, Vector right_vector);
Vector operator / (Vector left_vector, soleq_float right_value);


}


#endif
