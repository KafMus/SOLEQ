#ifndef THREEDIAG_HPP_UUID_0000
#define THREEDIAG_HPP_UUID_0000

#include <iostream>
#include <array>
#include <vector>


namespace kfsoleq
{

#ifndef SOLEQ_FLOAT
#define SOLEQ_FLOAT double
#endif

class DiagThree {
private:
        unsigned int size;
        std::array<std::vector<SOLEQ_FLOAT>, 3> diagonals;
public:
	// Constructors and destructors
	DiagThree(); // Default constructor
	DiagThree(const DiagThree& root_diagThree); // Copy constructor
	DiagThree(DiagThree&& base_diagThree); // Move constructor
	~DiagThree(); // Destructor
        DiagThree(unsigned int size);
	
	// Getters and setters
        unsigned int getSize() const { return size; }
	std::array<std::vector<SOLEQ_FLOAT>, 3>& getDiagonalsRef() { return diagonals; } // Not Safe, should be removed
	
	// Additional infrastructure
	void print() const;
        void printDiagonals() const;
        
	
	// Operators overload
	DiagThree& operator = (const DiagThree& root_diagThree); // DiagThree assignment
	DiagThree& operator = (DiagThree&& base_diagThree); // Move assignment
};


}


#endif
